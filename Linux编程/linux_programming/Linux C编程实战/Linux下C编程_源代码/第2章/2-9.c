#include<stdio.h>

int main()
{
	char	c = 'a';
	int	    i = 1234;
	float	f = 12.123456;
	double	d = 12.5;

	printf("%d %o %x\n", i, i, i);
	printf("%c %d\n", c, c);
	printf("%s\n", "hello");
	printf("%f %e %g\n", f, f, f);

	printf("123456789012345678901234567890\n");
	printf("%5c%5d%10.5f%10.5f\n",c,i,f,d);
	printf("123456789012345678901234567890\n");
	printf("%-5c%-5d%-10.5f%-10.5f\n",c,i,f,d);
}



