#include<stdio.h>

char *RetMemory()
{
	char p[] = "hello world";
	return p;
}

void main()
{
	char *str = NULL;
	str = RetMemory();
	printf(str);
}
