#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "GarageLib.h"

/* Our possible garage door states */
#define DoorClosed 1
#define DoorOpening 2
#define DoorOpen 3
#define DoorClosing 4


int main()
{
    printf("Garage Startup\n");
    GarageStartup();
    SetDoorSpeed(1);

    int state = DoorClosed;

    while(IsGarageRunning())
    {
        switch(state)
        {
        case DoorClosed:
            StateDoorClosed(&state);
            break;

        case DoorOpening:
            StateDoorOpening(&state);
            break;

        case DoorOpen:
            StateDoorOpen(&state);
            break;

        case DoorClosing:
            StateDoorClosing(&state);
            break;
        }
        // Check if the beam is broken
        if(IsBeamBroken())
        {
            if(state == DoorClosing)
            {
                // If the door is closing and the beam is broken, reverse the motor to open the door instead
                SetMotorPower(1);
                state = DoorOpening;
            }
            else if(state == DoorOpen)
            {
                // If the door is open, the beam is broken, and the button is pressed, ignore the button
                if(WasButtonPressed())
                {
                    // do nothing
                }
            }
        }

    }

    printf("Garage Shutdown\n");
    GarageShutdown();
    return 0;
}

void StateDoorClosed(int *state)
{
    if(WasButtonPressed())
    {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}

void StateDoorOpening(int *state)
{
    if(GetDoorPosition() >= (DoorHeight - DoorTolerance))
    {
        SetMotorPower(0);
        *state = DoorOpen;
    }
    else if(WasButtonPressed())
    {
        SetMotorPower(-1);
        *state = DoorClosing;
    }  
}

void StateDoorOpen(int *state)
{
    static int timer_started = 0;
    if(WasButtonPressed())
    {
        SetMotorPower(-1);
        *state = DoorClosing;
        timer_started = 0; // reset timer if the button was pressed
    }
    else if(IsBeamBroken())
    {
        // ignore beam break if timer has not started
        if(timer_started == 0)
        {
            return;
        }
        // close the door if timer has expired and beam is not broken
        if(GetTimer() > 10)
        {
            SetMotorPower(-1);
            *state = DoorClosing;
            timer_started = 0; // reset timer
        }
    }
    else
    {
        // start timer if beam is not broken and timer has not started
        if(timer_started == 0)
        {
            ResetTimer();
            timer_started = 1;
        }
    }
}

void StateDoorClosing(int *state)
{
    if(GetDoorPosition() < DoorTolerance)
    {
        SetMotorPower(0);
        *state = DoorClosed;
    }
    else if(WasButtonPressed())
    {
        SetMotorPower(1);
        *state = DoorOpening;
    }
}