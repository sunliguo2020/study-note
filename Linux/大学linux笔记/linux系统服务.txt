linux系统服务详解FC5

  linux系统中的服务与windows是截然不同的，今天开始正式来了解linux的服务，Linux在启动统服务向本地和网络用户提供了Linux的系统功能接口，直接面向应用程序和用户。但是，开启不必要或有漏洞的服务则会给操作系统带来安全和性能上的影响。所有我们应该了解各个服务的功能,以关闭不需要的服务.下面是详细说明.（为了详尽把我现在系统FC5中出现的全部载录，有部分暂时没去找中文文档的，就用系统自带描述，一般也能够从描述中读懂）
1、acpid
Listen and dispatch ACPI events from the kernel
强大的ACPI电源管理内核直接集成

2、alsasound
Alsa 声卡驱动程序支持。Alsa声卡驱动程序本来是为了一种声卡Gravis UltraSound(GUS)而写的，该程序被证明很优秀，于是作者就开始为一般的声卡写驱动程序。 Alsa和OSS/Free 及OSS/Linux兼容，但是有自己的接口，甚至比OSS优秀。

3、anacron
Run cron jobs that were left out due to downtime
Redhat 系统自带的cron守护进程

4、amd
运行automount精灵程序，该精灵在必要时自动安装一些本地设备和NFS文件系统。

5、apmd
apmd is used for monitoring battery status and logging it via syslog(8). It can also be used for shutting down the machine when the battery is low.
apmd用来监视系统用电状态，并将相关信息通过syslogd 写入日志。也可以用来在电源不足时关机。

6、arpwatch
该程序主要用来维护以太网物理地址和IP地址的对应关系。

7、atalk
AppleTalk精灵程序。注意不要在后台运行该程序，该程序的数据结构必须在运行其他进程前先花一定时间初始化。

8、atd
Runs commands scheduled by the at command at the time specified when at was run, and runs batch commands when the load average is low enough.
运行用户用At命令调度的任务。也在系统负荷比较低时运行批处理任务。

9、autofs
当您需要时自动转载文件系统，而当您不需要时自动卸载。

10、avahi-daemon:This is a daemon which runs on client machines to perform Zeroconf service discovery on a network. avahi-daemon must be running on systems  that use Avahi for service discovery. Avahi-daemon should not be running otherwise.
11、avahi-dnsconfd：connects to a running avahi-daemon and runs  the  script
12、bootparamd（FC5没有）
该服务允许老的Sun工作站从Linux网络启动，它和rarp 现在很少使用，基本上被bootp和dhcp取代了。
13、Bluetooth services for service discovery, authentication, Human Interface Devices, etc.
14、cpu speed:Run dynamic CPU speed daemon
15、crond
cron是Unix下的一个传统程序，该程序周期地运行用户调度的任务。比起传统的Unix版本，Vixie版本添加了不少属性，而且更安全，配置更简单。
dhcpd 该精灵提供了对动态主机控制协议(Dynamic Host Control Protocol)的访问支持。
16、cpus:Startup/shutdown script for the Common UNIX Printing System (CUPS).
基于unix系统的打印服务
17、cpus-config-deamon:This is a daemon for configuring printers through D-BUS
18、dhcdbd provides D-BUS control of the ISC DHCP client, dhclient,
18、diskdump：Save dump file if previous system crashed and initialize diskdump module.
19、firstboot:Firstboot is a druid style program that runs on the first time a machine is booted after install.  It checks for the existence of an /etc/sysconfig/firstboot file.  If it doesn't find the file, then the firstboot program needs to run.  If it finds the file, firstboot will not be run.
20、gated
gated通过一个数据库提供了网络路由功能支持。它支持各种路由协议，包括RIP版本1和2、DCN HELLO协议、 OSPF版本2以及EGP版本2到4。
21、gpm：GPM adds mouse support to text-based Linux applications such as the Midnight Commander. It also allows mouse-based console cut-and-paste operations, and includes support for pop-up menus on the console.
gpm为文本模式下的Linux程序如mc(Midnight Commander)提供了鼠标的支持。它也支持控制台下鼠标的拷贝，粘贴操作以及弹出式菜单。
22、haldaemon:This is a daemon for collecting and maintaing information about hardware from several sources. See http://www.freedesktop.org/Software/hal
23、httpd：Apache is a World Wide Web server.  It is used to serve HTML files and CGI.

hidd
http是著名的www服务器，可用来提供HTML文件以及CGI动态内容服务。
24、iptables: Starts, stops and saves iptables firewall
25、irda:IrDA(TM) (Infrared Data Association) is an industry standard for wireless, infrared communication between devices. IrDA speeds range from 9600 bps to 4 Mbps, and IrDA can be used by many modern devices including laptops, LAN adapters, PDAs, printers, and mobile phones.
25、irqbalance:The irqbalance daemon will distribute interrupts across the cpus on a multiprocessor system with the purpose of spreading the load. processname: irqbalance
26、inetd 
因特网操作服务程序。监控网络对各种它管理的服务的需求，并在必要的时候启动相应的服务程序。通常，inetd 管理的程序有telnet、ftp、rsh和rlogin。关闭inetd也就关闭了这些由它管理的服务。
27、innd
inn是最流行的用户组新闻服务器。它允许您建立起本地新闻服务器。配置有一定的难度，可以先阅读/usr/doc/ inn*文档获得帮助。
28、keytable 该程序的功能是转载您在/etc/sysconfig/keyboards里说明的键盘映射表，该表可以通过kbdconfig工具进行选择。您应该使该程序处于激活状态。
29、kudzu:This runs the hardware probe, and optionally configures changed hardware.
30、ldap
LDAP代表Lightweight Directory Access Protocol，实现了目录访问协议的行业标准。
31、linuxconf
linuxconf是Linux下的一个有效的系统配置工具，该服务允许远程运行。
32、lpd
lpd是系统打印守护程序，负责将lpr等程序提交给打印作业。
33、mcserv
34、Midnight Commander服务进程允许远程机器上的用户 通过Midnight Commander文件管理器操作本机文件。服务进程用PAM来验证用户，需要给出“用户名/口令” 以通过验证。
35、mdmonitor:software RAID monitoring and management
36、mdmpd:multipath device monitoring and management
37、messagebus:This is a daemon which broadcasts notifications of system events and other messages. See http://www.freedesktop.org/software/dbus/
38、mysql 一个快速高效可靠的轻型SQL数据库引擎。
39、named 域名服务器，将Internet主机名解析为点分的IP地址。
40、netdump:Initialize console side of netconsole and netcrashdump facility
41、netfs 负责装载/卸载NFS、Samba、NCP(Netware)文件系统。
42、netplugd:netplugd is a daemon for managing non-static network interfaces.
43、network 激活/关闭启动时的各个网络接口。
44、nfs
NFS是一个流行的基于TCP/IP网络的文件共享协议。该服务提供了NFS文件共享服务，具体的配置在/etc/ exports文件里。
45、nfslock:NFS is a popular protocol for file sharing across TCP/IP networks. This service provides NFS file locking functionality.
46、nscd该服务负责密码和组的查询，并且缓冲查询结果。如果您的系统有比较慢的服务(如NIS和NIS+)，则应该启动该服务。
47、ntpd:ntpd is the NTPv4 daemon. The Network Time Protocol (NTP) is used to synchronize the time of a computer client or server to another server or reference time source, such as a radio or satellite receiver or modem.
48、pcmcia pcmcia主要用于支持笔记本电脑。
49、portmap portmap用来支持RPC连接，RPC被用于NFS以及NIS 等服务。
50、postgresql PostgreSQL关系数据库引擎。
51、proftpd proftpd是Unix下的一个配置灵活的ftp守护程序。
52、psact:Starts and stops process accounting
53、radvd 路由广播程序。
54、random
保存和恢复系统的高质量随机数生成器，这些随机数是系统一些随机行为提供的。
55、rdisc:This is a daemon which discovers routers on the local subnet.
56、readahead:This service causes the programs used during startup to be loaded into memory before they are needed, thus improving startup performance
57、readahead_early:
58、rpcgssd:Starts user-level daemon that manages RPCSEC GSS contexts for the NFSv4 client.
59、rpcidmapd:Starts user-level daemon for NFSv4 that maps user names to UID and GID numbers.
60、rpcsvcgssd:Starts user-level daemon that manages RPCSEC GSS contexts for the NFSv4 server.
61、routed
该守护程序支持RIP协议的自动IP路由表维护。RIP主要使用在小型网络上，大一点的网络就需要复杂一点的协议。
62、rstatd Rstat协议允许网络上的用户获得同一网络上各机器的性能参数。
63、rusersd 该服务使网络用户可以定位同一网络上的其他用户。
64、rwalld
Rwall协议允许远程用户向在同一系统中活跃着的终端发送消息，类似wall的本地行为。
65、rwhod
允许远程用户获得运行rwho精灵的机器上所有已登录用户的列表，与finger类似。
66、saslauthd:saslauthd is a server process which handles plaintext authentication requests on behalf of the cyrus-sasl library.
67、sendmail 大名鼎鼎的邮件服务器。
68、smartd
69、smb:Starts and stops the Samba smbd and nmbd daemons used to provide SMB network services.
smb 启动和关闭smbd和nmbd精灵程序以提供SMB网络服务。
70、spamassassin:spamd is a daemon process which uses SpamAssassin to check email messages for SPAM.  It is normally called by spamc from a MDA.
71、sshd:OpenSSH server daemon
72、snmpd 简单网络管理协议(SNMP)的守护精灵。
73、syslog
syslog是操作系统提供的一种机制，守护程序通常使用这种机制将各种信息写到各个系统日志文件。通常应该启动该服务。
74、vncserver:Starts and stops vncserver. used to provide remote X administration services.
75、Vsftpd is a ftp daemon, which is the program that answers incoming ftp service requests.
76、winbind:Starts and stops the Samba winbind daemon
77、wpa_supplicant:wpa_supplicant is a WPA Supplicant for Linux, BSD and Windows with support for WPA and WPA2 (IEEE 802.11i / RSN). Supplicant is the IEEE 802.1X/WPA component that is used in the client stations. It implements key negotiation with a WPA Authenticator and it controls the roaming and IEEE 802.11 authentication/association of the wlan driver.
78、xfs X的字体服务器。
79、ypbind NIS/YP的客户端守护程序。如果您需要使用NIS/YP机器，请启动这项服务，否则，关闭这项服务。
80、yppasswd
让NIS用户能够修改密码。运行在NIS域的服务器上。客户端程序同样也叫yppasswd。
81、ypserv
标准NIS/YP网络协议的一个实现。允许主机名，用户名和其他信息分布于网络各端。运行在NIS服务器上，客户端不需要。
82、yum:Enable daily run of yum, a program updater.
为了提高运行速度，我们一般都会禁用不少服务，在需要的时候在启用，我把自己现在启动的服务用红色标记，供大家参考。

