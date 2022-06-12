master 主dns服务器
slave 次dns服务器
named.ca根域名服务器配置文件放在/var/named/chroot/var/named/目录下
named.ca要去ftp://ftp.rs.internic.net/domain/named.root下载，重命名为named.ca
1 默认是把named.conf放在/etc/目录下
2 如有安装chroot,要把配置文件放在/var/named/chroot/etc/目录下
3 把主区域文件与反向解析文件放在/var/named/chroot/var/named/目录下
4 指定ftp的负载均衡，在主区域文件添加相关ftp 对应主机地址；
5 service named restart 重启dns服务；
6 linux主机作DNS客户端 更改/etc/resolv.conf 加入如下内容
  nameserver 192.168.200.202       (192.168.200.202为dns IP)
7 cache-only dns服务器配置
  做一个named.conf文件，内容为
options {
	directory "/var/named";
	dump-file "/var/named/data/cache_dump.db";
	statistics-file "/var/named/data/named_stats.txt";
	version "4.9.11";
forward only;
	forwarders {
		192.168.200.202;   ; 注：指定从哪个dns上获取数据
	};
};
include "/etc/rndc.key";

8 三种查看域名解析的命令
host
nslookup
dig

9 windows中查看dns记录
 ipconfig/displaydns
 ipconfig/flushdns 清空dns缓存；
  



 
