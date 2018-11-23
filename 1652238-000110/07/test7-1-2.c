#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <wait.h>

int main()
{
    int fd;

    printf("attemp to open the file...\n");
    fd = open("temp", O_RDWR|O_CREAT|O_TRUNC, 0644);
    if (fd < 0) {
        perror("open() error: ");
        exit(1);
    }

    printf("file opened, read lock it now \n");
    if (flock(fd, LOCK_SH) < 0) {
        perror("flock() error: ");
        exit(1);
    }
	printf("file locked!\n");

    char buff[256];
	int readret = read(fd, buff, sizeof(buff));
    if(readret >= 0)
    {
        printf("read %d from file: %s\n", readret, buff);
        perror("");
    }
    else
        perror("read error: ");

    unlink("temp");
    exit(0);
}