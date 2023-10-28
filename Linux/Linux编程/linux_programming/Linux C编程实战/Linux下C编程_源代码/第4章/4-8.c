#include <stdio.h>

int main()
{
	int a = 100,b = 200;
	int *p1 = &a,*p2 = &b;

	printf("%d,%d\n",a,b);
	printf("%d,%d\n",*p1,*p2);
	printf("%x,%x\n",&a,&b);
	printf("%x,%x\n\n",p1,p2);

	*p1 = *p1*3;
	printf("%d\n",a);
	printf("%d\n\n",*p1);

	p1 = &b;
	printf("%x\n",p1);
	printf("%x\n",p2);

	return 0;
}
