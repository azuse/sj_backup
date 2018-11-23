all	:	test7-1 test7-2

test7-1	:	test7-1-1.c	test7-1-2.c
	gcc test7-1-1.c -o test7-1-1
	gcc test7-1-2.c -o test7-1-2

test7-2	:	test7-2-1.c	test7-2-2.c
	gcc test7-2-1.c -o test7-2-1
	gcc test7-2-2.c -o test7-2-2

clean	:
	rm -rf test7-1-1 test7-1-2 test7-2-1 test7-2-2 