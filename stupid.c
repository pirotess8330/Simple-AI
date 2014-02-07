#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long next = 1;

int random1(void)
{
	next = next * 1103515245 + 12345;
	return(unsigned int)(next/65536) % 21;
}

int main()
{
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	printf("%d\n", random1());
	return 0;
}
