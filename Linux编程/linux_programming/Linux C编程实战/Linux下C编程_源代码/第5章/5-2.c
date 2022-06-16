#include<stdio.h>
#define  MAX(x,y)  (x>y?x:y)

int main()
{
	int  a = 5,b = 10,max;
	
	max = MAX(a,b);
	printf("The max between(%d,%d) is %d\n",a,b,max);

	return 0;
}
