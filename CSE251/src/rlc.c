#include <stdio.h>
#include <math.h>

int main() {

    double L, C; // Inductance in millihenrys and capacitance in microfarads 
    double w; // Resonant frequency in radians per second 
    double f; // Resonant frequency in Hertz 

    printf("Enter the inductance (in millihenrys): ");
    scanf("%lf", &L);

    printf("Enter the capacitance (in microfarads): ");
    scanf("%lf", &C);
    L = L/1000000;
    C = C/1000;
    w = 1 / sqrt(L * C); // Calculate resonant frequency in radians per second 

    f = w / (2 * M_PI); // Convert from radians to Hertz 

    printf("The resonant frequency is %.2f Hz\n", f);

    return 0;
}
