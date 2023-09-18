
#include "vm/csapp.h"

#include <stdio.h>

int main() {

    int fd;

    fd = Open("hello.txt", O_RDWR, 0);

    struct stat st;
    fstat(fd, &st);

    size_t size;
    size = st.st_size;

    char *bufp;
    bufp = Mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);

    bufp[0] = 'J';

    Munmap(bufp, size);

    return 0;
}