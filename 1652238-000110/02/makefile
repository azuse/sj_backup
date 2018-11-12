all	:	test2-1 test2-2 test2-3 test2-4 test2-5
test2-1	:	test2-1.c
	gcc test2-1.c -o test2-1
test2-2	:	test2-2.c
	gcc test2-2.c -o test2-2
test2-3	:	test2-3.c
	gcc test2-3.c -o test2-3
test2-4	:	test2-4-1.c test2-4-2.c
	gcc test2-4-1.c -o test2-4-1
	gcc test2-4-2.c -o test2-4-2

test2-5	:	test2-5-1.c test2-5-2.c
	gcc test2-5-1.c -o test2-5-1
	gcc test2-5-2.c -o test2-5-2
clean	:
	rm -rf test2-1 test2-2 test2-3 test2-4-1 test2-4-2 test2-5-1 test2-5-2