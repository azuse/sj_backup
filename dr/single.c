#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MATRIX_LINE 2048
int matrix[MATRIX_LINE][MATRIX_LINE];
volatile int ans[MATRIX_LINE];


int main(int argc, char *argv[])
{
	//fill the matrix
	srand(time(NULL));
	int i, j;
	for (j = 0; j < MATRIX_LINE; j++)
	{

		for (i = 0; i < MATRIX_LINE; i++)
		{
			int r = rand();
			matrix[j][i] = r;
		}
	}

	struct timeval start;
	struct timezone tz;
	gettimeofday(&start, &tz);
	for (j = 0 ; j < MATRIX_LINE; j++)
		{
			int ans_tmp;
			for (i = 0; i < MATRIX_LINE; i++)
			{
				ans_tmp += matrix[j][i]*matrix[i][j];
			}
			ans[j] = ans_tmp;
		}
	struct timeval end;
	gettimeofday(&end, &tz);
	long int diff = end.tv_usec - start.tv_usec;
	printf("time used: %ld\n", diff);
	FILE *f;
	f = fopen("single.ans", "w");
	for (i = 0; i < MATRIX_LINE; i++)
	{
		fprintf(f, "%d\n", ans[i]);
	}
	fclose(f);
}