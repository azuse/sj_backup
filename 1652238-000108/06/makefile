all	:	tcp_server6-1 tcp_client6-1 tcp_server6-2 tcp_client6-2 tcp_server6-3 tcp_client6-3 tcp_server6-4 tcp_client6-4
tcp_server6-1	:	tcp_server6-1.c
	gcc tcp_server6-1.c -o tcp_server6-1
tcp_client6-1	:	tcp_client6-1.c
	gcc tcp_client6-1.c -o tcp_client6-1 -pthread

tcp_server6-2	:	tcp_server6-2.c
	gcc tcp_server6-2.c -o tcp_server6-2
tcp_client6-2	:	tcp_client6-2.c
	gcc tcp_client6-2.c -o tcp_client6-2 -pthread

tcp_server6-3	:	tcp_server6-3.c
	gcc tcp_server6-3.c -o tcp_server6-3
tcp_client6-3	:	tcp_client6-3.c
	gcc tcp_client6-3.c -o tcp_client6-3 -pthread

tcp_server6-4	:	tcp_server6-4.c
	gcc tcp_server6-4.c -o tcp_server6-4
tcp_client6-4	:	tcp_client6-4.c
	gcc tcp_client6-4.c -o tcp_client6-4 -pthread


clean	:

	rm -rf tcp_client6-1 tcp_server6-1 tcp_client6-2 tcp_server6-2 tcp_client6-3 tcp_server6-3 tcp_client6-4 tcp_server6-4
