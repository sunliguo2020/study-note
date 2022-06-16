#include<stdio.h>
	
main()
{
	int sum=0, i=1;

	while(i<=100)
	{
		sum=sum+i;
		i=i+1;
	}

	printf("%d\n", sum);
}
