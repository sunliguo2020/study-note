		Linux下配置完整安全的DHCP服务器详解

	一、建立DHCP服务器配置文件 

　　 dhcpd配置文件是/etc目录中的名为dhcpd.conf的文件。
下面手工建立/etc/dhcpd.conf文件。
/etc/dhcpd.conf通常包括三部分：parameters、declarations 、option。

　　1.DHCP配置文件中的parameters（参数）：表明如何执行任务，是否要执行任务，或将哪些网络配置选项发送给客户。主要内容见表1 
 
   参 数                                           解 释 
 
 ddns-update-style                   	配置DHCP-DNS 互动更新模式。  
 default-lease-time                  	指定确省租赁时间的长度，单位是秒。 
 max-lease-time                      	指定最大租赁时间长度，单位是秒。  
 hardware                            	指定网卡接口类型和MAC地址。  
 server-name                        	通知DHCP客户服务器名称。 
 get-lease-hostnames flag           	检查客户端使用的IP地址。  
 fixed-address ip                   	分配给客户端一个固定的地址。 
 authritative                       	拒绝不正确的IP地址的要求。 

　　2. DHCP配置文件中的declarations （声明）
：用来描述网络布局、提供客户的IP地址等。主要内容见表2： 
 
 声 明                          		解 释 
 
 shared-network     				用来告知是否一些子网络分享相同网络。  
 subnet         				描述一个IP地址是否属于该子网。  
 range 						起始IP 终止IP  提供动态分配IP 的范围。 
 host 						主机名称  参考特别的主机。  
 group  					为一组参数提供声明。  
 allow unknown-clients;deny unknown-client 	是否动态分配IP给未知的使用者。  
 allow bootp;deny bootp  			是否响应激活查询。  
 allow booting;deny booting 			是否响应使用者查询。 
 filename  					开始启动文件的名称，应用于无盘工作站。 
 next-server  					设置服务器从引导文件中装如主机名，应用于无盘工作站。 


　　3. DHCP配置文件中的option（选项）：用来配置DHCP可选参数，全部用option关键字作为开始，主要内容包括见表3： 
 
 选 项  				 解 释 
 
 subnet-mask  				为客户端设定子网掩码。  
 domain-name  				为客户端指明DNS名字。  
 domain-name-servers  			为客户端指明DNS服务器IP地址。 
 host-name  				为客户端指定主机名称。  
 routers  				为客户端设定默认网关。  
 broadcast-address  			为客户端设定广播地址。  
 ntp-server  				为客户端设定网络时间服务器IP地址。 
 time－offset  				为客户端设定和格林威治时间的偏移时间，单位是秒。


　　这是一个Ｃ类网络，共126个IP地址可以分配的例子。

 ddns-update-style interim; 
ignore client-updates;
subnet 192.168.1.0 netmask 255.255.255.0 {

    option routers          192.168.1.254;
    option subnet-mask      255.255.255.0;
    option broadcast-address        192.168.1.255;
    option domain-name-servers      192.168.1.3;
    option domain-name          "www.cao.com";　#DNS名称#

    option domain-name-servers  192.168.1.3;
    option time-offset      -18000; 
    range dynamic-bootp 192.168.1.128 192.168.1.255;
    default-lease-time 21600;
    max-lease-time 43200;
        host ns {
        hardware ethernet 52:54:AB:34:5B:09;#运行DHCP的网络接口的MAC地址#
        fixed-address 192.168.1.9;
    }
}

二、建立客户租约文件 

　　运行DHCP服务器还需要一个名为 dhcpd.leases 的文件，保持所有已经分发出去的 IP 地址。在Redhat Linux 发行版本中，该文件位于 /var/lib/dhcp/ 目录中。如果您通过 RPM 安装 ISC DHCP，那么该目录应该已经存在。dhcpd.leases的文件格式为： 
 
 Leases address ｛statement｝ 

　一个典型的文件内容如下： 

lease 192.168.1.255 {             #DHCP服务器分配的IP地址#
  starts 1 2005/05/02 03:02:26;    # lease 开始租约时间#
  ends 1 2005/05/02 09:02:26;       # lease 结束租约时间# 
  binding state active;
  next binding state free;
  hardware ethernet 00:00:e8:a0:25:86;  #客户机网卡MAC地址#
  uid "%content%01%content%00%content%00\350\240%\206";   #用来验证客户机的UID标示#
  client-hostname "cjh1";    #客户机名称#
}
 
 
　　注意lease 开始租约时间和lease 结束租约时间是格林威治标准时间（GMT），不是本地时间。
　　第一次运行DHCP服务器时dhcpd.leases是一个空文件，也不用手工建立。如果不是通过 RPM 安装 ISC DHCP，或者 dhcpd 已经安装，那么您应该试着确定 dhcpd 将其 lease 文件写到何处，并确保该文件存在。也可以手工建立一个空文件： 
 
 #touch /var/lib/dhcp/dhcpd.leases 
 
三、启动和检查DHCP服务器 

　　使用命令启动DHCP服务器：  #service dhcpd start 
 
　　使用ps命令检查dhcpd进程： 
 
 #ps -ef | grep dhcpd
root      2402     1  0 14:25 ?        00:00:00 /usr/sbin/dhcpd
root      2764  2725  0 14:29 pts/2    00:00:00 grep dhcpd 
 
　　使用检查dhcpd运行的端口：  
 
 # netstat -nutap | grep dhcpd
udp   0  0 0.0.0.0:67         0.0.0.0:*              2402/dhcpd 

四、配置DHCP客户端 

通常网管员使用选择手工配置 DHCP 客户，需要修改 /etc/sysconfig/network 文件来启用联网；并修改 /etc/sysconfig/network-scripts 目录中每个网络设备的配置文件。在该目录中，每个设备都有一个叫做 ifcfg-eth？ 的配置文件，eth？是网络设备的名称。 如eth0等。如果你想在引导时启动联网，NETWORKING 变量必须 被设为 yes。 除了此处之外/etc/sysconfig/network 文件应该包含以下行： 

NETWORKING=yes
DEVICE=eth0
BOOTPROTO=dhcp
ONBOOT=yes

五、DHCP配置常见错误排除 

　　通常配置DHCP 服务器很容易，不过，在这里有一些技巧可以帮助您避免出现问题。对服务器而言，要确保网卡正常工作，并具备广播功能。对客户机而言，还要确保客户机的网卡正常工作。最后，要考虑网络的拓扑，并考虑客户机向 DHCP 服务器发出的广播消息是否会受到阻碍。另外如果dhcpd进程没有启动，那么可以浏览 syslog 消息文件来确定是哪里出了问题。这个消息文件通常是 /var/log/messages。 
　　典型故障： 
　　1.DHCP服务器配置完成，没有语法错误。但是网络中的客户机却没办法取得IP地址。 

　　通常是Linux DHCP服务器沒有办法接收來自255.255.255.255 的 DHCP 客户机的Request 封包造成的。一般是Linux DHCP服务器的网卡没有设置具有MULTICAST功能。为了让dhcpd(dhcp程序的守护进程)能够正常的和DHCP客户机沟通，dhcpd必须传送封包到255.255.255.255这个IP地址，但是有些Linux系统里255.255.255.255这个IP地址被用来做为监听区域子网域（local subnet）广播的 IP地址，所以需要在路由表（routing table）里加入255.255.255.255以激活MULTICAST功能； 

　　使用命令：  
 route add -host 255.255.255.255 dev eth0 
　　如果报告错误消息：255.255.255.255：Unkown host 
　　那么请先修改/etc/hosts加入一行： 
　　255.255.255.255 dhcp 
　　2. DHCP客户端程序和DHCP服务器不兼容 
　　由于Linux有许多发现版本，不同版本使用DHCP客户端程序和DHCP服务器也不相同。Linux提供了四种DHCP客户端程序：pump, dhclient, dhcpxd, 和dhcpcd。了解不同Linux发行版本的服务器端和客户端程序对于常见错误排除是必要的。笔者曾经遇到过使用SuSE Linux 9.1 DHCP服务器和使用Mandrake Linux 9.0客户机不兼容的情况。此时就必须更换客户端程序。方法是先停止客户机的网络服务，卸载原程序，安装和服务器端兼容程序。附表：主要Linux发行版使用的DHCP客户端。 
 
  发行版本 
  缺省 DHCP客户端 
  可选 DHCP 客户端 
  DHCP客户端启动脚本 
  附加配置文件 
 
 Red Hat Linux 9.0 
 dhclient 
 无 
 /sbin/ifup 

/etc/sysconfig/network
/etc/sysconfig/network-scripts/ifcfg-eth0 
 Debian Linux 3.0 
 dhclient 
 无 
 /sbin/ifup 
/etc/network/interfaces
/etc/dhclient.conf
 Mandrake Linux 9.1 
 dhclient 
 dhcpcd, dhcpxd, pump 
 /sbin/ifup 
/etc/sysconfig/network
/etc/sysconfig/network-scripts/ifcfg-eth0
/etc/dhclient-eth0.conf 
 SuSE Linux 9.1 
 dhcpcd 
 dhclient 
 /sbin/ifup-dhcp 
/etc/sysconfig/network/dhcp
/etc/sysconfig/network/ifcfg-eth0

六、DHCP服务器的安全 
　　1. 在指定网络接口启动DHCP服务器 

　　如果你的Linux系统连接了不止一个网络界面，但是你只想让 DHCP 服务器启动其中之一，你可以配置 DHCP 服务器只在那个设备上启动。在 /etc/sysconfig/dhcpd 中，把界面的名称添加到 DHCPDARGS 的列表中： 
 
 DHCPDARGS=eth0 
　　或者直接使用命令：  
 Echo "DHCPDARGS=eth0" >> /etc/ sysconfig/dhcpd 
 
　　这样对于带有两个网卡的防火墙机器，更加安全：一个网卡可以被配置成 DHCP 客户来从互联网上检索 IP 地址；另一个网卡可以被用作防火墙之后的内部网络的 DHCP 服务器。仅指定连接到内部网络的网卡使系统更加安全，因为用户无法通过互联网来连接它的守护进程。 
　　2. 让DHCP服务器在监牢中运行 
　　所谓"监牢"就是指通过chroot机制来更改某个软件运行时所能看到的根目录，即将某软件运行限制在指定目录中，保证该软件只能对该目录及其子目录的文件有所动作，从而保证整个服务器的安全。这样即使出现被破坏或被侵入，所受的损失也较小。
　　将软件chroot化的一个问题是该软件运行时需要的所有程序、配置文件和库文件都必须事先安装到chroot目录中，通常称这个目录为chroot jail（chroot"监牢"）。如果要在"监牢"中运行dhcpd，而事实上根本看不到文件系统中那个真正的目录。因此需要事先创建目录，并将dhcpd复制到其中。同时dhcpd需要几个库文件，可以使用ldd（library Dependency Display缩写）命令，ldd作用是显示一个可执行程序必须使用的共享库。 
 

ldd dhcpd
        libc.so.6 => 
/lib/tls/libc.so.6 (0x42000000)
        /lib/ld-linux.so.2 
=> /lib/ld-linux.so.2 (0x40000000)
style='font-family:宋体'>

　　这意味着还需要在"监牢"中创建lib目录，并将库文件复制到其中。手工完成这一工作是非常麻烦的，此时可以用jail软件包来帮助简化chroot"监牢"建立的过程。 
　　(1)Jail软件的编译和安装 
　　Jail官方网站是：http://www.jmcresearch.com/ ，最新版本：1.9a。
 
 #Wget http://www.jmcresearch.com/stati ... il/jail_1.9a.tar.gz 
#tar xzvf jail.tar.gz; cd jail/src
#make; make install 
 
　　(2)用jail创建监牢 
　　jail软件包提供了几个Perl脚本作为其核心命令，包括mkjailenv、addjailuser和addjailsw。
　　mkjailenv：创建chroot"监牢"目录，并且从真实文件系统中拷贝基本的软件环境。addjailsw：从真实文件系统中拷贝二进制可执行文件及其相关的其它文件（包括库文件、辅助性文件和设备文件）到该"监牢"中。addjailuser：创建新的chroot"监牢"用户。
　　首先停止目前dhcpd服务，然后建立chroot目录：  

#/sbin/service dhcpd start
#mkjailenv  /chroot/
mkjailenv

A component of Jail (version 1.9 for linux)



http://www.gsyc.inf.uc3m.es/~assman/jail/



Juan M. Casillas 

Making chrooted environment into /chroot
        Doing preinstall()
        Doing special_devices()

        Doing gen_template_password()

        Doing postinstall()
Done.
 
 
　　下面的例子展示为"监牢"添加dhcpd程序的过程： 
# addjailsw  /chroot/ -P /usr/sbin/dhcpd
addjailsw
A component of Jail (version 1.9 for linux)
http://www.gsyc.inf.uc3m.es/~assman/jail/
Juan M. Casillas 
Guessing dhcpd args(0)
Warning: file /chroot//lib/tls/libc.so.6 exists. Overwritting it
Warning: file /chroot//lib/ld-linux.so.2 exists. Overwritting it
………
Done.
 
 
　　不用在意那些警告信息，因为jail会调用ldd检查dhcpd用到的库文件。而几乎所有基于共享库的二进制可执行文件都需要上述的几个库文件。接下来将dhcpd的相关文件拷贝到"监牢"中： 
 
 #  mkdir -p /chroot/dhcp/etc
# cp /etc/dhcpd.conf /chroot/dhcp/etc/
# mkdir -p /chroot/dhcp/var/state/dhcp
# touch /chroot/dhcp/var/state/dhcp/dhcp.leases 

　　重新启动dhcpd： 
 
 [root@www root]# /chroot/usr/sbin/dhcpd 
 
　　使用ps命令检查dhcpd进程： 
 
 #ps -ef | grep dhcpd
root      2402     1  0 14:25 ?        00:00:00 /chroot/usr/sbin/dhcpd 
root      2764  2725  0 14:29 pts/2    00:00:00 grep dhcpd 
 
　　注意此时进程名称已经改变，使用检查dhcpd运行的端口： 
 # netstat -nutap | grep dhcpd
udp   0  0 0.0.0.0:67         0.0.0.0:*                     2402/dhcpd 
 
　　端口号没有改变。现在dhcpd已经成功运行在"监牢"中。到此为止一个这样，一个完整和安全的 DHCP服务器就完成了。





 
