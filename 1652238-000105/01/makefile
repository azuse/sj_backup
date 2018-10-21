# makefile 01
all : test1.so test2
test1.so : 
	gcc -fPIC -shared test1.c -o libtest1.so
test2 : 
	gcc test2.c -L. -ltest1 -o test2
.PHONY: clean
clean :
	rm -f test2 *.o *.so