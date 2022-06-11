/var/log/secure
/var/log/wtmp  : 记录登录者的资料  last
/var/log/messages :

syslogd :进行系统或者网络服务的登录记录工作

/etc/syslog.conf
auth,authpriv 认证有关的
daemon  与各个daemon有关的讯息
cron
kern
lpr :
mail
news


logrotate : 
facility.priority
facility.level[;facility.level..]      
facility 是产生信息的系统应用程序或工具
level 是这个信息的重要程度
   priority:
     debug   debugging information   调试信息
     info    general information messages    一般信息
     notice  normal but significant ,condition 值得注意的信息
     warning warning messages     警告
     err     error condition    一般性错误
     crit    critical condition  严重错误
     alert   immediate action required   紧急情况
     emerg   system no longer aviailable
facility 包含：
  auth  认证信息
  cron 系统执行定期任务时发出的信息
  daemon 某些系统的守护程序的syslog
  kern   内核的信息
  lpr  打印机
  mail 处理邮件的守护进程发出的信息
  mark  定时发送消息时的程序
  news 
  user  本地用户的应用程序的信息
  uucp 
  ×  所有可能的facility

