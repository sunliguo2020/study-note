#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	char str[] = "ABCD1234efgh";
	int length = strlen(str);
	char *p1 = str;			// p1ָ���ַ����ĵ�һ���ַ�
	char *p2 = str + length - 1;	// p2ָ���ַ��������һ���ַ�
	
	// ����Ե���һ�������һ���ַ����ڶ����͵����ڶ��ַ�
	// �����ȥ��ֱ���ﵽ�ַ������м�
	while(p1 < p2)
	{
		// �Ե��ַ�
		char c = *p1;
		*p1 = *p2;
		*p2 = c;
		// �ƶ�ָ��
		++p1;
		--p2;
	}
	
	printf("string now is  %s\n",str);
	return 0;
}
