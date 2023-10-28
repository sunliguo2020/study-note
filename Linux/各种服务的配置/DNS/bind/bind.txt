安装 域名服务器
 
1:
   下载bind-version.tar.gz
2: 
  解压 编译：
  tar zxvf bind-version.tar.gz
  cd bind-version
  ./configure 
  make&&make install
3:
  创建chroot环境:
  The chroot Environment   From BIND's point of view ,/var/named is the root of the filesystem.
 /dev/zero /dev/random /dev/log and/or /etc/localtime`

  mkdir -p /var/named/chroot
  添加用户:
 # useradd named -g named -d /var/named/chroot -s /sbin/nologin
  mkdir -p /var/named/chroot/var/run
  mkdir -p /var/named/chroot/etc
  mkdir -p /var/named/chroot/var/named
  mkdir -p /var/named/chroot/var/run
  chown -R named.named *

安装后的文件：

 /usr/local/sbin/ 下有：
    dnssec-keygen dnssec-signzone lwresd named named-checkconf named-checkzone  rndc rndc-confgen
 /usr/local/bin 下有：
    host nsloookup nsupdate 
 /usr/local/man/  下有manual手册

4: 配置文件：
cd /var/named/chroot/var/named

vi named.conf

options{
     //定义服务器区配置文件的工作目录
     dictory    "/var/named";   //working directory
     forwarders { 10.0.1.245;};
};
//定义根区声明
zone "." IN {
    type hint;         //一个区为启动时初始化高速缓存的域名服务器
    file "named.ca"    //一个区的域信息源数据库信息文件名
};

//定义localhost正向解析区声明
zone "localhost" IN{
      type master;
      file "localhost.zone";
      allow-update { none; };
};

//反向解析区文件
zone "0.0.127.in-addr.arpa" IN {
    type master;
    file "named.local"
}

本地正向解析文件：/var/named/chroot/var/named
vi localhost.zone

//RR 记录的基本格式：
//  [name] [ttl] IN type rdata
[domain] [ttl] [class] <type> <rdata>

<type> SOA (start of authority)  MX (Name server A 

$TTL 86400
@ 1D IN SOA @ root(
        42
        3H
        15M
        1W
        1D)
   IN NS @
   IN A  127.0.0.1

本地反向解析文件：

vi named.local
$TTL 86400
@ IN　SOA　lcoalhost. root.localhost. (
          20061202 ;Serial
          2800     ;Refresh
          14400    ;Retry
          3600000  ;Expire
          864000 ) ；Minimum
   IN NS  localhost.
1  IN PTR localhost.

创建根服务器的数据文件(最新的根域服务器列) named.ca
dig -t NS . >/var/named/chroot/var/named/named.ca

/usr/local/sbin/named -g 调试
最后的文件目录：
tree /var/named/chroot

/var/named/chroot
|-- dev
|   |-- random
|   `-- zero
|-- etc
|   |-- localtime
|   |-- named.conf
|   `-- rndc.key
`-- var
    |-- named
    |   |-- 59.81.183.rev
    |   |-- localhost.zone
    |   |-- named.ca
    |   |-- named.local
    |   `-- sunliguo.edu1000.net
    `-- run
        `-- named.pid

5 directories, 11 files
用RNDC控制服务器
rndc 
1:  产生rndc控制文件
# rndc-confgen>/etc/rndc.conf
tail +13 /etc/rndc.conf >>/etc/named.conf 

DNS 测试工具：host dig nslookup