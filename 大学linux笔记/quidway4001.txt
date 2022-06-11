[问题] 最近，有用户提出用QUIDWAY4001作接入服务器的要求，确实，对一个企业或公司来说，用QUIDWAY4001的PRI口做30路用户的接入，的确是一个不错的选择。下面是一个配置实例。
[分析]： 根据用户需求,QUIDWAY4001的 CE1/PRI口 走PRI30B+D信令可以接入30路用户.
[解决]： 配置如下：
sh run
Now create configuration...
Current configuration
!
user aa password 0 123
user bb password 0 321
dialer-list 1 protocol ip permit
ip local pool 1 192.168.1.1 192.168.1.31
snmp-server traps enable
hostname Quidway4001
!
controller e 0
pri-group timeslot 1-31
!
interface Ethernet0
ip address 100.10.10.1 255.255.0.0
!
interface Serial0
enable
encapsulation ppp
!
interface Serial1
flowcontrol normal
encapsulation ppp
!
interface Serial2:15
encapsulation ppp
ppp authentication pap
peer default ip address pool 1
ip address 192.168.1.254 255.255.0.0
dialer in-band
dialer-group 1
!
router rip
!
end 大家注意

在华为的低端路由器上加入如下路由不生效

ip route 10.0.0.0 255.0.0.0 s1
ip route 192.168.0.0 255.255.0.0 s1

换成

ip route 0.0.0.0 0.0.0.0 s1

就生效了

很奇怪 呵呵！



华为路由器和cisco的telnet配置不同,其没有line.
VRP1.4.1配置为config模式下:
user xxx pass 7 xxx
login telnet

VRP1.5.6配置为config模式下:
aaa-enable
user xxx service-type exec pass 7 xxx
login telnet



运营商网络上的无线数据功能的种类在大量地增长。这种增长与标准和提供的服务有关。本文介绍一些无线运营商提供的数据功能和一些正在使用的技术。

目前的运营商面临多种技术和一些新兴的标准。这些技术和新的标准为在蜂窝干线网络上提供数据的能力提供了大量的选择。下面列出一些可以考虑的词汇，每一个词汇都有一个简单的说明:

GSM(全球移动通讯系统):用于蜂窝电话服务的国际标准。

3G(第三代无线技术):GSM的升级技术。

4G(第四代无线技术):3G的后续技术。

CDMA(码分多址):基于数据包的无线接入技术。

W-CDMA(宽带码分多址)和UMTS(通用移动电信系统):欧洲数据传输标准，车上使用的数据传输速度为每秒144KB，行人使用的数据传输速度为每秒384KB，室内使用的数据传输速度最多为每秒2MB。

GPRS(通用分组无线业务):GSM网络上的无线服务，通常指2.5G技术。

HSDPA(高速数据分组接入):GSM网络上的数据服务，通常指3.5G或者4G(速度比GPRS快)。

EDGE(增强型数字全球移动通讯系统):增强2G和2.5G性能的数字移动电话技术。

EV-DO或者1xEV-DO(Evolution Data Optimized):用于CDMA网络的数据包服务。

1xRTT(单个运营商(1x)无线电传输技术):使用CDMA的3G技术。

在美国，主要运营商或者采用CDMA(Verizon和Sprint公司)，或者采用GSM(Cingular/AT&T公司)作为移动数据通讯的选择。这些运营商都希望提高其服务以支持高速数据能力。

各个运营商提供的服务如下:

CDMA: Verizon和Sprint1xRTT: 50-70 kbpsEV-DO: 300-500 kbpsGSM: (Cingular/AT&T)MGPRS: 50 kbpsEDGE: 70-130 kbpsUMTS: 200-320 kbpsHSDPA: 400-700 kbps (2007年推出) 

正如你所看到的，随着技术本身的标准化，运营商内部将发生重大的变化。关键是速度和覆盖率。Verizon和Sprint在美国国内领先于Cingular，因为Cingular没有全面部署自己的4G服务(HSDPA)。然而，Sprint和Verizon的电话在国际上不好用。

无论怎样，无线技术现在已经能够支持商业应用程序，一旦运营商能够进入这个市场，这种服务就可以继续扩大。关键是要评估你要购买的电话和服务，找到支持你的具体业务和个人需求的产品和服务。