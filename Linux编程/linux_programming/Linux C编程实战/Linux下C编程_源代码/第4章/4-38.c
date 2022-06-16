#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int findnumstring(char *outputstr, char *inputstr)
{
    /* temp用于指向正在搜索中的数字子串
           final用于指向最终的最长的数字子串
     */
	char *in = inputstr, *out = outputstr, *temp, *final;
	int count = 0, maxlen = 0;
	int i;
	
	while( *in != '\0' )   //该循环用于找到最长的数字串，初始in指向输入串
	{
		// 如果in所指向的字符串的第一个字符为数字
		// 就获取以此数字字符开始的数字串的长度
		// 如果不是数字字符，in指向输入串的下一个字符
		if( *in > 47 && *in < 58 )  		
		{
			// 注意in指针在变化
			for(temp = in; *in > 47 && *in < 58 ; in++ )  
				count++;
		}
		else
			in++;
		
		// 如果temp所指向数字串的长度比上一次找到的长
		// 则把当前找到的最长数字串长度和地址分别赋给maxlen和final
		if( maxlen < count )
		{
			maxlen = count;
			final  = temp;
		}
		
		// 把count清零
		count = 0;
	}
	
	// while循环结束后，最长的数字串已经找到。
	// 把找到的最长数字串存储到out所指的存储空间
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
	// 主函数测试findnumstring函数是否正常工作
	char string[] = "abcd12345eee125ss123456789";
	char *p = (char *)malloc( strlen(string)+1 );
	int  count = findnumstring(p,string);
	printf("%s\nnumber string length = %d\n",p,count);
}
