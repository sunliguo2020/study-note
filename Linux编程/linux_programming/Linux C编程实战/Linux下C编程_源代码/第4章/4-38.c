#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int findnumstring(char *outputstr, char *inputstr)
{
    /* temp����ָ�����������е������Ӵ�
           final����ָ�����յ���������Ӵ�
     */
	char *in = inputstr, *out = outputstr, *temp, *final;
	int count = 0, maxlen = 0;
	int i;
	
	while( *in != '\0' )   //��ѭ�������ҵ�������ִ�����ʼinָ�����봮
	{
		// ���in��ָ����ַ����ĵ�һ���ַ�Ϊ����
		// �ͻ�ȡ�Դ������ַ���ʼ�����ִ��ĳ���
		// ������������ַ���inָ�����봮����һ���ַ�
		if( *in > 47 && *in < 58 )  		
		{
			// ע��inָ���ڱ仯
			for(temp = in; *in > 47 && *in < 58 ; in++ )  
				count++;
		}
		else
			in++;
		
		// ���temp��ָ�����ִ��ĳ��ȱ���һ���ҵ��ĳ�
		// ��ѵ�ǰ�ҵ�������ִ����Ⱥ͵�ַ�ֱ𸳸�maxlen��final
		if( maxlen < count )
		{
			maxlen = count;
			final  = temp;
		}
		
		// ��count����
		count = 0;
	}
	
	// whileѭ��������������ִ��Ѿ��ҵ���
	// ���ҵ�������ִ��洢��out��ָ�Ĵ洢�ռ�
	for(i = 0; i < maxlen; i++)
	{
		*out = *final;
		out++;
		final++;
	}
	*out = '\0';
	
	return maxlen;
}

int main()
{
	// ����������findnumstring�����Ƿ���������
	char string[] = "abcd12345eee125ss123456789";
	char *p = (char *)malloc( strlen(string)+1 );
	int  count = findnumstring(p,string);
	printf("%s\nnumber string length = %d\n",p,count);
}
