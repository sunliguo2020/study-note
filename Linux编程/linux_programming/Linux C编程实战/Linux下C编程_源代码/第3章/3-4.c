#include<stdio.h>
	
main()
{
	int number;
	
	for(number=1; number<=100; number++)
	{
		if(number%13 == 0)
			continue;
		printf("%d ",number);
	}

	printf("\n");
}
