各项服务的中文解释.
============================================================================================
acpid--- Advanced Configuration an Power Interface even daemon .Listen and dispatch ACPI events from the kernel 强大的ACPI电源管理,内核直接集成. 
alsasound--Alsa 声卡驱动程序支持。
anacron---和cron相似的任务调度器
apmd－－apmd用来监视系统用电状态，并将相关信息通过syslogd写入日志。也可以用来在电源不足时关机
arpwatch－－用来维护以太网物理地址和ip地址的对应关系
atd－－运行用户用at命令调度的任务。也在系统负荷比较低时运行批处理任务
autofs－－当您需要时自动转载文件系统，而当您不需要时自动卸载
avahi-daemon--This is a daemon which runs on client machines to perform Zeroconf service discovery on a network.avahi-daemon must be running on
systems that use Avahi for service discovery.Avahi-daemon should not be running other wise.
avahi-dnsconfd--connects to a running avahi-daemon and runs the script 
chargen－－tcp版本的chargen server
chargen-udp－－udp版本的chargen server
crond－－周期地运行用户调度的任务。比起传统的unix版本添加了不少属性，而且更安全，配置更简单
cups－－cups(Common UNIX Printing System)
cpuspeed--监视系统空闲百分比，降低或加快CPU时钟速度和电压从而在系统空闲是将能源消耗降为最小，而在系统繁忙时最大化加快系统执行速度。
daytime－－tcp版本的daytime server
daytime-udp－－udp版本的daytime server
dhcpd--动态主机控制协议的服务守护进程。
echo－－tcp版本的echo server
echo-udp－－udp版本的echo server
eklogin－－接受rlogin会话鉴证和用kerberos5加密的一种服务
finger－－用于应答finger请求的服务
firstboot--Firstboot is a druid style program that runs on the first time a
machine is booted after install. It checks for the existence of an
/etc/sysconfig/firstboot file. If it doesn't find the file 
gpm－－为文本模式下的linux程序提供了鼠标的支持。它也支持控制台鼠标的拷贝，粘帖操作以及弹出式菜单 (必须)
gssftp－－接受可被kerberos5验证的ftp连接
haldaemon接受由udev通过D—BUS传递来的消息后调fstab－sysc修改fstab文件，动态创建／media目录下的子目录作为挂载点。
httpd－－http是著名的www服务器，可用来提供html文件以及cgi动态内容服务
identd－－提供验证身份的方法
ipchains－－ipchains包过滤防火墙
iptables－－iptables包过滤防火墙
ipvsadm－－调用ipvsadm来建立和维护ipvs路由选择表
isdn－－启用isdn(综合服务数字网)服务
kadmin－－更改在主控kdc中使用本机的kadmin工具，或透过kadmin服务来完成
kdcrotate－－设置配置文件/etc/krb5.con中的kdcs表项
keytable－－该程序的功能是转载您在/etc/sysconfig/keyboards里说明的键盘映射表
klogin－－接受bsd方式的rlogin会话，但需要使用kerbeos5验证
kprop－－是否允许kdc接收来的master kdc的升级
krb5-telnet－－允许普通的telnet登陆，但也可使用kerberos5验证
krb524－－是以改变kerberos5到kerberosIV的赁证
krb5kdc－－开启kerberosIV和5所需的连接以获得赁证
kshell－－接受rshell命令鉴证和用kerberos加密的服务
kudzu－－运行硬件检测，并可选择性地设置硬件变化
linuconf
允许那些GUI的系统管理员在运行某个GUI任务过程中的任何时刻调用Linuxconf程序，对他们的系统设置值进行维护或修改。
lpd－－lpd是系统打印守护程序，负责将lpr等程序提交给打印作业
messagebus--负责在各个系统进程之间传递消息。
netfs－－负责装载/卸载nfs、samba、ncp文件系统
network－－激活/关闭启动时的各个网络接口 （必须）
nfs－－nfs是一个流行的基于tcp/ip网络的文件共享协议.该服务提供了nfs文件共享服务
nfslock－－提供nfs文件上锁功能
nscd－－该服务负责密码和组的查询，并且缓冲查询结果
pcmcia 用来管理使用PCMIA槽的笔记本电脑的外设
portmap－－portmap用来支持rpc连接，rpc被用于nfs以及nis等服务
postgresql－－postgresql关系数据库引擎
random－－保存和恢复系统的高质量随机数生成器，这些随机数是系统一些随机行为提供的
rlogin－－rlogin程序服务，提供来自远程信任主机的注册功能
routed－－该守护程序支持rip协议的自动ip路由表维护.rip主要使用在小型网络上，大一点的网络就需要复杂一点的协议
rsh－－提供rcmd程序或者rsh程序的服务
rstatd－－rstat协议允许网络上的用户获得同一网络上各机器的性能参数
rsync－－对ftp服务的一个很好的附加，允许循环码求和校验等
rusersd－－该服务使网络用户可以定位同一网络上的其他用户
rwalld－－rwall协议允许远程用户向在同一系统中活跃着的终端发送消息，类似wall的本地行为
rwhod－－允许远程用户获得运行rwho精灵的机器上所有已登录用户的列表，与finger类似
sendmai 服务管理着你从一台计算机发向另一台计算机的电子邮件.
smb－－启动和关闭smbd和nmbd精灵程序以提供smb网络服务
snortd－－一个轻量级的网络入侵检测工具
swat－－samba网络配置工具，可以通过流览器的901端口连接使用swat
syslog－－syslog是操作系统提供一种机制，守护程序通常使用这些机制将各种信息写到各个系统日志文件 (必须)
telnet－－提供telnet服务，使用未加密的用户/密码组进行验证
time－－tcp版本的rfc 868 time server
time-udp－－udp版本的rfc 868 time server
udev－－负责动态维护/dev目录，使/dev目录和当前的系统状态保持一致，创建/dev/sdax等设备文件。
webmin－－webmin是基于web的集系统管理与网络管理于一身的强大管理工具
xfs－－在引导和关闭时启动和停上x字体服务，并可能重新生成字体表 (必须)
xinetd－－因特网操作服务程序。提供类似于inetd+tcp_wrapper的功能，但是更加强大和安全，监控网络对各种它管理的服务的需求，并在要的时候启动相应的服务程序
ypbind－－实现网络信息服务的服务器端

redhat 下常用服务介绍

anacron 不考虑系统downtime期间的cron服务
amd 自动安装NFS守候进程
apmd 高级电源管理
arpwatch 记录日志并构建一个在LAN接口上看到的以太网地址和IP地址对数据库
atd 用于at和batch的服务
autofs 自动安装管理进程automount,与NFS相关,依赖于NIS
crond 为Linux下自动安排的进程提供运行服务.
Gpm 提供字符模式下对鼠标的支持.
Keytable 用于装载键盘镜像
Kudzu 硬件探测器
Netfs 安装和卸载NFS、SAMBA和NETWARE网络文件系统
Network 激活已配置网络接口的脚本程序
Nfslock NFS锁定
Pcmcia 安装pcmcia卡（一般用于笔记本电脑）
Sshd OpenSSH服务器
Syslog 一个让系统引导时启动syslog和klogd系统日志守候里程的脚本
Xfs Xwindow字型服务器，为本地和远程X服务器提供字型集
Xinetd 支持多种网络服务的核心守候程序。
