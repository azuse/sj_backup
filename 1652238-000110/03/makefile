all	:	test3-1 test3-extra test3-2
test3-1	:	test3-1-1.c test3-1-2.c
	gcc test3-1-1.c -o test3-1-1
	gcc test3-1-2.c -o test3-1-2
test3-extra	:	test3-extra.c
	gcc test3-extra.c -o test3-extra
test3-2	:	test3-2-1.c test3-2-2.c
	gcc test3-2-1.c -o test3-2-1
	gcc test3-2-2.c -o test3-2-2

clean	:
	rm -rf test3-1-1 test3-1-2 test3-extra test3-2-1 test3-2-2
