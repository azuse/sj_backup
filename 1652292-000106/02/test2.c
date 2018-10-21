//Ñî×¿Óî 1652292 ¼Æ¿Æ2°à
#include <stdio.h>
#include <unistd.h>

int main()
{
	daemon(1, 1);
	while (1)
	{
		printf("1652292\n");
		fflush(stdout);
		sleep(5);
	}
	return 0;
}
