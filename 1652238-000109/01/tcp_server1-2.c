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
	int server_fd, new_socket, valread;
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
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t *)&addrlen)) < 0)
	{
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%u.%u.%u.%u connected\n", address.sin_addr.s_addr & 0x000000FF, (address.sin_addr.s_addr & 0x0000FF00) >> 8, (address.sin_addr.s_addr & 0x00FF0000) >> 16, (address.sin_addr.s_addr & 0xFF000000) >> 24);
	}
	int flags = fcntl(new_socket, F_GETFL, 0);
	fcntl(new_socket, F_SETFL, flags|O_NONBLOCK);


	fd_set rfds, wfds;
	struct timeval tv;
	FD_ZERO(&rfds);
	FD_SET(new_socket, &rfds);
	/* set select() time out */
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	int selres = select(new_socket + 1, &rfds, NULL, NULL, &tv);
	printf("select returns %d\n", selres);
	printf("start reading...\n");
	int read = recv(new_socket, buffer, sizeof(buffer), 0);
	printf("recv returned: %d\n", read);
	selres = select(new_socket + 1, NULL, NULL, NULL, &tv);
	printf("socket over\n");
	return 0;
}