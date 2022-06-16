#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	char *src="hello,world";
	char *dest=NULL;
	int  len=strlen(src);
	dest=(char *)malloc(len);
	char *d=dest;
	char *s=&src[len];
	while(len--!=0)
		*d++=*s--;
	printf("%s\n",dest);
	return 0;
}
