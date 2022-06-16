#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define normal		0  /* һ������� */ 
#define out_redirect	1  /* ����ض��� */ 
#define in_redirect	2  /* �����ض��� */ 
#define have_pipe	3  /* �������йܵ� */ 

void print_prompt();						/* ��ӡ��ʾ�� */
void get_input(char *);						/* �õ���������� */
void explain_input(char *, int *, char a[ ][ ]);		/* ������������н��� */
void do_cmd(int, char a[ ][ ]);					/* ִ������ */
int  find_command(char *);					/* ���������еĿ�ִ�г��� */

int main(int argc, char **argv)
{
	int    i;
	int    argcount = 0;
	char   arglist[100][256];
	char   **arg = NULL;
	char   *buf  = NULL;
		
	buf = (char *)malloc(256);
	if( buf == NULL ) {
		perror("malloc failed");
		exit(-1);
	}
    
	while(1) {
		/* ��buf��ָ��Ŀռ����� */
		memset(buf, 0, 256);
		print_prompt();
		get_input(buf);
		/* �����������Ϊexit��logout���˳������� */
		if( strcmp(buf,"exit\n") == 0 || strcmp(buf,"logout\n") == 0 )
			break;
		for (i=0; i < 100; i++)
		{
			arglist[i][0]='\0';
		}
		argcount = 0;
		explain_input(buf, &argcount, arglist); 
		do_cmd(argcount, arglist);	
	}

	if(buf != NULL) {
		free(buf);
		buf = NULL;
	}

	exit(0);
}

void print_prompt()
{
	printf("myshell$$ ");
}

/*��ȡ�û�����*/
void get_input(char *buf)
{
	int len = 0;
	int ch;

	ch = getchar();
	while (len < 256 && ch != '\n') {
		buf[len++] = ch;
		ch = getchar();
	}

	if(len == 256) {
		printf("command is too long \n");
		exit(-1); /* ���������������˳����� */     
	}

	buf[len] = '\n';
	len++;
	buf[len] = '\0';        
}

/* ����buf�е�������������arglist�У������Իس�����\n���� */
/* ������������Ϊ"ls -l /tmp"����arglist[0]��arglist[1]��arglsit[2]�ֱ�Ϊls��-l��/tmp */
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
	char	*p	= buf;
	char	*q	= buf;
	int	number	= 0;

	while (1) {
		if ( p[0] == '\n' )
			break;

		if ( p[0] == ' '  )
			p++;
		else {
			q = p;
			number = 0;
			while( (q[0]!=' ') && (q[0]!='\n') ) {
				number++;
				q++;
			}
			strncpy(arglist[*argcount], p, number+1);
			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
		}
	}
}


void do_cmd(int argcount, char arglist[100][256])
{
	int	flag = 0;       
	int	how = 0;        /* ����ָʾ�������Ƿ���>��<��|   */
	int	background = 0; /* ��ʶ�������Ƿ��к�̨���б�ʶ��& */ 
	int	status;
	int	i;
	int	fd;
	char*	arg[argcount+1];
	char*	argnext[argcount+1];
	char*	file;
	pid_t	pid;

	/*������ȡ��*/
	for (i=0; i < argcount; i++) {
		arg[i] = (char *) arglist[i];
	}
	arg[argcount] = NULL;

	/*�鿴�������Ƿ��к�̨���з�*/
	for (i=0; i < argcount; i++) {
		if (strncmp(arg[i], "&",1) == 0) {
			if (i == argcount-1) {
				background = 1;
				arg[argcount-1] = NULL;
				break;
			}
			else {
				printf("wrong command\n");
				return ;
			}
		}
	}

	for (i=0; arg[i]!=NULL; i++) {
		if (strcmp(arg[i], ">") == 0 ) {
			flag++;
			how = out_redirect;
			if (arg[i+1] == NULL) 
				flag++;
		}
		if ( strcmp(arg[i],"<") == 0 ) {
			flag++;
			how = in_redirect;
			if(i == 0) 
				flag++;
		}
		if ( strcmp(arg[i],"|")==0 ) {
			flag++;
			how = have_pipe;
			if(arg[i+1] == NULL)
				flag++;
			if(i == 0 )
				flag++;
		}
	}
	/* flag����1��˵�������к��ж��> ,<,|���ţ��������ǲ�֧�������������
	   ���������ʽ���ԣ���"ls ��l /tmp >" */
	if (flag > 1) {
		printf("wrong command\n");
		return;
	}

	if (how == out_redirect) {  /*����ֻ����һ������ض������> */
		for (i=0; arg[i] != NULL; i++) {
			if (strcmp(arg[i],">")==0) {
				file   = arg[i+1];
				arg[i] = NULL;
			}			
		}
	}

	if (how == in_redirect) {    /*����ֻ����һ�������ض������< */
		for (i=0; arg[i] != NULL; i++) {
			if (strcmp (arg[i],"<") == 0) {
				file   = arg[i+1];
				arg[i] = NULL;
			}
		}
	}

	if (how == have_pipe) {  /* ����ֻ����һ���ܵ�����| */
/* �ѹܵ����ź��ŵĲ��ִ���argnext�У��ܵ�����Ĳ�����һ����ִ�е�shell���� */
		for (i=0; arg[i] != NULL; i++) {
			if (strcmp(arg[i],"|")==0) {
				arg[i] = NULL;
				int j;
				for (j=i+1; arg[j] != NULL; j++) {
					argnext[j-i-1] = arg[j];
				}
				argnext[j-i-1] = arg[j];
				break;
			}
		}
	}

	if ( (pid = fork()) < 0 ) {
		printf("fork error\n");
		return;
	}

	switch(how) {
		case 0:
			/* pidΪ0˵�����ӽ��̣����ӽ�����ִ����������� */
			/* ����������в���>��<��| */
			if (pid == 0) {
				if ( !(find_command(arg[0])) ) {
					printf("%s : command not found\n", arg[0]);
					exit (0);
				}
				execvp(arg[0], arg);
				exit(0);
			}
			break;
		case 1: 
			/* ����������к�������ض����> */
			if (pid == 0) {
				if ( !(find_command(arg[0])) ) {
					printf("%s : command not found\n",arg[0]);
					exit(0);
				}
				fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
				dup2(fd,1);
				execvp(arg[0],arg);
				exit(0);
			}
			break;
		case 2:
			/* ����������к��������ض����< */
			if (pid == 0) {
				if ( !(find_command (arg[0])) ) {
					printf("%s : command not found\n",arg[0]);
					exit(0);
				}
				fd = open(file,O_RDONLY);
				dup2(fd,0);  
				execvp(arg[0],arg);
				exit(0);
			}
			break;
		case 3:
			/* ����������к��йܵ���| */
			if(pid == 0) {
				int  pid2;
				int  status2;
				int  fd2;

				if ( (pid2 = fork()) < 0 ) {
					printf("fork2 error\n");
					return;
				}
				else if (pid2==0) {
					if ( !(find_command(arg[0])) ) {
						printf("%s : command not found\n",arg[0]);
						exit(0);
					}
					fd2 = open("/tmp/youdonotknowfile",
							O_WRONLY|O_CREAT|O_TRUNC,0644);
					dup2(fd2, 1);  
					execvp(arg[0], arg);
					exit(0);
				}

				if (waitpid(pid2, &status2, 0) == -1)
					printf("wait for child process error\n");

				if ( !(find_command(argnext[0])) ) {
					printf("%s : command not found\n",argnext[0]);
					exit(0);
				}
				fd2 = open("/tmp/youdonotknowfile",O_RDONLY);
				dup2(fd2,0);  
				execvp (argnext[0],argnext);
			
				if ( remove("/tmp/youdonotknowfile") )
					printf("remove error\n");
				exit(0);
			}
			break;
		default:
			break;
	}

	/* ����������&����ʾ��ִ̨�У�������ֱ�ӷ��ز��ȴ��ӽ��̽��� */
	if ( background == 1 ) {
		printf("[process id %d]\n",pid);
		return ;
	}
	
	/* �����̵ȴ��ӽ��̽��� */
	if (waitpid (pid, &status,0) == -1)
		printf("wait for child process error\n");
}

/* ���������еĿ�ִ�г��� */
int find_command (char *command)
{
	DIR*             dp;
	struct dirent*   dirp;
	char*			 path[] = { "./", "/bin", "/usr/bin", NULL};

	/* ʹ��ǰĿ¼�µĳ�����Ա����У�������"./fork"���Ա���ȷ���ͺ�ִ�� */
	if( strncmp(command,"./",2) == 0 )
		command = command + 2;

	/* �ֱ��ڵ�ǰĿ¼��/bin��/usr/binĿ¼����Ҫ��ִ�г��� */
	int i = 0;
	while (path[i] != NULL) {
		if ( (dp = opendir(path[i]) ) == NULL)  
			printf ("can not open /bin \n");
		while ( (dirp = readdir(dp)) != NULL) {
			if (strcmp(dirp->d_name,command) == 0) {
				closedir(dp);
				return 1;
			}
		}
		closedir (dp);
		i++;
	}
	return 0;
}
