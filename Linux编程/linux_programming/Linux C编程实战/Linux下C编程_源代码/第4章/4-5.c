#include<stdio.h>

int max(int a,int b)
{
	return a>b?a:b;
}

main()
{
	extern i,j;
	printf("%d\n",max(i,j));
}
