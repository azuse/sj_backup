// test5-1.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/prctl.h>

static void sig_child(int signo);

int main(int argc, char* argv[]){
	int pid;
	int i;
	if(argc == 1){
		printf("缺少参数 退出\n");
		exit(0);
	}
	int times = atoi(argv[1]);
	printf("循环生成%d个子进程\n",times);
	fflush(stdout);
	signal(SIGCHLD,sig_child);
	for(i=0;i<times;i++){
		pid = fork();
		if(pid == 0){
			prctl(PR_SET_PDEATHSIG, SIGHUP);
			break;
		}
		else if(pid == -1){
			printf("分裂失败 退出\n");
			fflush(stdout);
			return 0;
		}
		else{
			printf("已分裂 %d 个进程\n",i+1);
			fflush(stdout);
		}
	}
	int counter = 0;
	while(1){
		
		if(pid == 0){
			char str[1024*10];
			int j;
			for(j=0;j<1024;j++)
				str[j]='0';
			while(1)
				sleep(1);

			//printf("%d %d 1652238 sub\n",getpid(),getppid());
			//fflush(stdout);
			//sleep(15);
			//counter++;

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