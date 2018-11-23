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
    struct flock lock;
    memset (&lock, 0, sizeof(lock));
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    int fcntlret = fcntl(fd, F_SETLKW, &lock);
    if (fcntlret < 0)
    {
        perror("lock error: ");
        exit(1);
    }
    printf("file locked!  %d\n", fcntl);

    char buff[] = "hello from test7-2-1";
    write(fd, buff, sizeof(buff) + 1);
    printf("write to file: %s\n", buff);

    sleep(10);

    

    lock.l_type = F_UNLCK;
    if (fcntl (fd, F_SETLKW, &lock) < 0)
    {
        perror("flock() error: ");
        exit(1);
    }
    printf("file unlocked\n");

    while (1)
        sleep(1);

    //unlink("temp");
    exit(0);
}