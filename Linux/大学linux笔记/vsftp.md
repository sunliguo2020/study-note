 VSFTP配置大全

[root@sunliguo vsftpd]# /sbin/service vsftpd start
Starting vsftpd for vsftpd: [OK ]
3.2.2. 更换port 提供服务：将预设的port 21 更换为2121
为了安全，或是以port 来区隔不同的ftp 服务，我们可能会将ftp port 改为21 之外的port，那么，可参考以下步骤。
Step1. 修改/etc/vsftpd/vsftpd.conf
新增底下一行
listen_port=2121
Step2. 重新启动vsftpd
3.2.3. 特定使用者peter、john 不得变更目录
使用者的预设目录为/home/username，若是我们不希望使用者在ftp 时能够切换到上一层目录/home，则可参考以下步骤。
Step1. 修改/etc/vsftpd/vsftpd.conf
将底下三行
#chroot_list_enable=YES
# (default follows)
#chroot_list_file=/etc/vsftpd.chroot_list
改为
chroot_list_enable=YES
# (default follows)
chroot_list_file=/etc/vsftpd/chroot_list
Step2. 新增一个档案: /etc/vsftpd/chroot_list
内容增加两行：
peter
john
Step3. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd:[OK ]
Starting vsftpd for vsftpd: OK ]
若是peter 欲切换到根目录以外的目录，则会出现以下警告：
ftp> cd /home
550 Failed to change directory.
3.2.4. 取消anonymous 登入
若是读者的主机不希望使用者匿名登入，则可参考以下步骤。
Step1. 修改/etc/vsftpd/vsftpd.conf
将    anonymous_enable=YES
改为  anonymous_enable=NO
Step2. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: [OK ]
Starting vsftpd for vsftpd: [OK ]
3.2.5. 安排欢迎话语
若是我们希望使用者在登入时，能够看到欢迎话语，可能包括对该主机的说明，或是目录的介绍，可参考以下步骤。
首先确定在/etc/vsftpd/vsftpd.conf 当中是否有底下这一行
dirmessage_enable=YES
RedHat9 的默认值是有上面这行的。
接着，在各目录之中，新增名为.message 的档案，再这边假设有一个使用者test1，且此使用者的根目录下有个目录名为abc，那首先我们在/home/test1 之下新增.message，内容如下：
Hello~ Welcome to the home directory
This is for test only...
接着，在/home/test1/abc 的目录下新增.message，内容如下：
Welcome to abc's directory
This is subdir...
那么，当使用者test1 登入时，会看到以下讯息：
230- Hello~ Welcome to the home directory
230-
230- This is for test only...
230-
若是切换到abc 的目录，则会出现以下讯息：
250- Welcome to abc's directory
250-
250- This is subdir ...
3.2.6. 对于每一个联机，以独立的process 来运作一般启动vsftp 时，我们只会看到一个名为vsftpd 的process 在运作，但若是读者希望每一个联机，都能以独立的process 来呈现，则可执行以下步骤。
Step1. 修改/etc/vsftpd/vsftpd.conf
新增底下一行
setproctitle_enable=YES
Step2. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: OK ]
Starting vsftpd for vsftpd: OK ]
使用ps -ef 的指令，可以看告不同使用者联机的情形，如下图所示：
[root@home vsftpd]# ps -ef|grep ftp
root 2090 1 0 16:41 pts/0 00:00:00 vsftpd: LISTENER
nobody 2120 2090 0 17:18 ? 00:00:00 vsftpd: 192.168.10.244:
connected
test1 2122 2120 0 17:18 ? 00:00:00 vsftpd: 192.168.10.244/test1:
IDLE
nobody 2124 2090 0 17:19 ? 00:00:00 vsftpd: 192.168.10.244:
connected
test2 2126 2124 0 17:19 ? 00:00:00 vsftpd: 192.168.10.244/test2:
IDLE
root 2129 1343 0 17:20 pts/0 00:00:00 grep ftp
[root@home vsftpd]#
3.2.7. 限制传输档案的速度：本机的使用者最高速度为200KBytes/s，匿名登入
者所能使用的最高速度为50KBytes/s
Step1. 修改/etc/vsftpd/vsftpd.conf
新增底下两行
anon_max_rate=50000
local_max_rate=200000
Step2. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd:[ OK ]
Starting vsftpd for vsftpd:[ OK ]
在这边速度的单位为Bytes/s，其中anon_max_rate 所限制的是匿名登入的使用者，而local_max_rate 所限制的是本机的使用者。VSFTPD 对于速度的限制，范围大概在80%到120%之间，也就是我们限制最高速度为100KBytes/s，但实际的速度可能在80KBytes/s 到120KBytes/s 之间，当然，若是频宽不足时，数值会低于此限制。3.2.8. 针对不同的使用者限制不同的速度：假设test1 所能使用的最高速度为250KBytes/s，test2 所能使用的最高速度为500KBytes/s。
Step1. 修改/etc/vsftpd/vsftpd.conf
新增底下一行
user_config_dir=/etc/vsftpd/userconf
Step2. 新增一个目录：/etc/vsftpd/userconf
mkdir /etc/vsftpd/userconf
Step3. 在/etc/vsftpd/userconf 之下新增一个名为test1 的档案
内容增加一行：
local_max_rate=250000
Step4. 在/etc/vsftpd/userconf 之下新增一个名为test2 的档案
内容增加一行：
local_max_rate=500000
Step5. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: OK ]
Starting vsftpd for vsftpd: OK ]
3.2.9-1. 建置一个防火墙下的ftp server，使用PORT FTP mode：预设的ftp
port:21 以及ftp data port:20
启动VSFTPD 之后执行以下两行指令，只允许port 21 以及port 20 开放，
其它关闭。
iptables -A INPUT -p tcp -m multiport --dport 21,20 -j ACCEPT
iptables -A INPUT -p tcp -j REJECT --reject-with tcp-reset
3.2.9-2. 建置一个防火墙下的ftp server，使用PORT FTP mode：ftp port:2121
以及ftp data port:2020
Step1. 执行以下两行指令，只允许port 2121 以及port 2020 开放，其它关闭。
iptables -A INPUT -p tcp -m multiport --dport 2121,2020 -j ACCEPT
iptables -A INPUT -p tcp -j REJECT --reject-with tcp-reset
Step2. 修改/etc/vsftpd/vsftpd.conf
新增底下两行
listen_port=2121
ftp_data_port=2020
Step3. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: OK ]
Starting vsftpd for vsftpd: OK ]
在这边要注意，8、9 两个例子中，ftp client（如cuteftp）的联机方式不能
够选择passive mode，否则无法建立数据的联机。也就是读者可以连上ftp
server，但是执行ls、get 等等的指令时，便无法运作。
3.2.10. 建置一个防火墙下的ftp server，使用PASS FTP mode：ftp port:2121
以及ftp data port 从9981 到9986。
Step1. 执行以下两行指令，只允许port 2121 以及port 9981-9990 开放，其它关
闭。
iptables -A INPUT -p tcp -m multiport --dport
2121,9981,9982,9983,9984,9985,9986,9987,9988,9989,9990 -j ACCEPT
iptables -A INPUT -p tcp -j REJECT --reject-with tcp-reset
Step2. 修改/etc/vsftpd/vsftpd.conf
新增底下四行
listen_port=2121
pasv_enable=YES
pasv_min_port=9981
pasv_max_port=9986
Step3. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: OK ]
Starting vsftpd for vsftpd: OK ]
在这边要注意，在10 这个例子中，ftp client（如cuteftp）的联机方式必须
选择passive mode，否则无法建立数据的联机。也就是读者可以连上ftp
server，但是执行ls,get 等等的指令时，便无法运作。
8.2.11. 将vsftpd 与TCP_wrapper 结合
若是读者希望直接在/etc/hosts.allow 之中定义允许或是拒绝的来源地址，
可执行以下步骤。这是简易的防火墙设定。
Step1. 确定/etc/vsftpd/vsftpd.conf 之中tcp_wrappers 的设定为YES，如下图所示：
tcp_wrappers=YES
这是RedHat9 的默认值，基本上不需修改。
Step2. 重新启动vsftpd
[root@home vsftpd]# /sbin/service vsftpd restart
Shutting down vsftpd: OK ]
Starting vsftpd for vsftpd: OK ]
Step3. 设定/etc/hosts.allow，譬如提供111.22.33.4 以及10.1.1.1 到10.1.1.254 连线，则可做下图之设定：
vsftpd : 111.22.33.4 10.1.1. : allow
ALL : ALL : DENY
8.2.12. 将vsftpd 并入XINETD
若是读者希望将vsftpd 并入XINETD 之中，也就是7.x 版的预设设定，那么读者可以执行以下步骤。
Step1. 修改/etc/vsftpd/vsftpd.conf
将
listen=YES
改为
listen=NO
Step2. 新增一个档案： /etc/xinetd.d/vsftpd
内容如下：
service vsftpd
{
disable = no
socket_type = stream
wait = no
user = root
server = /usr/sbin/vsftpd
port = 21
log_on_success += PID HOST DURATION
log_on_failure += HOST
}
Step3. 重新启动xinetd
[root@home vsftpd]# /sbin/service xinetd restart
Stopping xinetd: OK ]
Starting xinetd: OK ]
3.2.3 设定档说明
在范例中，有些省略的设定可以在这边找到，譬如联机的总数、同一个位址的联机数、显示档案拥有者的名称等等，希望读者细读后，可以做出最适合自己的设定。
格式
vsftpd.conf 的内容非常单纯，每一行即为一项设定。若是空白行或是开头为#的一行，将会被忽略。内容的格式只有一种，如下所示
option=value
要注意的是，等号两边不能加空白，不然是不正确的设定。
＝＝＝ascii 设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
ascii_download_enable
管控是否可用ASCII 模式下载。默认值为NO。
ascii_upload_enable
管控是否可用ASCII 模式上传。默认值为NO。
＝＝＝个别使用者设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
chroot_list_enable
如果启动这项功能，则所有的本机使用者登入均可进到根目录之外的数据夹，除了列
在/etc/vsftpd.chroot_list 之中的使用者之外。默认值为NO。
userlist_enable
用法：YES/NO
若是启动此功能，则会读取/etc/vsftpd.user_list 当中的使用者名称。此项功能可以在询
问密码前就出现失败讯息，而不需要检验密码的程序。默认值为关闭。
userlist_deny
用法：YES/NO
这个选项只有在userlist_enable 启动时才会被检验。如果将这个选项设为YES，则在
/etc/vsftpd.user_list 中的使用者将无法登入﹔ 若设为NO ， 则只有在
/etc/vsftpd.user_list 中的使用者才能登入。而且此项功能可以在询问密码前就出现错误
讯息，而不需要检验密码的程序。
user_config_dir
定义个别使用者设定文件所在的目录，例如定义user_config_dir=/etc/vsftpd/userconf，
且主机上有使用者test1,test2，那我们可以在user_config_dir 的目录新增文件名为
test1 以及test2。若是test1 登入，则会读取user_config_dir 下的test1 这个档案内的设
定。默认值为无。
＝＝＝欢迎语设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
dirmessage_enable
如果启动这个选项，使用者第一次进入一个目录时，会检查该目录下是否有.message
这个档案，若是有，则会出现此档案的内容，通常这个档案会放置欢迎话语，或是对
该目录的说明。默认值为开启。
banner_file
当使用者登入时，会显示此设定所在的档案内容，通常为欢迎话语或是说明。默认值
为无。
ftpd_banner
这边可定义欢迎话语的字符串，相较于banner_file 是档案的形式，而ftpd_banner 是字
串的格式。预设为无。
＝＝＝特殊安全设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
chroot_local_user
如果设定为YES，那么所有的本机的使用者都可以切换到根目录以外的数据夹。预设
值为NO。
hide_ids
如果启动这项功能，所有档案的拥有者与群组都为ftp，也就是使用者登入使用ls -al
之类的指令，所看到的档案拥有者跟群组均为ftp。默认值为关闭。
ls_recurse_enable
若是启动此功能，则允许登入者使用ls -R 这个指令。默认值为NO。
write_enable
用法：YES/NO
这个选项可以控制FTP 的指令是否允许更改file system，譬如STOR、DELE、
RNFR、RNTO、MKD、RMD、APPE 以及SITE。预设是关闭。
setproctitle_enable
用法：YES/NO
启动这项功能，vsftpd 会将所有联机的状况已不同的process 呈现出来，换句话说，使
用ps -ef 这类的指令就可以看到联机的状态。默认值为关闭。
tcp_wrappers
用法：YES/NO
如果启动，则会将vsftpd 与tcp wrapper 结合，也就是可以在/etc/hosts.allow 与
/etc/hosts.deny 中定义可联机或是拒绝的来源地址。
pam_service_name
这边定义PAM 所使用的名称，预设为vsftpd。
secure_chroot_dir
这个选项必须指定一个空的数据夹且任何登入者都不能有写入的权限，当vsftpd 不需
要file system 的权限时，就会将使用者限制在此数据夹中。默认值为/usr/share/empty
＝＝＝纪录文件设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
xferlog_enable
用法：YES/NO
如果启动，上传与下载的信息将被完整纪录在底下xferlog_file 所定义的档案中。预设
为开启。
xferlog_file
这个选项可设定纪录文件所在的位置，默认值为/var/log/vsftpd.log。
xferlog_std_format
如果启动，则纪录文件将会写为xferlog 的标准格式，如同wu-ftpd 一般。默认值为关
闭。
＝＝＝逾时设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
accept_timeout
接受建立联机的逾时设定，单位为秒。默认值为60。
connect_timeout
响应PORT 方式的数据联机的逾时设定，单位为秒。默认值为60。
data_connection_timeout
建立数据联机的逾时设定。默认值为300 秒。
idle_session_timeout
发呆的逾时设定，若是超出这时间没有数据的传送或是指令的输入，则会强迫断线，
单位为秒。默认值为300。
＝＝＝速率限制＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
anon_max_rate
匿名登入所能使用的最大传输速度，单位为每秒多少bytes，0 表示不限速度。默认值
为0。
local_max_rate
本机使用者所能使用的最大传输速度，单位为每秒多少bytes，0 表示不限速度。预设
值为0。
＝＝＝新增档案权限设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
anon_umask
匿名登入者新增档案时的umask 数值。默认值为077。
file_open_mode
上传档案的权限，与chmod 所使用的数值相同。默认值为0666。
local_umask
本机登入者新增档案时的umask 数值。默认值为077。
＝＝＝port 设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
connect_from_port_20
用法：YES/NO
若设为YES，则强迫ftp-data 的数据传送使用port 20。默认值为YES。
ftp_data_port
设定ftp 数据联机所使用的port。默认值为20。
listen_port
FTP server 所使用的port。默认值为21。
pasv_max_port
建立资料联机所可以使用port 范围的上界，0 表示任意。默认值为0。
pasv_min_port
建立资料联机所可以使用port 范围的下界，0 表示任意。默认值为0。
＝＝＝其它＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
anon_root
使用匿名登入时，所登入的目录。默认值为无。
local_enable
用法：YES/NO
启动此功能则允许本机使用者登入。默认值为YES。
local_root
本机使用者登入时，将被更换到定义的目录下。默认值为无。
text_userdb_names
用法：YES/NO
当使用者登入后使用ls -al 之类的指令查询该档案的管理权时，预设会出现拥有者的
UID，而不是该档案拥有者的名称。若是希望出现拥有者的名称，则将此功能开启。
默认值为NO。
pasv_enable
若是设为NO，则不允许使用PASV 的模式建立数据的联机。默认值为开启。
＝＝＝更换档案所有权＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
chown_uploads
用法：YES/NO
若是启动，所有匿名上传数据的拥有者将被更换为chown_username 当中所设定的使
用者。这样的选项对于安全及管理，是很有用的。默认值为NO。
chown_username
这里可以定义当匿名登入者上传档案时，该档案的拥有者将被置换的使用者名称。预
设值为root。
＝＝＝guest 设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
guest_enable
用法：YES/NO
若是启动这项功能，所有的非匿名登入者都视为guest。默认值为关闭。
guest_username
这里将定义guest 的使用者名称。默认值为ftp。
＝＝＝anonymous 设定＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
anonymous_enable
用法：YES/NO
管控使否允许匿名登入，YES 为允许匿名登入，NO 为不允许。默认值为YES。
no_anon_password
若是启动这项功能，则使用匿名登入时，不会询问密码。默认值为NO。
anon_mkdir_write_enable
用法：YES/NO
如果设为YES，匿名登入者会被允许新增目录，当然，匿名使用者必须要有对上层目
录的写入权。默认值为NO。
anon_other_write_enable
用法：YES/NO
如果设为YES，匿名登入者会被允许更多于上传与建立目录之外的权限，譬如删除或
是更名。默认值为NO。
anon_upload_enable
用法：YES/NO
如果设为YES，匿名登入者会被允许上传目录的权限，当然，匿名使用者必须要有对
上层目录的写入权。默认值为NO。
anon_world_readable_only
用法：YES/NO
如果设为YES，匿名登入者会被允许下载可阅读的档案。默认值为YES。
ftp_username
定义匿名登入的使用者名称。默认值为ftp。
deny_email_enable
若是启动这项功能，则必须提供一个档案/etc/vsftpd.banner_emails，内容为email
address。若是使用匿名登入，则会要求输入email address，若输入的email address 在
此档案内，则不允许联机。默认值为NO。
＝＝＝Standalone 选项＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
listen
用法：YES/NO
若是启动，则vsftpd 将会以独立运作的方式执行，若是vsftpd 独立执行，如RedHat9
的默认值，则必须启动﹔若是vsftpd 包含在xinetd 之中，则必须关闭此功能，如
RedHat8。在RedHat9 的默认值为YES。
listen_address
若是vsftpd 使用standalone 的模式，可使用这个参数定义使用哪个IP address 提供这
项服务，若是主机上只有定义一个IP address，则此选项不需使用，若是有多个IP
address，可定义在哪个IP address 上提供ftp 服务。若是不设定，则所有的IP address
均会提供此服务。默认值为无。
max_clients
若是vsftpd 使用standalone 的模式，可使用这个参数定义最大的总联机数。超过这个
数目将会拒绝联机，0 表示不限。默认值为0。
max_per_ip
若是vsftpd 使用standalone 的模式，可使用这个参数定义每个ip address 所可以联机
的数目。超过这个数目将会拒绝联机，0 表示不限。默认值为0。
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
3.2.4 FTP 数字代码的意义
110 重新启动标记应答。
120 服务在多久时间内ready。
125 数据链路埠开启，准备传送。
150 文件状态正常，开启数据连接端口。
200 命令执行成功。
202 命令执行失败。
211 系统状态或是系统求助响应。
212 目录的状态。
213 文件的状态。
214 求助的讯息。
215 名称系统类型。
220 新的联机服务ready。
221 服务的控制连接埠关闭，可以注销。
225 数据连结开启，但无传输动作。
226 关闭数据连接端口，请求的文件操作成功。
227 进入passive mode。
230 使用者登入。
250 请求的文件操作完成。
257 显示目前的路径名称。
331 用户名称正确，需要密码。
332 登入时需要账号信息。
350 请求的操作需要进一部的命令。
421 无法提供服务，关闭控制连结。
425 无法开启数据链路。
426 关闭联机，终止传输。
450 请求的操作未执行。
451 命令终止：有本地的错误。
452 未执行命令：磁盘空间不足。
500 格式错误，无法识别命令。
501 参数语法错误。
502 命令执行失败。
503 命令顺序错误。
504 命令所接的参数不正确。
530 未登入。
532 储存文件需要账户登入。
550 未执行请求的操作。
551 请求的命令终止，类型未知。
552 请求的文件终止，储存位溢出。
553 未执行请求的的命令，名称不正确。







VSFTPD.CONF
Section: File Formats (5)
Index Return to Main Contents  
NAME
vsftpd.conf - config file for vsftpd  
DESCRIPTION
vsftpd.conf may be used to control various aspects of vsftpd's behaviour. By default, vsftpd looks for this file at the location /etc/vsftpd.conf. However, you may override this by specifying a command line argument 参数to vsftpd. The command line argument is the pathname of the configuration file for vsftpd. This behaviour is useful because you may wish to use an advanced inetd such as xinetd to launch vsftpd with different configuration files on a per virtual host basis.

 
FORMAT
The format of vsftpd.conf is very simple. Each line is either a comment or a directive. Comment lines start with a # and are ignored. A directive line has the format:

option=value

It is important to note that it is an error to put any space between the option, = and value.

Each setting has a compiled in default which may be modified in the configuration file.

 
BOOLEAN OPTIONS
Below is a list of boolean options. The value for a boolean option may be set to YES or NO.

allow_anon_ssl
    Only applies if ssl_enable is active. If set to YES, anonymous users will be allowed to use secured SSL connections.

    Default: NO 
anon_mkdir_write_enable
    If set to YES, anonymous users will be permitted 许可to create new directories under certain conditions. For this to work, the option write_enable must be activated, and the anonymous ftp user must have write permission on the parent directory.

    Default: NO 
anon_other_write_enable
    If set to YES, anonymous users will be permitted to perform write operations other than upload and create directory, such as deletion and renaming. This is generally not recommended but included for completeness.

    Default: NO 
anon_upload_enable
    If set to YES, anonymous users will be permitted to upload files under certain conditions. For this to work, the option write_enable must be activated, and the anonymous ftp user must have write permission on desired upload locations.

    Default: NO 
anon_world_readable_only
    When enabled, anonymous users will only be allowed to download files which are world readable. This is recognising that the ftp user may own files, especially in the presence of uploads.

    Default: YES 
anonymous_enable
    Controls whether anonymous logins are permitted or not. If enabled, both the usernames ftp and anonymous are recognised as anonymous logins.

    Default: YES 
ascii_download_enable
    When enabled, ASCII mode data transfers will be honoured on downloads.

    Default: NO 
ascii_upload_enable
    When enabled, ASCII mode data transfers will be honoured on uploads.

    Default: NO 
async_abor_enable
    When enabled, a special FTP command known as "async ABOR" will be enabled. Only ill advised FTP clients will use this feature. Additionally, this feature is awkward to handle, so it is disabled by default. Unfortunately, some FTP clients will hang when cancelling a transfer unless this feature is available, so you may wish to enable it.

    Default: NO 
background
    When enabled, and vsftpd is started in "listen" mode, vsftpd will background the listener process. i.e. control will immediately be returned to the shell which launched vsftpd.

    Default: NO 
check_shell
    Note! This option only has an effect for non-PAM builds of vsftpd. If disabled, vsftpd will not check /etc/shells for a valid user shell for local logins.

    Default: YES 
chmod_enable
    When enables, allows use of the SITE CHMOD command. NOTE! This only applies to local users. Anonymous users never get to use SITE CHMOD.

    Default: YES 
chown_uploads
    If enabled, all anonymously uploaded files will have the ownership changed to the user specified in the setting chown_username. This is useful from an administrative, and perhaps security, standpoint.

    Default: NO 
chroot_list_enable
    If activated, you may provide a list of local users who are placed in a chroot() jail in their home directory upon login. The meaning is slightly different if chroot_local_user is set to YES. In this case, the list becomes a list of users which are NOT to be placed in a chroot() jail. By default, the file containing this list is /etc/vsftpd.chroot_list, but you may override this with the chroot_list_file setting.

    Default: NO 
chroot_local_user
    If set to YES, local users will be (by default) placed in a chroot() jail in their home directory after login. Warning: This option has security implications, especially if the users have upload permission, or shell access. Only enable if you know what you are doing. Note that these security implications are not vsftpd specific. They apply to all FTP daemons which offer to put local users in chroot() jails.

    Default: NO 
connect_from_port_20
    This controls whether PORT style data connections use port 20 (ftp-data) on the server machine. For security reasons, some clients may insist that this is the case. Conversely, disabling this option enables vsftpd to run with slightly less privilege.

    Default: NO (but the sample config file enables it) 
deny_email_enable
    If activated, you may provide a list of anonymous password e-mail responses which cause login to be denied. By default, the file containing this list is /etc/vsftpd.banned_emails, but you may override this with the banned_email_file setting.

    Default: NO 
dirlist_enable
    If set to NO, all directory list commands will give permission denied.

    Default: YES 
dirmessage_enable
    If enabled, users of the FTP server can be shown messages when they first enter a new directory. By default, a directory is scanned for the file .message, but that may be overridden with the configuration setting message_file.

    Default: NO (but the sample config file enables it) 
download_enable
    If set to NO, all download requests will give permission denied.

    Default: YES 
dual_log_enable
    If enabled, two log files are generated in parallel, going by default to /var/log/xferlog and /var/log/vsftpd.log. The former is a wu-ftpd style transfer log, parseable by standard tools. The latter is vsftpd's own style log.

    Default: NO 
force_dot_files
    If activated, files and directories starting with . will be shown in directory listings even if the "a" flag was not used by the client. This override excludes the "." and ".." entries.

    Default: NO 
force_local_data_ssl
    Only applies if ssl_enable is activated. If activated, all non-anonymous logins are forced to use a secure SSL connection in order to send and receive data on data connections.

    Default: YES 
force_local_logins_ssl
    Only applies if ssl_enable is activated. If activated, all non-anonymous logins are forced to use a secure SSL connection in order to send the password.

    Default: YES 
guest_enable
    If enabled, all non-anonymous logins are classed as "guest" logins. A guest login is remapped to the user specified in the guest_username setting.

    Default: NO 
hide_ids
    If enabled, all user and group information in directory listings will be displayed as "ftp".

    Default: NO 
listen
    If enabled, vsftpd will run in standalone mode. This means that vsftpd must not be run from an inetd of some kind. Instead, the vsftpd executable is run once directly. vsftpd itself will then take care of listening for and handling incoming connections.

    Default: NO 
listen_ipv6
    Like the listen parameter, except vsftpd will listen on an IPv6 socket instead of an IPv4 one. This parameter and the listen parameter are mutually exclusive.

    Default: NO 
local_enable
    Controls whether local logins are permitted or not. If enabled, normal user accounts in /etc/passwd may be used to log in.

    Default: NO 
log_ftp_protocol
    When enabled, all FTP requests and responses are logged, providing the option xferlog_std_format is not enabled. Useful for debugging.

    Default: NO 
ls_recurse_enable
    When enabled, this setting will allow the use of "ls -R". This is a minor security risk, because a ls -R at the top level of a large site may consume a lot of resources.

    Default: NO 
no_anon_password
    When enabled, this prevents vsftpd from asking for an anonymous password - the anonymous user will log straight in.

    Default: NO 
no_log_lock
    When enabled, this prevents vsftpd from taking a file lock when writing to log files. This option should generally not be enabled. It exists to workaround operating system bugs such as the Solaris / Veritas filesystem combination which has been observed to sometimes exhibit hangs trying to lock log files.

    Default: NO 
one_process_model
    If you have a Linux 2.4 kernel, it is possible to use a different security model which only uses one process per connection. It is a less pure security model, but gains you performance. You really don't want to enable this unless you know what you are doing, and your site supports huge numbers of simultaneously connected users.

    Default: NO 
passwd_chroot_enable
    If enabled, along with chroot_local_user , then a chroot() jail location may be specified on a per-user basis. Each user's jail is derived from their home directory string in /etc/passwd. The occurrence of /./ in the home directory string denotes that the jail is at that particular location in the path.

    Default: NO 
pasv_enable
    Set to NO if you want to disallow the PASV method of obtaining a data connection.

    Default: YES 
pasv_promiscuous
    Set to YES if you want to disable the PASV security check that ensures the data connection originates from the same IP address as the control connection. Only enable if you know what you are doing! The only legitimate use for this is in some form of secure tunnelling scheme, or perhaps to facilitate FXP support.

    Default: NO 
port_enable
    Set to NO if you want to disallow the PORT method of obtaining a data connection.

    Default: YES 
port_promiscuous
    Set to YES if you want to disable the PORT security check that ensures that outgoing data connections can only connect to the client. Only enable if you know what you are doing!

    Default: NO 
run_as_launching_user
    Set to YES if you want vsftpd to run as the user which launched vsftpd. This is useful where root access is not available. MASSIVE WARNING! Do NOT enable this option unless you totally know what you are doing, as naive use of this option can create massive security problems. Specifically, vsftpd does not / cannot use chroot technology to restrict file access when this option is set (even if launched by root). A poor substitute could be to use a deny_file setting such as {/*,*..*}, but the reliability of this cannot compare to chroot, and should not be relied on. If using this option, many restrictions on other options apply. For example, options requiring privilege such as non-anonymous logins, upload ownership changing, connecting from port 20 and listen ports less than 1024 are not expected to work. Other options may be impacted.

    Default: NO 
secure_email_list_enable
    Set to YES if you want only a specified list of e-mail passwords for anonymous logins to be accepted. This is useful as a low-hassle way of restricting access to low-security content without needing virtual users. When enabled, anonymous logins are prevented unless the password provided is listed in the file specified by the email_password_file setting. The file format is one password per line, no extra whitespace. The default filename is /etc/vsftpd.email_passwords.

    Default: NO 
session_support
    This controls whether vsftpd attempts to maintain sessions for logins. If vsftpd is maintaining sessions, it will try and update utmp and wtmp. It will also open a pam_session if using PAM to authenticate, and only close this upon logout. You may wish to disable this if you do not need session logging, and you wish to give vsftpd more opportunity to run with less processes and / or less privilege. NOTE - utmp and wtmp support is only provided with PAM enabled builds.

    Default: NO 
setproctitle_enable
    If enabled, vsftpd will try and show session status information in the system process listing. In other words, the reported name of the process will change to reflect what a vsftpd session is doing (idle, downloading etc). You probably want to leave this off for security purposes.

    Default: NO 
ssl_enable
    If enabled, and vsftpd was compiled against OpenSSL, vsftpd will support secure connections via SSL. This applies to the control connection (including login) and also data connections. You'll need a client with SSL support too. NOTE!! Beware enabling this option. Only enable it if you need it. vsftpd can make no guarantees about the security of the OpenSSL libraries. By enabling this option, you are declaring that you trust the security of your installed OpenSSL library.

    Default: NO 
ssl_sslv2
    Only applies if ssl_enable is activated. If enabled, this option will permit SSL v2 protocol connections. TLS v1 connections are preferred.

    Default: NO 
ssl_sslv3
    Only applies if ssl_enable is activated. If enabled, this option will permit SSL v3 protocol connections. TLS v1 connections are preferred.

    Default: NO 
ssl_tlsv1
    Only applies if ssl_enable is activated. If enabled, this option will permit TLS v1 protocol connections. TLS v1 connections are preferred.

    Default: YES 
syslog_enable
    If enabled, then any log output which would have gone to /var/log/vsftpd.log goes to the system log instead. Logging is done under the FTPD facility.

    Default: NO 
tcp_wrappers
    If enabled, and vsftpd was compiled with tcp_wrappers support, incoming connections will be fed through tcp_wrappers access control. Furthermore, there is a mechanism for per-IP based configuration. If tcp_wrappers sets the VSFTPD_LOAD_CONF environment variable, then the vsftpd session will try and load the vsftpd configuration file specified in this variable.

    Default: NO 
text_userdb_names
    By default, numeric IDs are shown in the user and group fields of directory listings. You can get textual names by enabling this parameter. It is off by default for performance reasons.

    Default: NO 
tilde_user_enable
    If enabled, vsftpd will try and resolve pathnames such as ~chris/pics, i.e. a tilde followed by a username. Note that vsftpd will always resolve the pathnames ~ and ~/something (in this case the ~ resolves to the initial login directory). Note that ~user paths will only resolve if the file /etc/passwd may be found within the _current_ chroot() jail.

    Default: NO 
use_localtime
    If enabled, vsftpd will display directory listings with the time in your local time zone. The default is to display GMT. The times returned by the MDTM FTP command are also affected by this option.

    Default: NO 
use_sendfile
    An internal setting used for testing the relative benefit of using the sendfile() system call on your platform.

    Default: YES 
userlist_deny
    This option is examined if userlist_enable is activated. If you set this setting to NO, then users will be denied login unless they are explicitly listed in the file specified by userlist_file. When login is denied, the denial is issued before the user is asked for a password.

    Default: YES 
userlist_enable
    If enabled, vsftpd will load a list of usernames, from the filename given by userlist_file. If a user tries to log in using a name in this file, they will be denied before they are asked for a password. This may be useful in preventing cleartext passwords being transmitted. See also userlist_deny.

    Default: NO 
virtual_use_local_privs
    If enabled, virtual users will use the same privileges as local users. By default, virtual users will use the same privileges as anonymous users, which tends to be more restrictive (especially in terms of write access).

    Default: NO 
write_enable
    This controls whether any FTP commands which change the filesystem are allowed or not. These commands are: STOR, DELE, RNFR, RNTO, MKD, RMD, APPE and SITE.

    Default: NO 
xferlog_enable
    If enabled, a log file will be maintained detailling uploads and downloads. By default, this file will be placed at /var/log/vsftpd.log, but this location may be overridden using the configuration setting vsftpd_log_file.

    Default: NO (but the sample config file enables it) 
xferlog_std_format
    If enabled, the transfer log file will be written in standard xferlog format, as used by wu-ftpd. This is useful because you can reuse existing transfer statistics generators. The default format is more readable, however. The default location for this style of log file is /var/log/xferlog, but you may change it with the setting xferlog_file.

    Default: NO

 
NUMERIC OPTIONS
Below is a list of numeric options. A numeric option must be set to a non negative integer. Octal numbers are supported, for convenience of the umask options. To specify an octal number, use 0 as the first digit of the number.

accept_timeout
    The timeout, in seconds, for a remote client to establish connection with a PASV style data connection.

    Default: 60 
anon_max_rate
    The maximum data transfer rate permitted, in bytes per second, for anonymous clients.

    Default: 0 (unlimited) 
anon_umask
    The value that the umask for file creation is set to for anonymous users. NOTE! If you want to specify octal values, remember the "0" prefix otherwise the value will be treated as a base 10 integer!

    Default: 077 
connect_timeout
    The timeout, in seconds, for a remote client to respond to our PORT style data connection.

    Default: 60 
data_connection_timeout
    The timeout, in seconds, which is roughly the maximum time we permit data transfers to stall for with no progress. If the timeout triggers, the remote client is kicked off.

    Default: 300 
file_open_mode
    The permissions with which uploaded files are created. Umasks are applied on top of this value. You may wish to change to 0777 if you want uploaded files to be executable.

    Default: 0666 
ftp_data_port
    The port from which PORT style connections originate (as long as the poorly named connect_from_port_20 is enabled).

    Default: 20 
idle_session_timeout
    The timeout, in seconds, which is the maximum time a remote client may spend between FTP commands. If the timeout triggers, the remote client is kicked off.

    Default: 300 
listen_port
    If vsftpd is in standalone mode, this is the port it will listen on for incoming FTP connections.

    Default: 21 
local_max_rate
    The maximum data transfer rate permitted, in bytes per second, for local authenticated users.

    Default: 0 (unlimited) 
local_umask
    The value that the umask for file creation is set to for local users. NOTE! If you want to specify octal values, remember the "0" prefix otherwise the value will be treated as a base 10 integer!

    Default: 077 
max_clients
    If vsftpd is in standalone mode, this is the maximum number of clients which may be connected. Any additional clients connecting will get an error message.

    Default: 0 (unlimited) 
max_per_ip
    If vsftpd is in standalone mode, this is the maximum number of clients which may be connected from the same source internet address. A client will get an error message if they go over this limit.

    Default: 0 (unlimited) 
pasv_max_port
    The maximum port to allocate for PASV style data connections. Can be used to specify a narrow port range to assist firewalling.

    Default: 0 (use any port) 
pasv_min_port
    The minimum port to allocate for PASV style data connections. Can be used to specify a narrow port range to assist firewalling.

    Default: 0 (use any port) 
trans_chunk_size
    You probably don't want to change this, but try setting it to something like 8192 for a much smoother bandwidth limiter.

    Default: 0 (let vsftpd pick a sensible setting)

 
STRING OPTIONS
Below is a list of string options.

anon_root
    This option represents a directory which vsftpd will try to change into after an anonymous login. Failure is silently ignored.

    Default: (none) 
banned_email_file
    This option is the name of a file containing a list of anonymous e-mail passwords which are not permitted. This file is consulted if the option deny_email_enable is enabled.

    Default: /etc/vsftpd.banned_emails 
banner_file
    This option is the name of a file containing text to display when someone connects to the server. If set, it overrides the banner string provided by the ftpd_banner option.

    Default: (none) 
chown_username
    This is the name of the user who is given ownership of anonymously uploaded files. This option is only relevant if another option, chown_uploads, is set.

    Default: root 
chroot_list_file
    The option is the name of a file containing a list of local users which will be placed in a chroot() jail in their home directory. This option is only relevant if the option chroot_list_enable is enabled. If the option chroot_local_user is enabled, then the list file becomes a list of users to NOT place in a chroot() jail.

    Default: /etc/vsftpd.chroot_list 
cmds_allowed
    This options specifies a comma separated list of allowed FTP commands (post login. USER, PASS and QUIT are always allowed pre-login). Other commands are rejected. This is a powerful method of really locking down an FTP server. Example: cmds_allowed=PASV,RETR,QUIT

    Default: (none) 
deny_file
    This option can be used to set a pattern for filenames (and directory names etc.) which should not be accessible in any way. The affected items are not hidden, but any attempt to do anything to them (download, change into directory, affect something within directory etc.) will be denied. This option is very simple, and should not be used for serious access control - the filesystem's permissions should be used in preference. However, this option may be useful in certain virtual user setups. In particular aware that if a filename is accessible by a variety of names (perhaps due to symbolic links or hard links), then care must be taken to deny access to all the names. Access will be denied to items if their name contains the string given by hide_file, or if they match the regular expression specified by hide_file. Note that vsftpd's regular expression matching code is a simple implementation which is a subset of full regular expression functionality. Because of this, you will need to carefully and exhaustively test any application of this option. And you are recommended to use filesystem permissions for any important security policies due to their greater reliability. Example: deny_file={*.mp3,*.mov,.private}

    Default: (none) 
dsa_cert_file
    This option specifies the location of the DSA certificate to use for SSL encrypted connections.

    Default: (none - an RSA certificate suffices) 
email_password_file
    This option can be used to provide an alternate file for usage by the secure_email_list_enable setting.

    Default: /etc/vsftpd.email_passwords 
ftp_username
    This is the name of the user we use for handling anonymous FTP. The home directory of this user is the root of the anonymous FTP area.

    Default: ftp 
ftpd_banner
    This string option allows you to override the greeting banner displayed by vsftpd when a connection first comes in.

    Default: (none - default vsftpd banner is displayed) 
guest_username
    See the boolean setting guest_enable for a description of what constitutes a guest login. This setting is the real username which guest users are mapped to.

    Default: ftp 
hide_file
    This option can be used to set a pattern for filenames (and directory names etc.) which should be hidden from directory listings. Despite being hidden, the files / directories etc. are fully accessible to clients who know what names to actually use. Items will be hidden if their names contain the string given by hide_file, or if they match the regular expression specified by hide_file. Note that vsftpd's regular expression matching code is a simple implementation which is a subset of full regular expression functionality. Example: hide_file={*.mp3,.hidden,hide*,h?}

    Default: (none) 
listen_address
    If vsftpd is in standalone mode, the default listen address (of all local interfaces) may be overridden by this setting. Provide a numeric IP address.

    Default: (none) 
listen_address6
    Like listen_address, but specifies a default listen address for the IPv6 listener (which is used if listen_ipv6 is set). Format is standard IPv6 address format.

    Default: (none) 
local_root
    This option represents a directory which vsftpd will try to change into after a local (i.e. non-anonymous) login. Failure is silently ignored.

    Default: (none) 
message_file
    This option is the name of the file we look for when a new directory is entered. The contents are displayed to the remote user. This option is only relevant if the option dirmessage_enable is enabled.

    Default: .message 
nopriv_user
    This is the name of the user that is used by vsftpd when it wants to be totally unprivileged. Note that this should be a dedicated user, rather than nobody. The user nobody tends to be used for rather a lot of important things on most machines.

    Default: nobody 
pam_service_name
    This string is the name of the PAM service vsftpd will use.

    Default: ftp 
pasv_address
    Use this option to override the IP address that vsftpd will advertise in response to the PASV command. Provide a numeric IP address.

    Default: (none - the address is taken from the incoming connected socket) 
rsa_cert_file
    This option specifies the location of the RSA certificate to use for SSL encrypted connections.

    Default: /usr/share/ssl/certs/vsftpd.pem 
secure_chroot_dir
    This option should be the name of a directory which is empty. Also, the directory should not be writable by the ftp user. This directory is used as a secure chroot() jail at times vsftpd does not require filesystem access.

    Default: /usr/share/empty 
ssl_ciphers
    This option can be used to select which SSL ciphers vsftpd will allow for encrpyted SSL connections. See the ciphers man page for further details. Note that restricting ciphers can be a useful security precaution as it prevents malicious remote parties forcing a cipher which they have found problems with.

    Default: DES-CBC3-SHA 
user_config_dir
    This powerful option allows the override of any config option specified in the manual page, on a per-user basis. Usage is simple, and is best illustrated with an example. If you set user_config_dir to be /etc/vsftpd_user_conf and then log on as the user "chris", then vsftpd will apply the settings in the file /etc/vsftpd_user_conf/chris for the duration of the session. The format of this file is as detailed in this manual page! PLEASE NOTE that not all settings are effective on a per-user basis. For example, many settings only prior to the user's session being started. Examples of settings which will not affect any behviour on a per-user basis include listen_address, banner_file, max_per_ip, max_clients, xferlog_file, etc.

    Default: (none) 
user_sub_token
    This option is useful is conjunction with virtual users. It is used to automatically generate a home directory for each virtual user, based on a template. For example, if the home directory of the real user specified via guest_username is /home/virtual/$USER, and user_sub_token is set to $USER, then when virtual user fred logs in, he will end up (usually chroot()'ed) in the directory /home/virtual/fred. This option also takes affect if local_root contains user_sub_token.

    Default: (none) 
userlist_file
    This option is the name of the file loaded when the userlist_enable option is active.

    Default: /etc/vsftpd.user_list 
vsftpd_log_file
    This option is the name of the file to which we write the vsftpd style log file. This log is only written if the option xferlog_enable is set, and xferlog_std_format is NOT set. Alternatively, it is written if you have set the option dual_log_enable. One further complication - if you have set syslog_enable, then this file is not written and output is sent to the system log instead.

    Default: /var/log/vsftpd.log 
xferlog_file
    This option is the name of the file to which we write the wu-ftpd style transfer log. The transfer log is only written if the option xferlog_enable is set, along with xferlog_std_format. Alternatively, it is written if you have set the option dual_log_enable.

    Default: /var/log/xferlog 
