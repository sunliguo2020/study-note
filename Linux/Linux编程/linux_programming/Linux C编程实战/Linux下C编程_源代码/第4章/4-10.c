#include <stdio.h>

int main()
{
	int a[5] = {1,3,5,7,9};
	int *p[5],i;
	int **pp = p;

	for(i=0; i<5; i++)
		p[i] = &a[i];

	for(i=0; i<5; i++)
		printf("%d ",*p[i]);
	printf("\n");

	for(i=0; i<5; i++,pp++)
		printf("%d ",**pp);

	return 0;
}
