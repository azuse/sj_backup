all	:	tcp_server4-1 tcp_client4-1 tcp_server4-2 tcp_client4-2 
tcp_server4-1	:	tcp_server4-1.c
	gcc tcp_server4-1.c -o tcp_server4-1
tcp_client4-1	:	tcp_client4-1.c
	gcc tcp_client4-1.c -o tcp_client4-1
	
tcp_server4-2	:	tcp_server4-2.c
	gcc tcp_server4-2.c -o tcp_server4-2
tcp_client4-2	:	tcp_client4-2.c
	gcc tcp_client4-2.c -o tcp_client4-2


clean	:
	rm -rf tcp_client4-2 tcp_server4-2 tcp_client4-1 tcp_server4-1
