#include<stdio.h>

int main()
{
	int a, b, c, d;

	a = 10;
	b = a++;
	c = ++a;
	d = 10*a++;

	printf("b, c, d:%d, %d, %d\n", b, c, d);
}

