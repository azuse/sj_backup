all	:	tcp_server2-1 tcp_client2-1 tcp_server2-2 tcp_client2-2 
tcp_server2-1	:	tcp_server2-1.c
	gcc tcp_server2-1.c -o tcp_server2-1
tcp_client2-1	:	tcp_client2-1.c
	gcc tcp_client2-1.c -o tcp_client2-1
	
tcp_server2-2	:	tcp_server2-2.c
	gcc tcp_server2-2.c -o tcp_server2-2
tcp_client2-2	:	tcp_client2-2.c
	gcc tcp_client2-2.c -o tcp_client2-2


clean	:
	rm -rf tcp_client2-2 tcp_server2-2 tcp_client2-1 tcp_server2-1
