#include<stdio.h>
#include<string.h> 
#include<stdlib.h>
int main(int argc, char* argv[])
{
	char a;
	char *str=&a;
	strcpy(str,"hello");
	printf("%s\n",str);	
	return 0;
}
