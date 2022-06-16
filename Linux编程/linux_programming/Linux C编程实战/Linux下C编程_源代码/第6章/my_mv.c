#include <stdio.h>

int main(int argc, char ** argv)
{
	/*检查参数个数的合法性*/
	if(argc < 3) {
		printf("my_mv <old file> <new file>\n");
		exit(0);
	}

	if (rename(argv[1], argv[2]) < 0) {
		perror("rename");
		exit(1);
	}
	
	return 0;
}
