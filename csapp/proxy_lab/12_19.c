
#include <stdio.h>
#include "csapp.h"

/* Global variables */
int readcnt; /* Initially = 0 */
int reader_first;
sem_t mutex, w; /* Both initially = 1 */
void reader(void)
{
    while (1)
    {
        P(&mutex);
        readcnt++;
        if (readcnt == 1) /* First in */
            P(&w);
        V(&mutex);
        /* Critical section */
        reader_first = 0;
        /* Reading happens  */
        P(&mutex);
        readcnt--;
        if (readcnt == 0) /* Last out */
            V(&w);
        V(&mutex);
    }
}
void writer(void)
{
    while (1)
    {
        if (reader_first == 1)
        {
            continue;
        }
        P(&w);
        /* Critical section */
        /* Writing happens  */

        // if a reader is waiting, reader_first next round will be 1
        if (readcnt == 1)
        {
            reader_first = 1;
        }
        V(&w);
    }
}