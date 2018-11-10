all	:	tcp_server1-1 tcp_client1-1 tcp_client1-3 tcp_server1-3 tcp_client1-2 tcp_server1-2
tcp_server1-1	:	tcp_server1-1.c
	gcc tcp_server1-1.c -o tcp_server1-1
tcp_client1-1	:	tcp_client1-1.c
	gcc tcp_client1-1.c -o tcp_client1-1

tcp_server1-2	:	tcp_server1-2.c
	gcc tcp_server1-2.c -o tcp_server1-2
tcp_client1-2	:	tcp_client1-2.c
	gcc tcp_client1-2.c -o tcp_client1-2

tcp_server1-3	:	tcp_server1-3.c
	gcc tcp_server1-3.c -o tcp_server1-3
tcp_client1-3	:	tcp_client1-3.c
	gcc tcp_client1-3.c -o tcp_client1-3	
clean	:
	rm -rf tcp_client1-3 tcp_server1-3 tcp_client1-1 tcp_server1-1 tcp_client1-2 tcp_server1-2
