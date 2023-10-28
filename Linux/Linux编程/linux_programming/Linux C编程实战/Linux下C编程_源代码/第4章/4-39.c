#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char str[] = "ABCD1234efgh";
	int length = strlen(str);
	char *p1 = str;			// p1指向字符串的第一个字符
	char *p2 = str + length - 1;	// p2指向字符串的最后一个字符
	
	// 逐个对调第一个和最后一个字符、第二个和倒数第二字符
	// 如此下去，直到达到字符串的中间
	while(p1 < p2)
	{
		// 对调字符
		char c = *p1;
		*p1 = *p2;
		*p2 = c;
		// 移动指针
		++p1;
		--p2;
	}
	
	printf("string now is  %s\n",str);
	return 0;
}
