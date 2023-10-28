linux技巧收集

1 变文件或目录之读、写、执行之允许权
====================================
执行格式：chmod [-R] mode name ( name 可为文件名或目录名;mode可为 3 个 8 位元之数字，或利用ls -l 命令，列出文件或目录之读、写、执行允许权之文字缩写。)
mode : rwx rwx rwx r:read w:write x:execute(user group other 缩写为: u g o)
Example :
% chmod 755 dir1　将目录dir1，设定成任何使用者，皆有读取及执行之权利，但只有拥有者可做修改。
% chmod 700 file1 将文件file1，设定只有拥有者可以读、写和执行。
% chmod o+x file2 将文件file2，增加拥有者可以执行之权利。
% chmod g+x file3 将文件file3，增加群组使用者可执行之权利。
% chmod o-r file4 将文件file4，除去其它使用者可读取之权利。
改变文件或目录之拥有权
======================
执行格式：chown [-R] username name ( name 可为文件名或目录名。)
Example ：
% chown user file1 将文件 file1 之拥有权，改为使用者 user 所有。
% chown -R user dir1 将目录 dir1，及其下所有文件和子目录之拥有权，改为使用者 user 所有。
检查自己所属之群组名称
======================
执行格式：groups
Example :
% groups
改变文件或目录之群组拥有权
==========================
执行格式：chgrp [-R] groupname name ( name 可为文件名或目录名 )
Example :
% chgrp vlsi file1 将文件 file1 之群组拥有权，改为 vlsi 群组。
% chgrp -R image dir1 将目录dir1，及其下所有文件和子目录，改为 image 群组。

改变文件或目录之最后修改时间(
变为当前时间)
=========================================
执行格式：touch name ( name 可为文件或目录名称。)
Example :
% touch file1
% touch dir1
文件之连结
=================
同一文件，可拥有一个以上之名称，可将文件做数个连结。
执行格式：ln oldname newname ( Hard link )
Example ：
% ln file1 file2 　　将名称 file2，连结至文件 file1。
执行格式：ln -s oldname newname ( Symblick link )
Example ：
% ln -s file3 file4　将名称 file4，连结至文件file3。
文件之字串找寻
==============
执行格式：grep string file
Example ：
% grep abc file1 寻找文件file1中，列出字串 abc 所在之整行文字内容。
找寻文件或命令之路径
====================
执行格式：whereis command ( 显示命令之路径。)
执行格式：which command ( 显示命令之路径，及使用者所定义之别 )
执行格式：whatis command ( 显示命令功能之摘要。)
执行格式：find search-path -name filename -print ( 搜寻指定路径下，某文件之路径 )
Example ：
% find / -name file1 -print ( 自根目录下，寻找文件名为 file1 之路径)
比较文件或目录之内容
====================
执行格式：diff [-r] name1 name2 ( name1 name2 可同时为文件名，或目录名称 )
Example :
% diff file1 file2 比较文件 file1 与 file2 内，各行之不同处。
% diff -r dir1 dir2 比较目录 dir1 与 dir2 内，各文件之不同处。
如何实现为一个网卡绑定多个IP地址？ 
====================================
　　Linux的网络设备配置文件存放在/etc/sysconfig/network-scripts里面，对于以太网的第一个网络设备，配置文件名一般为 ifcfg-eth0 如果需要为第一个网络设备绑定多一个IP地址，只需要在/etc/sysconfig/network-scripts目录里面创建一个名为ifcfg-eth0:0的文件，内容样例为：
DEVICE="eth0:0"
IPADDR="211.100.10.119"
NETMASK="255.255.255.0"
ONBOOT="yes"
　　其中的DEVICE为设备的名称，IPADDR为此设备的IP地址，NETMASK为子网掩码，ONBOOT表示在系统启动时自动启动。
　　如果需要再绑定多一个IP地址，只需要把文件名和文件内的DEVICE中的eth0:x加一即可。LINUX最多可以支持255个IP别名。 
如何设置login后欢迎信息
==================================== 
　　修改/etc/motd，往里面写入文本，就能使用户通过telnet正确登录后执行shell之前得到相应的提示信息。
　　motd就是“messages of the day”，也就是当日信息的意思。管理员可以往里面写一些需要注意的事项或者通知等来提醒正式用户。 
如何设置login前欢迎界面 
====================================
　　修改/etc/issue或者issue.net，往里面写入文本，就能使得用户在login前得到相应的提示，这将有助于用户分辨自己正在连接哪里的主机。
　　issue的内容是出现在本机登录的用户界面上，而issue.net则是在用户通过网络telnet的时候出现。 
如何在bash下快速执行某个特定历史命令
====================================
在bash下面按ctrl+r可以查找历史命令中匹配的命令并执行
如何查看进程继承关系
====================================
直接在命令行中输入
pstree
即可，程序会以树状结构方式列出系统中正在运行的各进程之间的继承关系。 
如何找出内存占用最大的进程 
====================================
除了可以使用top命令查看内存使用情况之外，还可以使用更快的命令行命令，相关的命令如下：
ps aux | sort +4n
或者
ps aux | sort +5n 
如何在Linux下面编辑二进制文件 
====================================
到http://freshmeat.net/redir/hexedit/4088/url_tgz/hexedit-1.2.3.src.tgz下载hexedit安装到系统上，就能用hexedit filename来编辑二进制文件。 
如何设置用户密码过期时间 
====================================
设置某个用户的密码过期时间可以用usermod -e来设置，如果要统一设置用户的密码过期时间，那么就要修改/etc/login.defs里面的PASS_MAX_DAYS，比如修改所有用户的密码过期时间是30天：
PASS_MAX_DAYS 30
如果这个值是99999，那么表示密码永不过期。 
如何修改网卡MAC地址 
====================================
首先必须关闭网卡设备，否则会报告系统忙，无法更改。
命令是： /sbin/ifconfig eth0 down
修改 MAC 地址，这一步较 Windows 中的修改要简单。
命令是：/sbin/ifconfig eth0 hw ether 00:AA:BB:CC:DD:EE
重新启用网卡 /sbin/ifconfig eht0 up
网卡的 MAC 地址更改就完成了
如何用Bash纠正错误命令
====================================
当你输入一个命令不知道是否正确的时候，可以使用ctrl+t来纠正到正确的命令。
比如输入mkdri，然后按ctrl+t，bash会帮你纠正到最接近的命令mkdir。 
如何不显示其他用户的消息
====================================
用户可以使用mesg n来禁止别人给他发送信息，其实就是禁止别人往自己的终端上面的写权限。当别人试图再使用write给他发送信息时，发送者将会看见提示：
write: user has messages disabled on pts/n
如何知道某个命令使用了什么库文件
====================================
例如要知道ls使用了什么库文件，可以使用：
$ ldd /bin/ls
如何临时增加交换空间 
====================================
产生一个64M的空文件
#dd if=/dev/zero of=/swapfile bs=1024 count=65536
初始化该文件为交换文件：
mkswap /swapfile 65536
sync
激活这个交换文件：
swapon /swapfile
如何使一个用户进程在用户退出系统后仍然运行
====================================
　　使用nohup command &，比如：
　　nohup wget -c ftp://test.com/test.iso
　　这样即使用户退出系统，wget进程仍然继续运行直到test.iso下载完成为止
如何限制用户的最小密码长度
====================================
修改/etc/login.defs里面的PASS_MIN_LEN的值。比如限制用户最小密码长度是8：
PASS_MIN_LEN 8
这样用户设置密码的时候如果输入的密码长度小于8将不能设置
如何限制只有0组(gid=0)的用户可以su成root 
====================================
修改/etc/login.defs里面的SU_WHEEL_ONLY的值为：
SU_WHEEL_ONLY yes
那么就只有gid为0的用户可以su成root。 
如何禁用Ctrl+Alt+Del键重启系统
====================================
有时候为了防止误操作导致系统重新启动(如机房里面新来了个习惯用Window$系统的管理员:-D)，或者出于安全的原因，需要禁用Ctrl+Alt+Del组合键。
只需要注释掉/etc/inittab文件内的
ca::ctrlaltdel:/sbin/shutdown -t3 -r now
这一行即可。如何注释？在这一行的行首放一个“#”号即可。 
怎么样格式化磁盘 
====================================
Linux下有一条mkfs命令，相当于format，可以对磁盘进行文件系统制作操作(或者说格式化)。命令的语法为：
mkfs -t 文件系统类型 /dev/设备名
如要把/dev/sda1格式为reiserfs格式，使用以下命令：
mkfs -t reiserfs /dev/sda1
当然，也可以使用mkfs.fstype命令来格式化磁盘，其中的fstype为文件系统名，如reiserfs文件系统的格式化命令为mkfs.reiserfs。上面那条命令的相应版本为：
mkfs.reiserfs /dev/sda1
如何取消root命令历史记录以增加安全性 
====================================
　　为了设置系统不记录每个人执行过的命令，就在/etc/profile里设置： 
　　HISTFILESIZE=0 
　　HISTSIZE=0 
　　或者：
　　ln -s /dev/null ~/.bash_history 
　　这样就可以了。 
如何使用netrc文件进行自动ftp 
====================================
在自己的home目录下建立一个权限600，名为.netrc的文件，内容是：
machine 192.168.0.1 login test password test
这样以后你每次ftp 192.168.0.1的时候，系统都会帮你以用户名test，密码test登录。
利用这个特征可以实现自动ftp。
例如你想要每天5:00到192.168.0.1机器上面获得/test目录下的文件test.txt，可以这么做：
建立一个文件ftp_cmd，内容为：
cd test
get test.txt
bye
然后使用crontab -e设置定时任务：
0 5 * * * ftp 192.168.0.1 
如何测试硬盘性能 
====================================
使用hdparm -t -T /dev/hdX就可以测试硬盘的buffer-cache reads和buffered disk reads两个数据，可以用来当作硬盘性能的参考。
同时使用hdparm -c3 /dev/hdaX还能设置硬盘以32bit传输，以加快数据传输的速度。
压缩和打包文件
====================================
.bz2 文件如何解压缩 用tar -I 或者bunzip2 命令都可以。
.bz2 — 使用bzip2命令压缩的文件，可以使用bzip2 -d filename 解包
.gz — 使用gzip命令压缩的文件，可以使用gunzip -d filename 解包
.tar — 使用tar打包的文件，即tarball文件，可以使用tar xf filename 解包
.tbz — 使用tar打完包后再以bzip2命令压缩的文件，可以使用tar jxf filename 解包
.tgz — 使用tar打完包后再以gzip命令压缩的文件，可以使用tar zxf filename 解包
个人总结：
[.tar] 解开：tar xvf *.tar 把文件打包不压缩：tar cvf *.tar DirName
[.tar.gz]解开：tar xzvf *.tar.gz 把文件打包并压缩：tar czvf *.tar.gz DirName 
[.bz2] 解开：bzip2 -d *.bz2 
[.bz] 解开：bzip -d *.bz 
[.gz] 解开：gzip -d *.gz 
如何对光驱、软驱实现AutoMount 
====================================
安装完Redhat Linux之后，运行ntsysv,选中服务后台程序autofs.autofs的两个配置文件在/etc/auto.misc和 /etc/auto.master。
/etc/auto.master定义了mount目录和mount所需的配置文件名及其空闲时自动umount的时间。下面是默认配置：
[jephe@sh3 /etc]$ more auto.master
/misc /etc/auto.misc --timeout 60 
下面是我的/etc/auto.misc配置文件：
[jephe@sh3 /etc]$ more auto.misc
cdrom -fstype=iso9660,ro :/dev/cdrom
floppy -fstype=vfat :/dev/fd0
e2floppy -fstype=ext2 :/dev/fd0
注：
a.确保/dev/cdrom作为符号链接指向你的光驱所在的分区，作为我的情况：
[jephe@sh3 /dev]$ ls cdrom -l
lrwxrwxrwx 1 root root 3 Aug 26 08:44 cdrom -> hdd 
b.当软盘为windows 95格化化的vfat分区类型时，设定了安装目录/misc/floppy
c.当软盘为Linux格式化过的ext2分区类型时，设定了安装目录/misc/e2floppy
至此，若还未启动autofs,则运行/etc/rc.d/init.d/autofs start, 若对上述两个文件中做过任何更改，运行/etc/rc.d/init.d/autofs restart即可。
放入一片光盘进入光驱后，不需任何动作，直接进入目录/misc/cdrom，autofs 将自动先为你mount光驱同样，若放入一张vfat格式的软盘，你可以cd /misc/floppy，若是ext2格式的软盘，则cd /misc/e2floppy。在超过一分钟未使用它们，且当前目录不是自动mount目录/misc/cdrom，/misc/floppy，/misc/e2floppy，系统将自动umount它们。
cron 计划任务
====================================
简介 
crontab-操作每个用户的守护程序和该执行的时间表。 
部分参数说明 
crontab file [-u user]-用指定的文件替代目前的crontab。 
crontab-[-u user]-用标准输入替代目前的crontab. 
crontab-1[user]-列出用户目前的crontab. 
crontab-e[user]-编辑用户目前的crontab. 
crontab-d[user]-删除用户目前的crontab. 
crontab-c dir- 指定crontab的目录。 
crontab文件的格式：M H D m d cmd. 
M: 分钟（0-59）。 
H：小时（0-23）。 
D：天（1-31）。 
m: 月（1-12）。 
d: 一星期内的天（0~6，0为星期天）。 
cmd要运行的程序，程序被送入sh执行，这个shell只有USER,HOME,SHELL这三个环境变量。 
下面是一个例子文件： 
#MIN HOUR DAY MONTH DAYOFWEEK COMMAND 
#每天早上6点10分 
10 6 * * * date 
#每两个小时 
0 */2 * * * date 
#晚上11点到早上8点之间每两个小时，早上8点 
0 23-7/2，8 * * * date 
#每个月的4号和每个礼拜的礼拜一到礼拜三的早上11点 
0 11 4 * mon-wed date 
#1月份日早上4点 
0 4 1 jan * date 
范例 
$crontab -l 列出用户目前的crontab. 
#MIN HOUR DAY MONTH DAYOFWEEK COMMAND 
10 6 * * * date 
0 */2 * * * date 
0 23-7/2,8 * * * date 
如何在Linux里面恢复mbr？
====================================
　　可以使用下面的命令来恢复：
　　dd if=/boot/boot.NNNN of=/dev/hda bs=446 count=1
　　其中bs（buffer size)是指重写的字节数。为什么不是512呢？主引导扇区是一个扇区(512字节)呀？答案是因为我们用上面的命令是为了修复可能被病毒修改了的主引导记录MBR，或者想把LILO卸载掉，而不是恢复整个主引导扇区。所以我们只把主引导扇区的备份文件boot.NNNN的前446个字节重写入主引导扇区。boot.NNNN是我们在安装Linux之前整个主引导分区的备份。如果我们把512个字节全部写入主引导扇区就可能会把安装了Linux后改变了的硬盘DPT表也破坏掉。那就坏事了。 :-)
如何列出一个目录占用的空间 
====================================
du或du -s或du -k 
du -S | sort -n 可以迅速发现那个目录是最大的。 
用df可以看到已安装的文件系统的空间大小及剩余空间大小。 
quota -v查看用户的磁盘空间信息,如果你用quota限制了用户空间大小的话。
在使用less 或 more时，如何直接启动编辑器
====================================
在less或者more中打入v键，会立即启动vi编辑器，可以对文件进行编辑
如何察看你当前使用的Linux内核的版本 
====================================
　　可以使用uname -r来查看当前内核版本。如果使用uname -a可以查看包括内核版本，机器硬件信息、网络节点名、操作系统名字等信息
如何显示文件的类型 
====================================
　　用命令 file 可以使你知道某个文件究竟是ELF格式的可执行文件, 还是shell script文件或是其他的什么格式 例如: 
#file startx 
如何将man page转成HTML格式 
====================================
　　使用 man2html 这个指令，就可以将 man page 转成 HTML 格式了。用法是： 
　　man2html filename > htmlfile.html 
　　例子： 
　　man2html /usr/man/man1/man2html.1 > ~/man2html.html 
查看文件内容的特殊方法 
====================================
相信最基本的cat和less你已经很熟悉了，如果有特殊的要求呢：
如果你只想看文件的前5行，可以使用head命令，如： 
head -5 /etc/passwd 
如果你想查看文件的后10行，可以使用tail命令，如： 
tail -10 /etc/passwd 
tail -f /var/log/messages 
参数-f使tail不停地去读最新的内容，这样有实时监视的效果，当你在ppp拨号的过程中用它岂不是很方便！ 
查看文件中间一段，你可以使用sed命令，如： 
sed -n '5,10p' /etc/passwd 
这样你就可以只查看文件的第5行到第10行。
linux下文件分割与合并 
====================================
　　$dd if=source of=target.1 bs=1M count=10 
　　$dd if=source of=target.2 bs=1M skip=10 
　　source被分为target.1和target.2两个文件，其中target.1为source的前10M部分；target.2为source的减去10M后的部分。 
　　$cat target.1 target.2 > othersource 
　　source与othersource是同一个文件。 
RedHat下如何显示彩色目录列表
====================================
　　打开/etc/bashrc, 加入如下一行: 
　　alias ls="ls --color" 
　　下次启动bash时就可以像在Slackware里那样显示彩色的目录列表了, 其中颜色的含义如下: 
蓝色-->目录 
绿色-->可执行文件 
红色-->压缩文件 
浅蓝色-->链接文件 
灰色-->其他文件 
什么是Linux 运行级？
====================================
　　什么是运行级呢？简单的说，运行级就是操作系统当前正在运行的功能级别。这个级别从1到6，具有不同的功能。这些级别在/etc/inittab文件里指定。这个文件是init程序寻找的主要文件，最先运行的服务是那些放在/etc/rc.d 目录下的文件。
　　不同的运行级定义如下：(可以参考Red Hat Linux 里面的/etc/inittab） 
　　# 缺省的运行级，RHS 用到的级别如下： 
　　# 0 - 停机（千万不要把initdefault 设置为0 ） 
　　# 1 - 单用户模式 
　　# 2 - 多用户，但是没有 NFS 
　　# 3 - 完全多用户模式 
　　# 4 - 没有用到 
　　# 5 - X11 
　　# 6 - 重新启动 （千万不要把initdefault 设置为6 ） 
　　对各个运行级的详细解释： 
　　0 为停机，机器关闭。 
　　1 为单用户模式，就像Win9x 下的安全模式类似。 
　　2 为多用户模式，但是没有NFS 支持。 
　　3 为完整的多用户模式，是标准的运行级。 
　　4 一般不用，在一些特殊情况下可以用它来做一些事情。例如在笔记本电脑的电池用尽时，可以切换到这个模式来做一些设置。 
　　5 就是X11，进到Xwindow系统了。 
　　6 为重启，运行init 6机器就会重启。 
　　不同的运行级有不同的用处，也应该根据自己的不同情形来设置。例如，如果丢失了root 口令，那么可以让机器启动进入单用户状态来设置。在启动后的 lilo 提示符下输入： 
　　init=/bin/sh rw 
　　就可以使机器进入运行级1 ，并把root文件系统挂为读写。他会跳过所有系统认证，让你使用passwd 程序来改变root口令，然后启动到一个新的运行级。 
系统平均负载(Load average)释疑 
====================================
　　在Linux系统中，uptime、w、top等命令都会有系统平均负载load average的输出，那么什么是系统平均负载呢？
　　系统平均负载被定义为在特定时间间隔内运行队列中的平均进程树。如果一个进程满足以下条件则其就会位于运行队列中：
　　- 它没有在等待I/O操作的结果
　　- 它没有主动进入等待状态(也就是没有调用'wait')
　　- 没有被停止(例如：等待终止)
　　例如：
　　[root@www2 init.d]# uptime
　　7:51pm up 2 days, 5:43, 2 users, load average: 8.13, 5.90, 4.94
　　命令输出的最后内容表示在过去的1、5、15分钟内运行队列中的平均进程数量。
　　一般来说只要每个CPU的当前活动进程数不大于3那么系统的性能就是良好的，如果每个CPU的任务数大于5，那么就表示这台机器的性能有严重问题。对于上面的例子来说，假设系统有两个CPU，那么其每个CPU的当前任务数为：8.13/2=4.065。这表示该系统的性能是可以接受的。 
如何以树状结构显示系统当前的任务 
====================================
　　运行ps时指定—forest选项，当前运行的进程将会以树状格式显示出来。比如：所有由xserver运行的程序，将会以xserver做为它们的“根”显示出来。
命令格式：
　　ps afx 
　　其中’a’表示列出所有运行的进程；’x’列出所有的后台进程；’f’是’-forest’的缩写。输出的格式如下：
　　329 ? SW 0:00 [wdm]
　　342 ? R 9:57 \_ /usr/X11R6/bin/X :0 vt7 -fbbpp 16 -auth /usr/etc/
　　343 ? SW 0:00 \_ [wdm]
　　364 ? S 0:45 \_ /usr/bin/enlightenment
　　399 ? S 0:00 \_ /usr/bin/ssh-agent sh /home/tuneup/.xse
　　404 ? S 2:28 \_ gkrellm -wm
　　787 ? S 0:05 \_ aterm -fg white -tr
　　788 ttyp0 SW 0:00 \_ [bash]
　　792 ttyp0 S 0:00 \_ vim todo
　　注：另外一种得到格式化输出结果的方法是：pstree -pu 
列目录时如何显示中文文件名 
====================================
　　我们可以使用--show-control-chars命令选项来显示。 
　　例如：
　　$ls --show-control-chars
　　如果使用的是一个比较常用的windows的分区，那么可以通过修改fstab来实现，在fstab中加入类似内容：
　　/dev/hda1 /mnt/c vfat defaults,codepage=936,iocharset=cp936 0 0
　　那么以后进入系统后都可以方便地使用/mnt/c访问windows的这个目录并正确显示目录名和文件名。 
如何使用iso文件？
====================================
　　许多Linux发行版本都有.iso的光盘镜像文件，可以用来刻录光盘。我们也可以在Linux系统下直接使用。 
　　#mount -t iso9660 -o loop xxxxx.iso /any/path/if/u/like 
查询你的CPU等级
====================================
cat /proc/cpuinfo
如何使用户没有telnet和ftp权限 
====================================
若只希望用户没telnet权限，则需要修改/etc/passwd中对应该用户的shell为/bin/true。
若只希望用户没有telnet和ftp权限，则需要修改/etc/passwd中对应该用户的shell为/bin/false。 
如何连续执行一个命令 
====================================
　　使用watch命令，可以反复执行命令，如果和ls配合，可以达到观察某文件大小变化的效果。例如： 
　　$watch ls －l file.name 
如何防止某个关键文件被修改
====================================
　　在linux下，有些配置文件是不允许任何人包括root修改的，为了防止被误删除或修改，可以设定该文件的"不可修改位(immutable)"。
　　例如：
　　chattr +i /etc/fstab
　　如果需要修改文件则：
　　chattr -i /etc/fstab
　　以后再修改文件。 
linux环境下如何undelete 
====================================
　　先在自己的主目录下创建一个名为.trash的子目录，然后在bashrc加入以下指令：
　　alias rm 'mv -f !* ~/.trash'
　　alias undel 'mv ~/.trash/!* ./!*'
　　alias cleantrash '/bin/rm -rf ~/.trash; mkdir ~/.trash;sync'
　　alias lrm 'ls ~/.trash'
　　若文档是直接用rm命令删除的，理论上 ext2 内 rm 掉的档案还是可以用 debugfs , ext2ed 救回来的.当然... 被 overwrite 掉就没救了。 
如何找出磁盘中某个大小范围内的文件 
====================================
　　比如要查找磁盘中大于3M的文件：
　　find . -size +3000k -exec ls -ld {} ; 
如何快速重新执行已经执行过的命令
====================================
　　使用!可以实现该功能，例如你前面执行了很多命令，现在突然想执行上一次执行的./configure命令，则只需要输入“!./con”即可而无需使用上下键来滚动查找。
　　而!!则能代替前面一个命令。比如刚执行过一次ifconfig，输入“!!”则等于再执行一次ifconfig。
　　而且这两个用法可以和其他命令组合，比如你刚执行过ifconfig，然后执行man !!，就等于执行man ifconfig。
当终端出现混乱时，如何让它恢复正常 
====================================
　　当使用stty命令而出现一些混乱或者更糟的是，使用一个程序而使终端设置完全混乱了时怎么办？要回到“现实”，试试下面的命令：
　　stty sane
　　如果击键变得混乱时，试着用来把命令括起来，输入的顺序是先按下CTRL再键入j键。
　　ctty sane 
　　这个命令不会回到先前的设置，但却可以去除一些稀奇古怪的设置。而真正会出现什么设置要依赖于所使用的系统，但它至少会让你能输入字符，并见到结果。从这里开始，你可以把一些组合键设置为你所喜欢的方式。 
如何将.gz文件分割为数个1.44mb 
====================================
把一个文件分割到软盘：
tar cfvm /dev/fd0 file.tar.gz
把软盘上的文件合并到硬盘：
tar xvfm /dev/fd0
如何一次处理一整个目录 
====================================
　　Linux/UNIX 的很多常用命令如 rm ， cp 等都有一个参数---- -r ， 是递归的意思， 命令里加了参数 -r 就可以对目标目录及其下所有子目录进行操作，如：
　　rm -rf /test (f 是 force 意为强行)
　　该命令完全删除根目录下的子目录 test ，作用类似于 dos 下的 deltree ，当然使用这个命令时要特别小心。再如：
　　cp -r /test /test1
　　有类似 dos 下 xcopy /s 的作用。 
redhat下如何允许root通过telnet登录? 
====================================
方法1：/etc/securetty ( 加入 pts/0 、pts/1、...)
# echo "pts/0" >> /etc/securetty
方法2：为了在redhat linux系统中激活远程登陆，从文件/etc/pam.d/login中移去下面这一行： 
auth required /lib/security/pam_security.so
将/etc/securetty这个文件改名就行啦，该文件是定义root只能在tty1~tty6的终端上登录的，详细的信息可以"man login"。
Linux正常重新启动的方法有很多种，下面介绍几种常用的重新启动方法：
====================================
Ctrl＋Alt＋Del 
#init 6 
#shutdown －r now 
#reboot
为什么我的linux不允许普通用户登录？ 
====================================
　　以root的身份登录系统，检查是不是有/etc/nologin这个文件，删除这个文件，然后再以普通用户的身份登录。相信问题已经解决。
　　出现这种问题一般是因为系统在关闭的过程中意外中断了操作，如断线或者是插头被拔了之类的意外。而系统在关闭的过程中会自动的产生这个文件，以便通知用户系统正在关闭这就造成普通用户无法登录了。
　　另外一种原因是系统管理员在对系统进行维护，为了维护的过程中不受其他用户的影响，需要生成这个文件来禁止其他用户登录。但很不幸系统管理维护完以后忘记删除这个文件了。 
如何改变当前路径下所有目录和文件的所有权 
====================================
改变所有子目录及文件的所有权
#chown －R owner[.group] *
也可以用find命令来实现： 
#find . －exec chown owner[.group] {} ;
改变所有子目录及文件的属性 
在你要改变属性的目录下，输入命令： 
#chmod －R 777 *
就可以改变下面所有子目录及文件的属性，不过使用这个命令的时候要特别小心，要是在根目录下打入这个命令，你所有文件的属性都将改变，这就会引起很大的安全性问题。
如何快速查找文件 
====================================
　　查找文件可以用find，但最好是用locate，速度快，参数少。 
　　$locate filename 
　　它是在一个数据库里面查找，所以，要记得经常用updatedb命令更新数据库。一般地，在crontab中的cron.daily脚本会执行/usr/sbin/logrotate /etc/logrotate.conf命令，让机子在每天深夜更新数据库。 
如何将Linux或FreeBSD复制到另一颗硬盘 ? 
====================================
　　Linux上的系统复制很简单，使用cp -ax将partition资料复制过去，重开机後设定lilo就可以了。
　　FreeBSD也可以用cp来复制文档，但是对于复制整个文档系统并不是好方法。
　　这里介绍使用dump和restore来做：
创建新的文档系统 
假如你的新硬盘为ad1, 而将来的根分区将是ad1s1a, 你可以先创建文档系统：
newfs /dev/ad1s1a 
mount /dev/ad1s1a /mnt 
cd /mnt
复制：
dump -f- / | restore -f- -r 
这是把老的根文档系统复制输出到管道，restore从管道里读数据，写入当前目录所在的文档系统。
按部就班复制其他文档系统 
复制完後，也许 要修改新硬盘下的/etc/fstab，安装上新的分区，摘下老硬盘就可以了。
再补充一点，如果你要复制的是另外一台机器，可以用rsh，这样就可以通过网络把一个分区数据传送到另外一台机器，不需要NFS，不需SAMBA等就可以解决问题，而cp就很难作到了。
newfs /dev/ad1s1a 
mount /dev/ad1s1a /mnt 
cd /mnt 
rsh -l yourname thathost 'dump -f- /' | restore -f- -r
linux怎么给一个普通用户reboot权限? 
====================================
分四种情况讨论：
1.让任何人（包括根本不拥有系统帐号的人）都可以通过控制台reboot
在/etc/inittab文件中保留ca::ctrlaltdel:/sbin/shutdown -t3 -r now
这一行。这样全国人民都可以reboot你的机器，只要你把控制台交出来。
2.让所有系统用户都可以reboot
执行# > /etc/security/console.apps/reboot即可。这就在console.apps目录下生成了一个空文件，文件名就是授权的application。以上路径是针对Mandrake系统而言的，其他系统我不清楚。不过，真正高雅的Mandraker或许根本就不会去靠“>”来生成这个文件——他们会使用msec来进行控制的。
3.让指定的用户才可以reboot
假设我们要让用户zhizunbao拥有reboot的权限，我们靠uid/gid来完成控制：
# groupadd reboot
# cd /usr/local
# mkdir reboot
# chown root:reboot reboot/
# chmod 750 reboot/
# cd reboot
# cp /sbin/reboot .
# chmod 4755 reboot
# usermod -G reboot zhizunbao
现在，zhizunbao就可以运行/usr/local/reboot/reboot来重启动机器。
4.在一台不设普通用户的机器上启用口令验证reboot
这实际上是靠添加一个关机帐号来实现的，该帐号的shell就是加了s位的/sbin/halt，并且口令只有少数维护人员知道。我们这里采用的就是第4套方案。
怎样知道自己的机器上有哪些服务在运行
====================================
若一台机器运行有很多不需要的服务，那么被攻击者入侵的可能性就会大大加大，因此作为管理员就应该经常查看系统运行有哪些服务。
首先查看系统运行的进程
若需要查看系统当前运行的所有进程，就需要用如下命令：
# ps auxw
其中参数a表示显示系统中所有用户的的进程；u表示输出进程用户所属信息；x表示也显示没有控制台的进程；若显示行太长而被截断则可以使用f参数；
查看系统监听的服务
# netstat -ln
l表示显示当前系统监听的端口信息；n表示端口按照端口号来显示，而不转换为service文件中定义的端口名；若希望了解各个端口都是由哪些进程监听则可以使用p参数。
　　若发现不需要的服务，可以使用linuxconf或ntsysv命令来关闭这些服务在系统启动时自启动，然后重新启动系统则这些服务将在运行。
有些服务是由inetd超级服务器来监控的，则需要标记/etc/inetd.conf来关闭这些服务。 

查询端口对应的服务
====================================
# lsof -i :端口号
查询此端口对应的服务。
vi 中设置自动缩进
====================================
:set autoindent 
:set ai
取消
:set noautoindent
:set noai
如何使linux系统对ping不反应 
====================================
　　在linux里，如果要想使ping 没反应也就是用来忽略icmp包。可以用：
　　echo 1 > /proc/sys/net/ipv4/icmp_echo_ignore_all 
　　若想恢复就用： 
　　echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_all 
如何实现多网卡bondin 
====================================
　　使用多块网卡虚拟成为一块网卡，具有相同的IP地址。这项技术其实在sun和cisco中已经存在，分别称为Trunking和etherchannel技术，在Linux中，这种技术称为bonding。
　　因为bonding在内核2.4.x中已经包含了，只需要在编译的时候把网络设备选项中的Bonding driver support选中就可以了。
　　然后，重新编译核心，重新起动计算机，执行如下命令：
　　ismod bonding
　　ifconfig eth0 down
　　ifconfig eth1 down
　　ifconfig bond0 ipaddress
　　ifenslave bond0 eth0
　　ifenslave bond0 eth1
　　现在两块网卡已经象一块一样工作了.这样可以提高集群节点间的数据传输.
　　你最好把这几句写成一个脚本,再由/etc/rc.d/rc.local调用,以便一开机就生效.
　　bonding对于服务器来是个比较好的选择,在没有千兆网卡时,用两三块100兆网卡作bonding,可大大提高服务器到交换机之间的带宽.但是需要在交换机上设置连接bonding网卡的两个口子映射为同一个虚拟接口。
字符终端关掉喇叭
将/etc/inputrc中的set bell-style none 前的＃去掉，或echo "set bell-style none" >> ~/.bashrc

/etc/fstab 文件说明
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
使用编辑器来修改 /etc/fstab (eg. vi /etc/fstab) 
功能：存放文件系统与目录结构对应资料的档案 
fstab 栏位说明： 
第一栏(fs_spec)： 实际的设备名称 
第二栏(fs_file)： 对应到的目录结构，挂载点
第三栏(fs_vfstype)：该分区的文件系统格式，常见的有： 
ext2、ext3,xfs,reiserfs,vfat（fat32）,ntfs iso9660、nfs、swap 
第四栏(fs_mntops)： 在 mount 时的参数 
第五栏(fs_freq)： 在使用 dump 时是否记录，不需要则输入0 
第六栏(fs_passno)： 决定在开机时执行 fsck 的先后顺序 
例子 : 
IDE 硬盘分成两个 partition 与一个 swap，还有一台光驱跟一台软驱的情形 :  
/dev/hda1   /            ext2    defaults        1 1 
/dev/hda6   swap         swap    defaults        0 0 
/dev/cdrom  /mnt/cdrom   iso9660 noauto,user,ro  0 0 
/dev/fd0    /mnt/floppy  ext2    noauto,owner    0 0 
none        /proc        proc    defaults        0 0 
none        /dev/pts     devpts  gid=5,mode=620  0 0 
/dev/hda2 /mnt/wind  vfat defaults,iocharset=cp936,umask=000 0 0
为现有系统做启动盘 
==================================== 
# mkbootdisk --device /dev/fd0 `uname -r`
如何去掉nvidia显卡启动时的logo画面
=======================================
在/etc/X11/XF86Config文件
Driver "nvidia" 那节，加入 
Option “NoLogo”
让wget 自动走代理下载
=======================================
在用户主目录下建立.wgetrc 文件，格式举例如下
http-proxy=205.155.212.11:80
ftp-proxy=205.155.212.11:80
修改mozilla，mozilla firefox系列浏览器隐藏参数
=======================================
在地址栏输入 about:config

adsl共享上网，由adsl做网关然后nat

如何使新用户首次登陆后强制修改密码(猫小)
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#useradd -p '' testuser; chage -d 0 testuser

日志维护工具logrotate(hotbox)
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
在/etc/logrotate.conf中配置，作用：定义log文件达到预定的大小或时间时，自动压缩log文件 


让vi不响铃(sakulagi)

＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
echo "set vb t_vb=" >> ~/.vimrc

tar打包一个目录时，去掉其中的几个子目录
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
tar cvfz chenxu.tar.gz dir --exclude dir/dir1 --exclude dir/dir2/dir3
可以陆续添加, 注意添加排队目录时不要加“/”根符号

用tar 来备份恢复linux系统举例
===============================================
tar -cjpvf /mnt/wind/linux.tar.bz2 / --exclude=/mnt 
tar -xjpvf /mnt/wind/linux.tar.bz2 -C /

adsl 拨号成功后无法上网
===============================================
/sbin/route add default ppp0


如何在RED Hat Linux 防一用户两个人用登陆
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
直接在shell里面，就是你的命令行下面输入 
echo "* hard maxlogins 2" &gt;&gt; /etc/security/limits.conf 
然后回车，这个命令会将内容 
* hard maxlogins 2 
写到文件/etc/security/limits.conf中

还要防终端呀，那就继续 
echo "session required pam_limits.so" &gt;&gt; /etc/pam.d/login

KDM 允许root登录
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
修改 /etc/kde3/kdm/kdmrc
找到
AllowRootLogin=false
修改为 
AllowRootLogin=true


从rpm文件中解出某个文件的三种方法
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
Peck Dickens的两种方法 

1) 使用Midnight Commander (mc), 翻看rpm内部文件，并将某文件拷贝出来 

2) 命令行方式 
cd /tmp 
md rpmtmp 
cd rpmtmp 
rpm2cpio {FullNameOfRPM} | cpio -iumd {FullNameOfFileToExtract} 
注意，完成后请删除临时文件 

Pam Roberts的一种方法 

3) 使用rpm-utils-1.5-1.noarch.rpm中的rpm-get命令，该rpm可以从rpmfind.net获取

1.设置文本方式下的分辩率
在grub的启动参数中加入vga=xxx
value mode video ram
769 640 x 480 x 8 bit (1M)
785 640 x 480 x 16 bit (1M)
786 640 x 480 x 24 bit (1M)
771 800 x 600 x 8 bit (1M)
788 800 x 600 x 16 bit (1M)
789 800 x 600 x 24 bit (2M)
773 1024 x 768 x 8 bit (1M)
791 1024 x 768 x 16 bit (2M)
792 1024 x 768 x 24 bit (4M)
775 1280 x 1024 x 8 bit (2M)
794 1280 x 1024 x 16 bit (4M)
795 1280 x 1024 x 24 bit (8M
796 1600 x 1200 x 8 bit (2M)
798 1600 x 1200 x 16 bit (4M)
799 1600 x 1200 x 24 bit (4M)

2.更改桌面分辨率到1024x768(有时无效,不知道为何)
修改/etc/X11/xorg.conf文件,修改前先备分此文件,以防万一.
注释掉设置行频的这一行(必须)
#HorizSync 31.5 - 37.9
在Section "Screen"的Subsection "Dispaley"中把Modes一行改成
Modes "1024x768"

3.启动多个X桌面
用别名
alias X1='startx -- :1 -bpp 32 -quiet&'
alias X2='startx -- :2 -bpp 32 -quiet&'
或者直接用命令
startx -- :1 -bpp 32 -quiet&
startx -- :2 -bpp 32 -quiet&
然后可用CTRL+ALT+F8,CTRL+ALT+F9切换,依此类推到CTRL+ALT+F12
最简单的方法
startx -- :1

4.调整显示器
xvidtune

5.给文件输出加上行号
nl /etc/passwd
nl /etc/passwd -s '.'
在vi中
:%!nl
: set nu

6.大小写转换
cat filename | tr "[a-z]" "[A-Z]"

7.统计文件的行数
wc -l filename # line
wc -c filename # char
wc -w filename # word

8.找回root帐号密码
进入单用户模式,对于用grub的用户,在启动参数后的kernel一行后加single,
然后可不用密码进入单用心模式,再在单用户模式下修改你的密码.

9.设置grub密码
如上8所述,实际上只要能够接触到机器,如果grub没有密码,就可以轻易地进入机器.
生成md5码
输入命令
grub-md5-crypt
然后输入法你要设置的密码,grub-md5-crypt就会生成一个字符串xxxxxxxx.
加入到你在grub配置文件/boot/grub/grub.conf(有的可能用在的/boot/grub/menu.lst)
在title的下一行加入
password --md5 xxxxxxxx

10.用命令弹出光驱
eject # 弹出
eject -t # 弹回
很有意思

11.反转文件在内容
tac /etc/passwd
在vi中
%!tac in vi

12.输出文件前n行的几种方法
head -5 filename
awk 'NR==1,NR==5 {print $0}' filename
sed -n '1,5p' filename
此法可变通到输出文件的其它行
sed -n '5,$p' filename

13.改变grub背景
grub背景用的是xpm文件在图片格式,因此你需要把你在图片转换成xpm格式,可用gimp
在X Window下,输入
gimp filename
修改图片的颜色数为14
right click on image-> image->mode->indexed->color number 14
然后保存为xpm文件/yourpath/yourimage.xpm
也可以用命令
convert yourimage.jpg -colors 14 -geometry 640x480! yourimage.xpm
修改grub
在grub中添加
splashimage (hd0,0)/yourpath/yourimage.xpm
有的可能是
splashimage=(hd0,0)/yourpath/yourimae.xpm
分区(hdx,y),根据你的具体情况而定.另外也可以把图片压缩为.gz格式.

14.ssh技巧
(1)不用login远程执行命令
格式:
ssh hostname command
如:
ssh hostname ls /usr/share/doc
(2)远程文件拷贝scp,windows下用pscp
scp localfile username@hostname:/newfilename

15.Linux下使用NFS QuickStart
修改/etc/exports就可.如果不考虑安全问题,可在该文件中加入
/ master(rw) trusty(rw,no_root_squash)
再执行
service nfs restart
然后就可在远程主机上mount它了
mount hostname:/ /media

16.ftp自动登陆下载shell脚本
SRC_FTP_SERVER=hostname
SRC_FTP_USER=anonymous
SRC_FTP_PASSWD=user@xxx.com
SRC_FTP_DIR=/diskimages/
echo "open $SRC_FTP_SERVER
user $SRC_FTP_USER $SRC_FTP_PASSWD
lcd ${TMP_DIR}
cd $SRC_FTP_DIR
binary
get $SRC_FTP_DIR/filename " | ftp -n 1>/dev/null 2>&1

17.命令下发送邮件
cat "mail content" | mail yourname@domain.com -s "mail title"
cat /dir/file_conent | mail yourname@domain.com -s "mail title"
带附件,用mutt
cat "mail content" | mutt yourname@domain.com -s "mail title" -a attach_file
cat /dir/file_conent | mutt yourname@domain.com -s "mail title" -a attach_file

18.tar打包时去掉某些目录或文件
cd /
tar cvf usr.tar usr --exclude usr/share --exclude /usr/bin/unzip
添加排队目录时不要加/根符号

19.显示xx天前/后的日期
date -d "now" #同date
date -d "today" #同date
date -d "45 days ago" # 45天前
date -d "45 days" # 45天后

20.Linux使用*.rar文件
安装rar软件包(google一下就知道了)
压缩
rar a usr_share.rar usr/share
解开
rar x usr_share.rar /root

21.用命令截屏
import -window root hello.jpg

22.非交互方式文本转html
vim -c ":TOhtml" -c ":wq %" -c ":q" filename

23.其它
监视文件的变化
tail -f /var/log/messages  
命令行下HTML相关命令
wget www.xxxx.com/filename.tar.gz #下载文件
lynx www.163.com #命令行看网页
htmlview www.163.com #命令行看网页

