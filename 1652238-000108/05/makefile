all	:	tcp_server5-1 tcp_client5-1 tcp_server5-2 tcp_client5-2 tcp_server5-3 tcp_client5-3
tcp_server5-1	:	tcp_server5-1.c
	gcc tcp_server5-1.c -o tcp_server5-1
tcp_client5-1	:	tcp_client5-1.c
	gcc tcp_client5-1.c -o tcp_client5-1 -pthread

tcp_server5-2	:	tcp_server5-2.c
	gcc tcp_server5-2.c -o tcp_server5-2
tcp_client5-2	:	tcp_client5-2.c
	gcc tcp_client5-2.c -o tcp_client5-2 -pthread

tcp_server5-3	:	tcp_server5-3.c
	gcc tcp_server5-3.c -o tcp_server5-3
tcp_client5-3	:	tcp_client5-3.c
	gcc tcp_client5-3.c -o tcp_client5-3 -pthread

clean	:

	rm -rf tcp_client5-1 tcp_server5-1 tcp_client5-2 tcp_server5-2 tcp_client5-3 tcp_server5-3
