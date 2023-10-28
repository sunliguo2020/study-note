#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <linux/limits.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>

#define		PARAM_NONE	0	// �޲���
#define		PARAM_A		1	// -a: ��ʾ�����ļ�
#define		PARAM_L		2	// -l:һ����ʾһ���ļ�����ϸ��Ϣ

#define		MAXROWLEN	80	// һ����ʾ������ַ���

int		g_leave_len = MAXROWLEN;	// һ��ʣ�೤�ȣ������������
int		g_maxlen;			// ���ĳĿ¼����ļ����ĳ���

/* ������������ӡ�����������е������ʹ�����Ϣ */
void my_err(const char *err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

/* ��ȡ�ļ����Բ���ӡ */
void display_attribute(struct stat buf, char * name)
{
	char		buf_time[32];
	struct passwd	*psd;	//�Ӹýṹ���л�ȡ�ļ������ߵ��û���
	struct group	*grp;	//�Ӹýṹ���л�ȡ�ļ������������������

	/*��ȡ����ӡ�ļ�����*/
	if (S_ISLNK(buf.st_mode)) {
		printf("l");
	} else if (S_ISREG(buf.st_mode)) {
		printf("-");
	} else if (S_ISDIR(buf.st_mode)) {
		printf("d");
	} else if (S_ISCHR(buf.st_mode)) {
		printf("c");
	} else if (S_ISBLK(buf.st_mode)) {
		printf("b");
	} else if (S_ISFIFO(buf.st_mode)) {
		printf("f");
	} else if (S_ISSOCK(buf.st_mode)) {
		printf("s");
	}

	/*��ȡ����ӡ�ļ������ߵ�Ȩ��*/
	if (buf.st_mode & S_IRUSR){
		printf("r");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IWUSR){
		printf("w");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IXUSR){
		printf("x");
	} else {
		printf("-");
	}

	/*��ȡ����ӡ���ļ�������ͬ����û��Ը��ļ��Ĳ���Ȩ��*/
	if (buf.st_mode & S_IRGRP){
		printf("r");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IWGRP){
		printf("w");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IXGRP){
		printf("x");
	} else {
		printf("-");
	}

	/*��ȡ����ӡ�����û��ĶԸ��ļ��Ĳ���Ȩ��*/
	if (buf.st_mode & S_IROTH){
		printf("r");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IWOTH){
		printf("w");
	} else {
		printf("-");
	}
	if (buf.st_mode & S_IXOTH){
		printf("x");
	} else {
		printf("-");
	}

	printf("    ");

	/*����uid��gid��ȡ�ļ������ߵ��û���������*/
	psd = getpwuid(buf.st_uid);
	grp = getgrgid(buf.st_gid);
	printf("%4d ",buf.st_nlink);   // ��ӡ�ļ���������
	printf("%-8s", psd->pw_name);
	printf("%-8s", grp->gr_name);

	printf("%6d",buf.st_size);     // ��ӡ�ļ��Ĵ�С 
	strcpy(buf_time, ctime(&buf.st_mtime));
	buf_time[strlen(buf_time) - 1] = '\0';	// ȥ�����з�
	printf("  %s", buf_time);				// ��ӡ�ļ���ʱ����Ϣ
}

/* ��û��ʹ��-lѡ��ʱ����ӡһ���ļ�������ӡʱ������֮����ж��� */
void display_single(char *name)
{
	int i, len;

	// ������в����Դ�ӡһ���ļ�������
	if (g_leave_len < g_maxlen) {	
		printf("\n");
		g_leave_len = MAXROWLEN;
	}

	len = strlen(name);
	len = g_maxlen - len;
	printf("%-s", name);
	
	for (i=0; i<len; i++) {
		printf(" ");
	}
	printf("  ");
	//�����2ָʾ������
	g_leave_len -= (g_maxlen + 2);
}

/*
*	���������в���������·������ʾĿ���ļ�
*	����flag�� �����в���
*	����pathname�� �������ļ�����·����
*/
void display(int flag, char * pathname)
{
	int		i, j;
	struct stat	buf;
	char		name[NAME_MAX + 1];

	/*��·���н������ļ���*/
	for (i=0, j=0; i<strlen(pathname); i++) {
		if (pathname[i] == '/') {
			j = 0;
			continue;
		}
		name[j++] = pathname[i];
	}
	name[j] = '\0';
	
	/*��lstat������stat�Է�����������ļ�*/
	if ( lstat(pathname, &buf) == -1 ) {
		my_err("stat", __LINE__);
	}
	
	switch (flag) {
		case PARAM_NONE:  // û��-l��-aѡ��
			if (name[0] != '.') {
				display_single(name);
			}
			break;

		case PARAM_A:	  // -a:��ʾ���������ļ����ڵ������ļ�
			display_single(name);
			break;

		case PARAM_L:	  // -l:ÿ���ļ�����ռһ�У���ʾ�ļ�����ϸ������Ϣ
			if (name[0] != '.') {
				display_attribute(buf, name);
				printf("  %-s\n", name);
			}
			break;

		case PARAM_A + PARAM_L:		// ͬʱ��-a��-lѡ������
			display_attribute(buf, name);
			printf("  %-s\n", name);
			break;

		default:
			break;
	}
}

void display_dir(int flag_param, char *path)
{
        DIR            *dir;
        struct dirent  *ptr;
        int            count = 0;
        char           filenames[256][PATH_MAX+1],temp[PATH_MAX+1];

		// ��ȡ��Ŀ¼���ļ�����������ļ���
        dir = opendir(path);
        if (dir == NULL) {
                my_err("opendir", __LINE__);
        }
        while ((ptr = readdir(dir))!=NULL) {
                if (g_maxlen < strlen(ptr->d_name))
                         g_maxlen =  strlen(ptr->d_name);
                count++;
        }
        closedir(dir);

        if(count>256)
                my_err("too many files under this dir",__LINE__);
		

        int i, j, len = strlen(path);
		// ��ȡ��Ŀ¼�����е��ļ���
        dir = opendir(path);
        for(i = 0; i < count; i++){
                ptr = readdir(dir);
                if( ptr == NULL){
                        my_err("readdir",__LINE__);
                }
                strncpy(filenames[i],path,len);
                filenames[i][len] = '\0';
                strcat(filenames[i],ptr->d_name);
                filenames[i][len+strlen(ptr->d_name)] = '\0';
        }

		// ʹ��ð�ݷ����ļ�����������������ļ�������ĸ˳��洢��filenames
        for(i = 0; i < count-1; i++)
                for(j = 0; j < count-1-i; j++) {
                        if( strcmp(filenames[j],filenames[j+1]) > 0 ) {
                                strcpy(temp,filenames[j+1]);
                                temp[strlen(filenames[j+1])] = '\0';
                                strcpy(filenames[j+1],filenames[j]);
                                filenames[j+1][strlen(filenames[j])] = '\0';
                                strcpy(filenames[j], temp);
                                filenames[j][strlen(temp)] = '\0';
                        }
                }
        for(i = 0; i < count; i++)
                display(flag_param, filenames[i]);

        closedir(dir);

        // �����������û��-lѡ���ӡһ�����з�
        if( (flag_param & PARAM_L) == 0)
                printf("\n");}


int main(int argc, char ** argv)
{
	int		i, j, k, num;
	char		path[PATH_MAX+1];
	char		param[32];	      // ���������в�����Ŀ���ļ�����Ŀ¼�����ڴ���
	int		flag_param = PARAM_NONE; // ������־�������࣬���Ƿ���-l��-aѡ��
	struct stat	buf;


	/*�����в����Ľ���������-l��-a��-al��-laѡ��*/
	j   = 0,
	num = 0;
	for (i=1; i<argc; i++) {
		if (argv[i][0] == '-') {
			for(k=1; k < strlen(argv[i]); k++,j++) {
				param[j] = argv[i][k];	// ��ȡ-����Ĳ������浽����param��
			}
		num++;  // ����"��"�ĸ���
		}
	}
	
	/*ֻ֧�ֲ���a��l�������������ѡ��ͱ���*/
	for(i=0; i<j; i++) {
		if (param[i] == 'a') {
			flag_param |= PARAM_A;
			continue;
		} else if (param[i] == 'l') {
			flag_param |= PARAM_L;
			continue;
		} else {
			printf("my_ls: invalid option -%c\n", param[i]);
			exit(1);
		}
	}
	param[j] = '\0';
	
	// ���û�������ļ�����Ŀ¼������ʾ��ǰĿ¼
	if ((num + 1) == argc) {	
		strcpy(path, "./");
		path[2] = '\0';
		display_dir(flag_param, path);
		return 0;
	}

	i=1;
	do {
		// �������Ŀ���ļ�����Ŀ¼��������һ�������в���
		if (argv[i][0] == '-') { 
			i++;
			continue;	
		} else {
			strcpy(path, argv[i]);

			// ���Ŀ���ļ���Ŀ¼�����ڣ������˳�����
			if ( stat(path, &buf) == -1 )  
				my_err("stat", __LINE__);	

			if ( S_ISDIR(buf.st_mode) ) {   // argv[i]��һ��Ŀ¼
				// ���Ŀ¼�����һ���ַ�����'/'���ͼ���'/'
				if ( path[ strlen(argv[i])-1 ] != '/') {
					path[ strlen(argv[i]) ] = '/';
					path[ strlen(argv[i])+1 ] = '\0';
				}
				else
					path[ strlen(argv[i]) ] = '\0';

				display_dir(flag_param,path);
				i++;
			}
			else {  //argv[i]��һ���ļ�
				display(flag_param, path);
				i++;
			}
		}
	} while (i<argc);

	return 0;
}
