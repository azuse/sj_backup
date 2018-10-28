#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if (argc < 4)
	{
		printf("缺少参数\n");
		return -1;
	}
	else
	{
		printf("使用端口 %d\n", atoi(argv[1]));
		printf("连接ip %s\n", argv[2]);
		printf("连接端口 %d\n", atoi(argv[3]));
	}
	struct sockaddr_in address, my_addr;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;

	char sendbuffer[20];
	
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
		printf("连接成功\n");
	}
	//send(sock , hello , strlen(hello) , 0 );
	//printf("Hello message sent\n");
	//recv(sock, buffer, sizeof(buffer), 0);
	//valread = read( sock , buffer, 1024);
	strcpy(sendbuffer, "20byte length send");
	write(sock, sendbuffer, sizeof(sendbuffer));
	printf("message write: %s\n",sendbuffer);
	return 0;
}