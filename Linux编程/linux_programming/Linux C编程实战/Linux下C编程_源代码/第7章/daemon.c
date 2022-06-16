#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <time.h>
#include <syslog.h>

int init_daemon(void) 
{ 
	int pid; 
	int i; 

	/*�����ն�I/O�źţ�STOP�ź�*/
	signal(SIGTTOU,SIG_IGN);
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
	
	pid = fork();
	if(pid > 0) {
		exit(0); /*���������̣�ʹ���ӽ��̳�Ϊ��̨����*/
	}
	else if(pid < 0) { 
		return -1;
	}

	/*����һ���µĽ�����,������µĽ�������,�ӽ��̳�Ϊ�����������׽���,��ʹ�ý������������ն�*/
	setsid();

	/*�ٴ��½�һ���ӽ��̣��˳������̣���֤�ý��̲��ǽ����鳤��ͬʱ�øý����޷��ٴ�һ���µ��ն�*/
	pid=fork();
	if( pid > 0) {
		exit(0);
	}
	else if( pid< 0) {
		return -1;
	}

	/*�ر����дӸ����̼̳еĲ�����Ҫ���ļ�������*/
	for(i=0;i< NOFILE;close(i++));

	/*�ı乤��Ŀ¼��ʹ�ý��̲����κ��ļ�ϵͳ��ϵ*/
	chdir("/");

	/*���ļ���ʱ��������������Ϊ0*/
	umask(0);

	/*����SIGCHLD�ź�*/
	signal(SIGCHLD,SIG_IGN); 
	
	return 0;
}

int main() 
{ 
	time_t now;
	init_daemon();
	syslog(LOG_USER|LOG_INFO,"�����ػ�����! \n");
	while(1) { 
		sleep(8);
		time(&now); 
		syslog(LOG_USER|LOG_INFO,"ϵͳʱ��: \t%s\t\t\n",ctime(&now));
	} 
}
