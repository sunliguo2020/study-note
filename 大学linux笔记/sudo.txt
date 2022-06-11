sodu 使用
配置文件:
     /etc/sudoers
 The file must be edited with the 'visudo' command.
用visudo 打开/etc/sudoers

Users can run what software on which machines (the sudoers file can be shared
between multiple systems).
Syntax: 
      user MACHINE=COMMAND
 Allow root to run any commands anywhere
   root	 ALL=(ALL)   ALL
用户名  host=(username)  command
tom     ALL=(ALL)        NOPASSWD:/sbin/service

例子:
   1> tom    ALL=(lake)   /bin/ls
 tom$sudo -u lake ls ~lake

2>  ##ALllows people in group wheel to run all commands
       %wheel     ALL=(ALL)     ALL
    ##Same thing without a password
      %wherl     ALL=(ALL)   NOPASSWD:ALL
3>  ##Allows members of the users group to shutdown this system
    %users localhost=/sbin/shutdown -h now
sudo -l 
sudo -u
sudo

sudo /etc/init.d/httpd start
/etc/sudoers
visodu
root ALL=(ALL) ALL
 username host=(user) /bin/ls
 tom	ALL=(ALL)  /etc/init.d/httpd
sudo -l
tom ALL=(ALL) NOPASSWD:/sbin/service
