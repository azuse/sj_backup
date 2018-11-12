all	:	test4-1 test4-2

test4-1	:	test4-1-1.c	test4-1-2.c
	gcc test4-1-1.c -o test4-1-1
	gcc test4-1-2.c -o test4-1-2

test4-2	:	test4-2-1.c	test4-2-2.c
	gcc test4-2-1.c -o test4-2-1
	gcc test4-2-2.c -o test4-2-2

clean	:
	rm -rf test4-1-1 test4-1-2 test4-2-1 test4-2-2