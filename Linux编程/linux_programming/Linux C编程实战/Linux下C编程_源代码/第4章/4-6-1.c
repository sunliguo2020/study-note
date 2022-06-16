#include<stdio.h>

extern long power(int);
int A = 2;

main()
{
	int n = 10,total;
	total = power(n);
	printf("2^10 = %d \n",total);
	return 0;
}
