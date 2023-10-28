														CISCO路由器配置基础

		
	路由器是计算机网络的桥梁，是连接IP网的核心设备。通过它不仅可以连通不同的网络，还能选择数据传送的路经，
	并能阻隔非法访问。路由器的配置对初学者来说，并不是件容易的事。现以CISCO路由器为例，将路由器的一般常识
		和配置介绍给大家，供朋友们在配置路由器时参考。
	
一、 路由器的一般常识
   路由器具有创建路由、执行命令以及在网络接口上使用路由协议对数据包进行路由等功能。它的硬件基础是接口、
CPU和存在器，软件基础是网络互联操作系统IOS。

1、 路由器接口

·路由器接口用作将路由器连接到网络，可以分为局域网接口和广域网接口两种。由于路由器型号的不同，接口数目
和类型也不尽一样。常见的接口主要有以下几种：

·高速同步串口，可连接DDN，帧中继（Frame Relay），X.25，PSTN（模拟电话线路）。

·同步/异步串口，可用软件将端口设置为同步工作方式。

·AUI端口，即粗缆口。一般需要外接转换器（AUI-RJ45），连接10Base-T以太网络。

·ISDN端口，可以连接ISDN网络(2B+D)，可作为局域网接入Internet 之用。

·AUX端口，该端口为异步端口，主要用于远程配置，也可用于拔号备份，可与MODEM连接。支持硬件流控制（
Hardware Flow Ctrol）。

·Console端口，该端口为异步端口，主要连接终端或运行终端仿真程序的计算机，在本地配置路由器。不支持硬件
流控制。

2、 路由器的CPU

路由器和PC机一样，有中央处理单元CPU，而且不同的路由器，其CPU一般也不相同，CPU是路由器的处理中心。

3、 路由器的内存组件

内存是路由器存储信息和数据的地方，CISCO路由器有以下几种内存组件：

·ROM（Read Only Memory）

·ROM中存储路由器加电自检（POST：Power-On Self-Test）、启动程序（Bootstrap Program）和部分或全部的IOS。
路由器中的ROM是可擦写的，所以IOS是可以升级的。

·NVRAM(Nonvolatile Random Access Memory)

·非易失RAM，存储路由器的启动配置文件。NVRAM是可擦写的，可将路由器的配置信息拷贝到NVRAM中。

·FLASH　RAM

·闪存，是一种特殊的ROM，可擦写的，也可编程，用于存储CISCO　IOS的其它版本，用于对路由器的IOS进行升级。

·RAM（Random Access Memory）

RAM与PC机上的随机存储器相似，提供临时信息的存储，同时保存着当前的路由表和配置信息。


 4、 路由器的启动过程

① 加电之后，ROM运行加电自检程序（POST）,检查路由器的处理器、接口及内存等硬件设备。

② 执行路由器中的启动程序（Bootstrap）,搜索CISCO的IOS。路由器中的IOS可从ROM中装入，或从Flash RAM中装入，
也可从TFTP服务器装入。

③ 装入IOS后，寻找配置文件。配置文件通常在NVRAM中。配置文件也可从TFTP服务器装入。

④ 装入配置文件后，其中的信息将激活有关接口、协议和网络参数。

⑤ 当找不到配置文件时，路由器进入配置模式。

二、 路由器的配置途径

可通过以下几种途径对CISCO路由器进行配置：

1、 控制台

将PC机的串口直接通过Rollover线与路由器控制台端口Console相连，在PC计算机上运行终端防真软件，与路由器进行
通信，完成路由器的配置。也可将PC与路由器辅助端口AUX直接相连，进行路由器的配置。

2、 虚拟终端（Telnet）

如果路由器已有一些基本配置，至少有一个端口有效（如Ethernet 口），就可通过运行Telnet程序的计算机作为
路由器的虚拟终端与路由器建立通信，完成路由器的配置。

3、 网络管理工作站

路由器可通过运行网络管理软件的工作站配置，如Cisco的CiscoWorks、HP的OpenView等。

4、 CISCO　ConfigMaker

ConfigMaker是一个由CISCO开发的免费的路由器配置工具。ConfigMaker采用图形化的方式对路由器进行配置，然后
将所做的配置通过网络下载到路由器上。ConfigMaker要求路由器运行在IOS　11.2以上版本，可用Show Version命令
查看路由器的版本信息。

5、 TFTP(Trivial File Transfer Protocol)服务器

TFTP是一个TCP/IP简单文件传输协议，可将配置文件从路由器传送到TFTP服务器上，也可将配置文件从TFTP服务器
传送到路由器上。TFTP不需要用户名和口令，使用非常简单。

三、 路由器配置中的三种模式

路由器有三种基本的访问模式：

1、 用户模式（User EXEC）

用户模式是路由器启动时的缺省模式，提供有限的路由器访问权限，允许执行一些非破坏性的操作，如查看路由器
的配置参数，测试路由器的连通性等，但不能对路由器配置做任何改动。该模式下的提示符（Prompt）为“＞”。
show interface命令，查看路由器接口信息，即为用户模式下的命令。

2、 特权模式(Privileged EXEC)

特权模式，也叫使能（enable）模式，可对路由器进行更多的操作，使用的命令集比用户模式多，可对路由器进行
更高级的测试，如使用debug命令。在用户模式下通过使能口令进入特权模式。提示符为“＃”。Show running-config
即为特权模式命令。

3、 配置模式(Global Configuration)

配置模式是路由器的最高操作模式，可以设置路由器上的运行的硬件和软件的相关参数；配置各接口、路由协议和
广域网协议；设置用户和访问密码等。在特权模式“＃”提示符下输入config命令，进入配置模式。

四、 IP路由的配置

Ip路由的配置主要完成以下任务：一是配置局域网LAN接口和广域网WAN接口；二是激活IP路由协议；三是配置广域
网协议。具体配置方法如下：

1、 LAN接口的配置

LAN接口是路由器与局域网的连接点，每个LAN接口与一个子网相连，配置LAN接口就是将LAN接口子网地址范围内的
一个IP地址分配给LAN接口。配置方法如下：

①． 在特权模式下输入config t命令，按回车，路由器进入配置模式；

②． 在配置模式下输入要配置的接口名，如interface ethernet 0，按回车，提示符变为config-if；

③． 输入ip address＋IP地址和子网掩码，如：ip address 200.38.118.9 255.255.255.0。

④． 配置完成后按Ctrl+Z退出配置，回到特权模式。可用show ip interface　e0命令查看配置参数。

2、 WAN接口的配置

WAN接口的配置方法和LAN接口一样，以配置串口1为例。

①． 在特权模式下，输入config t命令，按回车进入配置模式；

②． 输入所要配置的WAN接口，如串口0，命令格式为：interface serial 0，按回车，进入config-if 模式；

③． 输入ip address 加ip地址和子网掩码，按回车完成。

④． 按Ctrl+Z结束接口配置，返回特权模式。可用show interface s0命令来查看串口配置。

3、 路由协议的配置

首先确定选择什么样的路由协议。根据网络规模和大小，跳数（从一个路由器到另一个路由器称为一跳）在15以内的
小型网络选择路由信息协议RIP （Routing Information Protocol）；大型网络可选择内部网关路由协议IGRP
（Interior Gateway Routing Protocol）或开放最短路径优先OSPF(Open Shortest Path First)。各种协议的配置
方法如下：

①． 配置RIP协议

·启动RIP路由协议。在配置模式下输入router rip，则RIP被确定为路由协议。

配置与路由器直接相连的网络。在配置模式下输入network 网络地址。如network 139.10.0.0。如有不同的网络地址
与路由器相连，重复上述命令。

·配置允许在非广播型网络中进行RIP路由广播，在配置模式下输入neighbor 相邻路由器相邻端口的IP地址。

②． 配置IGRP协议

·启动IGRP路由协议。在配置设置模式下输入router igrp 加上自治域号。如router igrp 2。只有同一自治域内的
路由器才能交换路由信息。

·IGRP是将由network指定的子网在各端口中进行传送来交换路由信息，如果不指定子网，则路由器不会将该子网广
播给其它路由器。在配置模式下输入network 加上子网号，配置参加动态路由的子网。

·指定某路由器所知的IGRP路由信息广播给那些与其相邻接的路由器。IGRP是一个广播型协议，为了使IGRP路由信息
能在非广播型网络中传输，必须使用该设置，以允许路由器间在非广播型网络中交换路由信息。广播型网络如以太网
无须设置此项。在配置模式下输入neighbor 加上邻接路由器的相邻端口IP地址。

③． 配置OSPF协议

·启用OSPF动态路由协议在配置模式下输入router ospf 进程号。如router ospf 2。

·定义参与ospf的子网。在配置模式下输入network ip 子网号 通配符 area 区域号。路由器将限制只能在相同区域
内交换子网信息，不同区域间不交换路由信息。

·指明网络类型。在配置模式下输入ip ospf network broadcast或non-broadcast或point-to –mutlipoint。一般地，
对于 DDN，帧中继和X.25属于非广播型的网络，即non-broadcast

·对于非广播型的网络连接，需指明路由器的相邻路由器

4、 常用广域网协议的配置

常用广域网协议主要有高级数据链路控制协议HDLC、综合服务数字网ISDN 、点对点协议PPP、分组交换协议X.25和
帧中继Frame-Relay等。路由器的串口提供与广域网的连接，但与ISDN的连接需通过ISDN接口。广域网协议的配置
方法如下：

①． 配置HDLC

·高级数据链路控制协议HDLC是一个点对点的WAN协议，是CISCO路由器缺省的广域网协议。配置方法如下：

·在特权模式下输入config t命令进入配置模式。

·配置连接的WAN接口。如：interface serial 1,进入config-if模式。

·HDLC协议封装。输入encapsulation HDLC，按回车。

·设置带宽。输入bandwidth 传输速率[kilobits/second]，如56K，则输入bandwidth 56。

②． 配置基带ISDN

·ISDN是在已有的电话线上使用数字技术开展的数字服务。ISDN有两种，BRI（Basic Rate ISDN）和
PRI（Primary Rate ISDN），其中BRI提供2B＋D三个通道，每个B通道的带宽为64K，B通道由
SPID（Service Profile Identifier）号标识。ISDB与其它WAN协议的配置有些区别。

·在特权模式下，输入config t，按回车，进入配置模式。

·配置ISDN连接的交换类型。输入isdn switch type basic-[switch identifier]。switch identifier为
所连交换机类型的厂商ID号。

·配置ISDN接口，输入int bri[number]，number为BRI接口号。

·封装成PPP，输入encapsulation ppp。

·配置SPID1，输入isdn spid1 [SPID#]。SPID#为服务商提供的电话号码。

·配置SPID2，输入isdn spid2 [SPID#]。

·Ctrl+Z，结束配置。

③． 配置PPP

·特权模式下输入config t命令，进入配置模式。

·配置WAN接口。输入具体接口号，如interface serial 0，进入config –if模式。

·封装PPP协议，输入encapsulation PPP。

·设置带宽，输入bandwidth 带宽。

·Ctrl+Z，结束配置。

④． 配置X.25

·在特权模式下，输入config t，进入配置模式。

·配置WAN接口。输入具体接口号，如interface serial 0，进入config –if模式。

·封装X.25协议，输入encapsulation X.25。

·设置带宽，输入bandwidth 带宽。

·设置接口的X.25地址，即X.121地址，输入X.25 address X.25地址，如X.25 address 8015117011。

·Ctrl+Z，结束配置。

⑤． 配置帧中继

在特权模式下，输入config t，进入配置模式。

配置WAN接口。输入具体接口号，如interface serial 0，进入config –if模式。

封装frame-relay协议，输入encapsulation frame。

设置本地管理接口LMI（Local Management Interface），输入frame-relay lmi-type LMI类型。

LMI类型有在种：cisco、ansi、q933a，如frame-relay lmi-type ansi。

设置DLCI，输入frame-relay interface-dlci [#]，＃为DLCI号。帧中继以永久虚电路来在WAN之间建立通讯会话，
用DLCI号来标识。帧中继技术提供面向连接的数据链路层的通信，在每对设备之间都存在一条定义好的通信链路，
且该链路有一个链路标识码DLCI（Data Line Connection Identifier）。这种服务通过帧中继虚电路实现，
每个帧中继虚电路都以数据链路识别码（DLCI）标识自己。DLCI的值一般由帧中继服务提供商指定。
帧中继即支持PVC也支持SVC。

设置带宽，输入bandwidth 带宽。

Ctrl+Z，结束配置。