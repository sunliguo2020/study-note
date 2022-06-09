#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define LENGTH 100
int main()
{
  int fd,len;
  char str[LENGTH];
  fd = open("hello.txt",O_CREAT|O_RDWR,0755);

  if(fd)
  {
    write (fd,"Hello,Software Weekly",strlen("Hello,Software Weekly"));
    close(fd);
  }
 fd = open("hello.txt",O_RDWR);
 len = read (fd,str,LENGTH);
 //str[len]='\0';
 printf("%s\n",str);
 close(fd);
}
