刚才给你打过电话，现简要说一下需求：ne40上有三个口，一个百灵出口，一个教育网出口，一个内网，内网全部使用教育网地址，现已申请到部分网通地址。现在想访问教育网地址时保持原有地址走教育网，访问其它的地址时都将源地址nat成百灵的地址后从网通口出去。
注：百灵也是一家宽带接入商。

现在出现的结果是测试了一下在rule1中的几个地址，并没有成功的nat。难道非要把nat做到内网的入口处？难道ne40只支持流入端口的数据做nat，不支持流出端口的数据做nat？


我们的配置如下：其中ethernet 3/0/5是百灵出口，ethernet 4/0/3接内网。
因加入nat enable address-group命令时出现点问题，所以我就直接加了一条静态路由。
218.98.166.32/27   STATIC   60   0           0.0.0.0         NULL0 
#
 sysname sdieNe40
#
 super password level 3 simple ****
#
 nat address-group beelinkpool1 218.98.166.32 218.98.166.62 mask 255.255.255.224 slot 2
 nat service-class 4 connections 0
#
 rule-map intervlan dorm1 ip any 202.194.241.0 0.0.0.255
 rule-map intervlan dorm2 ip any 202.194.242.0 0.0.1.255
 rule-map intervlan dorm3 ip any 202.194.244.0 0.0.0.255
 rule-map intervlan rule1 ip 202.194.240.32 0.0.0.15 any
 rule-map intervlan rule2 ip any any
 rule-map intervlan rule3 ip 202.194.240.0 0.0.15.255 any
#
 flow-action action2 nat address-group beelinkpool1 service-class 4
#
 eacl eacl2 rule2 action2
 eacl eacl3 rule3 action2
 eacl eacl1 rule1 action2
#
vlan 2
vlan 3
vlan 5                                    
vlan 6
vlan 8
vlan 555
#
interface Aux0/0/1
 async mode flow
 undo shutdown
#
interface Vlanif2
 description conn_8512
 undo shutdown
 ip address 202.194.240.203 255.255.255.248
#
interface Vlanif3
 description conn_cernet
 undo shutdown
 ip address 202.194.96.62 255.255.255.252
#
interface Vlanif5
 description conn_bailing
 undo shutdown
 ip address 218.98.166.62 255.255.255.192
#                                         

interface MEth0
 undo shutdown
#
interface Ethernet2/1/0
#
interface Ethernet2/1/1
#
interface Ethernet2/1/2
#
interface Ethernet2/1/3
#
interface Ethernet3/0/0                   
 description conn_8512
 negotiation auto
 undo shutdown
 port default vlan 2
#
interface Ethernet3/0/1
 description conn_8512
 negotiation auto
 undo shutdown
 port default vlan 2
#
interface Ethernet3/0/2
 description conn_cernet
 negotiation auto
 undo shutdown
 port default vlan 3
#
interface Ethernet3/0/3
 description conn_cernet
 negotiation auto
 undo shutdown
 port default vlan 3                      
#
interface Ethernet3/0/4
 description conn_bailing
 negotiation auto
 undo shutdown
 port default vlan 5
#
interface Ethernet3/0/5
 description conn_bailing
 negotiation auto
 undo shutdown
 port default vlan 5
 nat match-host beelinkpool1
 access-group switch eacl eacl1 vlan all
#
interface Ethernet3/0/6
#
interface Ethernet3/0/7                   
#
interface Ethernet3/0/8
#
interface Ethernet3/0/9
#
interface Ethernet3/0/10
#
interface Ethernet3/0/11
#
interface Ethernet3/0/12
#
interface Ethernet3/0/13
#
interface Ethernet3/0/14
#
interface Ethernet3/0/15
#
interface GigabitEthernet4/0/0            
 description conn_8512
 undo negotiation auto
 undo shutdown
 port default vlan 2
#
interface GigabitEthernet4/0/1
#
interface GigabitEthernet4/0/2
 negotiation auto
 undo shutdown
#
interface GigabitEthernet4/0/3
 description conn_8512
 negotiation auto
 undo shutdown
 port default vlan 2
 access-group switch eacl eacl1 vlan all
#                                         
interface NULL0
#
ospf
 import-route static
 import-route direct
 default-route-advertise
 #
 area 0.0.0.0
  network 202.194.240.200 0.0.0.7
#
 ip route-static 0.0.0.0 0.0.0.0 218.98.166.1 preference 60
 ip route-static 58.154.0.0 255.254.0.0 202.194.96.61 preference 60
 ip route-static 58.192.0.0 255.240.0.0 202.194.96.61 preference 60
 ip route-static 59.64.0.0 255.240.0.0 202.194.96.61 preference 60
 ip route-static 121.48.0.0 255.254.0.0 202.194.96.61 preference 60
 ip route-static 121.192.0.0 255.252.0.0 202.194.96.61 preference 60
 ip route-static 121.248.0.0 255.252.0.0 202.194.96.61 preference 60
 ip route-static 122.204.0.0 255.252.0.0 202.194.96.61 preference 60
 ip route-static 125.216.0.0 255.248.0.0 202.194.96.61 preference 60
 ip route-static 162.105.0.0 255.255.0.0 202.194.96.61 preference 60
 ip route-static 166.111.0.0 255.255.0.0 202.194.96.61 preference 60