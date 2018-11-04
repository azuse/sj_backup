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
	if (argc < 4)
	{
		printf("È±ÉÙ²ÎÊý\n");
		return -1;
	}
	else
	{
		printf("local port=%d\n", atoi(argv[1]));
		printf("connect ip=%s\n", argv[2]);
		printf("remote port=%d\n", atoi(argv[3]));
	}
	struct sockaddr_in address, my_addr;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;

	char send_buffer[1000] = {52};
	send_buffer[999] = '\0';
	char buffer[1024] = {0};
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[3]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[2]);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, argv[2], &serv_addr.sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	int opt = 2000;
	if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	else
	{
		int rc;
		int optval;
		int optlen;
		struct linger l;
		optlen = sizeof(int);
		rc = getsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char *)&optval, &optlen);
		if (rc == 0)
		{
			if (optlen == sizeof(int))
			{
				printf("SNDBUF SET: %d\n", optval);
			}
		}
	}

	int port = atoi(argv[1]);
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
		printf("CONNCTED\n");
	}
	//printf("Hello message sent\n");
	//strcpy(send_buffer, "ABCDEFGHIJKLMNOPQRS");
	//long int sendbytes = 0;
	//pthread_t p1;
	//pthread_create(&p1, NULL, daemon, NULL);
	long int shmid = shmget(IPC_PRIVATE, sizeof(long int), IPC_CREAT | 0600);
	//sendbytes_p = (int *)shmat(shmid, NULL, 0);

	signal(SIGCHLD, sig_child);

	int pid = fork();

	if (pid == 0)
	{
		prctl(PR_SET_PDEATHSIG, SIGHUP);
		long int *sendbytes_p = (long int *)shmat(shmid, NULL, 0);
		while (1)
		{
			write(sock, send_buffer, sizeof(send_buffer));
			*sendbytes_p += 1;
			printf("write %d bytes, %ld total\n", sizeof(send_buffer), *sendbytes_p * sizeof(send_buffer));
			getchar();
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