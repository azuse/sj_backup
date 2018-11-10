all	:	tcp_server5 tcp_client5-1 tcp_client5-2 
tcp_server5	:	tcp_server5.c
	gcc tcp_server5.c -o tcp_server5
tcp_client5-1	:	tcp_client5-1.c
	gcc tcp_client5-1.c -o tcp_client5-1
tcp_client5-2	:	tcp_client5-2.c
	gcc tcp_client5-2.c -o tcp_client5-2


clean	:
	rm -rf tcp_client5-2 tcp_client5-1 tcp_server5
