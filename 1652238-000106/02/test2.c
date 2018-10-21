// test2.c
#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
	daemon(1,1);
	
	while(1){
		printf("1652238\n");
		fflush(stdout);
		sleep(5);
	};
	return 0;
}