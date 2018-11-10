all	:	tcp_server3-1 tcp_client3-1 tcp_server3-2 tcp_client3-2 
tcp_server3-1	:	tcp_server3-1.c
	gcc tcp_server3-1.c -o tcp_server3-1
tcp_client3-1	:	tcp_client3-1.c
	gcc tcp_client3-1.c -o tcp_client3-1
	
tcp_server3-2	:	tcp_server3-2.c
	gcc tcp_server3-2.c -o tcp_server3-2
tcp_client3-2	:	tcp_client3-2.c
	gcc tcp_client3-2.c -o tcp_client3-2


clean	:
	rm -rf tcp_client3-2 tcp_server3-2 tcp_client3-1 tcp_server3-1
