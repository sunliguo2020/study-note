#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void fun(char str[100])
{
	printf("%d\n",sizeof(str));
}

int main()
{
	char  str[] = "Hello";
	char  *p1 = str;
	int   n = 10;
	char  *p2 = (char *)malloc(100);
	
	printf("%d\n",sizeof(str) );
	printf("%d\n",strlen(str) );

	printf("%d\n",sizeof(p1)  );
	printf("%d\n",strlen(p1)  );
	
	printf("%d\n",sizeof(n)   );
	printf("%d\n",sizeof(p2)  );
	fun(p2);

	printf("\n");
	return 0;
}
