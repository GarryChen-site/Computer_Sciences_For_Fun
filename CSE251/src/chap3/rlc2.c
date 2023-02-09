#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {

    double L, C; // Inductance in millihenrys and capacitance in microfarads 
    double w; // Resonant frequency in radians per second 
    double f; // Resonant frequency in Hertz 
    bool valid = true; 

    printf("Enter the inductance (in millihenrys): ");
    scanf("%lf", &L);
        /* Test to see if the user entered an invalid value */    
    if(L < 0) {
        printf("You moron, you entered a negative inductance!\n");
        // L = 1;
        // exit(1); // If you call exit(0), that means you have exited successfully. If you call exit(1) that means your program exited with an error.
        valid = false;
    }
    else if(L == 0) {
        printf("You are really dumb, you entered zero.\n");
        // exit(0);
        valid = false;
    }
    else {
        printf("Okay, I guess that's reasonable\n");
    }

    printf("Enter the capacitance (in microfarads): ");
    scanf("%lf", &C);
    if (valid) {
        L = L/1000000;
        C = C/1000;
        w = 1 / sqrt(L * C); // Calculate resonant frequency in radians per second 
        f = w / (2 * M_PI); // Convert from radians to Hertz     
        printf("The resonant frequency is %.2f Hz\n", f);
    }

    return 0;
}
