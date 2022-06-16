#include<stdio.h>

main()
{	
	int   i;
	float f = 1;

	for(i=1; i<=10; i++)
		f = f * i;

	printf("10! = %10.0f\n",f);
}
