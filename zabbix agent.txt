安装
 yum install zabbix22-agent -y
 
[root@localhost 201702]# rpm -qa|grep zabbix
zabbix22-agent-2.2.21-1.el7.x86_64
zabbix22-2.2.21-1.el7.x86_64
[root@localhost 201702]# rpm -ql zabbix22
/etc/zabbix
/etc/zabbix/zabbix_agentd.conf
/etc/zabbix_agentd.conf
/usr/bin/zabbix_get
/usr/bin/zabbix_sender
/usr/share/doc/zabbix22-2.2.21
/usr/share/doc/zabbix22-2.2.21/AUTHORS
/usr/share/doc/zabbix22-2.2.21/COPYING
/usr/share/doc/zabbix22-2.2.21/ChangeLog
/usr/share/doc/zabbix22-2.2.21/NEWS
/usr/share/doc/zabbix22-2.2.21/README
/usr/share/doc/zabbix22-2.2.21/zabbix-fedora-epel.README
/usr/share/man/man1/zabbix_get.1.gz
/usr/share/man/man1/zabbix_sender.1.gz
[root@localhost 201702]# rpm -ql zabbix22-agent
/etc/logrotate.d/zabbix-agent
/etc/zabbix/zabbix_agent.conf
/etc/zabbix/zabbix_agentd.conf
/etc/zabbix_agent.conf
/etc/zabbix_agentd.conf
/run/zabbix
/usr/lib/systemd/system/zabbix-agent.service
/usr/lib/tmpfiles.d/zabbix.conf
/usr/sbin/zabbix_agent
/usr/sbin/zabbix_agentd
/usr/share/doc/zabbix22-agent-2.2.21
/usr/share/doc/zabbix22-agent-2.2.21/userparameter_examples.conf
/usr/share/doc/zabbix22-agent-2.2.21/userparameter_mysql.conf
/usr/share/man/man8/zabbix_agentd.8.gz
/var/lib/zabbix
/var/log/zabbix

[sunliguo@localhost ~]$ ls -l /etc/zabbix*
-rw-r--r--. 1 root root 2455 Dec 29 18:07 /etc/zabbix_agent.conf
-rw-r--r--. 1 root root 7446 Dec 29 18:07 /etc/zabbix_agentd.conf

/etc/zabbix:
total 0
lrwxrwxrwx. 1 root root 22 Jan 23 10:55 zabbix_agent.conf -> /etc/zabbix_agent.conf
lrwxrwxrwx. 1 root root 23 Jan 23 10:55 zabbix_agentd.conf -> /etc/zabbix_agentd.conf
修改配置文件：
[sunliguo@localhost ~]$ vi zabbix_agent.conf
Server=172.19.35.19
[root@localhost etc]# grep ^[a-Z] zabbix_agentd.conf
PidFile=/run/zabbix/zabbix_agentd.pid
LogFile=/var/log/zabbix/zabbix_agentd.log
LogFileSize=0
Server=192.168.10.98
ServerActive=192.168.10.98
Hostname=test01
