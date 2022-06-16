#include<stdio.h>

void function()
{
	static int a = 0;
	int b = 0;
	a++;
	b++;
	printf("a=%d,b=%d\n",a,b);
}

main()
{
	function();
	function();
	function();
}
