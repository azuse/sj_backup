# makefile 02
objects = test1.o test2.o test3.o
test : $(objects)
	gcc -o test $(objects)
test1.o : test.h
test2.o : test.h
test3.o : test.h
.PHONY : clean
clean :
	rm test $(objects)