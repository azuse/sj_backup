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

	// if (mkfifo(fn, S_IRWXU) != 0)
	// {
	// 	perror("mkfifo() error");
	// 	exit(-1);
	// }
	
	if ((rfd = open(fn, O_RDONLY)) < 0)
		perror("open() error for read end");
	if (read(rfd, in, sizeof(in)) == -1)
		perror("read() error");
	else
		printf("test2-4-2 read '%s' from the FIFO\n", in);


	close(rfd);
	// unlink(fn);
	int stat;
	wait(NULL);
}