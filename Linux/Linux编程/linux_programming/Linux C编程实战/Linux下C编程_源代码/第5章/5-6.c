#include<stdio.h>

int main()
{
	typedef union { long i; int  k[6]; char c; } DATE;

	struct data { int cat; double dog; DATE cow; } too;
	
	DATE max;

	printf("%d", sizeof(struct data)+sizeof(max) );

	return 0;
}
