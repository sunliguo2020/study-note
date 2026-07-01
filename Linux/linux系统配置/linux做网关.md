1:开启ip转发功能

sysctl -a |grep "net.ipv4.ip_forward"
/proc/sys/net/ipv4/ip_forward

/etc/sysctl.conf

[root@localhost etc]# more sysctl.conf 
# sysctl settings are defined through files in
# /usr/lib/sysctl.d/, /run/sysctl.d/, and /etc/sysctl.d/.
#
# Vendors settings live in /usr/lib/sysctl.d/.
# To override a whole file, create a new file with the same in
# /etc/sysctl.d/ and put new settings there. To override
# only specific settings, add a file with a lexically later
# name in /etc/sysctl.d/ and put new settings there.
#
# For more information, see sysctl.conf(5) and sysctl.d(5).

net.ipv4.ip_forward=1

echo "1" >/proc/sys/net/ipv4/ip_forward

2、设置iptables规则

在A电脑上执行

iptables -t nat -A POSTROUTING -s 10.1.1.0/24 -j SNAT --to-source 192.168.1.1

service iptables save

这个语句就是告诉系统把即将要流出本机的数据的source ip address修改成为192.168.1.1。这样，数据包在达到目的机器以后，目的机器会将包返回到192.168.1.1。
如果不做这个操作，那么数据包在传递的过程中，reply的包肯定会丢失。 

假如当前系统用的是ADSL/3G/4G动态拨号方式，那么每次拨号，出口ip都会改变，snat是把源地址转换为固定的ip地址，这样就会有局限性。这时可以使用：

iptables -t nat -A POSTROUTING -s 10.1.1.0/24 -o eth0 -j MASQUERADE

与snat不同的是，masquerade可以自动读取外网卡获得动态ip地址，然后进行地址转换。

POSTROUTING：在通过Linux路由器之后做的策略，也就是路由器的外网接口。

-s 10.1.1.0/24：源数据所来自这个网段，也可以是单个ip，不写表示所有内网ip。

-o eth0 -j MASQUERADE：表示在eth0这个外网接口上使用IP伪装。

iptables -t nat -A POSTROUTING -s 192.168.10.0/24 -o ens33 -j MASQUERADE