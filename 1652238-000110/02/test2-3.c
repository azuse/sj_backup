#define _POSIX_SOURCE
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char fn[] = "temp.fifo";
    char out[20] = "FIFO's are fun!", in[20];
    int rfd, wfd;

    if (mkfifo(fn, S_IRWXU) != 0)
    {
        perror("mkfifo() error");
        exit(-1);
    }
    int pid = fork();
    if (pid == 0)
    {
        if ((wfd = open(fn, O_RDWR)) < 0)
            perror("open() error for write end");
        if (write(wfd, out, strlen(out) + 1) == -1)
            perror("write() error");
        else
            printf("child write %s to pipe\n", out);
        sleep(1);

        if (read(wfd, in, sizeof(in)) == -1)
            perror("read() error");
        else
            printf("child read '%s' from the FIFO\n", in);

        
        close(wfd);

        return 0;
    }
    else
    {
        if ((rfd = open(fn, O_RDWR)) < 0)
            perror("open() error for read end");
        if (read(rfd, in, sizeof(in)) == -1)
            perror("read() error");
        else
            printf("main read '%s' from the FIFO\n", in);

        if (write(rfd, out, strlen(out) + 1) == -1)
            perror("write() error");
        else
            printf("main write %s to pipe\n", out);

        
        close(rfd);
    }
    unlink(fn);
    int stat;
    wait(NULL);
}