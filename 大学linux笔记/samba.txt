  samba的核心是两个守护进程smbd和nmbd程序.smbd 监听tcp 139 端口，nmbd 监听udp
137 和138 端口.
smbd和nmbd使用的全部信息保存在smb.conf文件中.smbd进程作用是处理来到smb数据包，为使用该文件包的资源与linux进行协商，
nmbd进程使其它主机能浏览linux服务器。
检查配置文件的正确性：
  #testparm
启动samba服务器
  #service smb start 
  #pstree |grep mbd
检查服务器所共享的资源
 #smbclinet -L localhost
列出samba的资源使用情况
 #smbstatus 
 #smbstatus -b 
samb 客户端工具
smbtree -b -D -U user%passwd 显示局域网中的所有共享主机和目录列表

nmblookup \* 显示一台主机的netbios主机名


smbclient 显示登录局域网中的共享文件夹
smbclient -L host
smbclient －U user
smbclient //192.168.1.3/ -U user%password
smbmount //192.168.13.1/test /mnt -o username=user%passwd
mount -t smbfs //server/share /locldir

smbtar 远程备份网上邻居中的文件
smbtar -s server -u user -p passwd -x sharename -t output
          Samba 服务器配置
/etc/samba/smb.conf

workgroup=workgroup 
security=share
[doc]
   path=/usr/share
   comment=share documents
   public=yes
   valid users = <username> <@groupname>
用户账号映射
 [global] 
    username map=/etc/samba/smbusers
    #smbuseradd unixname:mapname
 [home]
    command Home Directories
    valid users=%S
    browseable=no
    write lsit = redhat
    writable=yes
service smb restart
smbclient -L localhost
