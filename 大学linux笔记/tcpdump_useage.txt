                                 详细Tcpdump 的用法
第一种是关于类型的关键字，主要包括host，net，port,
    例如 host 210.27.48.2  指明 210.27.48.2是一台主机，
         net 202.0.0.0     指明 202.0.0.0是一个网络地址，
         port 23           指明端口号是23。如果没有指定类型，缺省的类型是host.

第二种是确定传输方向的关键字，主要包括src , dst ,dst or src, dst and src ,这些关键字指明了传输的方向。
     举例说明，src 210.27.48.2   指明ip包中源地址是210.27.48.2 ,
               dst net 202.0.0.0 指明目的网络地址是202.0.0.0 。
               如果没有指明方向关键字，则缺省是src or dst关键字。

第三种是协议的关键字，主要包括fddi,ip,arp,rarp, tcp,udp等类型。
    Fddi指明是在FDDI(分布式光纤数据接口网络)上的特定的网络协议，实际上它是"ether"的别名，fddi和ether具有类
似的源地址和目的地址，所以可以将fddi协议包当作ether的包进行处理和分析。其他的几个关键字就是指明了监听的包的
协 议内 容。如果没有指定任何协议，则tcpdump将会监听所有协议的信息包。

  除了这三种类型的关键字之外，其他重要的关键字如下：gateway, broadcast,less,greater,还有三种逻辑运算，取非
  运算是 'not ' '! ', 与运算是'and','&&';或运算 是'or' ,'││'；这些关键字可以组合起来构成强大的组合条件来满
  足人们的需要，下面举几个例子来说明。
    普通情况下，直接启动tcpdump将监视第一个网络界面上所有流过的数据包。
[root@slg ~]# tcpdump 
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), capture size 96 bytes
19:01:30.190127 arp who-has 192.168.1.1 tell 192.168.1.30
19:01:30.190559 arp reply 192.168.1.1 is-at 00:0a:eb:b3:f4:da (oui Unknown)
19:01:30.190574 IP 192.168.1.30.filenet-tms > 202.108.249.147.domain:  35372[1au] AAAA? hi.baidu.com. (41)
19:01:30.201200 IP 202.108.249.147.domain > 192.168.1.30.filenet-tms:  35372*-1/4/5 CNAME[|domain]
19:01:30.201804 IP 192.168.1.30.filenet-tms > 202.108.22.102.domain:  25331AAAA? hi.a.shifen.com. (33)

使用-i参数指定tcpdump监听的网络界面，这在计算机具有多个网络界面时非常有用，
使用-c参数指定要监听的数据包数量，
使用-w参数指定将监听到的数据包写入文件中保存

 A想要截获所有210.27.48.1 的主机收到的和发出的所有的数据包：
#tcpdump host 210.27.48.1

B想要截获主机210.27.48.1 和主机210.27.48.2 或210.27.48.3的通信，使用命令：（在命令行中使用括号时,一定要
#tcpdump host 210.27.48.1 and \ (210.27.48.2 or 210.27.48.3 \)

C如果想要获取主机210.27.48.1除了和主机210.27.48.2之外所有主机通信的ip包，使用命令：
#tcpdump ip host 210.27.48.1 and ! 210.27.48.2

D如果想要获取主机210.27.48.1接收或发出的telnet包，使用如下命令：
#tcpdump tcp port 23 host 210.27.48.1

E 对本机的udp 123 端口进行监视 123 为ntp的服务端口
# tcpdump udp port 123
  
F 系统将只对名为hostname的主机的通信数据包进行监视。主机名可以是本地主机，也可以是网络上的任何一台计算机。下面的命令可以读取主机hostname发送的所有数据：
#tcpdump -i eth0 src host hostname

G 下面的命令可以监视所有送到主机hostname的数据包：
#tcpdump -i eth0 dst host hostname

H  我们还可以监视通过指定网关的数据包：
#tcpdump -i eth0 gateway Gatewayname

I 如果你还想监视编址到指定端口的TCP或UDP数据包，那么执行以下命令：
#tcpdump -i eth0 host hostname and port 80

J 如果想要获取主机210.27.48.1除了和主机210.27.48.2之外所有主机通信的ip包
，使用命令：
#tcpdump ip host 210.27.48.1 and ! 210.27.48.2

K 想要截获主机210.27.48.1 和主机210.27.48.2 或210.27.48.3的通信，使用命令
：（在命令行中适用　　　括号时，一定要
#tcpdump host 210.27.48.1 and \ (210.27.48.2 or 210.27.48.3 \)

L 如果想要获取主机210.27.48.1除了和主机210.27.48.2之外所有主机通信的ip包，使用命令：
　　　#tcpdump ip host 210.27.48.1 and ! 210.27.48.2

M 如果想要获取主机210.27.48.1接收或发出的telnet包，使用如下命令：
　　　#tcpdump tcp port 23 host 210.27.48.1

如果在ethernet 使用混杂模式 系统的日志将会记录

May  7 20:03:46 localhost kernel: eth0: Promiscuous mode enabled.
May  7 20:03:46 localhost kernel: device eth0 entered promiscuous mode
May  7 20:03:57 localhost kernel: device eth0 left promiscuous mode

tcpdump 对截获的数据并没有进行彻底解码，数据包内的大部分内容是使用十六进制的形式直接打印输出的。显然这不利于分析网络故障
，通常的解决办法是先使用带-w参数的tcpdump 截获数据并保存到文件中，然后再使用其他程序进行解码分析。当然也应该定义过滤规则
，以避免捕获的数据包填满整个硬盘
