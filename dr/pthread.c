#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define MATRIX_LINE 3
int matrix[MATRIX_LINE][MATRIX_LINE];
volatile int ans[MATRIX_LINE][MATRIX_LINE];

void *worker(void *arg)
{
	int i, j, k;
	if (*(int *)arg == 1)
	{
		for (j = 0; j < MATRIX_LINE / 2; j++)
		{
			for (k = 0; k < MATRIX_LINE; k++)
			{
				int ans_tmp = 0;
				for (i = 0; i < MATRIX_LINE; i++)
				{
					ans_tmp += matrix[j][i] * matrix[i][k];
				}
				ans[j][k] = ans_tmp;
				
			}
		}
		
	}
	else if (*(int *)arg == 2)
	{
		for (j = MATRIX_LINE / 2; j < MATRIX_LINE; j++)
		{
			for (k = 0; k < MATRIX_LINE; k++)
			{
				int ans_tmp = 0;
				for (i = 0; i < MATRIX_LINE; i++)
				{
					ans_tmp += matrix[j][i] * matrix[i][k];
				}
				ans[j][k] = ans_tmp;
			}
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	//fill the matrix
	srand(time(NULL));
	int i, j, k;
	for (j = 0; j < MATRIX_LINE; j++)
	{

		for (i = 0; i < MATRIX_LINE; i++)
		{
			int r = rand();
			matrix[j][i] = r;
		}
	}

	pthread_t p1, p2;

	struct timeval start;
	struct timezone tz;
	gettimeofday(&start, &tz);
	int arg1 = 1;
	int arg2 = 2;
	pthread_create(&p1, NULL, worker, (void *)&arg1);
	pthread_create(&p2, NULL, worker, (void *)&arg2);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
	struct timeval end;
	gettimeofday(&end, &tz);
	long int diff = end.tv_usec - start.tv_usec;
	printf("time used: %ld\n", diff);
	FILE *f;
	f = fopen("pthread.ans", "w");
	for (k = 0; k < MATRIX_LINE; k++)
	{
		for (i = 0; i < MATRIX_LINE; i++)
		{
			fprintf(f, "%d\n", ans[i][k]);
		}
	}
	fclose(f);
}