#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 
 * Simple program to experiment with looping
 */

int main()
{
    double angle;
    double sinVal;
    int numSteps = 20;
    double maxAngle = M_PI * 2;
    int i;

    for(i = 0;  i<=numSteps;  i++)
    {
        angle = (double)i / (double)numSteps * maxAngle;
        sinVal = sin(angle);
        printf("%3d: %5.2f %6.3f\n", i, angle, sinVal);
    }
}