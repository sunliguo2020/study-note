#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	umask(0);	// �������κ�Ȩ��
	if (creat("example_681.test",S_IRWXU|S_IRWXG|S_IRWXO) < 0) {
		perror("creat");
		exit(1);
	}

	umask(S_IRWXO);	// ���������û�������Ȩ��
	if (creat("example_682.test",S_IRWXU|S_IRWXG|S_IRWXO) < 0) {
		perror("creat");
		exit(1);
	}

	return 0;
}
