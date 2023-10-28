#include <stdio.h>

int get_big(int i,int j)
{
	return i>j?i:j;
}

int get_max(int i,int j,int k,int (*p)(int,int))
{
	int ret;
	
	ret = p(i,j);
	ret = p(ret,k);

	return ret;
}

int main()
{
	int i = 5,j = 10,k=15,ret;

	ret = get_max(i,j,k,get_big);
	printf("The MAX is %d\n",ret);

	return 0 ;
}
