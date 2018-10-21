// test3-1.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
	int pid;
	int i;
	for(i=0;i<10;i++){
		pid = fork();
		if(pid == 0)break;
		else sleep(3);
	}
	int counter = 0;
	while(1){
		
		if(pid == 0){
			printf("%d %d 1652238 sub\n",getpid(),getppid());
			fflush(stdout);
			sleep(25);
			counter++;
			if(counter == 2){
				printf("sub %d exiting\n",getpid());
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