在iptables 中,提供了五个内置的规则链.INPUT和FORWARD链用于filter表,PREROUTEIN
G和POSTROUTING链用nat表,OUTPUT链可以用于两个表中.

#iptables -A INPUT -p icmp -j DROP 
                              Target
                              ACCETP
			      REJECT
			      LOG

iptables command rule-specification option extensions
command :
-A chain  add 追加一条规则(放在最后 )  
-p potocol
-I <链名>[规则号码]
   iptables -I INPUT -j DROP
   在filter表中的INPUT链中插入一条规则（插入成第一条）
   iptables -I INPUT 3 -j DROP 插入成第三条
-D <链名><规则号码|具体规则内容>
     DELETE
     iptables -D INPUT 3
     iptalbes -D INPUT -s 192.168.0.1 -j DROP
-R <链名><规则号码><具体内容>
     replace
     iptables -R INPUT 3 -j ACCEPT
-P <链名><动作>
    POLICY 设置某个链的默认规则 ACCEPT DROP QUEUE RETURN
-F [链名］ FLUSH,清空规则
   -L -[vxn]L 
   iptables -L 
   iptables -t nat -vnL
Rule-specification (规则规范参数)
-p [!]protocol 
-s [!]address[/mask]
-d [!]address[/mask]
-j target 
-i [!]interface-name
-o [!]interface-name
Option
-v
-n
-x
--line-numbers
Extensions

   iptables -t nat -vxnL PREROUTING
 匹配条件
      流入流出接口 -i -o 
      来源目的地址  -s -d 
      协议类型 -p
      来源 目的端口--sport --dport
   -i <匹配数据进入的网络接口>
      -i eth0 -i ppp0
   -o 匹配数据流出的网络接口
     -o eth0 -o ppp0
   -s <匹配来源地址>
    -s 192.168.0.1 -s 192.168.1.0/24 -s 192.168.0.0/16
   -d <匹配目的地址>
     -d 202.106.0.20 -d 202.106.0.0/16 -d www.abc.com
   -p <协议类型>
     -p tcp -p udp -p icmp --icmp-type --sport <匹配源端口号
-j 
#iptable -L -n 查看防火墙 
#iptable -F 清空
#iptables -A INPUT -p tcp -d 192.168.1.30 --dport 21 -j DROP
ssh:
#iptables -A INPUT -p tcp -d 192.168.1.30 --dport 22 -j ACCEPT
#iptables -A OUTPUT -p tcp -s 192.168.1.30 --sport 22 -j ACCEPT

#iptables -P INPUT DROP
#iptables -P FORWARD DROP
#iptables -P OUTPUT DROP
http:
#iptable -A INPUT -p tcp --dport 80 -j ACCEPT
#iptable -A OUTPUT -p tcp --sport 80 -j ACCEPT
 
#iptables -L -n --line-numbers
保存
/etc/sysconfig/iptaboles
server iptables save
iptables-save>/etc/sysconfig/iptales
iptables-save
#iptables -A OUTPUT -p tcp --sport 22 -m state --state ESTABLISHED -j ACCPT
日志
#iptables -A INPUT -p tcp --dport 22 -j LOG --log-level 5\
 --log-prefix "IPTABLES"

#/etc/syslog.conf 
 kern.=notice /var/log/firewall.log

 iptables -I INPUT 6 -p tcp --dport
查看:
  iptables -L -n
#iptables -A INPUT -p icmp -J DROP
                              目标(Target)
			       DROP 丢弃
			       ACCEPT 接受
			       REJECT弹回
			       LOG 日志
DNS 
  iptables -A OUTPUT -p tcp -dport 53 -j ACCEPT
  iptables -A INPUT  

  iptables -A OUTPUT -p tcp --sport 22 -m state --state ESTABLISHED -j ACCEPT
    1 框架图
    -->PREROUTING-->[ROUTE]-->FORWARD-->POSTROUTING-->
         mangle        |        mangle       ^ mangle
       nat             |      filter       | nat
	               |                     |
	               |                     |
	               v
		
	               INPUT		 OUTPUT
	                 |
			 |mangle 
			 |filter
			 											  ------>local------->|

