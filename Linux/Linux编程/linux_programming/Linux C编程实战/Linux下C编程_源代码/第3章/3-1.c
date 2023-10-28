#include<stdio.h>

main()
{
	float a, b, c, temp;

	scanf("%f,%f,%f", &a, &b, &c);

	if ( a > b )
	{
		temp=a; a=b; b=temp;
	}
	if ( a > c )
	{
		temp=a; a=c; c=temp;
	}
	if ( b > c )
	{
		temp=b; b=c; c=temp;
	}

	printf ("%f,%f,%f\n", a, b, c);
}
