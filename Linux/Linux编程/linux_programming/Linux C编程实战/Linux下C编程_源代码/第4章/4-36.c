#include<stdio.h>

int fun( int a[ ], int n )
{
	if( n==1 )
		return 1;
	if( n==2 )
		return (a[n-1]>=a[n-2]);
	return ( fun(a,n-1) && (a[n-1]>=a[n-2]) );
}

int main()
{
	int a[] = {1,2,3,4,5,6};
	int b[] = {1,2,3,4,6,5};
	
	if( fun(a,sizeof(a)/sizeof(a[0])) ==1 )
		printf("a:ok\n");
	else
		printf("a:no\n");
	
	if( fun(b,sizeof(a)/sizeof(a[0])) ==1 )
		printf("b:ok\n");
	else
		printf("b:no\n");

	return 0;
}
