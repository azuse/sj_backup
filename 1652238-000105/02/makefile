# makefile 02
all : test1.so test2
test1.so : 
	g++ -fPIC -shared test1.cpp -o libtest1.so
test2 : 
	g++ test2.cpp -L. -ltest1 -o test2
.PHONY: clean
clean :
	rm -f test2 *.o *.so