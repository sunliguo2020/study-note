自动挂载访问的分区

autofs软件包
  主配置文件 /etc/auto.master
 格式： 
    挂载目录    映射文件           参数
    /misc       /etc/auto.misc   --timeout=60

   映射文件 /etc/auto.misc 格式
      关键字     挂载选项     		设备
   例子:
     cd  	-fstype=iso9600,ro	:/dev/cdrom
     fd 	-fstype=atuo		:/dev/fd0
     linux	-fstype=nfs,ro		10.0.0.0:/var/ftp/pub	
     win 	-fstype=smbfs,username=redhat%123	://win2000/c 
 重启autofs  service autofs restart 
 访问设备的方法：挂载目录+关键字
 例子: ls /misc/cd
查看日志查错   tail /var/log/message
