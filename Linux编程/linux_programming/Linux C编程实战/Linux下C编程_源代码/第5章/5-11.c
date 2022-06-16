#include<stdio.h>

int main()
{
	struct data
	{
		long		l;
		char		*s;
		short int	i;
		char		c;
		short int	a[5];
	}d;

	struct data *p = &d;
	
	printf("%d\n",sizeof(d));
	printf("%x\t%x\n",p,p+1);
	printf("%x\t%x\n",p,(char *)p+1);
	printf("%x\t%x\n",p,(long *)p+1);

	return 0;
}
