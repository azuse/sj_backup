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

struct sockaddr_un
{
	sa_family_t sun_family;
	char sun_path[108];
};

int main()
{

	int server_fd, valread;
	struct sockaddr_un address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[100] = {0};
	char buffer_send[10] = {0};

	// Creating socket file descriptor
	if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	address.sun_family = AF_UNIX;
	strcpy(address.sun_path, "temp");

	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("bind success\n");
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("listening\n");
	}

	int new_socket = accept(server_fd, NULL, NULL);
	if (new_socket == -1)
	{
		perror("acccpet failed");
		exit(-1);
	}
	printf("start reading...\n");

	int read = recv(new_socket, buffer, 100, 0);
	if (read == 0)
	{
		perror("Connect closed");
	}
	else if (read < 0)
	{
		printf("recv return : %d\n", read);
		perror("");
	}
	else
	{
		printf("%d bytes read, msg is: \n", read);
		printf("%s\n", buffer);
	}

	printf("testing select ...\n");

	int flags = fcntl(new_socket, F_GETFL, 0);
	fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);
	fd_set rfds, wfds;
	struct timeval tv;

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(new_socket, &rfds);
	// FD_SET(sock, &wfds);
	/* set select() time out */
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	int selres = select(new_socket + 1, &rfds, NULL, NULL, &tv);
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
		int read = recv(new_socket, buffer, 100, 0);
		if (read == 0)
		{
			perror("Connect closed");
		}
		else if (read < 0)
		{
			printf("recv return : %d\n", read);
			perror("");
		}
		else
		{
			printf("%d bytes read, msg is: \n", read);
			printf("%s\n", buffer);
		}
	}

	// flags = fcntl(new_socket, F_GETFL, 0);
	// fcntl(new_socket, F_SETFL, flags & ~O_NONBLOCK);
	printf("testing max send bytes ...\n");
	int sum = 0;
	while(1)
	{
		int sndb = send(new_socket, buffer, 100, 0);
		sum += sndb;
		printf("%d bytes send, %d total\n", sndb, sum);
		getchar();
	}


	unlink(address.sun_path);
	printf("socket over\n");

	return 0;
}