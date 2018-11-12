#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

void static sig_pause(int signal)
{
	printf("signal captured : %d\n", signal);
	printf("keep running... \n");
}

void static sig_stop(int signal)
{
	printf("signal captured : %d\n", signal);
	printf("stop\n");
	exit(0);
}

int main(){
	signal(SIGRTMIN, sig_pause);
	signal(SIGRTMIN+1, sig_stop);

	printf("start\n");
	while(1)
		sleep(1);
	
	return 0;
}