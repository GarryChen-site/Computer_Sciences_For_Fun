
#include<stdio.h>
#include "csapp.h"

sem_t mutex, w;
int writecnt;

void *reader(void *vargp)
{
    while(1)
    {
        // write first
        if (writecnt > 0)
        {
            continue;
        }

        p(&w);

        V(&w);
    }
}

void *writer(void *vargp)
{
    while(1)
    {
        P(&mutex);
        writecnt++;
        V(&mutex);

        P(&w);

        V(&w);

        P(&mutex);
        // writer finished
        writecnt--;
        V(&mutex);
    }
}