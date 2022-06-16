// 示例采用循环检测来判断事件发生
#include <stdio.h>
#include <signal.h>

#define	UNHAPPEN	0	// 未发生
#define	HAPPENED	1	// 已发生

/*定义全局变量以标识事件是否发生*/
int		flag_happen;

void handler_sigint(int signo)
{
	flag_happen = HAPPENED;
}

int main()
{
	/*安装信号处理函数*/
	if (signal(SIGINT, handler_sigint) == SIG_ERR) {
		perror("signal");
		exit(1);
	}

	while (1) {
		if (flag_happen == HAPPENED) {
			printf("event happened\n");
			/*... you can do something else here...*/
			break;
		}
	}
	
	return 0;
}
