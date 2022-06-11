将Linux做代理服务器


需要配置:
CPU: Pentium 133 Mhz
内存: 32 MB
硬盘:640 MB
网卡:2块
(机器配置不符合以上条件请不要尝试安装Linux)

1.安装Linux,选择最小安装，把组件的勾全部去掉,除了配置一下IP,其它全部默认
安装好后进入提示符

2.首先配置网卡,如果用图形界面配置完成后检查一下IP是否正确
ifconfig eth0 #检查网卡0的状态,如果想更改配置文件(命令:vi /etc/sysconfig/network-scripts/ifcfg-eth0) 文件
ifconfig eth1 #检查网卡1的状态,如果想更改配置文件(命令:vi /etc/sysconfig/network-scripts/ifcfg-eth1) 文件
route #检查网关,想更改则用(命令:vi /etc/sysconfig/network)在这里的GATEWAY=后面填加想更改的网关就可以
#用route检查路由的状态,如果读出来很顺利则说明没问题,用PING检测一下内网和外网是否能PING通
3.用IPTABLES 实现双网卡NAT功能,从而实现代理服务器上网
vi /etc/sysconfig/network #首先,编辑这个文件,在文件末尾加上一行( FORWARD_IPV4=yes )只有打开IP中转功能才可以实现NAT
FORWARD_IPV4=yes
vi /etc/rc.d/rc.local #编辑起动批处理文件,在文件末尾添加如下几行 #号为Linux注释语句不用添
iptables -F #清除iptables表
iptables -F -t nat #清除iptables IP nat表
iptables -t nat -A POSTROUTING -o eth0 -s 192.168.0.0/16 -j MASQUERADE #添加新的IPnat表,192.168.0.0/16为局域网IP

echo l>/proc/sys/net/ipv4/ip_forward #启动ip中转功能，至此，重启机器后代理服务器就应该好像差不多可能凑和用了
4.配置系统启动时加载的服务
ntsysv #然后出现一个对话框,只留下iptables服务和networks服务,其它服务的勾全部去掉
vi /etc/grub.conf #如果系统起动时出现一个10秒等待时间对话框,则在这里设置等待时间

在unix/linux下安装配置DHCP服务(转载) 

 
作者：lonelykiller     发表时间：2002/02/23 04:43pm
 
大多数的情况下Linux作为DHCP服务器而windows 95/98作为DHCP客户。Linux也可以作为DHCP客户,即你要安装dhcpcd rpm 软件包 ，Linux作为DHCP服务器，只需要安装dhcpd rpm 包。 

　　一．DHCP服务器工作的前提条件： 

　　为了使DHCP服务器为windows机器服务，你可能需要创建一个到地址255.255.255.255的路由，加这条路由命令到/etc/rc.d/rc.local使得每次启动后自动运行。 

　　#route add -host 255.255.255.255 dev eth0 

　　如果报告错误消息：255.255.255.255：Unkown host 

　　试着加下面的入口到/etc/hosts文件: 

　　#route add -host dhcp dev eth0 。 


　　二．DHCPd后台程序总是读取配置文件/etc/dhcpd.conf, 下面给出一个DHCP配置文件的例子： 

　　#Sample /etc/dhcpd.conf 
ddns-update-style interim;
ignore client-updates;
default-lease-time 1200; 
max-lease-time 9200; 
option subnet-mask 255.255.255.0; 
option broadcast-address 192.168.1.255; 
option routers 192.168.1.1; 
option domain-name-servers 61.139.2.69,202.98.96.68; 
option domain-name "mydomain.org"; 
subnet 192.168.0.0 netmask 255.255.255.0 { 
range 192.168.0.2 192.168.0.100; 
range 192.168.0.110 192.168.1.200; 
} 

　　这将允许DHCP服务器分配两段地址范围给客户192.168.1.10-100或者192.168.1.150-200，如果客户不继续请求DHCP地址则1200秒后释放IP地址，否则最大允许租用的时间为9200秒。 

　　服务器发送下面的参数给DHCP客户机：用255.255.255.0作为子网掩码，用192.168.1.255作为广播地址，用192.168.1.254作为默认网关，用192.168.1.1 and 192.168.1.2作为DNS服务器如果你要为windows客户指定一个WINS服务器，你需要包括下面的选项到dhcpd.conf文件中：option netbios-name-servers 192.168.1.1。 


　　三.你也能为某块网卡指定固定的IP地址，无论何时，这块网卡将总是从DHCP服务器获得固定的IP地址，加下面的语句到/etc/dhcpd.conf: 

　　host haagen { 

　　hardware ethernet 08:00:2b:4c:59:23; 

　　fixed-address 192.168.1.222; 

　　} 

　　也可连写为一行： 

　　host Jephe {hardware ethernet 00:a0:c9:a6:96:33;fixed-address 192.168.1.12;} 

　　你也可为某台机器指定不同的网关地址，名服务器等： 

　　host Jephe {hardware ethernet 00:a0:c9:a6:96:33;fixed-address 192.168.1.12;option routers 192.168.11.5;} 


　　四. 大多数情况下，DHCP的安装不创建一个dhcpd.leases 文件，在你启动DHCP服务器之前，你必须创建空文件dhcpd.leases： 

　　#touch /var/state/dhcp/dhcpd.leases 

　　为启动DHCP服务器，简单地打入 /usr/sbin/dhcpd 或者用#ntsysv把DHCP服务自动启动，这将启动dhcpd在eth0设备上；如果你想在eth1设备上启动dhcpd，则#/usr/sbin/dhcpd eth1；如果为了调试DHCP，则用#/usr/sbin/dhcpd -d -f。 


　　五．两块网卡的情况： 

　　有时你需要在一台安装了两块网卡（作防火墙或网关）的机器上安装DHCP服务，下面的例子指出一台防火墙机器上的一种DHCP设置，因为对外的网卡（internet）不需要提供DHCP服务。 

　　因此这样设置如下： 

　　subnet 192.168.1.0 netmask 255.255.255.0 { 

　　range 192.168.1.2 192.168.1.4; 

　　default-lease-time 86400; 

　　max-lease-time 259200; 

　　option subnet-mask 255.255.255.0; 

　　option broadcast-address 192.168.1.255; 

　　option routers 192.168.1.254; 

　　option domain-name-servers 192.168.1.254; 

　　} 

　　subnet 202.102.34.102 netmask 255.255.255.255 { 

　　} 


　　六． FAQ 

　　a. 为MAC机器固定IP地址？ 

　　当设置MAC机用DHCP功能获得IP地址后，如不知得到何地址，可在MAC机上发送一邮件出去，收信者可通过mail header检查发送者IP地址，而后ping 该IP地址再利用arp命令检查arp缓存中的该IP地址的对应物理地址。 

　　b. 若LAN上有windows机器装上了某DHCP功能的软件，如sygate, wingate之类，则可能其他windows客户会优先去寻找windows DHCP服务器，而不是Linux DHCP服务器。 
 
 
大家知道，DHCP(动态主机配置协议）可以使客户端自动从服务器得到一个IP地址。如何配置DHCP服务器，在Windows 2000 Server中很容易实现。那在Linux中能否实现呢？答案是肯定的，大家知道Linux是非常好的网络操作系统，使用它可以很轻松的搭建一台高性能的DHCP服务器。本文就使用红旗Linux Server 2.0搭建DHCP的过程讲述一下。 

　　首先，我们来看DHCP工作的过程，看一下客户端是通过哪些手段得到IP地址的。当DHCP启动时，TCP/IP初始化并且由客户端发送一个DHCP DISCOVER的报文向DHCP服务器申请一个IP。DHCP服务器收到DHCP DISCOVER后，它将从客户端主机的地址池中为它提供一个尚未被分配的IP地址。该报文信息被返回到上述主机。客户端随后发出一个包含有DHCP服务器提供IP地址的DHCP REQUEST的报文。DHCP服务器向客户端发回一个含有原先被发出IP地址及其分配方案的应答报文。DHCP服务器提供给客户端的IP地址是有时间限制的，DHCP客户端要想继续使用这个IP地址，必须在租期到来时对它进行更新和续借。 

　　配置DHCP服务器的过程： 

　　DHCP服务是通过程序/usr/sbin/dhcpd提供的。在DHCP服务器启动时，dhcpd要读取dhcpd.conf文件的内容(dhcpd.conf保存的是DHCP服务器的配置信息)。dhcpd将客户端租用的信息保存在dhcpd.lease文件中。在DHCP服务器为客户提供IP地址之前，将在这个文件中记录租用的信息。新的租用信息会添加到dhcpd.leases的尾部。为了向一个子网提供DHCP服务，dhcpd需要知道子网的网络号码和子网掩码。还有地址范围等等。 

　　DHCP服务器配置文件内容： 

　　文件名： 

　　/etc/dhcpd.conf 

　　内容： 

　　subnet 192.168.0.0 netmask 255.255.255.0{
 　　range 192.168.0.10 192.168.0.30; 
　　default-lease-time 86400; 
　　max-lease-time 604800;
　　option subnet-mask 255.255.255.0; 
　　option routers 192.168.0.2; 
　　option domain-name "cy.com"; 
　　option broadcast-address 192.168.0.255; 
　　option domain-name-servers 192.168.0.3; } 

　　其中subnet x.x.x.x netmask x.x.x.x 说明IP地址是否属于该子网上，提供子网的一些参数；range x.x.x.x x.x.x.x 是DHCP服务器可以分配的IP地址范围； default-lease-time 设置缺省的IP租用时间，常用的是86400秒(一天)；max-lease-time 最大租用时间。常用的是604800(一周)；option subnet-mask 设置IP地址的子网掩码；option routers 设置在DHCP发布IP地址的同时，把网关发布出去，这一项是用来指明网关的；option domain-name-servers 设置在DHCP发布IP地址的同时,把DNS发布出去，这一项用来指明DNS服务器的IP地址；option broadcast-address 设置该子网的广播地址；option doamin-name 设置DNS域名。 

DHCP还可以把主机的MAC地址和IP捆绑在一起，防止IP地址的乱用。具体方法是，在/etc/dhcpd.conf中输入： 

　　host pc1{
　　　　hardware ethernet xx:xx:xx:xx:xx:xx  
　　　　fixed-address 192.168.0.9; 
　　}  

　　host pc1中的pc1是指定主机的名字；hardware ethernet 指定要捆绑IP地址主机的MAC地址；fixed-address 指定捆绑后的IP地址。 

　　现在配置文件已经有了，但还是不能启动dhcpd，为什么呢？因为我们还没有创建关于dhcpd的租用文件。 

　　现在我们创建dhcpd.leases文件： 

　　#toouch /var/state/dhcp/dhcpd.leases 

　　然后就可以启动DHCP了： 

　　#/etc/rc.d/init.d/dhcpd start 

　　如果希望在每次启动系统的时候也启动DHCPD，请执行命令： 

　　#/sbin/chkconfig --level 3 dhcpd on  

　　chkconfig 命令是检查、设置系统的各种服务。参数 —level <等级代号>指定该系统服务要在哪一个执行等级中开启或关闭，范围是0-7。然后，在Linux客户端的设置netconf在网络设置中把IP地址的获得设置为DHCP。 这样，我们DHCP服务器的配置就完成了。


