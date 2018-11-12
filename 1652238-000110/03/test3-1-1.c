#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

int main()
{
	FILE *fp = popen("ps -e | grep \'test3-1-2\' | awk \'{print $1}\'", "r"); //打开管道，执行shell 命令
	char buffer[10] = {0};
	while (NULL != fgets(buffer, 10, fp))
	{
		printf("test3-1-2 pid:  %s\n", buffer);
	}
	pclose(fp);

	int pid = atoi(buffer);
	printf("send signal SIGMIN\n");
	kill(pid, SIGRTMIN);
	sleep(1);
	printf("send signal SIGMIN+1\n");
	kill(pid, SIGRTMIN+1);

	return 0;
}