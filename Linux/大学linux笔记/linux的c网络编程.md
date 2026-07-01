                              ^_^ 大家好，我是丁林松 ^_^
                       ^_^  此教程由山东德州思蓝软件公司提供^_^
   (谨此给拥有linux精神的人，为中国软件的崛起而奋斗！！！）
                   linux  c语言网络编程

                      客户                                 服务器
               socket（）                     socket（）
                     |                                     bind（）
                     |                                        |
  sendto（）/send（）        recv（）/recvfrom（）
                     |                                         |
                     |                                         |
        recv/recvfrom                   listen（）
                    |                                          |
                    |                                          |
                close                             sendto    
   mailslot   pipe  signal   etc......
   windows   
   unix   
   // the net program example 
  #include <stdio.h>
#incldue <stdlib.h>
#include <sys/socket.h>  //struct sockaddr_in  
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h> //strcpy()
#include <netdb.h>
#define port  8888
int main()
{
          int sockfd,n ,rn;
          int circle;
          int process;
          char sendbuf[1024];
          char recvbuf[1024];   // recv and send message 
          struct sockaddr_in addr;
          if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
          {
               printf("  The Socket Buile Error \n");
               return 0;
          }
          memset((char *)&addr,0,sizeof(addr));
          //bzero((char *)&addr,sizeof(addr));
          addr.sin_family=AF_INET;
          addr.sin_addr.s_addr=inet_addr("192.168.1.2");
          addr.sin_port=htons(port);
          strcpy(sendbuf,"hello ,thank you \n\0");
          if((n=sendto(sockfd,sendbuf,sizeof(sendbuf),(struct sockaddr *)&addr,sizeof(addr))<=0)
         {
                    printf(" Send Buffer Error \n");
                    exit(1);
         }
         rn=recvform(sockfd,recvbuf,sizeof(char)*1024,0,(struct sockaddr *)&addr,sizeof(addr));
        if(rn<0)
       {
               printf(" recv from peer host , Error \n");
              exit(0);
         }
         recvbuf[rn]='\0';
         printf(" The Peer Say That  %s " ,recvbuf);
         close(sockfd);
          return 0;
}

                





                   
           
                 
          
         
          

    
      

