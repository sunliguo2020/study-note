#include <stdio.h>

int main()
{
	char a[] = "Linux C Program",b[20],c[20];
	int  i;

	for(i=0; *(a+i) != '\0'; i++)
		*(b+i) = *(a+i);
	*(b+i) = '\0';

	char *p1,*p2;
	p1 = a;
	p2 = c;

	for(; *p1 != '\0'; p1++,p2++)
		*p2 = *p1;
	*p2 = '\0';

	printf("%s\n",a);
	printf("%s\n",b);
	printf("%s\n",c);

	return 0 ;
}
