#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/prctl.h>
#include <signal.h>
#include <sys/shm.h>
#include <string.h>
volatile long int sendbytes = 0;

void *daemon();

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

int main(int argc, char const *argv[])
{
	int readlength = atoi(argv[3]);
	int writelength = atoi(argv[4]);
	if (argc < 4)
	{
		printf("缺少参数\n");
		return -1;
	}
	else
	{
		printf("连接ip %s\n", argv[1]);
		printf("连接端口 %d\n", atoi(argv[2]));
		printf("一次读%d 一次写%d\n", readlength, writelength);
	}
	struct sockaddr_in address, my_addr;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;

	char *send_buffer = (char *)malloc(sizeof(char) * atoi(argv[4]));
	char *read_buffer = (char *)malloc(sizeof(char) * atoi(argv[3]));
	
	int i;
	for (i = 0; i < atoi(argv[4]); i++)
	{
		send_buffer[i] = 'A';
	}
	send_buffer[atoi(argv[4]) - 1] = '\0';
	for (i = 0; i < atoi(argv[3]); i++)
	{
		read_buffer[i] = 'A';
	}
	read_buffer[atoi(argv[3]) - 1] = '\0';

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	int port = 233;
	my_addr.sin_family = AF_INET;
	my_addr.sin_addr.s_addr = inet_addr("192.168.81.233");
	my_addr.sin_port = htons(port);

	if (bind(sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr_in)) == 0)
		printf("Binded Correctly\n");
	else
		printf("Unable to bind\n");

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	else
	{
		printf("连接成功\n");
	}
	//printf("Hello message sent\n");
	//strcpy(send_buffer, "ABCDEFGHIJKLMNOPQRS");
	//long int sendbytes = 0;
	//pthread_t p1;
	//pthread_create(&p1, NULL, daemon, NULL);
	long int shmid = shmget(IPC_PRIVATE, sizeof(long int), IPC_CREAT | 0600);
	long int shmid2 = shmget(IPC_PRIVATE, sizeof(long int), IPC_CREAT | 0600);
	//sendbytes_p = (int *)shmat(shmid, NULL, 0);

	signal(SIGCHLD, sig_child);

	int pid = fork();

	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		long int *sendbytes_p = (long int *)shmat(shmid, NULL, 0);
		long int *readbytes_p = (long int *)shmat(shmid2, NULL, 0);
		*sendbytes_p = 0;
		*readbytes_p = 0;
		while (1)
		{
			int tmp;
			tmp = read(sock, read_buffer, readlength);
			if (tmp > 0)
			{
				*readbytes_p += tmp;
				printf("read %d bytes, %d total\n", tmp, *readbytes_p);
			}
			else if (tmp == 0)
				printf("read fail, connection closed\n");
			else
				printf("read error\n");
			//getchar();
			tmp = write(sock, send_buffer, writelength);
			if (tmp > 0)
			{
				*sendbytes_p += tmp;
				printf("write %d bytes, %d total\n", tmp, *sendbytes_p);
			}
			else
				printf("write error\n");
			//getchar();
			//sleep(1);
		}
		printf("socket over\n");
	}
	else
	{
		long int *sendbytes_p = (long int *)shmat(shmid, NULL, 0);
		long int sendbytes_cached;
		while (1)
		{
			sendbytes_cached = *sendbytes_p;
			sleep(0.5);
			if (*sendbytes_p == sendbytes_cached)
			{
				//printf("socket send stocked, send bytes: %ld, cached\n", *sendbytes_p, sendbytes_cached);
			}
		}
	}

	return 0;
}

void *daemon()
{
	long int sendbytes_cached;
	while (1)
	{
		sendbytes_cached = sendbytes;
		if (sendbytes == sendbytes_cached)
		{
			printf("socket send stocked, send bytes: %ld\n", sendbytes);
		}
	}
}