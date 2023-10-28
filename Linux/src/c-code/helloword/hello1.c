#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
    printf("Hello,World " "Linux " "参数1:%s" "\n", argv[0]);
    if (argc < 2)
	return -1;
    else {
	printf("argc=%d argv[0]=%s argv[1]=%s\n" "\n", argc, argv[0], argv[1]);
    }
    //exit(0);

    printf("hello "\
    "Linux" "\n");
   
    return 0;
}
