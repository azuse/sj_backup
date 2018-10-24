# makefile

all : pthread fork single

single : single.c
	gcc -o single single.c 

pthread : 	pthread.c
	gcc pthread.c  -o pthread -pthread

fork	:	fork.c
	gcc fork.c -o fork -pthread

.PHONY: clean

clean:
	rm -f *.o pthread fork
