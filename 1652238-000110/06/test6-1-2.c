#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <string.h>
#include <signal.h>

struct sockaddr_un
{
	sa_family_t sun_family;
	char sun_path[108];
};

int main()
{
	struct sockaddr_un address;
	int sock = 0, valread;
	struct sockaddr_un serv_addr;

	char *hello = "This is test6-1-2, Come in, Over";
	char buffer[100] = {0};
	char buffer_send[15] = {0};

	if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sun_family = AF_UNIX;
	strcpy(serv_addr.sun_path, "temp");

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	else
	{
		printf("connect success\n");
	}

	send(sock, hello, strlen(hello), 0);
	printf("msg send: %s\n", hello);

	int flags = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flags | O_NONBLOCK);

	fd_set rfds, wfds;
	struct timeval tv;

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	// FD_SET(sock, &rfds);
	FD_SET(sock, &wfds);
	/* set select() time out */
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	int selres = select(sock + 1, NULL, &wfds, NULL, &tv);
	switch (selres)
	{
	case -1:
		perror("select error: ");
		break;
	case 0:
		printf("select time out\n");
		break;
	default:
		printf("select return %d\n", selres);
		int write = send(sock, hello, 100, 0);
		if (write == 0)
		{
			perror("Connect closed");
		}
		else if (write < 0)
		{
			printf("send return : %d\n", write);
			perror("");
		}
		else
		{
			printf("%d bytes send, msg is: \n", write);
			printf("%s\n", hello);
		}
	}

	printf("testing max sending queue ...\n");
	while(1)
	{
		sleep(1);
	}
	

	return 0;
}