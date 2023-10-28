#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <dir.h>

#define DIRNAME "testdir.$$$"

int main(void)
{
    int stat;

    stat = mkdir(DIRNAME);
    if (!stat)
           printf("Directory created\n");
    else
    {
       printf("Unable to create directory\n");
       exit(1);
    }

    getch();
    system("dir/p");
    getch();

    stat = rmdir(DIRNAME);
    if (!stat)
           printf("\nDirectory deleted\n");
    else
    {
           perror("\nUnable to delete directory\n");
       exit(1);
    }

    return 0;
}