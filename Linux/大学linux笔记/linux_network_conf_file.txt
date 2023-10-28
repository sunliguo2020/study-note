/etc/hosts 
包含ip地址和主机名的对应。一个条目占一行。
格式为：
   IP_address canonical_hostname [aliases...]
/etc/networks
/etc/host.conf
  指明主机名是如何被解析的。

/etc/resolv.conf  \\域名服务器
nameserver 218.56.152.83

 
The rc Files 
  The rc files,otherwise known as run command files,are located in the /etc/rc.d
diectory .在系统初始化的时候，init 进程会从这个目录中读一些配置文件.
  /etc/rc.d/init.d /etc/rc.d/rc0.d /etc/rc.d/rc1.d  
最后 ,init 会执行rc.local 脚本。
The /etc/inittab file contains a significant amount of information concerning
boot up and shutdown.
Test the Network
 netsat ping 