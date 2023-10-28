在一台路由器上实现不同的网段走不同的网络出口,实现多出口分担
interface Aux0
async mode flow
link-protocol ppp
# interface Ethernet0/0/0    file://电信网络地址
ip address X.X.X.X 255.255.255.224
nat outbound 2001
# interface Ethernet0/0/1   file://联通网络地址
ip address X.X.X.X 255.255.255.224   
nat outbound 2003
# interface Ethernet1/0/0    file://内部网络地址
ip address X.X.X.X 255.255.255.0
ip policy route-policy asyx     file://在内网接三层交换机端口上应用策略路由
# interface Ethernet1/0/1     网通网络地址
ip address X.X.X.X 255.255.255.0
# interface NULL0
# acl number? 2000 match-order auto    file://访问控制列表
rule 0 permit source 20.0.3.1 0.0.0.64
rule 1 permit source 20.0.2.126 0.0.0.128
rule 2 permit source 20.0.4.1 0.0.0.32
rule 3 deny
acl number 2001 match-order auto    file://访问控制列表
rule 0 permit source 20.0.3.129 0.0.0.32
rule 1 permit source 20.0.4.222 0.0.0.32
rule 2 permit source 20.0.4.129 0.0.0.64
rule 3 permit source 20.0.6.129 0.0.0.32
rule 4 deny
acl number 2002 match-order auto   file://访问控制列表
rule 1 permit source 20.0.3.129 0.0.0.32
rule 0 permit source 20.0.6.1 0.0.0.64
rule 2 permit source 20.0.5.1 0.0.0.128
rule 3 permit source 20.0.7.0 0.0.0.255
rule 4 deny
# route-policy asyx permit node 1   file://匹配策略
if-match acl 2000
apply ip-address next-hop X.X.X.X
route-policy asyx permit node 2   file://匹配策略
if-match acl 2001
apply ip-address next-hop X.X.X.X
route-policy asyx permit node 3   file://匹配策略
if-match acl 2002
apply ip-address next-hop X.X.X.X
#

#
user-interface con 0
user-interface aux 0
user-interface vty 0 4
user privilege level 3
set authentication password cipher ;VFIFBGK<9:,YWX*NZ55OA!!
# return