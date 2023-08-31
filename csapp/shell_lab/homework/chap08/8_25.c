
#include <stdio.h>
#include "csapp.h"

sigjmp_buf buf;

void handler(int sig) {
    siglongjmp(buf, 1);
}

char* tfgets(char* s, int size, FILE* stream) {
    if (sigsetjmp(buf, 1) == 0) {
        alarm(5);
        if (Signal(SIGALRM, handler) == SIG_ERR)
            unix_error("signal error");
        char* result = fgets(s, size, stream);
        alarm(0); // cancel the alarm if fgets returns before the alarm goes off
        return result;
    }
    else {
        return NULL;
    }
}