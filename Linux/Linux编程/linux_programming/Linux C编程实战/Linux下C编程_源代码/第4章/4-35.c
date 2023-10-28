#include<stdio.h>

int sum(int a)
{
	auto   int c=0;
	static int b=3;
	c+=1;
	b+=2;
	return (a+b+c);
}

int main()
{
	int i;
	int a=2;
	for(i=0;i<5;i++)
	{
		printf("%d,", sum(a) );
	}
}
