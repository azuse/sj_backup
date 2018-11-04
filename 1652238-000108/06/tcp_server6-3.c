#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/if_link.h>

void listInterfaces(int *interface_num, char interface_address[100][NI_MAXHOST])
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s, n;
	char host[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1)
	{
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	/* Walk through linked list, maintaining head pointer so we
              can free list later */

	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++)
	{
		if (ifa->ifa_addr == NULL)
			continue;

		family = ifa->ifa_addr->sa_family;

		/* Display interface name and family (including symbolic
                  form of the latter for the common families) */

		// printf("%-8s %s (%d)\n",
		// 	   ifa->ifa_name,
		// 	   (family == AF_PACKET) ? "AF_PACKET" : (family == AF_INET) ? "AF_INET" : (family == AF_INET6) ? "AF_INET6" : "???",
		// 	   family);

		/* For an AF_INET* interface address, display the address */

		if (family == AF_INET || family == AF_INET6)
		{
			s = getnameinfo(ifa->ifa_addr,
							(family == AF_INET) ? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
							host, NI_MAXHOST,
							NULL, 0, NI_NUMERICHOST);
			if (s != 0)
			{
				//printf("getnameinfo() failed: %s\n", gai_strerror(s));
				exit(EXIT_FAILURE);
			}

			//printf("\t\taddress: <%s>\n", host);
			strcpy(interface_address[*interface_num], host);
			*interface_num = *interface_num + 1;
			printf("可用地址%ld: %s\n", *interface_num, host);
		}
		else if (family == AF_PACKET && ifa->ifa_data != NULL)
		{
			struct rtnl_link_stats *stats = ifa->ifa_data;

			// printf("\t\ttx_packets = %10u; rx_packets = %10u\n"
			// 	   "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
			// 	   stats->tx_packets, stats->rx_packets,
			// 	   stats->tx_bytes, stats->rx_bytes);
		}
	}

	freeifaddrs(ifaddr);
}

int main(int argc, char const *argv[])
{
	if (argc < 3)
	{
		printf("缺少参数\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("------------------\n");

		printf("监听 0.0.0.0  port=%d\n", atoi(argv[1]));
		printf("每次读%d字节，每次写%d字节\n",atoi(argv[2]),atoi(argv[3]));
	}
	int interface_num = 0;
	char interface_address[100][NI_MAXHOST];
	printf("------------------\n");
	// listInterfaces(&interface_num, interface_address);
	// printf("------------------\n");

	int i;

	// char socket_address[NI_MAXHOST];
	// strcpy(socket_address, "0.0.0.0");

	// for (i = 0; i < interface_num; i++)
	// {
	// 	if (strcmp(argv[1], interface_address[i]) == 0)
	// 	{
	// 		strcpy(socket_address, argv[1]);
	// 		break;
	// 	}
	// }
	printf("使用地址: %s\n", "0.0.0.0");
	printf("------------------\n");

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char *readbuffer = (char *)malloc(sizeof(char)*atoi(argv[2]));
	char *writebuffer = (char *)malloc(sizeof(char)*atoi(argv[3]));
	int readlength = atoi(argv[2]);
	int writelength = atoi(argv[3]);
	for (i = 0; i < atoi(argv[3]); i++)
	{
		writebuffer[i] = 'A';
	}
	writebuffer[atoi(argv[3]) - 1] = '\0';
	for (i = 0; i < atoi(argv[2]); i++)
	{
		readbuffer[i] = 'A';
	}
	readbuffer[atoi(argv[2]) - 1] = '\0';

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	// {
	// 	perror("setsockopt");
	// 	exit(EXIT_FAILURE);
	// }
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("0.0.0.0");
	;
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
	while (1)
	{
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
								 (socklen_t *)&addrlen)) < 0)
		{
			perror("accept failed");
			continue;
		}
		else
		{
			printf("%u.%u.%u.%u connected port=%d\n", address.sin_addr.s_addr & 0x000000FF, (address.sin_addr.s_addr & 0x0000FF00) >> 8, (address.sin_addr.s_addr & 0x00FF0000) >> 16, (address.sin_addr.s_addr & 0xFF000000) >> 24, ntohs(address.sin_port));
		}
		printf("waiting for recv, press anykey to start\n");
		//getchar();
		long int readbytes = 0;
		long int writebytes = 0;
		while(1)
		{
			int tmp;
			tmp = write(new_socket, writebuffer, writelength);
			if(tmp > 0)
			{
				writebytes += tmp;
				printf("write %d bytes, %d total\n", tmp, writebytes);
			
			}
			else
				printf("write error\n");
			//getchar();
			tmp = read(new_socket, readbuffer, readlength);
			if(tmp > 0)
			{
				readbytes += tmp;
				printf("read %d bytes, %d total\n", tmp, readbytes);
			
			}
			else if(tmp == 0)
				printf("read fail, connection closed\n");
			else
				printf("read error\n");
			
			//getchar();
			
		}
		
		printf("socket over\n");
	}

	return 0;
}