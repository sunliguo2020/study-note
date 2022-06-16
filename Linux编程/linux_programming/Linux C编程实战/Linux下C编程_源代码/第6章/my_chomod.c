/* �� �ܣ��ı��ļ�����Ȩ�� */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char ** argv)
{
	int	mode;	// Ȩ��
	int	mode_u;	// �����ߵ�Ȩ��
	int	mode_g;	// �������Ȩ��
	int	mode_o;	// �����û���Ȩ��
	char	*path;

	/*�����������ĺϷ���*/
	if(argc < 3) {
		printf("%s <mode num> <target file>\n",argv[0]);
		exit(0);
	}

	/*��ȡ�����в���*/
	mode = atoi(argv[1]);
	if (mode > 777 || mode < 0) {
		printf("mode num error!\n");
		exit(0);
	}
	mode_u = mode / 100;
	mode_g = (mode - (mode_u*100)) / 10;
	mode_o = mode - (mode_u*100) - (mode_g*10);
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o;	// �˽���ת��
	path = argv[2];

	if ( chmod(path, mode) == -1) {
		perror("chmod error");
		exit(1);
	}

	return 0;
}
