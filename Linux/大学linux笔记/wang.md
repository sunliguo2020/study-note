1-5   cbccc      cbccA    1
6-10  ddbad      CdACD    3
11-15 ddcdb               0
16-20 dbaba      dbBba    1
21-25 bcaba      bcaba     0
26-30 cabcd      Dabcd    1
31-35 cabdd      cabCd    1
36-40 bcbaa      bcbaa
41-45 cbcbd                0
46-50 cddbd      cBdbd     1
51-55 cdabc      cdaDc    1
56-60 dbccc      dAcAA    3
61-65 dabbb      dabCb     1
66-70 cabac      ABbac     2
71-75 bdcbc      bCcAD     3
下午
试题一
问题1:
1: 核心交换机
2: 汇聚交换机
3: 接入交换机
4:b汇聚层
5:b
6:A 54Mb/s
7:B channel
8:
9:A
bcbbaa
试题二
问题1:
1 b 分布式数据库
2 a C/S
3 a named
问题2：
4: c
5: a
6: b
问题3:
8: 222.35.40.0
9: /var/named
试题三:
1:不确定 
2: 192.168.0.1
3: 192.168.0.2
4: a
5: c
6: 192.168.0.2
7: 00-16-36-33-9B-BE
试题四:

abd

试题一：
采用Ipsec模式
默认时，允许任何用户访问


试题三：
1、从DHCP服务器获得DNS地址
DHCP绑定——选中“作用域选项”右击绑定
4、绑定——ip地址：192.168.0.2
mac地址：本地连接的那个（具体记不清楚了）

试题四：
1、ip nat inside 192.168.0.1 255.255.255.0
ip nat outside *.*.*.* 255.255.255.248 （地址记不清楚用*表示）
2、选择题：定义防火墙全局地址*.*.*.*
启用NAT,允许内网所有主机访问外网
将内网地址*.*.*.*转换成外网地址*.*.*.*
3、允许ip地址为*.*.*.*的主机80端口的数据包通过防火墙
conduit permit ip any eq icmp any 
4、启用Http端口，并将Http的端口号设置为8080
关闭Ftp的21号端口

试题五：
定义交换机的名称为SwitchA
进入Vlan的子配置模式
定义VTP管理域的域名服务器为VTPSEVER
启用VTP剪裁工具
mode trunk
vlan all
switchport mode access
switchport access vlan 10
默认权值为128
通过E0/3端口（以太网0槽第3端口）发送数据 
