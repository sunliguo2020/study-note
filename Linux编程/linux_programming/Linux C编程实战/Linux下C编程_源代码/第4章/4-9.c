#include <stdio.h>

int main()
{
	int a[10],i,*p = NULL;

	for(i=0; i<10; i++)
		a[i] = i;

	for(i=0; i<10; i++)
		printf("%d ",a[i]);
	printf("\n");

	for(i=0; i<10; i++)
		printf("%d ",*(a+i));
	printf("\n");
	
	for(p=a; p<a+10; )
		printf("%d ",*p++);
	printf("\n");

	return 0;
}
