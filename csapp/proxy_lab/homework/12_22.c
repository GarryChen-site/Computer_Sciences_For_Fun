
/* $begin select */
#include "csapp.h"
void echo(int connfd);
void command(void);
int echo_line(int connfd);

int main(int argc, char **argv)
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]); // line:conc:select:openlistenfd

    FD_ZERO(&read_set); /* Clear read set */                     // line:conc:select:clearreadset
    FD_SET(STDIN_FILENO, &read_set); /* Add stdin to read set */ // line:conc:select:addstdin
    FD_SET(listenfd, &read_set); /* Add listenfd to read set */  // line:conc:select:addlistenfd

    // max n for select
    int n = listenfd + 1;

    while (1)
    {
        ready_set = read_set;
        Select(listenfd + 1, &ready_set, NULL, NULL, NULL); // line:conc:select:select
        if (FD_ISSET(STDIN_FILENO, &ready_set))             // line:conc:select:stdinready
            command();                                      /* Read command line from stdin */
        if (FD_ISSET(listenfd, &ready_set))
        { // line:conc:select:listenfdready
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);

            if (connfd + 1 > FD_SETSIZE)
            {
                fprintf(stderr, "too many clients\n");
                Close(connfd);
            }

            n = n > connfd + 1 ? n : connfd + 1;
            FD_SET(connfd, &read_set); /* Add connfd to read set */ // line:conc:select:addconnfd
        }

        // echo one line every time
        for (int i = listenfd + 1; i < n; i++)
        {
            if (FD_ISSET(i, &ready_set))
            {
                if (echo_line(i) < 0)
                {
                    FD_CLR(i, &read_set);
                    Close(i);
                }
            }
        }
    }
}

void command(void)
{
    char buf[MAXLINE];
    if (!Fgets(buf, MAXLINE, stdin))
        exit(0);       /* EOF */
    printf("%s", buf); /* Process the input command */
}
/* $end select */

int echo_line(int connfd)
{
    ssize_t n;
    char buf[1];

    while ((n = Rio_readn(connfd, buf, 1)) > 0)
    {
        Rio_writen(connfd, buf, n);
        if (buf[0] == '\n')
        {
            return 0;
        }
    }
    return -1;
}
