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

	if (mkfifo(fn, 0777) != 0)
	{
		perror("mkfifo() error");
		exit(-1);
	}

	if ((wfd = open(fn, O_WRONLY)) < 0)
		perror("open() error for write end");
	
	if (write(wfd, out, strlen(out) + 1) == -1)
		perror("write() error");
	else
		printf("test2-4-1 write %s to pipe\n", out);
	
	close(wfd);

	unlink(fn);
	int stat;
	wait(NULL);
}