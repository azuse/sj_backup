#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/file.h>
#include <wait.h>
#include <string.h>

int main()
{
	int fd;
	pid_t pid;
    printf("attemp to open the file...\n");

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open() error: ");
		exit(1);
	}
    printf("file opened, lock it now \n");
	// struct flock lock;
    // memset (&lock, 0, sizeof(lock));
	// lock.l_type = F_WRLCK;
    // if (fcntl (fd, F_SETLKW, &lock) < 0)
    // {
    //     perror("lock error: ");
    //     exit(1);
    // }
	// printf("file locked!\n");
	printf("jumped locking file\n");
	char buff[256];
	int readret = read(fd, buff, sizeof(buff));
	if (readret >= 0)
		printf("read %d from file: %s\n", readret, buff);
	else
		perror("read error: ");

	strcpy(buff, "write from 7-2-2\n");
	readret = write(fd, buff, strlen(buff) + 1);	
	if (readret >= 0)
		printf("write %d to file: %s\n", readret, buff);
	else
		perror("write error: ");

	close(fd);
	//unlink("temp");
	exit(0);
}