#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

void static sigkill(int signal)
{
	printf("signal captured : %d\n", signal);
	printf("exiting... \n");
	exit(0);
}


int main(){
	signal(SIGCHLD, sigkill);

	printf("start\n");
	int pid = fork();
	if(pid == 0)
	{
		while(1)
			sleep(1);
	}
	else
		while(1)
			sleep(1);
	
	return 0;
}