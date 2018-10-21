// test3-2.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
	int pid;
	int i;
	for(i=0;i<10;i++){
		pid = fork();
		if(pid == 0){
			pid = fork();
			if(pid == 0)
				break;
			else{
				printf("son %d exiting\n",getpid());
				fflush(stdout);
				return 0;
			}
		}
		else sleep(3);
		waitpid(pid, NULL, 0);
		printf("son %d exited\n",pid);
		fflush(stdout);
	}
	int counter = 0;
	while(1){
		
		if(pid == 0){
			printf("grandson %d %d 1652238 sub working\n",getpid(),getppid());
			fflush(stdout);
			sleep(25);
			counter++;
			if(counter == 2){
				printf("grandson sub %d exited\n",getpid());
				fflush(stdout);
				break;
			}
		}else{
			printf("%d %d 1652238 main\n",getpid(),getppid());
			fflush(stdout);
			sleep(5);
			
		} 
	};
	return 0;
}