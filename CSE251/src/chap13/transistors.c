#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "transistors.h"

/*
 * Name :  < insert name here >
 * Description : Simple transistor description example program
*/




int main()
{
    // struct Transistor t1;
    // Tran trans[3];
    // int i;

    // printf("transistors!\n");
    
    // for(i=0;  i<3;  i++)
    // {
    //     trans[i] = InputTransistor();
    // }
    
    // printf("\nThe transistors:\n");
    // DisplayTransistor(trans[0]);

    int i;
    Tran *trans;
    int numTrans = 0;

    printf("transistors!\n");

    /* Allocate space for one transistor*/
    trans = malloc(sizeof(Tran));
    numTrans = 1;

    /* Input the transistor*/
    trans[0] = InputTransistor();

    /* Output the transistors */
    printf("\nThe transistors:\n");
    for(i=0;  i<numTrans;  i++)
    {
        DisplayTransistor(trans[i]);
    }
    
    /* Free the memory */
    free(trans);  
}