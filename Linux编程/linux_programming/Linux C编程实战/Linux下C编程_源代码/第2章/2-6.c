#include<stdio.h>

int main( )
{
	int i=3,j,k;
	
	j=i++;
	k=++i;

	printf("i=%d,j=%d,k=%d\n",i,j,k);
	printf("%d\n",-i++);
	printf("%d,%d,%d",i,i++,i++);
}
