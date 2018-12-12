#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

///max connection num///
#define num 100
#define debug

int main(int argc, char const *argv[])
{
	int serverFd;
	struct sockaddr_in serverAddress;
	int addressLen = sizeof(serverAddress);

	if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket creation error:");
		exit(-1);
	}

	//////////////////////
	// ip   ->  0.0.0.0 //
	// this is no-block //
	//////////////////////

	int flags = fcntl(serverFd, F_GETFL, 0);
	fcntl(serverFd, F_SETFL, flags | O_NONBLOCK);

	int opt = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt error ");
		exit(-1);
	}

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(1000);

	if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		perror("bind error:");
		exit(-1);
	}
	else
	{
		perror("bind sucess");
	}

	if (listen(serverFd, 100))
	{
		perror("listen error:");
		exit(-1);
	}
	else
	{
		perror("listening ");
	}

	fd_set rfds, wfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(serverFd, &rfds);
	FD_SET(serverFd, &wfds);
	/* set select() time out */
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	int new_socket[num] = {0};
	int new_socket_state[num] = {0};
	// 0: S->C send "StuNo"
	// 1: C->S
	int maxConnectNum = 0;
	while (1)
	{
		int maxFd;
#ifdef debug
		printf("info : new_socket[maxConnectNum - 1] %d\n", new_socket[maxConnectNum - 1]);
		printf("info : serverFd %d\n", serverFd);
#endif

		if (new_socket[maxConnectNum - 1] > serverFd)
			maxFd = new_socket[maxConnectNum - 1];
		else
			maxFd = serverFd;

#ifdef debug
		printf("info : maxFd is %d\n", maxFd);
#endif

		tv.tv_sec = 2;
		
		
		FD_SET(serverFd, &rfds);
		int i;
		for(i=0; i<maxConnectNum;i++)
		{
			// ***client is anytime readable && writeable***
			//FD_SET(new_socket[i], &rfds);
			//FD_SET(new_socket[i], &wfds);
		}
		int selres = select(maxFd + 1, &rfds, &wfds, NULL, NULL);
		if (selres == 0)
		{
			printf("info : select return 0, timeout\n");
		}
		else if(selres == -1)
		{
			perror("select return -1 :");
		}
		else if (selres > 0 && FD_ISSET(serverFd, &rfds))
		{
			if (FD_ISSET(serverFd, &rfds))
			{
				printf("serverfd read is set\n");
			}
			else if (FD_ISSET(serverFd, &wfds))
			{
				printf("serverfd write is set\n");
			}

			new_socket[maxConnectNum] = accept(serverFd, (struct sockaddr *)&serverAddress, (socklen_t *)&addressLen);
			if (new_socket[maxConnectNum] == -1)
			{
				perror("acccpet failed");
				continue;
			}
			else
			{
				printf("client %d connected \n", maxConnectNum);
				flags = fcntl(new_socket[maxConnectNum], F_GETFL, 0);
				fcntl(new_socket[maxConnectNum], F_SETFL, flags | O_NONBLOCK);
				FD_SET(new_socket[maxConnectNum], &rfds);
				maxConnectNum++;

				char *p = "StuNo";
				size_t len = strlen(p);
				n = write(new_socket[maxConnectNum], p, len);

				print("info : %d written client no %d", n, maxConnectNum);



			}
		}
		else if (selres > 0)
		{
			//// read client
			int i;
			for (i = 0; i < maxConnectNum; i++)
			{
				if (FD_ISSET(new_socket[i], &rfds))
				{
					if (FD_ISSET(new_socket[i], &rfds))
					{
						printf("client %d read is set\n", i);
						FD_CLR(new_socket[i], &rfds);

						char readbuf[1024];
						int ret = recv(new_socket[i], readbuf, sizeof(readbuf), 0);
						if (ret > 0)
						{
							printf("info : read %d bytes\n", ret);
							printf("info : read message is : %s \n", readbuf);

							n = recv(new_socket[i], buf, MAXLINE, 0);
							if (n == sizeof(int))
							{
								memcpy(&stuno, buf, n);
								stuno = ntohl(stuno);
								// printf("StuNo = %d\n", stuno);
							}
							else
							{
								printf("StuNo read error, n = %d\n", n);
								close(new_socket[i]);
								exit(0);
							}

							

						}
						else
						{
							printf("info : read return %d \n", ret);
							perror("");
						}
					}
				}
			}
		}
	}
}