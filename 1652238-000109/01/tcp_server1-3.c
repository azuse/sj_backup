#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/select.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	if (argc < 2)
	{
		printf("缺少参数\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("监听端口 %d\n", atoi(argv[1]));
	}
	int server_fd, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	int flags = fcntl(server_fd, F_GETFL, 0);
	fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(atoi(argv[1]));

	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
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
	fd_set rfds, wfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(server_fd, &rfds);
	FD_SET(server_fd, &wfds);
	/* set select() time out */
	tv.tv_sec = 10;
	tv.tv_usec = 0;

	int selres = select(server_fd + 1, &rfds, &wfds, NULL, NULL);
	printf("select return %d\n", selres);

	int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (new_socket == -1)
	{
		perror("acccpet failed");
		exit(-1);
	}

	switch (selres)
	{
	case -1:
		printf("select error\n");
		break;
	case 0:
		printf("select time out\n");
		break;
	default:
		printf("select return %d\n", selres);
		flags = fcntl(new_socket, F_GETFL, 0);
		fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);

		printf("start reading...\n");
		int read = recv(new_socket, buffer, sizeof(buffer), 0);
		printf("recv returned: %d\n", read);

		fd_set rfds2, wfds2;
		struct timeval tv2;
		FD_ZERO(&rfds2);
		FD_ZERO(&wfds2);
		FD_SET(new_socket, &rfds2);
		FD_SET(new_socket, &wfds2);
		/* set select() time out */
		tv2.tv_sec = 10;
		tv2.tv_usec = 0;
		selres = select(new_socket + 1, NULL, NULL, NULL, &tv2);

		printf("socket over\n");
	}
	return 0;
}