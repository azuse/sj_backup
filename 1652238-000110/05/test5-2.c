#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <semaphore.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <malloc.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/shm.h>

int main()
{
	char mem[1024];
	int shmem_id;
	char *shmaddr;
	shmem_id = shmget(51, sizeof(mem), IPC_CREAT | 0600);
	shmaddr = (char *)shmat(shmem_id, NULL, 0);
	printf("recived from shared memory: %s\n", shmaddr);

	return 0;
}