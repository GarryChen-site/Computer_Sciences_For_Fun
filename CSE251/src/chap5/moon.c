#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 
 * Simple lunar lander program.
 * By:  <insert name here>
 */
 
int main()
{
    printf("Lunar Lander - (c) 2012, by <insert name here>\n");
    
    double altitude = 100;  /* Meters */
    double velocity = 0;    /* Meters per second */
    double fuel = 100;      /* Kilograms */
    double power = 1.5;     /* Acceleration per pound of fuel */
    double g = -1.63;       /* Moon gravity in m/s^2 */
    double burn;            /* Amount of fuel to burn */
    bool valid;

while(altitude > 0)
{
    printf("Altitude: %.2f\n", altitude);
    printf("Velocity: %.2f\n", velocity);
    printf("You have %.2f kilograms of fuel\n", fuel);    

    do
    {
	valid = false;
    printf("How much fuel would you like to burn: ");
    scanf("%lf", &burn);

    if(burn < 0)
    {
        printf("You can't burn negative fuel\n");
    }
    else if(burn > 5)
    {
        printf("You can't burn more than 5 kilograms per second\n");
    }
    else if(burn > fuel)
    {
        printf("You can't burn fuel you don't have\n");
    }
    else
    {
        printf("Burning %.1f kilograms of fuel\n", burn);
    }
    } while(!valid);
    
    velocity = velocity + g + power * burn;
    altitude += velocity;
    fuel -= burn;
}

}