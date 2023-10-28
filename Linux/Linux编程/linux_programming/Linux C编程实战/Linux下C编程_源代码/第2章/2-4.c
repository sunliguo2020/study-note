#include<stdio.h>

int main( )
{
	int   c1,c2;
	char  c3;

	c1='a'-'A';
	c2='b'-'B';
	c3='c'-32;

	printf("c1 is %d and c2 is %d\n",c1,c2);
	printf("c3 is %d and %c\n",c3,c3);
}
