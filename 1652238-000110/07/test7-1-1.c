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

    printf("file opened, lock it now \n");
    if (flock(fd, LOCK_EX) < 0) {
        perror("flock() error: ");
        exit(1);
    }	
    printf("file locked!\n");

    sleep(10);

    char buff[] = "hello from test7-1-1";
	write(fd, buff, sizeof(buff) + 1);
    printf("write to file: %s\n", buff);

    if (flock(fd, LOCK_UN) < 0) {
        perror("flock() error: ");
        exit(1);
    }
    printf("file unlocked\n");

	while(1)
        sleep(1);
    //unlink("temp");
    exit(0);
}