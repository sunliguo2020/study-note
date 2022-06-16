#include<stdio.h>

float fac(int n)
{
	float f;
	if(n<0)
	{
		printf("n<0,data error!");
		return -1;
	}
	else if( n==0 || n==1)
		f = 1;
	else
		f = n * fac(n-1);
	return f;
}

main()
{
	int   n = 10;
	float f;

	f = fac(n);

	printf("n! = %10.0f\n",f);
}
