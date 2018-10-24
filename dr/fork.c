#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <malloc.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/shm.h>
#define MATRIX_LINE 3
int matrix[MATRIX_LINE][MATRIX_LINE];
volatile int ans[MATRIX_LINE];


static void sig_child(int signo);

int main(int argc, char *argv[])
{
	sem_t son, son1;
	sem_t *sh_son,*sh_son1;
	int sh_son_id,sh_son1_id;
	sh_son_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
	sh_son1_id = shmget(IPC_PRIVATE, sizeof(sem_t), IPC_CREAT | 0600);
	//–≈∫≈¡ø semget()°¢semop()°¢semctl()
	int shmid;
	int *shmaddr;
	signal(SIGCHLD, sig_child);
	shmid = shmget(IPC_PRIVATE, sizeof(int) * MATRIX_LINE * MATRIX_LINE, IPC_CREAT | 0600);
	sem_destroy(&son);
	sem_init(&son, 0, 0);
	sem_init(&son1, 0, 0);
	//fill the matrix
	srand(time(NULL));
	int i, j, k;
	for (j = 0; j < MATRIX_LINE; j++)
	{
		for (i = 0; i < MATRIX_LINE; i++)
		{
			int r = rand();
			matrix[j][i] = 1;
		}
	}

	struct timeval start;
	struct timezone tz;
	gettimeofday(&start, &tz);
	int pid = fork();
	if (pid == 0)
	{
		shmaddr = (int *)shmat(shmid, NULL, 0);
		sh_son = (sem_t*)shmat(sh_son_id, NULL, 0);
		prctl(PR_SET_PDEATHSIG, SIGHUP);

		for (j = MATRIX_LINE / 2; j < MATRIX_LINE; j++)
		{
			for (k = 0; k < MATRIX_LINE; k++)
			{
				int ans_tmp = 0;
				for (i = 0; i < MATRIX_LINE; i++)
				{
					ans_tmp += matrix[j][i] * matrix[i][k];
				}
				*(shmaddr + j*MATRIX_LINE + k) = ans_tmp;
			}
		}
		sem_post(sh_son);
		printf("son posted\n");
		return 0;
	}
	else if (pid > 0)
	{
		pid = fork();
		if (pid == 0)
		{
			shmaddr = (int *)shmat(shmid, NULL, 0);
			sh_son1 = (sem_t*)shmat(sh_son1_id, NULL, 0);

			prctl(PR_SET_PDEATHSIG, SIGHUP);
			for (j = 0; j < MATRIX_LINE / 2; j++)
			{
				for (k = 0; k < MATRIX_LINE; k++)
				{
					int ans_tmp = 0;
					for (i = 0; i < MATRIX_LINE; i++)
					{
						ans_tmp += matrix[j][i] * matrix[i][k];
					}
					*(shmaddr + j*MATRIX_LINE + k) = ans_tmp;
				}
			}
			printf("son1 posted\n");
			sem_post(sh_son1);
			return 0;
		}
		else
		{
			sleep(1);
			int i;
			sh_son = (sem_t  *)shmat(sh_son_id, NULL, 0);
			sh_son1 = (sem_t  *)shmat(sh_son1_id, NULL, 0);
			
			sem_getvalue(sh_son,&i);
			printf("main waitng son %d\n",i);
			sem_wait(sh_son);
			sem_getvalue(sh_son1,&i);
			printf("main waitng son1 %d\n",i);
			sem_wait(sh_son1);
			printf("main go\n");
			struct timeval end;
			gettimeofday(&end, &tz);
			long int diff = end.tv_usec - start.tv_usec;
			printf("time used: %ld\n", diff);
		}
	}
	else
	{
		printf("fork fail\n");
	}
	shmaddr = (int *)shmat(shmid, NULL, 0);
	FILE *f;
	f = fopen("fork.ans", "w");
	for (i = 0; i < MATRIX_LINE; i++)
	{
		for (k = 0; k < MATRIX_LINE; k++)
		{
			fprintf(f, "%d\n", *(shmaddr + i*MATRIX_LINE + k));
		}
	}
	fclose(f);
	return 0;
}

static void sig_child(int signo)
{
	pid_t pid;
	int stat;
	while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		//printf("child %d exited with signal %d\n", pid, signo);
		fflush(stdout);
	}
}