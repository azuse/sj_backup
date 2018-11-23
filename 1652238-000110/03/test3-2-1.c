#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>
FILE *fd;
int pid = 1;

void static sigmin(int signal)
{
	printf("signal recived\n");

	fd = fopen("temp", "r");

	char buffer[256] = {0};
	fread(buffer, 256, 1, fd);
	printf("read from file: %s\n", buffer);

	ftruncate(fd, 0);
	lseek(fd, 0, SEEK_SET);
	fclose(fd);
	
	fd = fopen("temp", "w");

	strcpy(buffer, "this is 3-2-1, over");
	fwrite(buffer, 256, 1, fd);
	printf("write to file: %s\n", buffer);

	fclose(fd);
	printf("send signal SIGMIN to pid %d\n\n\n", pid);
	kill(pid, SIGRTMIN);
}

int main()
{
	while (1)
	{
		FILE *fp = popen("ps -e | grep \'test3-2-2\' | awk \'{print $1}\'", "r"); //打开管道，执行shell 命令
		char buffer[10] = {0};
		while (NULL != fgets(buffer, 10, fp))
		{
			printf("test3-2-2 pid:  %s\n", buffer);
		}
		pclose(fp);
		pid = atoi(buffer);
		if (pid != 0)
			break;
	}

	signal(SIGRTMIN, sigmin);

	fd = fopen("temp", "wr");
	char buffer[256];
	strcpy(buffer, "this is 3-2-1, over");
	fwrite(buffer, 256, 1, fd);
	printf("send signal SIGMIN to pid %d\n", pid);

	fclose(fd);

	kill(pid, SIGRTMIN);

	while (1)
		sleep(1);

	return 0;
}