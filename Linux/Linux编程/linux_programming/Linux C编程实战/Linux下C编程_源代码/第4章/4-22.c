#include<stdio.h>

int inc(int a)
{
	return (++a);
}

int multi(int*a,int*b,int*c)
{
	return (*c=*a**b);
}

int (*p)(int);

void show( int(*fun)(int*,int*,int*),int arg1, int *arg2)
{
	p=&inc;
	int temp =p(arg1);
	fun(&temp,&arg1,arg2);
	printf("%d\n",*arg2);
}

int main()
{
	int a;
	show(multi,10,&a);
	return 0;
}
