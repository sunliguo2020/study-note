在电信和网通之间做vpn桥
Idc(电信机房)-----办公室-----cnc(网通机房)

由于网通机房需访问电信idc机房的数据库等一些原因，须架个vpn,网通直接到电信的速度我就不说了,所以嘛，在中间办公司做了个桥

IDC(电信):
Eth0: 222.77.A.72(公ip)
Eth1:10.59.96.72(内ip)
代码：

[root@idc]cat start_gre.sh
#!/bin/bash
modprobe ip_gre
ip tunnel add netb mode gre remote 218.66.B.45 local 222.77.A.72 ttl 255
ip link set netb up
ip addr add 10.59.96.72 dev netb
ip route add 10.5.0.0/16 dev netb
ip route add 10.59.97.0/24 dev netb

[root@idc]cat stop_gre.sh
#!/bin/bash
ip link set netb down
ip tunnel del netb
 


IDC2CNC(办公室): 
Eth0:10.5.17.101/24 (内ip)
Eth1:218.66.B.45 (电信ip)
Eth2:220.C.22.2 (网通ip)
代码：

[root@idc2cnet ~]# cat /etc/sysconfig/network
NETWORKING=yes
HOSTNAME=idc2cnet.mydomain.com
GATEWAY=218.66.B.60

[root@idc2cnet ~]# cat /etc/rc.local
route add -net X.22.96.34 netmask 255.255.255.255 gw 220.C.22.1

[root@idc2cnet ~]#cat start_idc.sh
#!/bin/bash
modprobe ip_gre
ip tunnel add neta mode gre remote 222.77.A.72 local 218.66.B.45 ttl 255
ip link set neta up
ip addr add 10.5.17.101 dev neta
ip route add 10.59.96.0/24 dev neta

[root@idc2cnet ~]#cat stop_idc.sh
#!/bin/bash
ip link set neta down
ip tunnel del neta
[root@idc2cnet ~]#cat start_cnc.sh
#!/bin/bash
modprobe ip_gre
ip tunnel add cnc mode gre remote X.22.96.34 local 220.C.22.2 ttl 255
ip link set cnc up
ip addr add 10.5.17.101 dev cnc
ip route add 10.59.97.0/24 dev cnc

[root@idc2cnet ~]#cat stop_cnc.sh
#!/bin/bash
ip link set cnc down
ip tunnel del cnc
 


CNC(网通):
Eth0: X.22.96.34(公ip)
Eth1: 10.59.97.254(内ip)
代码：

[root@cnet bin]#cat start_cnc.sh
#!/bin/bash
modprobe ip_gre
ip tunnel add cnc mode gre remote 220.C.22.2 local X.22.96.34 ttl 255
ip link set cnc up
ip addr add 10.59.97.254 dev cnc
ip route add 10.59.96.0/24 dev cnc
ip route add 10.5.0.0/16 dev cnc

[root@cnet bin]#cat stop_cnc.sh
#!/bin/bash
ip link set cnc down
ip tunnel del cnc
 

备注:
注意转发要开net.ipv4.ip_forward=1，iptables要关掉。

iptables开起来也可，但要在iptables做如下操作
代码：

vi /etc/sysconfig/iptables
-A RH-Firewall-1-INPUT -p 47 -j ACCEPT #让gre协议通过
-A RH-Firewall-1-INPUT -s 10.59.0.0/16 -j ACCEPT #让对端和本端内网ip通过
-A RH-Firewall-1-INPUT -s 10.5.0.0/16 -j ACCEPT #让对端和本端内网ip通过
 








在这企业网中计划规划四个VLAN子网对应着四个重要部门，笔者认为这也是小企业最普遍的部门结构，分别是：
VLAN10——综合行政办公室；
VLAN20——销售部；
VLAN30——财务部；
VLAN40——数据中心（网络中心）。
划分VLAN以后，要为每一个VLAN配一个“虚拟接口IP地址”。
VLAN10——192.168.10.1
VLAN20——192.168.20.1
VLAN30——192.168.30.1
VLAN40——192.168.40.1VLAN及路由配置  


1.DES-3326SR三层交换机的VLAN的配置过程：


（1）创建VLAN
DES-3326SR#Config vlan default delete 1 -24 删除默认VLAN(default)包含的端口1-24'
'DES-3326SR#Create vlan vlan10 tag 10 ?创建VLAN名为vlan10，并标记VID为10
DES-3326SR#Create vlan vlan20 tag 20 ?创建VLAN名为vlan20，并标记VID为20
DES-3326SR#Create vlan vlan30 tag 30 ?创建VLAN名为vlan10，并标记VID为30
DES-3326SR#Create vlan vlan40 tag 40 ?创建VLAN名为vlan10，并标记VID为40 


（2）添加端口到各VLAN
DES-3326SR#Config vlan vlan10 add untag 1-6 ?把端口1-6添加到VLAN10
DES-3326SR#Config vlan vlan20 add untag 7-12 ?把端口1-6添加到VLAN20
DES-3326SR#Config vlan vlan30 add untag 13-18 ?把端口1-6添加到VLAN30
DES-3326SR#Config vlan vlan40 add untag 19-24 ?把端口1-6添加到VLAN40 


（3）创建VLAN接口IP


DES-3326SR#Create ipif if10 192.168.10.1/24 VLAN10 state enabled  ?创建虑拟的接口if10给名为VLAN10的VLAN子网，并且指定该接口的IP为192.168.10.1/24。创建后enabled激活该接口。


同样方法设置其它的接口IP：
DES-3326SR#Create ipif if20 192.168.20.1/24 VLAN20 state enabled
DES-3326SR#Create ipif if30 192.168.30.1/24 VLAN30 state enabled
DES-3326SR#Create ipif if40 192.168.40.1/24 VLAN40 state enabled 


（4）路由


当配置三层交换机的三层功能时，如果只是单台三层交换机，只需要配置各VLAN的虚拟接口就行，不再配路由选择协议。因为一台三层交换机上的虚拟接口会在交换机里以直接路由的身份出现，因此不需要静态路由或动态路由协议的配置。


2.DES-3226S二层交换机的VLAN的配置过程：


（1）创建VLAN
DES-3226S#Config vlan default delete 1 -24 ?删除默认VLAN(default)包含的端口1-24''
DES-3226S#Create vlan vlan10 tag 10 ?创建VLAN名为vlan10，并标记VID为10 


（2）添加端口到各VLAN


DES-3226S#Config vlan vlan10 add untag 1-24 ?把端口1-24添加到VLAN10


同理，配置其它DES-3226S二层交换机。完成以后就可以将各个所属VLAN的二层交换机与DES-3326SR三层交换机的相应VLAN的端口连接即可。





华为RT2611路由器做nat实例

[Quidway]dis cur 
Now create configuration... 
Current configuration 
! 
version 1.74 
firewall enable 
encrypt-card fast-switch 
!
acl 1 match-order auto
rule normal permit source 192.168.0.0 0.0.0.255
!
interface Aux0
async mode flow
link-protocol ppp
!
interface Ethernet0 /*内网*/
ip address 192.168.0.1 255.255.255.0
!
interface Ethernet1 /*外网*/
ip address 219.89.189.6 255.255.255.252
nat outbound 1 interface
!
interface Serial0
link-protocol ppp
!
quit
ip route-static 0.0.0.0 0.0.0.0 219.89.189.5 preference 60
!
return

___________________

很简单的应用，内部局域网的机器通过外网口上所连的宽带网口上因特网。内网的机器可以正常上网，但反应速度较慢，比如下载软件一般只有40多K，而以前用其他品牌的路由器（如edimax的6104）速度要快得多，有1百多K。不知道还有没有地方可以优化的。希望请告知。


--------------------------------------------------------------------------------
由 weidong 于 06-12-2003 02:20 PM 发表: 

另外，我在许多地方查看到华为的资料上面，配置方法和思科的基本相同，但为什么现在我手上这台的配置方法有所差异呢？
例如：查看现在配置 cisco为 show running-config，而华为 为 display current-config
这台2611的版本为:
VRP (R) software, Version 1.74 Release 0007


--------------------------------------------------------------------------------
由 7boy 于 06-13-2003 10:28 AM 发表: 


quote:
--------------------------------------------------------------------------------
最初由 weidong 发布
另外，我在许多地方查看到华为的资料上面，配置方法和思科的基本相同，但为什么现在我手上这台的配置方法有所差异呢？
例如：查看现在配置 cisco为 show running-config，而华为 为 display current-config
这台2611的版本为:
VRP (R) software, Version 1.74 Release 0007 
--------------------------------------------------------------------------------



因为华为的已经在近期修改了命令。
__________________
i must win,and i will win.


--------------------------------------------------------------------------------
由 beder 于 06-13-2003 08:24 PM 发表: 

因与思科的官司，华为在vrp1.7以后的版本中已经更改了命令行。且删除了eigrp的支持
