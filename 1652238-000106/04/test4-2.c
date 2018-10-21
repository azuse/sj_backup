// test4-2.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/prctl.h>

static void sig_child(int signo);

int main(){
	int pid;
	int i;
	signal(SIGCHLD,sig_child);
	for(i=0;i<10;i++){
		pid = fork();
		if(pid == 0){
			prctl(PR_SET_PDEATHSIG, SIGHUP);
			break;
		}
		else sleep(3);
	}
	int counter = 0;
	while(1){
		
		if(pid == 0){
			printf("%d %d 1652238 sub\n",getpid(),getppid());
			fflush(stdout);
			sleep(15);
			counter++;
			// if(counter == 2){
			// 	printf("sub %d exiting\n",getpid());
			// 	fflush(stdout);
			// 	break;
			// }
		}else{
			printf("%d %d 1652238 main\n",getpid(),getppid());
			fflush(stdout);
			sleep(5);
			
		} 
	};
	return 0;
}

static void sig_child(int signo){
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0){
		printf("child %d exited with signal %d\n",pid,signo);
		fflush(stdout);
	}
}