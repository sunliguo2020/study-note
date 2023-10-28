// ʾ������select()��ʹ��
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void display_time(const char *string)
{
	int		seconds;
	
	seconds = time((time_t*)NULL);
	printf("%s, %d\n", string, seconds);
}

int main(void) 
{
	fd_set		readfds;
	struct timeval	timeout;
	int		ret;
	
	/*�����ļ�������0�Ƿ����������룬���ļ�������0��ʾ��׼���뼴��������*/
	FD_ZERO(&readfds);  // ��ʼʹ��һ������������ǰһ��Ҫ�������
	FD_SET(0, &readfds);
	
	/*��������ʱ��Ϊ10��*/
	timeout.tv_sec = 10;
	timeout.tv_usec = 0;	
	
	while (1) {
		display_time("before select");
		ret = select(1, &readfds, NULL, NULL, &timeout);
		display_time("after select");
		
		switch (ret) {
			case 0:
				printf("No data in ten seconds.\n");
				exit(0);
				break;
			case -1:
				perror("select");
				exit(1);
				break;
			default:
				getchar();	 // �����ݶ��룬�����׼�����Ͻ�һֱΪ������
				printf("Data is available now.\n");
		}
	}
	
	return 0;
}
