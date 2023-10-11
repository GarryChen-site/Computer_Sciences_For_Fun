
#include <stdio.h>
#include "csapp.h"

sem_t mutex;
sem_t readercnt;

void *reader(void *vargp)
{
    while(1)
    {
        P(&readercnt);
        P(&mutex);

        // Critical section

        V(&mutex);
        V(&readercnt);
    }
}

void *writer(void *vargp)
{
    while(1)
    {
        P(&mutex);

        // Critical section

        V(&mutex);
    }
}