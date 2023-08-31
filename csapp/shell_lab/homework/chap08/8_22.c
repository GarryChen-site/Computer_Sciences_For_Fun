
#include <stdio.h>
#include "csapp.h"

int mysystem(char *command) {
    pid_t pid;
    int status;

    if((pid = Fork()) == 0) {
        // child process
        char *argv[4] = {"","-c", command, NULL};
        execve("/bin/sh", argv, environ);
    }

    // print child pid so we can kill it
    printf("child pid: %d\n", pid);

    if(Waitpid(pid, &status, 0) > 0){
        // exit normally
        if(WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }

        // exit by signal
        if(WIFSIGNALED(status)) {
            return WTERMSIG(status);
        }
    }
}