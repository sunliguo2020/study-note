ulimit -a一下，发现OPEN FILES不能超过1024，应该将这个问题消灭在萌芽状态，免得造成日后的困惑。
vi /etc/security/limits.conf

加上：
*                soft   nofile          8192
*                hard   nofile          20480

重启就OK。这个方法针对REDHAT LINUX。
修改完limits.conf并重启之后，root用户的ulimit -n 不会改变的，需要在脚本中再执行ulimit -n 8192才能生效。普通用户的倒是跟着改了。
以 Red Hat Linux 8.0 上设置 fcitx 输入法为例：
1. 输入法正常运行需三个条件： locale, XMODIFIERS 和中文字体。
( XMODIFIERS 是系统变量，用 echo $XMODIFERS 查看)。
2. 若安装系统时选择了简体中文， locale 应该已经设置好了，可用 locale 查看，大致应为：

LANG="zh_CN.GB18030"LC_CTYPE="zh_CN.GB18030"LC_NUMRIC="zh_CN.GB18030"LC_TIME="zh_CN.GB18030"...LC_ALL="zh_CN.GB18030"

3. echo $XMODIFERS 应显示： @im=fcitx
若不显示，或显示不正确，可在 .bashrc 或 .bash_profile 中添加或修改为：
export XMODIFERS=@im=fcitx

Tip：默认简体中文安装的系统改为英文menu显示：

mv /usr/share/locale/zh_CN /usr/share/locale/old_zh_CN
Comments (0)
Compile linux
Sunday, 8. January 2006, 07:11:25

GNU/Linux 

设置一个适当的.config文件是配置linux内核的过程中的最重要的部分。但必须跳过另外几个关口才能把这个文件最终转换为最终的内核。下面是整个过程的轮廓：

1. cd /usr/src/linux
2. 根据你的喜好，运行make xconfig或者make menuconfig
3. 运行make clean
4. 运行make bzImage
5. 运行make modules
6. 运行make modules_install
7. 把/usr/src/linux/arch/i386/boot/bzImage复制为/boot/vmlinuz
8. 编辑/boot/grub/grub.conf，添加一项用于新内核的配置


Note：第8步可用命令来自动完成。
#new-kernel-pkg --install --depmod --mkinitrd 2.4.20-kilvon.001
--mkinitrd 作Initial Ramdisk的,可以直接敲个mkinitrd -h看看
--depmod 检查内核中有没有未解析的symbol
--install 在grub中安装一个启动选项
Comments (0)
ulimit
Thursday, 29. December 2005, 14:37:57

GNU/Linux 

ulimit：显示(或设置)用户可以使用的资源限制

ulimit -a 显示用户可以使用的资源限制
ulimit unlimited 不限制用户可以使用的资源，但本设置对可打开的最大文件数(max open files)和可同时运行的最大进程数(max user processes)无效
ulimit -n <可以同时打开的文件数> 设置用户可以同时打开的最大文件数(max open files)
　　例如：ulimit -n 8192
　　如果本参数设置过小，对于并发访问量大的网站，可能会出现too many open files的错误

ulimit -u <可以运行的最大并发进程数> 设置用户可以同时运行的最大进程数(max user pocesses)
　　例如：ulimit -u 1024
Comments (0)
Modify system time
Saturday, 24. December 2005, 07:23:58

GNU/Linux 

用 date 指令可以显示和修改 GNU/Linux 的系统时间。
for example:
date 122518002005  # 系统时间修改为 2005/12/25 18:00clock -w   # 将当前系统时间写入CMOS

Note: 只有root可修改系统时间
Comments (0)
My public key
Monday, 19. December 2005, 16:05:26

GNU/Linux 

-----BEGIN PGP PUBLIC KEY BLOCK-----
Version: GnuPG v1.0.7 (GNU/Linux)

mQGiBECYwakRBADL8yX++S3iGEsvcKYG+kuxcSYYDIh06TYQk4UVRRLTGhvLD/mi
2YhQLVXRlI2BRkAaQvotY8SP/fCxMvDFQb29uLaOj2urVX9IeHQE9EJENQcCtqfD
ZARK/hKF/RSS7Vqht67Z0qMFisHq45UFo71wc97NTaAvkVKIvoVMj4EnOwCgiQrt
Ji+SuH920r0CCl7UcmuppD8D/0vbMSfnyUOy4eVM/mBDFuH0RcOTZxQ66k/SQrjn
EXrBEHpDlBhwdr7tuimTFPGbJ3s9vjhvtVrMgWcoGJ0/Jm7DAINbuAQNAJG+IK5d
6jZe1S/1BbQNU2P3OtjqTWOG12vnMuC2v9rKC0oT0ItAS0p5gutskcPKAy9xFsEo
L+eWBACC5+EPwkNDhScsWMQH/YDqsfJ2HnL8DPwj7cvrxcMnRRXHtXZTFJ0cJkEo
kfSEwl0ZEnALw8QkeSadkMuQ01e7sbS3/9InWRjOlnTMGEXvhnpKV3xM2HtGwHrT
lSZ5qj2L4oUzniy4ai+x9QZYzoeJuUcFy2xj+TLihmIoLn/WD7RTcmVkc3BpZGVy
IChJRDpyZWRzcGlkZXIgZW1haWw6cmVkc3BpZEBzaW5hLmNvbSxyZWRzcGlkQGV5
b3UuY29tKSA8cmVkc3BpZEBzaW5hLmNvbT6IWQQTEQIAGQUCQJjBqQQLBwMCAxUC
AwMWAgECHgECF4AACgkQdL5gST89SlxXCACfcjYd0tEFr+7o6QE4buxNU+X/e5UA
niG8st6UqdYN/0ESgdm4DAY1B16puM0EQJjBqhADAISWqa/ZkoC6EcwybD4bT5KZ
ipB40i3JGCYgGhDJOE15P5NO0XpVQNsTrvA4Bx7C4IYCSvqTiPTotsn/W89wM/LJ
AGl53tpJmBOXRvCvQdjjPPWRRoM3OSQ23+fIDmTHYwADBQL/TVUmi4FuOT21tmUb
KD5iAyxn9qkHls+WoUIhTZZq+SJnZzkOwiEvVZkc8al84SQfvhYcT+mZwk4c398L
oQoJrWPeMXiEj23LK29L4MBpJLoFngjnlTylru3DT4k7K5Y2iEYEGBECAAYFAkCY
waoACgkQdL5gST89SlwdCACfWqJQ/9bv4ze6OVabDEG8bFX+rgoAn2luiJeYXDUS
O0+Xh46BDffInv5q
=uodQ
-----END PGP PUBLIC KEY BLOCK-----
Comments (0)
CD burning
Tuesday, 13. December 2005, 14:59:26

GNU/linux 

 Linux下刻录光盘非常简单，只需在终端窗口输入命令即可： 　　cdrecord -v speed=2 dev=0,0,0 cd.iso 　　cdrecord软件在发行版中一般都有，如果安装系统时没有安装它，安装盘里应该能找到。　　speed是表明刻录速度的选项，可根据实际情况设置，但不要超过CD-R与刻录机的最大限速；dev是刻录设备的选项，可由  cdrecord -scanbus  命令获得，cd.iso是要刻录的影像文件，可根据实际情况加入路径。 　　有几个问题需要说明： 　　1、镜像文件如何做 　　Linux中有一个mkisofs命令，功能非常强大，可以做资料光盘、系统光盘等，还可以做可启动光盘。 　　mkisofs -r -o cd.iso -m temp burn/ 　　是基本的使用方法，－o cd.iso 指定光盘映像文件名称，－m temp 排除temp目录或文件，burn/ 将该目录下的文件加入到映像中。 　　2、光盘拷贝 　　有简单的做法，使光盘信息一丝不漏，包括启动信息： 　　dd if=/dev/cdrom of=cd.iso 　　/dev/cdrom为光驱设备名称，一般为/dev/cdrom ，可根据实际情况给定。    3、刻录机的安装 　　Linux系统只认SCSI刻录机，现在大部分使用的是IDE接口，需要做一转换，硬件链接后，运行命令cdrecord -scanbus，如果没有以下类似信息说明设备没有被系统识别： 　　Cdrecord 1.11a15 (i586-mandrake-Linux-gnu) Copyright (C) 1995-2001 J鲵g Schilling 　　Linux sg driver version: 3.1.22 　　Using libscg version 'schily-0.5' 　　scsibus0: 　　0,0,0 0) 'CD-RW ' 'SMART CLONE32 ' 'XSW1' Removable CD-ROM 　　0,1,0 1) * 　　0,2,0 2) * 　　0,3,0 3) * 　　0,4,0 4) * 　　0,5,0 5) * 　　0,6,0 6) * 　　0,7,0 7) * 　　解决的办法是在/etc/lilo.conf文件中加入 append="hdb=ide-scsi"，hdb是第一IDE接口从口，如果你的刻录机在第二IDE接口，应改为hdc(主)或hdd(从)，保存后运行lilo命令，然后重启系统，再测试，如果还不行，在/etc/modules.conf 文件中加入如下两行重启系统 　　probeall scsi_hostadapter ide-scsi 　　probeall usb-interface usb-uhci ehci-hcd 　　如果不行，说明系统内核没有配置好，需要重新编译内核。 　　4、关于MD5SUM 　　下载的光盘镜象一般都附带MD5SUM校验码，inux光盘内基本上对每个文件都提供了md5sum，文件名一般都是MD5SUMS，加载镜象文件后进入到RPMS目录内运行md5sum *.rpm 就会列出每个软件包的md5sum 然后与MD5SUMS文件内的码子逐一比较（利用diff可以提高效率）。
Comments (1)
ping ttl
Tuesday, 6. December 2005, 15:19:13

network 

TTL：生存时间
指定数据报被路由器丢弃之前允许通过的网段数量。
TTL 是由发送主机设置的，以防止数据包不断在 IP 互联网络上永不终止地循环。转发 IP 数据包时，要求路由器至少将 TTL 减小 1。

TTL 字段值可以帮助我们识别操作系统类型(不完全准确，因为 TTL 是可以修改的)。
LINUX 64
WIN2K/NT 128
WINDOWS 系列 32
UNIX 系列 255
Comments (0)
iptables && Linux modules
Monday, 5. December 2005, 15:56:46

GNU/linux, network 

2.4.xx 版本的核心一般既支持 iptables 又支持 ipchains，但着两个 modules 不能同时使用。可用lsmod查看已载入的 modules，若 ipchians 已载入，可将其卸载：rmmod ipchains。然后载入 iptables：modprobe iptables
Comments (0)
Auto refresh
Wednesday, 30. November 2005, 12:42:27

network 

<meta http-equiv="refresh" content="20; url=http://my.opera.com/redspider">

20秒后自动跳转至 http://my.opera.com/redspider
Comments (0)
Maximum Transmission Unit
Wednesday, 23. November 2005, 12:30:07

GNU linux network 

网络介质的最大传输单位( MTU )是有一定限制的。若设定的 MTU 超过了传输介质的负荷，除非操作系统支持数据包重组，否则，可能造成数据包无法传递的问题。此外，若数据包大小与 MTU 无法协调，导致数据包在传送的时候一再进行重组，会使网络传输效率下降。所以，网卡的 MTU 设定应针对传输介质最优化。
MTU 在以太网卡上的默认值是1500，其它传输介质如下：

网络传输介质         MTUEthernet           1500PPPoE              1492Dial-up(modem)     576

怎样确定合适的MTU(找出MTU值)：
由于 MTU 与 Router 有较大的关系，所以通常在 Client 端对 Router 进行 MTU 数值侦测。
在 GNU/Linux 上： ping -c <number> -M do -s <bytes> IP
(number 为次数；bytes 为数据包大小) 例

[root@test root]# ping -c 3 -M do -s 1472 192.168.1.2 PING 192.168.1.2 (192.168.1.2) from 192.168.1.13 : 1472(1500) bytes of data. 1480 bytes from 192.168.1.2: icmp_seq=0 ttl=255 time=2.408 msec 1480 bytes from 192.168.1.2: icmp_seq=1 ttl=255 time=2.392 msec 1480 bytes from 192.168.1.2: icmp_seq=2 ttl=255 time=2.440 msec 　 --- 192.168.1.2 ping statistics --- 3 packets transmitted, 3 packets received, 0% packet loss round-trip min/avg/max/mdev = 2.392/2.413/2.440/0.044 ms 　 [root@test root]# ping -c 3 -M do -s 1473 192.168.1.2 PING 192.168.1.2 (192.168.1.2) from 192.168.1.13 : 1473(1501) bytes of data. ping: sendto: Message too long ping: sendto: Message too long ping: sendto: Message too long --- 192.168.1.2 ping statistics --- 3 packets transmitted, 0 packets received, 100% packet loss

从上面就可以发现数值为1472，再加上数据包header的长度，MUT = 1472 + 28 = 1500

在windows上： ping -f -l <bytes> IP
(bytes 为数据包大小，IP 为 Gateway 的ip) 例

C:\WINDOWS> ping -f -l 1500 192.168.1.2 Pinging 192.168.1.2 with 1500 bytes of data: Packet needs to be fragmented but DF set. Packet needs to be fragmented but DF set. Packet needs to be fragmented but DF set. Packet needs to be fragmented but DF set. Ping statistics for 192.168.1.2:     Packets: Sent = 4, Received = 0, Lost = 4 (100% loss), Approximate round trip times in milli-seconds:     Minimum = 0ms, Maximum =  0ms, Average =  0ms

在上面的测试中，数据包设为1500时，出现了 Packet needs to be fragmented but DF set. 提示。意思是说，数据包大小超过 MTU 能接受的大小，但由于使用了 -f 参数，使得数据包不能重组，因此产生错误。也就是说，应减小 MTU 值。下面用1464来测试。

C:\WINDOWS> ping -f -l 1464 192.168.1.2 Pinging 192.168.1.2 with 1464 bytes of data: Reply from 192.168.1.2: bytes=1464 time=10ms TTL=128 Reply from 192.168.1.2: bytes=1464 time<10ms TTL=128 Reply from 192.168.1.2: bytes=1464 time<10ms TTL=128 Reply from 192.168.1.2: bytes=1464 time<10ms TTL=128 Ping statistics for 192.168.1.2:     Packets: Sent = 4, Received = 4, Lost = 0 (0% loss), Approximate round trip times in milli-seconds:     Minimum = 0ms, Maximum =  10ms, Average =  2ms

现在出现回应了，这表示这个 MTU 值是可行的。不过应尽量找出可行的最大 MTU 值。这样才可以达到最佳的网络速率。

GNU/Linux 中修改 MTU 值的命令：[root@test root]# ifconfig eth0 mtu 1500
Comments (0)
Matrix multiplication
Monday, 21. November 2005, 06:02:02

perl 

#!/usr/bin/perluse warnings;use strict;my @a_matrix=([166,76,29,76],[2,8,29,17],[166,67,52,25]);my @b_matrix=([8,6,9,6],[12,82,2,6],[66,26,75,6],[97,81,62,6]);my @res;# $r--raws  $s--columns of @a_matrix  $c--columns of @b_matrixmy($r,$s,$c)=(2,3,3);foreach my $m(0 .. $r){    foreach my $n(0 .. $c){$res[$m][$n] = 0;foreach(0 .. $s){    $res[$m][$n] += ($a_matrix[$m][$_] * $b_matrix[$_][$n]);}    }}# output resultsforeach my $m(0 .. $r){    foreach my $n(0 .. $c){print $res[$m][$n],"\t"    }    print "\n";}__END__
Comments (0)
Mutt && mailing list
Saturday, 19. November 2005, 14:54:40

GNU linux 

Mutt有些配置选项能够使我们更容易地处理大量邮件.首先需要让Mutt知道那些地址你认为是邮件列表(从技术上来讲,这个地址并不一定需要是个邮件列表,但是我们通常都这么来用),还有,你订阅了哪些列表.要完成上述任务,你在需要在你的muttrc中使用list和subscribe命令. 

现在,Mutt知道你的邮件列表了,它能够做一些事了.首先,它能够分析你接收的邮件属于哪个邮件列表,然后在index菜单中显示出来.在同一邮箱中区分个人邮件和邮件列表邮件当然是非常有用的了.如果在$index_format变量中使用'%L',那么当"list"出现在'To'的字段中,则"To"显示为"To ",如果"list"出现在"Cc"字段中,则"Cc"显示为"Cc ". 

通常,邮件列表中的"To"和"Cc"字段都是非常长的.很多人都忘记了将list中发件人的地址去掉,造成发件人同时收到两封同样的信件,这是非常令人烦恼的一件事."list-reply"命令,通常在index菜单中绑定"L"键,解决了这个问题,它只回复已知的邮件列表地址,而不是回复到所有的接收者地址(有一种情况是例外的,如果用Mail-Follow-up邮件头,见下面的说明). 

Mutt也支持Mail-Followup-To邮件头.如果使用了$followup_to选项,当你给邮件列表中的接收者(通常包含一个或多个已订阅的邮件列表)发送邮件时,Mutt会创建一个Mail-Follow-up邮件头,包含除你自己以外的所有邮件接收者.这表示group-replies和list-replies将发送给所有原始邮件接收者,而不仅仅是你自己,你也将从你自己的邮件列表中获得邮件. 

相反地,如果设置了$honor_follow_up变量,那么group-replying或者list-replying一个含有Mail-Followup-To邮件头的邮件时,Mutt会考虑处理邮件头.在这种情况下如果使用list-reply将确保回复到了邮件列表,即使邮件列表没有出现在Mail-Follow-Up接收者的列表中. 

需要注意的是,如果打开了邮件头编辑功能,那么你可以手工地创建一个Mail-Follow-To邮件头.在你发送邮件时,仅仅在邮件头不存在的时候,Mutt为你自动创建一个. 

另外一种邮件列表管理员使用的方法是创建一个"Reply-To"字段指向邮件列表地址而不是邮件接收者地址.如果需要单独回复给邮件发送者,这种方法就会有问题了,这是因为很多邮件客户端软件在看到"Reply-To"字段时候,就自动回复.Mutt使用$reply-to变量来判定使用哪个地址回复.如果设置了$reply-to,你将得到提示,是否使用"Reply-To"地址来回复或者直接回复到"From"字段的地址.如果没有设置,那么用"Reply-To"字段的地址回复. 

可以用"X-Label:"头字段来标识邮件列表或者列表主题等等.$index_format中的"%y"和"%Y"可用来展开邮件头字段中的"X-Label:".Mutt的模式匹配器(patten-matcher)按"y"键时匹配"X-Label:"中的正则表达式."X-Label:"不是一个标准的邮件头字段,但用procmail或者其它mail过滤代理可以很容易的插入字段. 

最后,mutt可以将mailbox按照标题(threads)排序,一个标题包含一组与同一主题相关的邮件.这样,使得整个邮件序列按照树形展开,所有的回复也图形化的表示.如果你用过标题化的新闻组客户端,和那个是同一个的意思.这样处理可以删除不敢兴趣的标题,也可以快速找到想要的标题,使我们处理大量邮件时变得十分轻松.
Comments (0)
network test,configure time in linux,little_bird.mp3
Sunday, 6. November 2005, 05:01:08

linux, network 

网络测试工具： ping, host, dig, traceroute, mtr, nmap。
GNU/Linux 的时间设置。# -->2050/12/24 blog
ext3 file system inode 大小设置。


一个小mm唱的《我是一只小小鸟》，好可爱啊，呵呵。


有时候我觉得自己永远都吃不饱
也许只有吃的很多才能够长高
盼望能有一张迷人的相貌把所有人都迷倒
最后发现只有一种方法使用蒙汗药
长大之后无奈进入了社会我总是睡不着
我怀疑公司给别人的工资都比我高
总是努力学着对别人微笑难免也中他们圈套
偶尔上帝也会对我说失败很重要
我是一只只只~~~小鸟
因为吃的太多已经飞飞不高
我寻觅一颗栖息的树已被我压折了
这样的重量算不算太高
我是一只只只~~~小鸟
突然一天醒来有了迷人的美貌
麻雀也能飞上青天谁的歌声真美妙
美女的要求也不算太高
Comments (0)
Figures in TeX documents
Sunday, 30. October 2005, 15:20:57

LaTeX 

在 ChinaUnix bbs 上看到一个好帖。是一组图，展示了宇宙从宏观到微观的景象。我把这组图用 LaTeX 编译成 pdf 文档，不过总是出现错误提示。上班时候空闲比较零碎，正好处理这些问题。


Universe
 # md5sum: 943ef24b65fce0c88903b70fdf12b663 universe.pdf
# 2005/12/11 在出现错误提示的地方加上一行 \clearpage 就 OK 。
Comments (0)
CJK macro package
Thursday, 27. October 2005, 15:57:51

LaTeX 

在公司的电脑上装的 MiKTeX 2.4。发现一个问题，在使用 CJK 的时候使用 color package 和 xcolor package，编译时就出现错误提示，不使用 CJK 即恢复正常。用 \rule 画线似乎也有问题，明天再验证一下。在我的 e-TeX(Web2C 7.5.2) 3.141592-2.1 for GNU/Linux 版本运行得非常好。 

试了一下，必须把 \begin{CJK}{GBK}{fs} 这行放在正文区，才能避免上面的错误，但是这样在导言区就不能用中文，faint # 2005/10/29 11:05

=空穴来风=返回首页 

January 16, 2006
系统平均负载(Load average)解释
在Linux系统中，uptime、w、top等命令都会有系统平均负载load average的输出，那么什么是系统平均负载呢？
系统平均负载被定义为在特定时间间隔内运行队列中的平均进程树。如果一个进程满足以下条件则其就会位于运行队列中：
- 它没有在等待I/O操作的结果
- 它没有主动进入等待状态(也就是没有调用'wait')
- 没有被停止(例如：等待终止)

例如：
[root@www2 init.d]# uptime
7:51pm up 2 days, 5:43, 2 users, load average: 8.13, 5.90, 4.94
命令输出的最后内容表示在过去的1、5、15分钟内运行队列中的平均进程数量。
一般来说只要每个CPU的当前活动进程数不大于3那么系统的性能就是良好的，如果每个CPU的任务数大于5，那么就表示这台机器的性能有严重问题。对于上面的例子来说，假设系统有两个CPU，那么其每个CPU的当前任务数为：8.13/2=4.065。这表示该系统的性能是可以接受的。 

空穴来风 发表于 10:45 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

November 02, 2005
以 iptables 架設 SME 防火牆
由於 Internet 的普及和連接的成本下降， 很多企業都已經把辦公室網絡接上 Internet 去了。 而當各企業正享受著 Internet 所帶來的商機和方便的同時， 亦為企業本身帶來各種的危機。 從一些貪玩小孩的入侵， 到大規模的網蟲 (NetWorm) 爆發。 企業的系統無時無刻面對著各種挑戰。 一但系統被入侵， 所損失的往往多於能從 Internet 中所得到的。 所以我們必需要有一個防禦的機制來保護企業內的資料和財產， 免受外來的種種攻擊。 而當中最為普及的技術便是『防火牆』(Firewall)。  

什麼是防火牆 
『防火牆』只是一個統稱， 或者可以說是一個概念。 其實， 任何一種能成功防止外來入侵的網絡裝置或軟件， 都可以稱為『防火牆』。 

從網絡保安而言， 防火牆通常會用作內部網絡對外連接的唯一通道。 如此一來， 防火牆便成為了一個網絡關卡， 所有進出內部網絡的交通都必先經過防火牆的檢查和過濾， 防止入侵者接近內部的資源。 

而防火牆是根據網絡管理員預先定下的規則 (Rules) 來過濾網絡交通。 而這些規則便是整個防火牆的靈魂、內部網絡的守衛。 在制定這些規則時， 大都是圍繞著以下幾個範籌而定：  

誰〔不〕能進出網絡 
什麼〔不〕可以進出網絡 
資料〔不〕可以傳到那裡去 
用什麼方法才〔不〕可進出網絡   
防火牆的種類  
現時所流行的防火牆大致可分為以下兩類：  

1 封包過濾 (Packet Filters)  
封包過濾是透過檢測網絡封包的標頭 (Header) 資料是否符合管理員所定下的規則， 而決定是否讓其通過。 這些標頭資料包括了: 

來源/目的地的位址 (Address) 
來源/目的地的通訊埠 (Port) 
通訊協定 (Protocol)  
使用封包過濾的好處是其系統和應用程式中立性 (Operating Sytem & Application-neutral)， 對於在內部網絡的客端程式不須作任可更改便可提供保謢。 而本文將會介紹的 防火牆亦是封包過濾式的。  

2 應用層閘道 (Application Gateway)  
應用層閘道式的防火牆， 主要是在客端和伺服器之間加上『代理伺服器』(Proxy Server) 而達成。 如此一來， 網絡間的連線得變成兩個部驟： 首先是客端和代理伺服器連線， 然後經過過濾後才由代理伺服器和真實的伺服器連線。 

但是使用應用層閘道式的防火牆， 往往須要更改客端程式的設定來佩合。 這對於一般的用家 (End-user) 來說， 並不如封包過濾般方便。 

Linux 與 封包過濾  
Linux 核心自版本 1.1 開始已提供了封包過濾的功能。 到了現時的 2.4 版本內建的 Netfilter 模組， 功能更臻完善。 這個模組利用了一致被資訊保安界好評的 『狀態性』(Stateful) 機制， 記下各網絡連線的狀態並檢查往後的封包是否屬於同一連線。 狀態性機制能使防火牆能過濾一些以往不能偵測的連線狀態， 加強了內部網絡安全。  

iptables  
Netfilter 是在 Linux 核心 (Kernel) 的模組， 我們不能和它直接溝通。 它只會依著管理員定下的規則， 對封包進行檢測。 至於把怎樣才能把規則告知 Netfilter， 就得靠一個名為 iptables 的用戶端的程式。 

要把 iptables 運用得當， 就先要理解 Netfilter 處理封包的機制。 

之前提及過防火牆是透過一系列的規則而建成， 而每個規則都包含了一個對封包的描述 (Match) 和 一個處置動作 (Target)。 每當封包符合規則中的描述時， 核心便會對封包進行相應的處置動作。 而在 Netfilter 的角度中， 這些規則是記錄在不同的鏈 (Chain) 中， 而鏈又會被歸納到不同的規則表 (Table) 中。 

封包會根據它在核心中不同的層次和狀態， 被送到一個或多個規則表和鏈中， 並和當中的每個規則作對比並執行相應的動作。 iptables 的功用就是讓管理員管理各個規則表和鏈中的規則。 

 核心中的規則表 

在核心中有三個規則表:  

filter  
這個規則表是最常用的規則表， 也是 iptables 的預設的規則表。 所有對封包進行過濾的規則都是加進這個規則表的鏈中。 這個規則表中有三個預設的鏈， 分別是： INPUT (給目的地是本機的封包)， FORWORD (給途經本機的封包)， OUTPUT (給由本機所發出的封包)  

nat 
 這個規則表主要是給予系統 網路位址轉換 (Network Address Translation) 的功能。顧名思義， 網路位址轉換就是把封包標頭的位址和通訊埠的資料更改。 這個功能主要的用處是：  

Internet 連線分享。 即使只得一個可用的 Internet 位址， 也可把整個內部網絡的電腦接上 Internet。 
隱蔽內部網絡的存在。 縱然有足夠的 Internet 位址可用， 但基於保安的理由我們有時會不希望其他人知到企業內部網絡的存在。 運用網路位址轉換就可把所有內部網絡對外的通訊轉換成看似是同一位址所發出的封包一樣。 
服務轉向 (Forwording )。 當有伺服器置於防火牆後， 但又須要對外提供時， 便可以把目的地位址是防火牆的封包轉向到真實的伺服器。這個規則表中有三個預設的鏈， 分別是： PREROUTING (給所有進入本機而未經路由處理 (Routing Decision)的封包)， POSTROUTING (給所有經過路由處理而目的地不是本機的封包)， OUTPUT (給由本機所發出的封包)   
mangle  
這個規則表用來更改封包的一些屬性 (Properties)， 這個規則表中有四個預設的鏈， 分別是： PREROUTEING， INPUT， FORWARD ， OUTPUT 和 POSTROUTING。  

Iptables 的基本語法  
iptables -t Table -Operation Chain Match -j Target 

Table 是所用的是個規則表 
Chain 指明是用規則表中的哪一個鏈 
Operation 是對鏈中的規則所進行的動作， 例如：增加，移除，清空 等 
Match 是一個對封包的描述， 例如：來源地址及通訊埠 
Target 是處置動作， 例如：ACCEPT， DROP， LOG等 
 

常用的描述語法  
語法 用途 
-p [!] protocol 指定所針對的通訊協定， 例如：tcp， udp， icmp 
-s [!] address[/mask] 指定所針對的來源位址。 這可以是一個IP位址， 主機名稱， 或加上網絡遮罩以表示一群 IP 位址。 
-d [!] address[/mask] 指定所針對的目的地位址。 這可以是一個IP位址， 主機名稱， 或加上網絡遮罩以表示一群IP位址。 
-i [!] name 指定從那個網絡介面進入的封包。 例如：eth0， ppp0 
-o [!] name 指定從那個網絡介面送出的封包。 例如：eth0， ppp0 
--sport [!] port[:port] 指定來源通訊埠。 這可以指明是那一個或那一組埠 
--dport [!] port[:port] 指定目的地通訊埠。 這可以指明是那一個或那一組埠 
[!] --syn 只限 TCP 協定所用， 這指定封包須為 TCP 連線要求封包 


 防火牆架設範例 

有了基本的認識後， 我們便開始架設防火牆。 我們假設企業Ａ 有一個 Internet 連線和足夠的合法 Internet 位址給所有電腦使用。 而企業Ａ 只希望員工使用 WWW 和 FTP。 

我們可以跟著以下的步驟制作一個 Shell Script， 來架設防火牆。 

設定網絡參數和載入相關的核心模組

$INTERNAL_NET=X.X.X.X/24 # Local LAN Subnet
$INTERNAL_NIC=eth0 # Local LAN interface


$EXTERNAL_NET=Y.Y.Y.Y/8 # Internet Subnet
$EXTERNAL_NIC=eth1 # Internet interface


echo 1 > /proc/sys/net/ipv4/ip_forward


/sbin/modprobe ip_conntrack
/sbin/modprobe ip_conntrack_ftp
/sbin/modprobe ipt_state  

清除現有的規則  
-F 動作會清除所指定的鏈中的所有規則， 如果沒有指明鏈則規則表中所有的鏈都會被清空。 

/sbin/iptables -t filter -F
/sbin/iptables -t nat -F
/sbin/iptables -t mangle -F 

-X 動作會移除指定規則表中所有由用者增加的鏈

/sbin/iptables -t filter -X
/sbin/iptables -t nat -X
/sbin/iptables -t mangle -X  

設定預設政策  
-P 動作會設定所指定的鏈的預設政策。 當一個封包進入鏈後， 但沒有規則能符合這個封包的資料和狀態時， 核心會以鏈的預設政策去處理該個封包。 

每一個良好的防火牆的預設政策都應設為 DROP。 正所謂寧枉無縱， 預設拒絕所有封包， 然後才讓真正有用封包通過。 能使防火牆更為堅固。 

/sbin/iptables -t filter -P INPUT DROP
/sbin/iptables -t filter -P OUTPUT DROP
/sbin/iptables -t filter -P FORWARD DROP  

不回應 ICMP 封包  
如要查看一部主機是否在線， 最簡單的方法是使用 ping 指令。 如果不想被 ping， 可以設定 Netfilter 不回應 ICMP 封包 

/sbin/iptables -t filter -A INPUT -p icmp --icmp-type echo-requested -j DROP
/sbin/iptables -t filter -A OUTPUT -p icmp --icmp-type echo-reply -j DROP
/sbin/iptables -t filter -A FORWARD -p icmp --icmp-type echo-requested -j DROP
/sbin/iptables -t filter -A FORWARD -p icmp --icmp-type echo-reply -j DROP  

防止 IP Spoofing 
 IP Spoofing 是把外來的封包假裝成是內部網絡所發出的， 試途讓防火牆誤認而允許其進入內部網絡。 而要防止 IP Spoofing， 我們只須要過濾那些從 Internet 進入而聲稱來源地址是內部網絡的封包便可。 

/sbin/iptables -t filter -A INPUT -i $EXTERNAL_NIC -s $INTERNAL_NET -j DROP
/sbin/iptables -t filter -A FORWARD -i $EXTERNAL_NIC -s $INTERNAL_NET -j DROP  

防止網絡掃描  
網絡掃描是利用一些不正常而又合法的封包去檢測伺服器所提供的服務和取得一些系統資訊。 亦有入侵者用這些封包企途繞過防火牆去入侵內部網絡， 所以必需過濾。 

/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL ALL -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL ALL -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL NONE -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL NONE -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags SYN,RST SYN,RST -j DROP  

允許內部網絡使用者瀏覽 Internet 網頁  
要允許瀏覽 Internet 網頁， 我們須要允許封包從內部網絡傳送到 Web Server 去， 並同時要允許封包從 Web Server返回內部網絡。 

/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 80 -j ACCEPT
/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 443 -j ACCEPT 

要允許封包從 Web Server返回內部網絡， 有兩個方法設定。 其一是利用狀態性機制去自動判斷相關的封包： 

/sbin/iptables -t filter -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT 

其次是加上相應的規則： 

/sbin/iptables -t filter -A FORWARD -p tcp -d $INTERNAL_NET -s 0/0 --sport 80 ! --syn -j ACCEPT
/sbin/iptables -t filter -A FORWARD -p tcp -d $INTERNAL_NET -s 0/0 --sport 443 ! --syn -j ACCEPT 

利用狀態性機制去自動判斷的好處是， 只須設定一次就能和其他規則分享使用 (象以下的 DNS 和 FTP)， 能減少規則的數量，方便管理。  

允許內部網絡查詢 DNS  
DNS 是主機名稱和 IP 位址互換的服務， 如果過濾了 DNS 查詢， 用戶便不能用主機名稱 (如：http://www.linuxpilot.net ) 來瀏覽網頁， 而是要直接用 IP 位址 (如： http://203.194.196.187)。 

/sbin/iptables -t filter -A FORWARD -p udp -s $INTERNAL_NET -d 0/0 --dport 53 -j ACCEPT 

如果已有固定的 DNS 伺服器， 可以以下規則去限制只可以查詢指定的 DNS 伺服器： 

$DNSSRV=202.181.230.106 # IP Address of the DNS Server
/sbin/iptables -t filter -A FORWARD -p udp -s $INTERNAL_NET -d $DNSSRV --dport 53 -j ACCEPT  

允許內部網絡使用者使用 FTP  
大部份的 Internet 服務的設定基本上和之前的大同小異， 讀者可以嚐試自行設定。 但可惜的是 FTP 不只用一個通訊埠來進行資料傳送， 而是要用兩個。 更甚的是其中一個通訊埠是次次不同的， 根本不可能預先在防火牆中設定。 

有幸的是 Netfilter 所提供的狀態性機制能解決這個問題。 由於 FTP 的第二個通訊埠的連線， 是透過在埠21已建立的連線來建立， 所以可以利用狀態性機制去允許所有由已建立的連線所衍生出來的連線。 

/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 21 -j ACCEPT  

允許管理員以 SSH 連線到防火牆修改設定  
最後， 開設一個通道給管理員以 SSH 連線到防火牆修改設定。 不然的話， 每當有設定要修改時， 管理員便要親身登入防火牆修改了。 

/sbin/iptables -t filter -A INPUT -i $INTERNAL_NIC -s $INTERNAL_NET --dport 22 -j ACCEPT  

最後的步驟  
當設計好所有的規則和相應的 Script 後， 把所有的 Script 集合起來製成一個 Shell Script， 然後於 /etc/rc.d/rc.local 中加入執行該 Script 的命令。 這樣每次系統啟動時便會自動啟動防火牆。  

Internet 連線分享 
雖然以上的防火牆是基於有足夠的合法位址而設計， 但只須多加一規則便可以讓內部網絡以一個合法位址分享Internet 連線。 

如果獲得一個固定的合法位址， 可以用： 

$FIREWALL_IP=y.y.y.z # IP Address that can connect to Internet
/sbin/iptables -t nat -A POSTROUTING -o $EXTERNAL_NIC -s $INTERNAL_NET -j SNAT –to $FIREWALL_IP 

如果位址是動態分佩的話， 則用： 

/sbin/iptables -t nat -A POSTROUTING -o $EXTERNAL_NIC -s $INTERNAL_NET -j MASQUERADE 

其實以上兩個規則，都是叫核心把由內部網絡所發出的封包內的來源位址， 先轉成防火牆的合法位址再送出 Internet。 只不過用 MASQUERADE 方法時, 因為要顧及動態位址分佩， 所以會比 SNAT 多用一點 CPU 資源。  

總結 
Linux 加上 Netfilter 的強大功能， 給予中小企一個低成本的防火牆的解決方案。 以保障企業的資源。 以上的範例雖已包含了一般防火牆的功能， 但單靠 Netfilter 是未能杜絕所有的入侵 (例如： 電郵病毒)的。 所以系統管理員仍是要綜合各種網絡保安的工具一起， 發揮最大的效能。 

作者Isaac Chau 

原文在 LinuxPilot 第 15 期刊登
http://www.linuxhall.org/modules.php?name=News&file=article&sid=108


参考
iptables实战记录   [一个小公司针对不同局域网机器网络访问控制的例子]
http://blog.csdn.net/lidaibin/archive/2004/09/27/118111.aspx
Iptables 中文 man 文档
http://blog.chinaunix.net/article.php?articleId=11351&blogId=4005
Iptables 指南 1.1.19
http://misc.bbgo.cn/linux/iptables-tutorial-cn-1.1.19.html

空穴来风 发表于 01:47 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
怎样用ipchains构建防火墙
提示：防火墙是提供网络安全性的重要手段之一，RedHat6.1提供了用于实现过滤型防火墙的工具包——ipchains。实现防火墙的策略一般有两种：在第一种方式下，首先允许所有的包，然后在禁止有危险的包通过防火墙；第二种方式则相反，首先禁止所有的包，然后再根据所需要的服务允许特定的包通过防火墙。相比较而言，第二种方式更能保证网络的安全性。但对于第二种方式，要求使用者知道Server/Client交互的基本原理和特定服务所对应的具体端口。本文将从一个具体的实列出发，讨论怎样采用第二种方式构建企业的防火墙系统。

一、Server/Client的交互原理

首先让我们看一下服务器/客户机的交互原理。服务器提供某特定功能的服务总是由特定的后台程序提供的。在TCP/IP网络中，常常把这个特定的服务绑定到特定的TCP或UDP端口。之后，该后台程序就不断地监听（listen)该端口，一旦接收到符合条件的客户端请求，该服务进行TCP握手后就同客户端建立一个连接，响应客户请求。与此同时，再产生一个该绑定的拷贝，继续监听客户端的请求。

举一个具体的例子：假设网络中有一台服务器A（IP地址为a.b.c.1)提供WWW服务，另有客户机B(a.b.c.4)、C(a.b.c.7)。首先，服务器A运行提供WWW服务的后台程序（比如Apache）并且把该服务绑定到端口80，也就是说，在端口80进行监听。当B发起一个连接请求时,B将打开一个大于1024的连接端口(1024内为已定义端口）,假设为1037。A在接收到请求后，用80端口与B建立连接以响应B的请求，同时产生一个80端口绑定的拷贝，继续监听客户端的请求。假如A又接收到C的连接请求（设连接请求端口为1071），则A在与C建立连接的同时又产生一个80端口绑定的拷贝继续监听客端的请求。如下所示，每个连接都是唯一的。

服务器 客户端
连接1：a.b.c.1:80 <=> a.b.c.4:1037
连接2：a.b.c.1:80 <=> a.b.c.7:1071

二、服务端口
每一种特定的服务都有自己特定的端口，一般说来小于1024的端口多为保留端口，或者说是已定义端口，低端口分配给众所周知的服务（如WWW、FTP等等），从512到1024的端口通常保留给特殊的UNIXTCP/IP应用程序，具体情况请参考/etc/services文件或RFC1700。

三、网络环境
假设网络环境如下：某一单位，租用DDN专线上网，网络拓扑如下：

+--------------+
| 内部网段     | eth1+--------+eth0 DDN
| +------------|firewall|<===============>Internet
| 198.168.80.0 | +--------+
+--------------+
eth0: 198.199.37.254
eth1: 198.168.80.254

以上的IP地址都是Internet上真实的IP，故没有用到IP欺骗。并且，我们假设在内部网中存在以下服务器：
dns服务器：dns.yourdomain.com 由firewall兼任
www服务器：www.yourdomain.com 198.168.80.11
ftp服务器：ftp.yourdomain.com 198.168.80.12
bbs服务器：bbs.yourdomain.com 198.168.80.13
email服务器：mail.yourdomain.com 198.168.80.14
下面我们将用ipchains一步一步地来建立我们的包过滤防火墙。

四、实现步骤
说明：有关ipchains的详细命令用法，请参考有关HOWTO文档。在本例中，我们将在eth0和eth1的input chain设置过滤规则。

1. 在/etc/rc.d/目录下用touch命令建立firewall文件，执行chmod u+x firewll以更改文件属性，编辑/etc/rc.d/rc.local文件，在末尾加上 /etc/rc.d/firewall 以确保开机时能自动执行该脚本。

2. 刷新所有的ipchains

 #!/bin/sh
 echo "Starting ipchains rules..."
 #Refresh all chains
 /sbin/ipchains -F
3.设置WWW包过滤
说明：WWW端口为80，采用tcp或udp协议。
规则为：eth1=>允许所有来自Intranet的WWW包；eth0=>仅允许目的为内部网WWW服务器的包。

#Define HTTP packets
#Allow www request packets from Internet clients to www servers
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.11/32 www -i eth0 -j ACCEPT
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 1024: -d 198.168.80.11/32 www -i eth0 -j ACCEPT
#Allow response from Intranet www servers to request Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.11/32 www -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
/sbin/ipchains -A input -p udp -s 198.168.80.11/32 www -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
#Allow www request packets from Intranet clients to Internet www servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 www -i eth1 -j ACCEPT
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 www -i eth1 -j ACCEPT
#Allow www response packets from Internet www servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 www -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 www -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
4.设置ftp包过滤

说明：ftp端口为21,ftp-data端口为20，均采用tcp协议。
规则为：eth1=>允许所有来自Intranet的ftp、ftp-data包；eth0=>仅允许目的为内部网ftp服务器的包。

#Define FTP packets
#Allow ftp request packets from Internet clients to Intranet ftp server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.12/32 ftp -i eth0 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.12/32 ftp-data -i eth0 -j ACCEPT
#Allow ftp response packets from Intranet ftp server to Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.12/32 ftp -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 198.168.80.12/32 ftp-data -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
#Allow ftp request packets from Intranet clients to Internet ftp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 ftp -i eth1 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 ftp-data -i eth1 -j ACCEPT
#Allow ftp response packets from Internet ftp servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 ftp -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 ftp-data -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
5.设置telnet包过滤 
说明：telnet端口为21，采用tcp协议。
规则为：eth1=>允许所有来自Intranet的telnet包；eth0=>仅允许目的为bbs服务器的包；为了提高网络安全性，禁止所有对firewall的telnet请求。 

#Define telnet packets 
#Allow telnet request packets from Internet clients to Intranet bbs server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.13/32 telnet -i eth0 -j ACCEPT 
#Allow telnet response packets from bbs server to Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.13/32 telnet -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT 
#Allow telnet request packets from Intranet clients to Internet telnet servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 telnet -i eth1 -j ACCEPT 
#Allow telent response packets from Internet telnet servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 telnet -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
6.设置smtp包过滤 
说明：smtp端口为21，采用tcp协议。
规则为：eth1=>允许所有来自Intranet的smtp包；eth0=>仅允许目的为email服务器的smtp请求。

#Define smtp packets 
#Allow smtp request packets from Internet smtp servers to Intranet email server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.14/32 smtp -i eth0 -j ACCEPT 
#Allow smtp response packets from Intranet email server to Internet smtp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.14/32 smtp -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT 
#Allow smtp request packets from Intranet clients to Internet smtp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 smtp -i eth1  -j ACCEPT 
#Allow smtp response packets from Internet smtp servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 smtp -d 198.168.80.0/24 1024: -i eth0  -j ACCEPT 
7.设置POP-3包过滤 
说明：POP-3端口为110，采用tcp或udp协议。
规则为：eth1=>允许所有来自Intranet的POP-3包；eth0=>允许所有目的为Intranet（email server 除外）的POP-3包。 

#Define pop-3 packets 
#Allow pop-3 request packets from Intranet clients to Internet pop-3 servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 pop-3 -i eth1 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 pop-3 -i eth1 -j ACCEPT 
#Allow pop-3 response packets from Internet pop-3 servers to Intranet clients (except email server)
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 pop-3 -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 pop-3 -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
9.设置domain包过滤 
说明：domain端口为53，采用tcp或udp协议。
规则为：允许所有来自Intranet和Internet的domain请求。笔者在用网络监视软件测试时，发现domain的请求端口都是大于1100的，但是找不到相关的解释。 

#Donmain name server 
#Allow domain request packets from Intranet clients to Internet domain servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1100: -d 0.0.0.0/0 domain -i eth1 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1100: -d 0.0.0.0/0 domain -i eth1 -j ACCEPT 
#Allow domain response packets from Internet domain servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 domain -d 198.168.80.0/24 1100: -i eth0 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 domain -d 198.168.80.0/24 1100: -i eth0 -j ACCEPT 
10.设置icmp包过滤 
说明：icmp包通常用于网络测试等，故允许所有的icmp包通过。（另：icmp包通常带来的危害为ping of death，但是高版本的linux内核已经包含了相应的措施来避免ping of death） 

#Define icmp packets 
/sbin/ipchains -A input -p icmp -j ACCEPT 
11.设置缺省包过滤规则 
说明:除了以上所允许通过的包以外,禁止其他包通过。 

#Define all rules on input chain 
/sbin/ipchains -A input -j DENY -l 
通过以上个步骤，我们建立了一个相对完整的防火墙。该防火墙禁止除了提供基本服务以外的包通过。但是该防火墙还有不完善的地方，比如，某些搜索引擎会打开一个小于1024的但不常用的端口的连接，这样的包就无法通过该防火墙，从而使用户不能使用该搜索引擎。但是提高了网络的安全性，消除了安全隐患，所谓鱼与熊掌不可兼得，安全性重要还是服务重要就要看不同的情况了。

空穴来风 发表于 01:42 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
iptables－－静态防火墙实例教程- -
    在网上寻找iptable 配置的时候,发现这一篇文章,感觉比man手册更容易上手.

1、iptables介绍
 iptables是复杂的，它集成到linux内核中。用户通过iptables，可以对进出你的计算机的数据包进行过滤。通过iptables命令设置你的规则，来把守你的计算机网络──哪些数据允许通过，哪些不能通过，哪些通过的数据进行记录（log）。接下来，我将告诉你如何设置自己的规则，从现在就开始吧。


2、初始化工作
 在shell提示符 # 下打入

#iptables -F
#iptables -X
#iptables -t nat -F 
#iptables -t nat -X
 以上每一个命令都有它确切的含义。一般设置你的iptables之前，首先要清除所有以前设置的规则，我们就把它叫做初始化好了。虽然很多情况下它什么也不做，但是保险起见，不妨小心一点吧！ 如果你用的是redhat 或fedora，那么你有更简单的办法

#service iptables stop
3、开始设置规则:
 接下下开始设置你的规则了

#iptables -P INPUT DROP

 这一条命令将会为你构建一个非常“安全”的防火墙，我很难想象有哪个hacker能攻破这样的机器，因为它将所有从网络进入你机器的数据丢弃(drop) 了。这当然是安全过头了，此时你的机器将相当于没有网络。如果你ping localhost，你就会发现屏幕一直停在那里，因为ping收不到任何回应。


4 、添加规则
 接着上文继续输入命令：

#iptables -A INPUT -i ! ppp0 -j ACCEPT

 这条规则的意思是：接受所有的，来源不是网络接口ppp0的数据。
 我们假设你有两个网络接口，eth0连接局域网，loop是回环网（localhost）。ppp0是一般的adsl上网的internet网络接口，如果你不是这种上网方式，那则有可能是eth1。在此我假设你是adsl上网，你的internet接口是ppp0.
 此时你即允许了局域网的访问，你也可以访问localhost,此时再输入命令 ping localhost，结果还会和刚才一样吗？
 到此我们还不能访问www,也不能mail，接着看吧。


5、我想访问www

#iptables -A INPUT -i ppp0 -p tcp -sport 80 -j ACCEPT

 允许来自网络接口ppp0(internet接口)，并且来源端口是80的数据进入你的计算机。80端口正是www服务所使用的端口。好了，现在可以看网页了。但是，你能看到吗？
 如果你在浏览器的地址中输入www.baidu.com，能看到网页吗？你得到的结果一定是：找不到主机www.baidu.com,但是，如果你再输入220.181.27.5,你仍然能够访问baidu的网页。为什么？如果你了解dns的话就一定知道原因了。因为如果你打入www.baidu.com,你的电脑无法取得www.baidu.com这个名称所能应的ip地址220.181.27.5。如果你确实记得这个ip，那么你仍然能够访问www,你当然可以只用ip来访问www，如果你想挑战你的记忆的话^ _ ^，当然，我们要打开DNS。


6、打开dns端口
 打开你的dns端口，输入如下命令：

#iptables -A INPUT -i ppp0 -p udp -sport 53 -j ACCEPT

 这条命令的含义是，接受所有来自网络接口ppp0,upd协议的53端口的数据。53也就是著名的dns端口。此时测试一下，你能通过主机名称访问www吗？你能通过ip访问www吗？当然，都可以！


7、查看防火墙
　此时可以查看你的防火墙了

iptables -L 

　如果你只想访问www，那么就可以到此为止，你将只能访问www了。 不过先别急，将上面讲的内容总结一下，写成一个脚本。

#!/bin/bash
# This is a script 
# Edit by liwei
# establish static firewall
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -P INPUT DROP
iptables -A INPUT -i ! ppp0 -j ACCEPT
iptables -A INPUT -i ppp0 -p tcp --sport 80 -j ACCEPT
iptables -A INPUT -i ppp0 -p udp --sport 53 -j ACCEPT


8、开发服务器www端口
 复杂吗?到此iptables可以按你的要求进行包过滤了。你可以再设定一些端口，允许你的机器访问这些端口。这样有可能，你不能访问QQ，也可能不能打网络游戏，是好是坏，还是要看你自己而定了。顺便说一下，QQ这个东西还真是不好控制，用户与服务器连接使用的好像是8888端口，而QQ上好友互发消息使用的又是udp的4444端口(具体是不是4444还不太清楚)。而且 QQ还可以使用www的80端口进行登录并发消息，看来学无止境，你真的想把这个家伙控制住还不容易呢？还是进入我们的正题吧。如果你的机器是服务器，怎么办？
 如果不巧你的机器是服务器，并且要提供www服务。显然，以上的脚本就不能符合我们的要求了。但只要你撑握了规则，稍作修改同样也能很好的工作。在最后面加上一句

#iptables -A INPUT -i ppp0 -p tcp --dport 80 -j ACCEPT
 这一句也就是将自己机器上的80端口对外开放了,这样internet上的其他人就能访问你的www了。当然，你的www服务器得工作才行。如果你的机器同时是smtp和pop3服务器，同样的再加上两条语句,将--dport后面的80改成25和110就行了。如果你还有一个ftp服务器，呵呵，如果你要打开100个端口呢……
 我们的工作好像是重复性的打入类似的语句，你可能自己也想到了，我可以用一个循环语句来完成，对，此处可以有效的利用shell脚本的功能，也让你体验到了shell脚本语言的威力。看下文：


9、用脚本简化你的工作
 阅读下面的脚本

#!/bin/sh
# This is a script 
# Edit by liwei
# establish a static firewall
# define const here
Open_ports="80 25 110 10" # 自己机器对外开放的端口
Allow_ports="53 80 20 21" # internet的数据可以进入自己机器的端口

#init
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -P INPUT DROP #we can use another method to instead it 
iptables -A INPUT -i ! ppp0 -j ACCEPT

# define ruler so that some data can come in.
for Port in "Allow_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -sport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -sport $Port -j ACCEPT 
done
for Port in "Open_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -dport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -dport $Port -j ACCEPT 
done

 这个脚本有三个部分（最前面的一段是注释，不算在这三部分中）
 第一部分是定义一些端口：访问你的机器"Open_ports"端口的数据，允许进入；来源是"Allow_ports"端口的数据，也能够进入。
 第二部分是iptables的初始化，第三部分是对定义的端口具体的操作。
 如果以后我们的要求发生了一些变化，比如,你给自己的机器加上了一个ftp服务器，那么只要在第一部分"Open_ports"的定义中，将ftp对应的20与21端口加上去就行了。呵呵，到此你也一定体会到了脚本功能的强大的伸缩性，但脚本的能力还远不止这些呢！


10、使你的防火墙更加完善
 看上面的脚本init部分的倒数第二句

#iptables -P INPUT DROP
 这是给防火墙设置默认规则。当进入我们计算机的数据，不匹配我们的任何一个条件时，那么就由默认规则来处理这个数据----drop掉，不给发送方任何应答。也就是说，如果你从internet另外的一台计算机上ping你的主机的话，ping会一直停在那里，没有回应。
 如果黑客用namp工具对你的电脑进行端口扫描，那么它会提示黑客，你的计算机处于防火墙的保护之中。我可不想让黑客对我的计算机了解太多，怎么办，如果我们把drop改成其他的动作，或许能够骗过这位刚出道的黑客呢。怎么改呢？将刚才的那一句( iptables -P INPUT DROP )去掉，在脚本的最后面加上

#iptables -A INPUT -i ppp0 -p tcp -j REJECT --reject-with tcp-reset
#iptables -A INPUT -i ppp0 -p udp -j REJECT --reject-with icmp-port-unreachable
 这样就好多了，黑客虽然能扫描出我们所开放的端口，但是他却很难知道，我们的机器处在防火墙的保护之中。如果你只运行了ftp并且仅仅对局域网内部访问, 他很难知道你是否运行了ftp。在此我们给不应该进入我们机器的数据，一个欺骗性的回答，而不是丢弃(drop)后就不再理会。这一个功能，在我们设计有状态的防火墙中(我这里讲的是静态的防火墙)特别有用。
 你可以亲自操作一下，看一看修改前后用namp扫描得到的结果会有什么不同？


11、
 这个教程我想到此就结束了，其中有很多东西在这里没有提到，如ip伪装，端口转发，对数据包的记录功能。还有一个很重要的东西就是：iptables处理数据包的流程.在这里我想告诉你，你设置的过滤规则的顺序很重要，在此不宜详细介绍，因为这样一来，这个教程就会拘泥于细节。
 iptables是复杂的，我在linuxsir上看过很多教程，它们往往多而全，反而让人望而生畏，希望我的这个教程，能够指导你入门。加油！
 最后，我把完整的脚本写出来如下，你只要修改常量定义部分，就能表现出较大的伸缩性^_^

#!/bin/bash
# This is a script 
# Edit by liwei
# establish a static firewall

# define const here
Open_ports="80 25 110 10" # 自己机器对外开放的端口
Allow_ports="53 80 20 21" # internet的数据可以进入自己机器的端口

#init
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X

# The follow is comment , for make it better
# iptables -P INPUT DROP 
iptables -A INPUT -i ! ppp0 -j ACCEPT

# define ruler so that some data can come in.
for Port in "Allow_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -sport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -sport $Port -j ACCEPT 
done
for Port in "Open_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -dport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -dport $Port -j ACCEPT 
done

# This is the last ruler , it can make you firewall better
iptables -A INPUT -i ppp0 -p tcp -j REJECT --reject-with tcp-reset
iptables -A INPUT -i ppp0 -p udp -j REJECT --reject-with icmp-port-unreachable


参考:
iptables－－静态防火墙实例教程 
http://antlinux.blogchina.com/1466805.html

空穴来风 发表于 01:17 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
[Linux]ident的作用
曾听过有人形容 identd (及 Ident protocol RFC1413) 像猴群一样, "你抓抓我的背, 我也抓抓你的背, 大家互惠" :-) 

假设您是一个 BBS 的管理者, 今天发现有一封广告信贴在所有的版子, 您想查清楚这封信的来源, 如果发现它是某学校的一台 PC, 那很好办, 但是, 如果您发现对方的来源 IP 是一拥有几万个 user 的工作站, 
say, tpts1.seed.net.tw, 那该怎麽办? 

Identd (及 Ident protocol) 就是针对这个理由设计出来的, 假设现在有两主机都 support Ident protocol, 也就是说, 除了双方都安装了 identd 之外, 双方的 server 程式 (telnetd, sendmail, bbs...) 
都启动 ident 查询功能. 如果您在主机 A 上要去连主机 B, 主机 B在接受您的连接 request 时, 会向主机 A 上的 Identd 做身份查询, 也就是问问 "现在要连上我机器的伙, 在你那儿是什麽身份" , 而 
主机 A 就会把你的身份 (username/id) 报给主机 B. 这麽一来, 主机 B 就有了你的身份纪录, 要是发生什麽事, 秋後算帐就比较容易了 :-) 

比较细节的身份查询过程, 可以用下图表示出来 

HOST A                                        HOSTB 
=============================          ================== 
1. 使用者 xyz 要telnet到 HOST B 
  xyz% telnet host-B 

2. 假设这个 telnet connection 在 
  双方主机上的 port  number 是 
  1027 (A) 和 23 (B) 

                                      3. 在收到这个 telnet request 
                                         的时候, telnetd (or tcpwrapper 
                                         or whatever) 就先连到 HOST 
                                         A 的 identd (port 113) 

                                      4. HOST B 向 HOST A 说: 
                                          "1027, 23" 

5. HOST A检查一下自己机器, 看看 
  是谁在 port 1027 连到 host B 
  的 port 23, 结果发现是 xyz 

6. HOST A 回覆查询结果: 
  "1027, 23 : userid : UNIX : xyz" 

                                      7. HOST B 就可以记录下来: 
                                         某年某月某日, xyz@hostA连到我的 
                                         机器.... 

从上面的说明, 或许您会发现, identd 的运作似乎与一般的 telnet/www/bbs等应用没有什麽关联, 如果不用 identd , 似乎也可以活得好好的. 确实如此, 不过, 基於 "给人方便, 自己方便" 的原则, 如果你有一台多用户 
工作站, 装上 identd, 在别人发生意外事件时调查起来比较容易. 

重复一次, Identd 对你自己的系统安全并没有任何助益 (事实上, 它有时会造成效率上的影响, 有些人甚至认为它漏了用户的隐私性), 但是, 如果您装上了identd, 未来某些时候可能某主机的 SA 会非常感激您, 同样地, 
如果你自己上发生什麽安全事件的话, 您也会很感激那些有装 Identd 的管理者. 


空穴来风 发表于 01:20 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

October 27, 2005
syslog.conf
1: syslog.conf的介绍

    对于不同类型的Unix，标准UnixLog系统的设置，实际上除了一些关键词的不同，系统的syslog.conf格式是相同的。syslog采用可配置的、统一的系统登记程序，随时从系统各处接受log请求，然后根据/etc/syslog.conf中的预先设定把log信息写入相应文件中、邮寄给特定用户或者直接以消息的方式发往控制台。值得注意的是，为了防止入侵者修改、删除messages里的记录信息，可以采用用打印机记录或采用方式来挫败入侵者的企图。

2: syslog.conf的格式

    可以参考man [5] syslog.conf。这里是对syslog.conf的简单介绍。
    /etc/syslog.conf文件中的一项配置记录由“选项”(selector)和“动作”(action)两个部分组成，两者间用tab制表符进行分隔(使用空格间隔是无效的)。而“选项”又由一个或多个形如“类型.级别”格式的保留字段组合而成，各保留字段间用分号分隔。如下行所示：

        类型.级别 [；类型.级别] `TAB` 动作 
2.1 类型 

    保留字段中的“类型”代表信息产生的源头，可以是： 

    auth    认证系统，即询问用户名和口令
    cron    系统定时系统执行定时任务时发出的信息
    daemon  某些系统的守护程序的syslog,如由in.ftpd产生的log
    kern    内核的syslog信息
    lpr     打印机的syslog信息
    mail    邮件系统的syslog信息
    mark    定时发送消息的时标程序
    news    新闻系统的syslog信息
    user    本地用户应用程序的syslog信息
    uucp    uucp子系统的syslog信息
    local0..7 种本地类型的syslog信息,这些信息可以又用户来定义
    *       代表以上各种设备
2.2 级别

    保留字段中的“级别”代表信息的重要性，可以是： 

    emerg   紧急，处于Panic状态。通常应广播到所有用户； 
    alert   告警，当前状态必须立即进行纠正。例如，系统数据库崩溃； 
    crit    关键状态的警告。例如，硬件故障； 
    err     其它错误； 
    warning 警告； 
    notice  注意；非错误状态的报告，但应特别处理； 
    info    通报信息； 
    debug   调试程序时的信息； 
    none    通常调试程序时用，指示带有none级别的类型产生的信息无需送出。如*.debug;mail.none表示调试时除邮件信息外其它信息都送出。 
2.3 动作

    “动作”域指示信息发送的目的地。可以是： 

    /filename   日志文件。由绝对路径指出的文件名，此文件必须事先建立； 
    @host       远程主机； @符号后面可以是ip,也可以是域名，默认在/etc/hosts文件下loghost这个别名已经指定给了本机。
    user1,user2 指定用户。如果指定用户已登录，那么他们将收到信息； 
    *           所有用户。所有已登录的用户都将收到信息。 
3: 具体实例

    我们来看看/etc/syslog.conf文件中的实例： 

    …… 
    *.err;kern.debug;daemon.notice;mail.crit    [TAB]   /var/adm/messages 
    …… 
    这行中的“action”就是我们常关心的那个/var/adm/messages文件，输出到它的信息源头“selector”是： 
    *.err - 所有的一般错误信息； 
    kern.debug - 核心产生的调试信息； 
    daemon.notice - 守护进程的注意信息； 
    mail.crit - 邮件系统的关键警告信息 




空穴来风 发表于 08:51 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
[Debian] Exim4 邮件服务器配置
    使用PHP的mail函数发送邮件的时候发现竟然没有接收到邮件.好像用Redhat的时候不需要配置就可以直接使用了.Debian的这个以前都没有怎么注意过.既然碰到了问题.当然今天要把它解决了.lol.

    1.首先安装配置exim4(sarge下默认为exim4).

apt-get install exim4 ##如果需要安装exim4
dpkg-reconfigure exim4-config 
    2.上面设置完后,得到的配置文件/etc/exim4/update-exim4.conf.conf 内容如下 

# /etc/exim4/update-exim4.conf.conf
#
# Edit this file and /etc/mailname by hand and execute update-exim4.conf
# yourself or use 'dpkg-reconfigure exim4-config'
#
# Please note that this is _not_ a dpkg-conffile and that automatic changes
# to this file might happen. The code handling this will honor your local
# changes, so this is usually fine, but will break local schemes that mess
# around with multiple versions of the file.
#
# update-exim4.conf uses this file to determine variable values to replace
# the DEBCONFsomethingDEBCONF strings in the configuration template files.
#
# Most settings found in here do have corresponding questions in the
# Debconf configuration, but not all of them.
#
# This is a Debian specific file

dc_eximconfig_configtype='internet'
dc_other_hostnames='bbgo.cn'
dc_local_interfaces='127.0.0.1'
dc_readhost=''
dc_relay_domains='localhost'
dc_minimaldns='false'
dc_relay_nets='222.36.45.20/32'
dc_smarthost=''
CFILEMODE='644'
dc_use_split_config='false'
dc_hide_mailname=''
dc_mailname_in_oh='true'

    3.然后重新启动服务器就可以了.

/etc/init.d/exim4 restart

    4.测试一下

echo "my test" | mail -s "test message" tommy
tail -f /var/log/exim4/mainlog
    如果显示complete，就表示成功了。用tommy用户登陆 

mail
    看看有没有信。 

    5.后记
    #1 在测试的时候,我发邮件给用户tommy,然后直接su过去,发现使用mail的时候没有显示有邮件.但是login的话,却有邮件提示.这个害我以为邮件服务器出错呢:(
    #2 /etc/exim4/update-exim4.conf.conf中的dc_relay_domains='localhost'这行之前我设置为其他的,不知道为什么出错:( 改为这个就ok了.
    #3 /var/log/exim4/mainlog 这个文件有丰富的信息,如果邮件服务器出错的话,可以参考这个文件对配置进行修改.

参考:
Debian exim4 设置
http://www.wasai.org/wiki/index.php/Debian_exim4_%E8%AE%BE%E7%BD%AE
安装 Exim 邮件服务器 
http://www.linuxforum.net/forum/gshowflat.php?Board=debian&Number=427997
Debian服务器设置入门 - 在Debian上用Exim配置邮件服务器
http://www.lslnet.com/linux/docs/linux-3895.htm


 

空穴来风 发表于 01:24 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

October 20, 2005
[Debian] 升级PHP4到PHP5
安装了Sarge以后,发现Vanilla和PhpWind这两个论坛不能使用了.可能是PHP4的问题吧.不过Debian官方没有发布PHP5的Debian包.还好Dotdeb 提供了PHP5以及相应的Module.

安装如下:

##在/etc/apt/source.list 添加下面两行
deb http://packages.dotdeb.org stable all
deb-src http://packages.dotdeb.org stable all
##运行命令
#apt-get update
#apt-get install php5 libapache2-mod-php5 php5-mysql 
安装以后可能需要重新修改php.ini 以及 php5.conf文件.

参考:
Dotdeb [提供包括供Sarge使用PHP4&5,mysql 4.1&5.0,Qmail,Vpopmail等]
http://dotdeb.org/


空穴来风 发表于 03:02 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 30, 2005
Redhat 下的yum
一. yum是什么
yum = Yellow dog Updater, Modified
主要功能是更方便的添加/删除/更新RPM包.
它能自动解决包的倚赖性问题.
它能便于管理大量系统的更新问题
注:为什么要使用yum而不用apt,最简单的原因,Fedora自带

二. yum特点
*可以同时配置多个资源库(Repository)
*简洁的配置文件(/etc/yum.conf)
*自动解决增加或删除rpm包时遇到的倚赖性问题
*使用方便
*保持与RPM数据库的一致性

三. yum安装
Fedora自带
#rpm -ivh yum-2.0.4-2.noarch.rpm

四. yum配置
注:修改和增加配置文件中的资源库,加快下载速度和拥有更多可更新的rpm包
将/etc/yum.conf的内容全部替换为

[main]
    cachedir=/var/cache/yum
    debuglevel=2
    logfile=/var/log/yum.log
    pkgpolicy=newest
    distroverpkg=fedora-release
    tolerant=1
    exactarch=1

[fedora-us-1]
    name=Fedora Core 1 -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/os

[fedora-us-1-updates]
    name=Fedora Core 1 updates -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/updates

[fedora-us-1-stable]
    name=Fedora Linux (stable) for Fedora Core 1 -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/stable

[freshrpms]
    name=Fedora Linux $releasever - $basearch - freshrpms
    baseurl=http://ayo.freshrpms.net/fedora/linux/$releasever/$basearch/freshrpms

五. yum应用
注:当第一次使用yum或yum资源库有更新时,yum会自动下载所有所需的headers放置于/var/cache/yum目录下,所需时间可能较长.

//检查有哪些可更新的rpm包
#yum check-update
//安装rpm包,使xmms可以播放mp3
#yum install xmms-mp3
//安装mplayer,同时自动安装相关的软件
#yum install mplayer
//删除licq包,同时删除与该包有倚赖性的包
#yum remove licq
注:同时会提示删除licq-gnome,licq-qt,licq-text,非常方便
//系统更新(更新所有可以升级的rpm包,包括kernel)
#yum -y update
//每天定期执行系统更新
#chkconfig yum on
#service yum start
六. yum指令详解
*rpm包的更新

//检查可更新的rpm包
#yum check-update
//更新所有的rpm包
#yum update
//更新指定的rpm包,如更新kernel和kernel source
#yum update kernel kernel-source
//大规模的版本升级,与yum update不同的是,连旧的淘汰的包也升级
#yum upgrade

*rpm包的安装和删除

//安装rpm包,如xmms-mp3
#yum install xmms-mp3
//删除rpm包,包括与该包有倚赖性的包
#yum remove licq
注:同时会提示删除licq-gnome,licq-qt,licq-text

*yum暂存(/var/cache/yum/)的相关参数

//清除暂存中rpm包文件
#yum clean packages
//清除暂存中rpm头文件
#yum clearn headers
//清除暂存中旧的rpm头文件
#yum clean oldheaders
//清除暂存中旧的rpm头文件和包文件
#yum clearn 或#yum clearn all
注:相当于yum clean packages + yum clean oldheaders

*rpm包列表

//列出资源库中所有可以安装或更新的rpm包
#yum list
//列出资源库中特定的可以安装或更新以及已经安装的rpm包
#yum list mozilla
#yum list mozilla*
注:可以在rpm包名中使用匹配符,如列出所有以mozilla开头的rpm包
//列出资源库中所有可以更新的rpm包
#yum list updates
//列出已经安装的所有的rpm包
#yum list installed
//列出已经安装的但是不包含在资源库中的rpm包
#yum list extras
注:通过其它网站下载安装的rpm包

*rpm包信息显示(info参数同list)

//列出资源库中所有可以安装或更新的rpm包的信息
#yum info
//列出资源库中特定的可以安装或更新以及已经安装的rpm包的信息
#yum info mozilla
#yum info mozilla*
注:可以在rpm包名中使用匹配符,如列出所有以mozilla开头的rpm包的信息
//列出资源库中所有可以更新的rpm包的信息
#yum info updates
//列出已经安装的所有的rpm包的信息
#yum info installed
//列出已经安装的但是不包含在资源库中的rpm包的信息
#yum info extras
注:通过其它网站下载安装的rpm包的信息

*搜索rpm包

//搜索匹配特定字符的rpm包
#yum search mozilla
注:在rpm包名,包描述等中搜索
//搜索有包含特定文件名的rpm包
#yum provides realplay
七. 安全的更新freshrpms.net的rpm包
安装freshrpms.net的GPG key

#rpm --import http://freshrpms.net/packages/build...G-KEY.freshrpms

编辑/etc/yum.conf,增加以下信息到尾部

[freshrpms]
name=Fedora Linux $releasever - $basearch - freshrpms
baseurl=http://ayo.freshrpms.net/fedora/linux/$releasever/$basearch/freshrpms
gpgcheck=1
注: 

  //检查GPG Key
# rpm -qa gpg-pubkey*
//显示Key信息
#rpm -qi gpg-pubkey-e42d547b-3960bdf1
//删除Key
#rpm -e gpg-pubkey-e42d547b-3960bdf1
参考:
Linux RPM包使用指南 


空穴来风 发表于 03:59 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
Baidu Top 500 歌曲下载
很早以前就有根据百度MP3_歌曲TOP500 来获取对应的mp3的脚本,在电脑中也放着这么一个,今天整理硬盘的时候才好好的看了一看:)其实原理就这么简单,呵呵.看脚本的时候最好对应着相应页面分析一下.

#!/bin/sh
# By 6e sixwings@gmail.com
#分析得出歌曲对应的页面
wget http://list.mp3.baidu.com/topso/mp3topsong.html
cat mp3topsong.html  | tr \" \\n | pcregrep tsomp3.htm$ > list.raw
#获取所有页面-每个里面包含了歌曲对应的mp3下载地址
#保存在[1-500].html文件中
CC=1
for VAL in `cat list.raw` do
wget http://list.mp3.baidu.com/topso/$VAL -O $CC.html &
usleep 100
CC=`expr $CC + 1`
done
#分析上面获取的页面来得到mp3文件地址
NUM=`cat list.raw | wc -l`
CC=1
while [ $CC -le $NUM ] do
#获取mp3列表的第一个地址
URL=`cat $CC.html  | tr \" \\\n | pcregrep mp3$ | pcregrep ^http:// | head -1`
#获取mp3文件名
TITLE=`head -8 $CC.html | pcregrep '^空穴来风 发表于 03:10 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 25, 2005
一个新的版本控制系统 GNU-arch
在搜索资料的时候发现了这个东东..

1.特点 
与其他版本控制系统最大差异:
1.可以控制整个目录结构,而不善只有单一档案的版本
2.在改版时不只是记录目录结构,还会包括所有异动的描述
3.不再透过统一的档案库控制,每个开发人员可以控制自己负责的范围,Arch会将其串联起来.

2.安装
在Debian下

apt-get install tla tla-doc

3.下载一个Archive
要下载一个Project的源码,你需要三个信息
-the archive's name (ex. tom@example.org--2004)
-the version name (ex. hello--main--1.0)
-the URI of that archive (ex. http://www.example.org/~tom/archives/2004)

First, you need to use register-archive to register the archive: 

$ tla register-archive http://www.example.org/~tom/archives/2004
Registering archive: tom@example.org--2004

You can verify that the archive was actually registered using archives. 

$ tla archives
tom@example.org--2004
    http://www.example.org/~tom/archives/2004


Now you can use get to get a copy of the current revision. 

$ tla get tom@example.org--2004/hello--main--1.0 hello
* from revision library: tom@example.org--2004/hello--main--1.0--patch-23
* making pristine copy
* tree version set tom@example.org--2004/hello--main--1.0

The exact output will vary, but after executing this command, you will have a copy of the latest revision of the hello--main--1.0 branch in the hello directory.



参考:
1.http://www.gnuarch.org/ -- GNU Arch 
2.http://www.linuxjournal.com/article/5928 -- An Introduction to the arch Version Control System
3.ftp://ftp.gnu.org/pub/gnu/gnu-arch -- the primary distribution site for GNU Arch.]
4.http://lists.gnu.org/mailman/listinfo/gnu-arch-users -- the gnu-arch-users mailing list. 
5.http://lists.seyza.com/cgi-bin/mailman/listinfo/gnu-arch-dev -- the gnu-arch-dev mailling list. 
6.http://wiki.gnuarch.org -- the Arch Wiki, maintained by users.

空穴来风 发表于 06:45 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 11, 2005
Linux RPM包使用指南
通常Linux应用软件的安装包有三种：tar包、rpm包和dpkg包。本文主要提到的rpm包是Redhat Linux提供的一种包封装格式。RPM 有五种基本的操作方式(不包括创建软件包): 安装，卸载，升级，查询和验证。下面我们就来逐一的讲解。 

一、安装RPM包 
　　 RPM 软件包通常具有类似foo-1.0-1.i386.rpm 的文件名。其中包括 软件包的名称(foo)，版本号(1.0)，发行号(1)， 和 硬件平台(i386)。安装一个软件包只需简单的键入以下命令： 

　　 $ rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　　　　　　　 #################################### 

　　 RPM安装完毕后会打印出软件包的名字(并不一定与文件名相同)， 而后打印一连串的#号以表示安装进度。虽然软件包的安装被设计的尽量简单易行， 但还是可能会发生如下的错误： 

　　 1、软件包已被安装 
　　 如果您的软件包已被安装, 将会出现以下信息： 

　　 $ rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　　　　　　　 package foo-1.0-1 is already installed 
　　 error: foo-1.0-1.i386.rpm cannot be installed 

　　 如果您仍旧要安装该软件包，可以在命令行上使用--replacepkgs 选项，RPM将忽略该错误信息强行安装。 

　　 2、文件冲突 
　　 如果您要安装的软件包中有一个文件已在安装其它软件包时安装，会出现以下错误信息： 

　　 # rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　 /usr/bin/foo conflicts with file from bar-1.0-1 
　　 error: foo-1.0-1.i386.rpm cannot be installed 

　　 要想让RPM 忽略该错误信息， 请使用--replacefiles 命令行选项。 

　　 3、未解决依赖关系 
　　 RPM软件包可能依赖于其它软件包，也就是说要求在安装了特定的软件包之后才能安装该软件包。如果在您安装某个软件包时存在这种未解决的依赖关系。会产生以下信息： 

　　 $ rpm -ivh bar-1.0-1.i386.rpm 
　　 failed dependencies: foo is needed by bar-1.0-1 

　　 您必须安装完所依赖的软件包，才能解决这个问题。如果您想强制安装(这是个坏主意， 因为安装后的软件包未必能正常运行)， 请使用--nodeps 命令行选项。 

二、卸载RPM包 
　　 卸载软件包就象安装软件包时一样简单： 

　　 $ rpm -e foo 

　　 注意这里使用软件包的名字name “foo”， 而不是软件包文件的名字file “foo-1.0-1.i386.rpm”。 

　　 如果其它软件包依赖于您要卸载的软件包，卸载时则会产生错误信息。如： 

　　 $ rpm -e foo 
　　 removing these packages would break dependencies:foo is needed by bar-1.0-1 

　　 若让RPM忽略这个错误继续卸载(这可不是一个好主意，因为依赖于该软件包的程序可能无法运行)，请使用--nodeps 命令行选项。 

三、升级RPM包 
　　 升级软件包和安装软件包十分类似： 

　　 $ rpm -Uvh foo-2.0-1.i386.rpm 
　　 foo　　　　　　　　　　 #################################### 

　　 RPM将自动卸载已安装的老板本的foo 软件包，您不会看到有关信息。事实上您可能总是使用 -U 来安装软件包，因为即便以往未安装过该软件包，也能正常运行。因为RPM 执行智能化的软件包升级，自动处理配置文件，您将会看到如下信息： 

　　 saving /etc/foo.conf as /etc/foo.conf.rpmsave 

　　 这表示您对配置文件的修改不一定能向上兼容。 因此，RPM 会先备份老文件再安装新文件。您应当尽快解决这两个配置文件的不同之处，以使系统能持续正常运行。 

　　 因为升级实际包括软件包的卸载与安装两个过程，所以您可能会碰到由这两个操作引起的错误。另一个你可能碰到的问题是：当您使用旧版本的软件包来升级新版本的软件时，RPM会产生以下错误信息： 


　　 $ rpm -Uvh foo-1.0-1.i386.rpm 
　　 foo　　package foo-2.0-1 (which is newer) is already installed 
　　 error: foo-1.0-1.i386.rpm cannot be installed 


　　 如果你确有需要将该软件包”降级，加入 --oldpackage 命令选项就可以了。 

四、查询已安装的软件包 
　　 使用命令rpm -q来查询已安装软件包的数据库。简单的使用命令 rpm -q foo 会打印出foo软件包 的包名 ，版本号，和发行号： 


　　 $ rpm -q foo 
　　 foo-2.0-1 


　　 除了指定软件包名以外，您还可以使用以下选项来指明要查询哪些软件包的信 息。 这些选项被称之为 “软件包指定选项“。 

　　 ●-a 查询所有已安装的软件包 
　　 ●-f 将查询包含有文件 . 的软件包 
　　 ●-p 查询软件包文件名为 的软件包 

　　 还可以指定查询软件包时所显示的信息。它们被称作信息选择选项： 

　　 ●-i 显示软件包信息，如描述, 发行号, 尺寸, 构建日期, 安装日期, 平台, 以及其它一些各类信息。
　　 ●-l 显示软件包中的文件列表。 
　　 ●-s 显示软件包中所有文件的状态。 
　　 ●-d 显示被标注为文档的文件列表(man 手册, info 手册, README's, etc)。 
　　 ●-c 显示被标注为配置文件的文件列表。这些是您要在安装完毕以后加以定制的文件(sendmail.cf, passwd, inittab, etc)。 

　　 对于那些要显示文件列表的文件, 您可以增加-v 命令行选项以获得如同 ls -l 格式的输出。 

五、验证软件包 
　　 验证软件包是通过比较已安装的文件和软件包中的原始文件信息来进行的。验证主要是比较文件的尺寸, MD5 校验码, 文件权限, 类型, 属主和用户组等。 

rpm-V命令用来验证一个软件包。您可以使用任何包选择选项来查询您要验证的软件包。 命令rpm -V foo 将用来验证foo软件包。又如： 

　　 ●验证包含特定文件的软件包：rpm -Vf /bin/vi； 
　　 ●验证所有已安装的软件包：rpm -Va； 
　　 ●根据一个RPM包来验证：rpm -Vp foo-1.0-1.i386.rpm。 

　　 如果您担心你的RPM数据库已被破坏，就可以使用这种方式。 

如果一切均校验正常将不会产生任何输出。如果有不一致的地方，就会显示出来。 输出格式是8位长字符串, “c” 用以指配置文件, 接着是文件名. 8位字符的每一个 用以表示文件与RPM数据库中一种属性的比较结果。“.” (点) 表示测试通过。下面的字符表示对RPM软件包进行的某种测试失败： 


　　 显示字符　　　　　　　　 错误源 
　　 5　　　　　　　　　　　　MD5 校验码 
　　 S　　　　　　　　　　　　文件尺寸 
　　 L　　　　　　　　　　　　符号连接 
　　 T　　　　　　　　　　　　文件修改日期 
　　 D　　　　　　　　　　　　设备 
　　 U　　　　　　　　　　　　用户 
　　 G　　　　　　　　　　　　用户组 
　　 M　　　　　　　　　　　　模式e (包括权限和文件类型) 


　　 如果有错误信息输出, 您应当认真加以考虑，是通过删除还是重新安装来解决出现的问题。 

六、教你一招 
　　 RPM不仅是安装/卸载程序的工具，它还是系统维护和诊断的一把好手。看过下面几个例子你就会领教它的厉害了。 

　　 ●如果您误删了一些文件，但您不能肯定到底都删除了那些文件，怎么办？您可以键入：rpm -Va。 
　　 rpm会在屏幕上显示出文件删除的情况。若你发现一些文件丢失了或已被损坏, 您就可以重新安装或先卸载再安装该软件包。 

　　 ●如果您碰到了一个自己不认识的文件，要想查处它属于哪个软件包，您可以输入以下命令： 

　　 rpm -qf /usr/X11R6/bin/xjewel 
　　 输出的结果会是：xjewel-1.6-1。 


　　 ●如果发生综合以上两个例子的情况，如文件/usr/bin/paste出了问题。您想知道哪个软件包中包含该文件，您这时可以简单的键入：rpm -Vf /usr/bin/paste。 

　　 ●如果您想了解正在使用的程序的详细信息, 您可以键入如下命令来获得软件包中关于该程序的文档信息： 


　　 rpm -qdf /usr/bin/ispell 
　　 输出结果为: 
　　 /usr/man/man4/ispell.4 
　　 /usr/man/man4/english.4 
　　 /usr/man/man1/unsq.1 
　　 /usr/man/man1/tryaffix.1 
　　 /usr/man/man1/sq.1 
　　 /usr/man/man1/munchlist.1 
　　 /usr/man/man1/ispell.1 
　　 /usr/man/man1/findaffix.1 
　　 /usr/man/man1/buildhash.1 
　　 /usr/info/ispell.info.gz 
　　 /usr/doc/ispell-3.1.18-1/README 


　　 ●您发现了一个新的koules RPM，但您不知道它是做什么的，您可以键入如下命令： 


　　 rpm -qip koules-1.2-2.i386.rpm 


　　 ●现在您想了解koules的 RPM包在系统里安装了哪些文件，您可以键入： 


　　 rpm -qlp koules-1.2-2.i386.rpm，输出结果为： 
　　 /usr/man/man6/koules.6 
　　 /usr/lib/games/kouleslib/start.raw 
　　 /usr/lib/games/kouleslib/end.raw 
　　 /usr/lib/games/kouleslib/destroy2.raw 
　　 /usr/lib/games/kouleslib/destroy1.raw 
　　 /usr/lib/games/kouleslib/creator2.raw 
　　 /usr/lib/games/kouleslib/creator1.raw 
　　 /usr/lib/games/kouleslib/colize.raw 
　　 /usr/lib/games/kouleslib 
　　 /usr/games/koules 


　　 以上只是几个常见例子。随着您进一步的使用RPM，您会发现它的各种功能选项组合可以实现更为强大的RPM包管理功能。 
空穴来风 发表于 01:37 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 06, 2005
配置squid加速Apache Web服务器
一 安装与配置

首先你得有squid代理服务器.不过在这里只讲述如何配置squid的配置文件，使其支持httpd加速器工作方式。编辑“squid.conf”文件（vi /etc/squid/squid.conf），增加下面内容：

http_port 80
visible_hostname hostname
cache_mgr mgr_email

acl all src 0.0.0.0/0.0.0.0
http_access allow all

########## Accelator control ############
httpd_accel_host virtual
httpd_accel_port 8088
httpd_accel_with_proxy on
httpd_accel_uses_host_header    on
cache_dir ufs /tmp 256 16 256 

http_port 参数指定Squid监听浏览器客户请求的端口号，这里当然是80了 

cache_dir参数设定使用的存储系统的类型。一般情况下都类型应该是ufs，目录应该是“/tmp”，在该目录下使用的缓冲值为256MB，允许在“/tmp”下创建的第一级子目录数为16，每个第一级子目录下可以创建的第二级子目录数量为256
选项“httpd_accel_host”和“httpd_accel_port”定义了真正的Web服务器的主机名和端口号。在这里的配置中，真正的HTTP服务器运行在virtual主机上，运行端口为8088。

ok，squid设置完毕。

接着设置apache，很简单，只要把你的httpd监听端口设置成8088就成，然后重启你的apache。

接着重启你的squid服务，现在你访问你的web网站，已经是用了squid的http加速工作模式，你可以通过看squid的log日记看到他的运行情况。

更详细的squid设置,参照
缓存代理服务器Squid 
http://pangty.ta139.com/MyLinux/squid.htm
利用squid实现反向代理（同时具备内网代理） 
http://www.cnfug.org/journal/archives/000079.html
传统代理,透明代理,plug-gw,Apache反向代理,IP伪装,端口转发[Jephe Wu] 
http://www.linuxforum.net/docnew/showthreaded.php?Cat=&Board=server&Number=169&page=4&view=collapsed&sb=5&o=all&fpart=
基于反向代理的Web缓存加速—可缓存的CMS系统设计 
http://www.chedong.com/tech/cache.html
基于反向代理的Web缓存加速 
http://www.uplinux.com/www/sys/02/89.shtml
为 LAMP 加速 
http://blog.supercn.net/archives/2005/02/08/204/
高效配置Linux代理服务器――Squid
http://www.sowarm.com/newyk/1164.htm

二 使用中的问题以及解决

1.Running out of filedescriptors

    在使用的时候会出现错误

WARNING! Your cache is running out of filedescriptors
    在google后发现这个是因为linux对每个程序进行了filedescriptors限制的缘故.

文件描述符是一个简单的整数，用以标明每一个被进程所打开的文件和socket。第一个打开的文件是0，第二个是1，依此类推。Unix 操作系统通常给每个进程能打开的文件数量强加一个限制。更甚的是，unix 通常有一个系统级的限制。

因为squid 的工作方式，文件描述符的限制可能会极大的影响性能。当squid 用完所有的文件描述符后，它不能接收用户新的连接。也就是说，用完文件描述符导致拒绝服务。直到一部分当前请求完成，相应的文件和socket 被关闭，squid 不能接收新请求。当squid发现文件描述符短缺时，它会发布警告。

在运行./configure 之前，检查你的系统的文件描述符限制是否合适，能给你避免一些麻烦。大多数情况下，1024 个文件描述符足够了。非常忙的cache可能需要4096或更多。在配置文件描述符限制时，我推荐设置系统级限制的数量为每个进程限制的2 倍。
    在Linux下可以运行下面命令来查看进程的filedescriptors限制.

# ulimit -n
1024
    可以通过下面的命令进行修改.从而解决出现的错误!

# ulimit -HSn 65536
# ulimit -n
65536
2.日志中一些错误信息分析(不是很重要的提示)

> 2005/10/25 14:30:17| storeDirClean: WARNING: Creating 
> /cache0/00/FD 

Seems your cache directory is only partially created, or that you deleted the 
cache while Squid was running.. 


> 2005/10/25 15:26:15| storeLateRelease: released 0 
> objects 
> 2005/10/25 15:26:52| Preparing for shutdown after 0 
> requests 

Looks like a normal restart. 


> 2005/11/05 21:18:58| assertion failed: 
> store_client.c:213: "sc->cmp_offset == copy_offset" 

Internal error. For some unknown reason the store client is out of synch with 
itself. 

更详细的问题解决,参考:
SQUID Frequently Asked Questions: Troubleshooting
http://www.unix.org.ua/squid/FAQ-10.html

 




空穴来风 发表于 03:37 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
Linux Time zone 的调整
对Linux的Time Zone以前都没有一个很好的认识.为了调整服务器的时间.看了一下相关的资料.

1.Linux下的时间区域好像存在误区. 
从worldtimezone.com上得知，一个时区缩写，的确是有多种含义的，CST可代表：

Central Standard Time (USA) Heure Normale du Centre (french)  UTC-06
Central Standard Time (Australia)  UTC+0930
China Time  UTC+08
Cuba Summer Time UTC-04 
因此，通过时区缩写设置时间，是不科学的。很容易导致zope等程序出现问题。
那么使用绝对时区，应该更加安全了。中国是东8区：+0800，那是否应该把时区设置为GMT+8呢？
答案居然是否！应该设置为GMT-8，这是非常奇怪的，相信是很多linux用户容易犯的错误。可以使用下面的命令测试：

# date +%z%Z
+0800GMT-8


这原来是posix规范的一个bug，而且没有人愿意去调整了。
Debian下使用dpkg-reconfigure timezoneconf时，不要使用etc中的GMT时区。那些时区是老的、过时的、很奇怪的东东，还是应该使用三个英文字母的缩写。但既然CST这么 不确定，就不能用。幸好有一个HKT，是表示香港的时间，也是东8区，这个没有错。托香港的福，就用这个好了。

2.Linux时间命令参考

Linux时间命令参考：

date -s "2004-08-16 GMT8"
date -s 8:46


3.手动修改Linux的Time Zone

手动调整Timezone,你需要修改/etc/sysconfig/clock文件,并且创建一个/etc/localtime到指定Timezone的软链接.下面将介绍如何手动设置Time Zone到"America/Denver":

1. 在/usr/share/zoneinfo 目录下选择相应的Time Zone. Time zone 相对于这个目录. 在这里我们选择 "America/Denver"

2. 编辑文件/etc/sysconfig/clock text  :

ZONE="America/Denver"
UTC=true
ARC=false
Of course, this assumes that your hardware clock is running UTC time...

3. 删除下面的文件: /etc/localtime

4. 创建一个软连接/etc/localtime. 链接到/usr/share/zoneinfo/目录下的Time Zone的一个文件.下面是3,4两步的示范:

# cd /etc
# ls -al localtime
lrwxrwxrwx 1 root root 39 Mar 28 07:00 localtime -> /usr/share/zoneinfo/America/Los_Angeles

# rm /etc/localtime

# ln -s /usr/share/zoneinfo/America/Denver /etc/localtime
# ls -al localtime
lrwxrwxrwx 1 root root 34 Mar 28 08:59 localtime -> /usr/share/zoneinfo/America/Denver

# date
Fri Mar 28 09:00:04 MST 2003





 


--------------------------------------------------------------------------------

 

Time, Date, and Time Zones for Red Hat Linux
A Practical Guide
http://www.vanemery.com/Linux/RH-Linux-Time.html

zope的时间bug
http://blog.czug.org/panjunyong/zope-datetime-bug

Linux上让人迷惑的时间设置
http://blog.czug.org/panjunyong/linux-date-cmd/



 

空穴来风 发表于 10:31 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 05, 2005
为 LAMP 加速
本技巧不仅仅可以为 PHP 提供加速的技巧，对于 Perl 和 Python 也有同样的效果。 

为了得到完整的调试结果，建议你采用 ApacheBench 或者 httperf之类的软件。如果你对非 LAMP 架构的服务器测试有兴趣的话，建议你采用微软的免费软件： Web Application Stress Tool（需要 NT 或者 2000）。 

检测 Apache ，采用 top d 1 显示所有进程的 CPU 和内存情况。另外，还采用 apachectl status 命令。 

1、升级硬件的一般规则：对于 PHP 脚本而言，主要的瓶颈是 CPU ，对于静态页面而言，瓶颈是内存和网络。一台 400 Mhz 的普通奔腾机器所下载的静态页面就能让 T3 专线（45Mbps）饱和。 

2、Apache 处理 PHP 脚本的速度要比静态页面慢 2-10 倍，因此尽量采用多的静态页面，少的脚本。 

3、PHP 脚本如果不做缓冲，每次调用都需要编译，因此，安装一个 PHP 缓冲产品能提升 25-100% 的性能。 

4、把基于文件的会话切换到基于共享内存的会话。编译 PHP 时采用 –with-mm 选项，在 php.ini 中设置 set session.save_handler=mm 。这个简单的修改能让会话管理时间缩短一半。 

5、另外一项缓冲技术是把不常修改的 PHP 页面采用 HTML 缓冲输出，这些缓冲工具可以参考这里。 

6、如果你采用了 Linux 系统，建议升级内核到 2.4，因为静态页面由内核服务。 

7、采用最新版本的 Apache ，并把 PHP 编译其中，或者采用 DSO 模式，不要采用 CGI 方式。 

8、采用输出缓冲（请参考ob_start），如果你的代码有很多的 print 和 echo 语句，能提速 5-15% 。 

9、不要在 Web 服务器上运行 X-Windows ，关掉没有必要运行的进程。 

10、如果能够用文本就不要用图像，尽量减小图片的尺寸。 

11、分散负载，把数据库服务器放到另外的机器上去。采用另外低端的机器服务图片和 HTML 页面，如果所有的静态页面在另外一台服务器上处理，可以设置 httpd.conf 中的 KeepAlives 为 off ，来减少断开连接的时间。 

12、采用 hdparm 来优化磁盘，一般能提升 IDE 磁盘读写性能 200%，但是对 SCSI 硬盘也有效果。 

13、修改 httpd.conf ： 
# 关闭 DNS lookups，PHP 脚本只拿 IP 地址
HostnameLookups off 

# 关闭 htaccess 检测
<Directory /> 
AllowOverride none 
</Directory> 

打开 FollowSymLinks ，关闭 SymLinksIfOwnerMatch 以防 lstat() 系统调用：
Options FollowSymLinks 
#Options SymLinksIfOwnerMatch
下面还有很多关于 httpd.conf 参数的调整。 

14、Kurt 简洁而完整的 Apache Tuning Tips。 

15、如果喜欢从修改 Apache 源码入手，可以安装 lingerd。在页面产生和发送后，每个 Apache 进程都会浪费一段时光在客户连接上，Lingerd 能接管这项工作，让 Apache 迅速服务下一个客户请求。 

16、如果网络拥挤，CPU 资源不够用，采用 PHP 的 HTML 压缩功能：
output_handler = ob_gzhandler
PHP 4.0.4 的用户请不要使用，因为存在内存泄漏问题。 

17、修改 httpd.conf 中的 SendBufferSize 为你最大的页面文件的大小。加大内核的 TCP/IP 写缓冲大小。 

18、另外一篇文章：Tuning Apache Web Servers for Speed，一篇 97 年的很古老的文章。 

19、采用数据库的持久连接时，不要把 MaxRequestsPerChild 设置得太大。 

20、Caching Tutorial for Web Authors and Webmasters 教你怎样实现浏览器缓冲。 

21、如果你足够勇敢的话，还可以采用 Silicon Graphics 的 Accelerated Apache 补丁。这个工程能使 Apache 1.3 快 10 倍，使 Apache 2.0 快 4 倍。 

22、来自Professional Apache的技巧。 

23、官方的Performance Tuning 文档，很好的资料，但是十分繁琐。 

24、编译 PHP 时，建议采用如下的参数：
–enable-inline-optimization –disable-debug 

25、优化 Linux ，more Linux 以及Solaris。 

26、以上所有的方法都是针对单机而言的，如果你觉得系统还是不够快，可以采用集群，负载均衡，缓冲技术。采用 Squid 作为缓冲，配置 Squid 的方法。 

空穴来风 发表于 03:55 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
25.root密码丢失解决
GRUB:在引导装载程序菜单上，键入 [e] 来进入编辑模式。
你会面对一个引导项目列表。查找其中类似以下输出 的句行：
kernel /vmlinuz-2.4.18-0.4 ro root=/dev/hda2
按箭头键直到这一行被突出显示，然后按 [e]。
你现在可在文本结尾处空一格再添加 single 来告诉 GRUB 引导单用户 Linux 模式。按 [Enter] 键来使编辑结果生效。
你会被带会编辑模式屏幕，从这里，按 [b]， GRUB 就会引导单用户 Linux 模式。 结束载入后，你会面对一个与以下相似的 shell 提示：
sh-2.05#
现在，你便可以改变根命令，键入：
bash# passwd root
你会被要求重新键入口令来校验。结束后， 口令就会被改变，你便可以在提示下键入 reboot 来重新引导；然后，象平常一样登录为根用户。
LILO:当系统启动到出现LILO引导画面时，对于图形引导方式按TAB键进入文本方式，然后在LILO处
输入linux single回车即可进入免密码的控制台，进入以后使用passwd命令修改root的密码
即可。
无软盘安装RedHat、SUSE、Mandrake


关机
init 0
poweroff
shutdown -h now


修改网络配置
會用 vi 或其它文字編輯器嗎？ 
若然，請改： 
/etc/sysconfig/network-scripts/ifcfg-eth0 
/etc/sysconfig/network 
/etc/resolv.conf 
/etc/hosts

 

利用光盘镜像
mount -o loop *.iso /mnt/cdrom
制作光盘镜像
dd if=/dev/cdrom of=*.iso


0001 
修改主机名 
vi /etc/sysconfig/network，修改HOSTNAME一行为HOSTNAME=主机名，重启后也能生效 

0002 
Ret Hat Linux启动到文字界面(不启动xwindow) 
将/etc/inittab中 id:5:initdefault: 一行中的5改为3 

0003 
redhat的自动问题 
在www.redhat.com/corp/support/errata/找到补丁，6.1以后的版本带有一个工 
具up2date，它能够测定哪些rpm包需要升级，然后自动从redhat的站点下载并完成安装。 

0004 
windows下看linux分区的软件 
Paragon.Ext2FS.Anywhere.2.5.rar和explore2fs-1.00-pre4.zip 

0005 
mount用法 
fat32的分区 mount -o codepage=936,iocharset=cp936 /dev/hda7 /mnt/cdrom 
iso文件 mount -o loop /abc.iso /mnt/cdrom 
软盘 mount /dev/fd0 /mnt/floppy 
USB闪存 mount /dev/sda1 /mnt/cdrom 
所有/etc/fstab内容 mount -a 

可以指定文件格式"-t 格式", 格式可以为vfat, ext2, ext3等. 

0006 
在vmware的LINUX中使用本地硬盘的FAT分区 
将本地的FAT分区共享，然后在VMWARE中使用SMBFS挂上。可以将如下的行放到/etc/fstab中： 
//win_ip/D$ /mnt/d smbfs defaults,auto,username=win_name,password=win_pass,codepage=936,iocharest=gb2312 0 0 
其中win_ip是你的windows的IP地址； 
D$是你的windows里面共享的D盘的共享名； 
/mnt/d是要将该分区mount到linux的目录； 
win_name和win_pass是你的WINDOWS里面可以读取该分区的用户，比如你的管理员名和密码。 
如果你运行了/etc/rc.d/init.d/netfs，那么在启动的时候就会自动挂载这个分区。 

0007.a 
删除名为-a的文件 
rm ./-a 
rm -- -a 告诉rm这是最后一个选项，参见getopt 
ls -i 列出inum，然后用find . -inum inum_of_thisfile -exec rm '{}' \; 

0007.b 
删除名为\a的文件 
rm \\a 

0007.c 
删除名字带的/和‘\0'文件 
这些字符是正常文件系统所不允许的字符，但可能在文件名中产生，如unix下的NFS文件系统在Mac系统上使用 
1.解决的方法，把NFS文件系统在挂到不过滤'/'字符的系统下删除含特殊文件名的文件。 
2.也可，将错误文件名的目录其它文件移走，ls -id 显示含该文件目录的inum，umount 文件系统， 
clri清除该目录的inum，fsck，mount，check your lost+found，rename the file in it. 
最好是通过WINDOWS FTP过去就可以删除任何文件名的文件了! 

0007.d 
删除名字带不可见字符的文件 
列出文件名并转储到文件：ls -l >aaa 
然后编辑文件的内容加入rm命令使其内容成为删除上述文件的格式： 
vi aaa 
[rm -r ******* 
] 
把文件加上执行权限 chmod +x aaa 
执行 $aaa 

0007.e 
删除文件大小为零的文件 
rm -i `find ./ -size 0` 
find ./ -size 0 -exec rm {} \; 
find ./ -size |xargs rm -f &非常有效 
for file in * #自己定义需要删除的文件类型 
do 
if [ ! -s ${file} ] 
then 
rm ${file} 
echo "rm $file Success!" 
fi 
done 

0008 
redhat设置滚轮鼠标 
进入X后，选择鼠标的配置，选择wheel mouse(ps/2)就可以了 

0009 
加装xwindow 
用linux光盘启动，选择升级，然后单独选择包，安装即可 

0010 
删除linux分区 
做一张partition magic的启动软盘,启动后删除. 或者用win2000的启动光盘启动,然后删除. 

0011 
新编译生成的gcc ，使用的标准连接库都在/usr/local/lib 下了，但使用的缺省的连接路径是 /usr/lib 怎样添加？（除了在每次编译时 增加 -L /usr/local/lib 以外)(sakulagi) 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib 
写到~/.bash_profile里面。 

0012 
不编译内核，mount ntfs分区 
原装rh8，未升级或编译内核 
1. 上google.com搜索并下载 kernel-ntfs-2.4.18-14.i686.rpm 
2. rpm -ivh kernel-ntfs-2.4.18-14.i686.rpm 
3. mkdir /mnt/c 
4. mount -t ntfs /dev/hda1 /mnt/c 

0013 
redhat 8.0中用xmms听mp3 
下载www.gurulabs.com/files/xmms-mp3-1.2.7-13.p.i386.rpm 
rpm -Uvh xmms-mp3-1.2.7-13.p.i386.rpm 

0014 
找回忘记了的root口令（lilo/grub） 
三种办法： 
1.在系统进入单用户状态，直接用passwd root去更改 
2.用安装光盘引导系统，进行linux rescue状态，将原来/分区挂接上来,作法如下： 
cd /mnt 
mkdir hd 
mount -t auto /dev/hdaX(原来/分区所在的分区号） hd 
cd hd 
chroot ./ 
passwd root 
这样可以搞定 
3.将本机的硬盘拿下来，挂到其他的linux系统上，采用的办法与第二种相同 
rh8中 
一. lilo 
1. 在出现 lilo: 提示时键入 linux single 
画面显示 lilo: linux single 
2. 回车可直接进入linux命令行 
3. #vi /etc/shadow 
将第一行，即以root开头的一行中root:后和下一个:前的内容删除， 
第一行将类似于 
root::...... 
保存 
4. #reboot重启，root密码为空 
二. grub 
1. 在出现grub画面时，用上下键选中你平时启动linux的那一项(别选dos哟)，然后按e键 
2. 再次用上下键选中你平时启动linux的那一项(类似于kernel /boot/vmlinuz-2.4.18-14 ro root=LABEL=/)，然后按e键 
3. 修改你现在见到的命令行，加入single，结果如下： 
kernel /boot/vmlinuz-2.4.18-14 single ro root=LABEL=/ 
4. 回车返回，然后按b键启动，即可直接进入linux命令行 
5. #vi /etc/shadow 
将第一行，即以root开头的一行中root:后和下一个:前的内容删除， 
第一行将类似于 
root::...... 
保存 
6. #reboot重启，root密码为空 

0015 
使ctrl + alt + del失效 
vi /etc/inittab 
将ca::ctrlaltdel:/sbin/shutdown -t3 -r now这行注释掉，就可以了 

0016 
gcc abc.c得到的a.out不能运行 
./a.out 

0017 
文件在哪个rpm中(无双) 
上www.rpmfind.net上搜，或者rpm -qf 文件名得到 

0018 
把man或info的信息存为文本文件 
以 tcsh 为例： 
man tcsh | col -b > tcsh.txt 
info tcsh -o tcsh.txt -s 

0019 
利用现存两个文件，生成一个新的文件 
1. 取出两个文件的并集(重复的行只保留一份) 
2. 取出两个文件的交集(只留下同时存在于两个文件中的文件) 
3. 删除交集，留下其他的行 
1. cat file1 file2 | sort | uniq 
2. cat file1 file2 | sort | uniq -d 
3. cat file1 file2 | sort | uniq -u 

0020 
设置com1口，让超级终端通过com1口进行登录 
确认有/sbin/agetty，编辑/etc/inittab，添加 
7:2345:respawn:/sbin/agetty /dev/ttyS0 9600 
9600bps是因为联路由器缺省一般都是这种速率，也可以设成 
19200、38400、57600、115200 
修改/etc/securetty，添加一行：ttyS0，确保root用户能登录 
重启机器，就可以拔掉鼠标键盘显示器（启动时最好还是要看看输出信息）了 

0021 
删除目录下所有文件包括子目录 
rm -rf 目录名 

0022 
查看系统信息 
cat /proc/cpuinfo - CPU (i.e. vendor, Mhz, flags like mmx) 
cat /proc/interrupts - 中断 
cat /proc/ioports - 设备IO端口 
cat /proc/meminfo - 内存信息(i.e. mem used, free, swap size) 
cat /proc/partitions - 所有设备的所有分区 
cat /proc/pci - PCI设备的信息 
cat /proc/swaps - 所有Swap分区的信息 
cat /proc/version - Linux的版本号 相当于 uname -r 

0023 
去掉多余的回车符 
sed 's/^M//' test.sh > back.sh， 注意^M是敲ctrl_v ctrl-m得到的 
或者 dos2unix filename 

0024 
切换X桌面(lnx3000) 
switchdesk KDE或者switchdesk GNOME 

0025 
通用的声卡驱动程序(lnx3000) 
OSS www.opensound.com/ ALSA www.alsa-project.org/ 

0026 
改变redhat的系统语言/字符集(beming) 
修改 /etc/sysconfig/i18n 文件，如 
LAGN="en_US"，xwindow会显示英文界面， 
LAGN="zh_CN.GB18030"，xwindow会显示中文界面。 

0027 
把屏幕设置为90列 
stty cols 90 

0028 
使用md5sum文件 
md5sum isofile > hashfile, 将 md5sum 档案与 hashfile 档案内容比对, 验证杂凑值 
是否一致 md5sum –c hashfile 

0029 
一次解压多个zip文件 
unzip "*"，注意引号不能少 

0030 
看pdf文件 
使用xpdf或者安装acrobat reader for linux 

0031 
查找权限位为S的文件 
find . -type f \( -perm -04000 -o -perm -02000 \) -exec ls -lg {} \; 

0032 
装中文输入法 
以redhat8为例,xwindow及其终端下的不用说了吧,缺省就安装了,用ctrl-space呼出。 
现在讨论纯console,请下载zhcon.gnuchina.org/download/src/zhcon-0.2.1.tar.gz, 
放在任一目录中,tar xvfz zhcon-0.2.1.tar.gz, cd zhcon-0.2.1, ./configure, 
make, make install。安装结束，要想使用，请运行zhcon，想退出，运行exit。 

0033 
把弹出的光盘收回来(beike) 
#eject －t 

0034 
cd光盘做成iso文件(弱智) 
cp /dev/cdrom xxxx.iso 

0035 
快速观看开机的硬件检测(弱智) 
dmesg | more 

0036 
查看硬盘的使用情况 
df -k 以K为单位显示 
df -h 以人性化单位显示，可以是b,k,m,g,t.. 

0037 
查看目录的大小 
du -sh dirname 
-s 仅显示总计 
-h 以K、M、G为单位，提高信息的可读性。KB、MB、GB是以1024为换算单 位， -H以1000为换算单位。 


----------------------------网络相关篇-------------------------- 
0001 
让apache的默认字符集变为中文 
找到 AddDefaultCharset ISO8859-1 一行，改为AddDefaultCharset GB2312 

0002 
永久更改ip 
ifconfig eth0 新ip 
然后编辑/etc/sysconfig/network-scripts/ifcfg-eth0，修改ip 

0003 
从Linux上远程显示Windows桌面(lnx3000) 
安装rdesktop包 

0004 
手动添加默认网关 
以root用户，执行: route add default gw 网关的IP 
想更改网关 
1 vi /etc/sysconfig/network-scripts/ifcfg-eth0 
更改GATEWAY 
2 /etc/init.d/network restart 

0005 
redhat 8.0上msn和qq 
下载Gaim 0.58版： 
www.linuxsir.org/gaim/gaim-0.58-2.i386.rpm 
下载QQ插件 for gcc2.9版： 
www.linuxsir.org/gaim/libqq-0.0.3-ft-0.58-gcc296.so.gz 
将下载的文件放入/temp目录，然后将系统中已有的Gaim删除，即在终端仿真器中键入命令：rpm -e gaim。 
开始安装 
打开终端仿真器，继续执行下列命令安装Gaim 0.58版，即： 
cd /temp　　　　　　　　　（进入temp目录） 
rpm -ivh gaim-0.58-2.i386.rpm　（安装软件） 
当安装成功后，你就可以在GNOME或KDE桌面建立Gaim图标了。 
继续安装QQ插件，即键入命令： 
gunzip libqq-0.0.3-ft-0.58-gcc296.so.gz (解压缩文件） 
cp libqq-0.0.3-ft-0.58-gcc296.so /usr/lib/gaim　（复制插件到gaim库目录中） 
软件设置 
首次启动Gaim 0.85版时，会出现的登录界面。先选择“插件”，在插件对话框中点击“加载”，分别将 
libmsn.so和libqq-0.0.3-ft-0.58-gcc296.so文件装入，确认后关闭。然后再选择“所有帐号”，在 
出现的帐号编辑器中继续点击“增加”，当出现的修改帐号页面时，我们就可以输入自己的QQ或MSN号 
了，登录名填写QQ号码或MSN邮箱，密码填写对应的QQ或MSN密码，Alias填写自己的昵称，协议选择 
相应的QQ或MSN，其他的设置按默认的即可。当全部设置完成后就可以登录使用了。 

0006 
查出22端口现在运行什么程序 
lsof -i :22 

0007 
查看本机的IP，gateway, dns 
IP： 
以root用户登录，执行ifconfig。其中eth0是第一块网卡，lo是默认的设备 
Gateway: 
以root用户登录，执行netstat -rn，以0.0.0.0开头的一行的Gateway即为默认网关 
也可以查看/etc/sysconfig/network文件，里面有指定的地址！ 
DNS： 
more /etc/reslov.conf，内容指定如下： 
nameserver 202.96.69.38 
nameserver 202.96.64.38 

0008 
RH8.0命令行下轻松改变ping 的TTL值(cgweb) 
#sysctl -w net.ipv4.ip_default_ttl=N 
(N=0~255),若N>255,则ttl=0 

0009 
RH8.0命令行下轻松改变系统配置默认值(houaq) 
编辑/etc/sysctl.conf, 例如，将 
net.ipv4.ip_forward = 0 
变为 
net.ipv4.ip_forward = 1 
重启后生效，用sysctl -a查看可知 

0010 
mount局域网上其他windows机器共享出的目录 
mount -t smbfs -o username=guest,password=guest //machine/path /mnt/cdrom 

0011 
允许｜禁止root通过SSH登陆(Fun-FreeBSD) 
修改sshd_config:PermitRootLogin no|yes 

0012 
让root直接telnet登陆 
编辑/etc/pam.d/login，去掉 
auth required /lib/security/pam_securetty.so 这句话 

0013 
在linux接adsl设备 
需要一个运转正常的Linux + 至少一块网卡 + 宽带设备已经申请完毕，同时已经开通 
前市场上大概有几种ADSL设备，他们工作的方式有一些细微的差别。 
就是通过虚拟拨号来完成上网的这一过程，也就是利用pppoe设备来进行虚拟拨号的 
叫作全向猫，就是一种加电后自动的进行拨号的工作，然后留给我们的接口是RJ45, 
大连地区一般留给我们的网关都是10.0.0.2,这种设备最容易对付，最后是直接分配 
给用户一个固定的IP，相对大家来说也比较容易对付 
1.第一种需要进行拨号： 
这几种设备都是通过eth接口与计算机进行通讯的，所以先将硬件设备的连接作好，尤 
其是宽带猫的，一定要确认无误（否则一会儿要不去可不算我的事情） 
然后启动系统，确认系统上是否安装rp-pppoe这个软件（通过rpm -qa|grep pppoe来查 
找），如没有安装的用户，在光盘里或是到网上去down一个来，安装上后，以root用户 
执行adsl-setup，这样就进入了adsl的资料的设定状态，要求输入申请宽带的用户名以 
及其他一些信息，确认没有问题，接受直至最后（里面都是E文，但是一看即能懂，比 
较简单，有关一个防火墙的设置，我一般都不用，选0，大家可以具体考虑）。 
配置完成后，以root用户执行adsl-start，这样将进行adsl的拨号工作，正常就会一下 
上线，如有什么具体问题，去看一下日志（/var/log/messages）里面告诉你什么了。 
停掉adsl，执行adsl-stop就可以了（很简单的） 
2.另外两种比较容易对付： 
全向猫：只要将你的网卡的IP设置成一个10网段的IP，然后网关指到全向猫的IP 
上（10.0.0.2),基本上不有太大的问题 
　固定IP：就像配置本地儿的网卡一样，将IP，网关，DNS都按申请来的填写上就可以搞定了 

0014 
让linux自动同步时间(shunz) 
vi /etc/crontab 
加上一句： 
00 0 1 * * root rdate -s time.nist.gov 
=空穴来风=返回首页 

January 16, 2006
系统平均负载(Load average)解释
在Linux系统中，uptime、w、top等命令都会有系统平均负载load average的输出，那么什么是系统平均负载呢？
系统平均负载被定义为在特定时间间隔内运行队列中的平均进程树。如果一个进程满足以下条件则其就会位于运行队列中：
- 它没有在等待I/O操作的结果
- 它没有主动进入等待状态(也就是没有调用'wait')
- 没有被停止(例如：等待终止)

例如：
[root@www2 init.d]# uptime
7:51pm up 2 days, 5:43, 2 users, load average: 8.13, 5.90, 4.94
命令输出的最后内容表示在过去的1、5、15分钟内运行队列中的平均进程数量。
一般来说只要每个CPU的当前活动进程数不大于3那么系统的性能就是良好的，如果每个CPU的任务数大于5，那么就表示这台机器的性能有严重问题。对于上面的例子来说，假设系统有两个CPU，那么其每个CPU的当前任务数为：8.13/2=4.065。这表示该系统的性能是可以接受的。 

空穴来风 发表于 10:45 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

November 02, 2005
以 iptables 架設 SME 防火牆
由於 Internet 的普及和連接的成本下降， 很多企業都已經把辦公室網絡接上 Internet 去了。 而當各企業正享受著 Internet 所帶來的商機和方便的同時， 亦為企業本身帶來各種的危機。 從一些貪玩小孩的入侵， 到大規模的網蟲 (NetWorm) 爆發。 企業的系統無時無刻面對著各種挑戰。 一但系統被入侵， 所損失的往往多於能從 Internet 中所得到的。 所以我們必需要有一個防禦的機制來保護企業內的資料和財產， 免受外來的種種攻擊。 而當中最為普及的技術便是『防火牆』(Firewall)。  

什麼是防火牆 
『防火牆』只是一個統稱， 或者可以說是一個概念。 其實， 任何一種能成功防止外來入侵的網絡裝置或軟件， 都可以稱為『防火牆』。 

從網絡保安而言， 防火牆通常會用作內部網絡對外連接的唯一通道。 如此一來， 防火牆便成為了一個網絡關卡， 所有進出內部網絡的交通都必先經過防火牆的檢查和過濾， 防止入侵者接近內部的資源。 

而防火牆是根據網絡管理員預先定下的規則 (Rules) 來過濾網絡交通。 而這些規則便是整個防火牆的靈魂、內部網絡的守衛。 在制定這些規則時， 大都是圍繞著以下幾個範籌而定：  

誰〔不〕能進出網絡 
什麼〔不〕可以進出網絡 
資料〔不〕可以傳到那裡去 
用什麼方法才〔不〕可進出網絡   
防火牆的種類  
現時所流行的防火牆大致可分為以下兩類：  

1 封包過濾 (Packet Filters)  
封包過濾是透過檢測網絡封包的標頭 (Header) 資料是否符合管理員所定下的規則， 而決定是否讓其通過。 這些標頭資料包括了: 

來源/目的地的位址 (Address) 
來源/目的地的通訊埠 (Port) 
通訊協定 (Protocol)  
使用封包過濾的好處是其系統和應用程式中立性 (Operating Sytem & Application-neutral)， 對於在內部網絡的客端程式不須作任可更改便可提供保謢。 而本文將會介紹的 防火牆亦是封包過濾式的。  

2 應用層閘道 (Application Gateway)  
應用層閘道式的防火牆， 主要是在客端和伺服器之間加上『代理伺服器』(Proxy Server) 而達成。 如此一來， 網絡間的連線得變成兩個部驟： 首先是客端和代理伺服器連線， 然後經過過濾後才由代理伺服器和真實的伺服器連線。 

但是使用應用層閘道式的防火牆， 往往須要更改客端程式的設定來佩合。 這對於一般的用家 (End-user) 來說， 並不如封包過濾般方便。 

Linux 與 封包過濾  
Linux 核心自版本 1.1 開始已提供了封包過濾的功能。 到了現時的 2.4 版本內建的 Netfilter 模組， 功能更臻完善。 這個模組利用了一致被資訊保安界好評的 『狀態性』(Stateful) 機制， 記下各網絡連線的狀態並檢查往後的封包是否屬於同一連線。 狀態性機制能使防火牆能過濾一些以往不能偵測的連線狀態， 加強了內部網絡安全。  

iptables  
Netfilter 是在 Linux 核心 (Kernel) 的模組， 我們不能和它直接溝通。 它只會依著管理員定下的規則， 對封包進行檢測。 至於把怎樣才能把規則告知 Netfilter， 就得靠一個名為 iptables 的用戶端的程式。 

要把 iptables 運用得當， 就先要理解 Netfilter 處理封包的機制。 

之前提及過防火牆是透過一系列的規則而建成， 而每個規則都包含了一個對封包的描述 (Match) 和 一個處置動作 (Target)。 每當封包符合規則中的描述時， 核心便會對封包進行相應的處置動作。 而在 Netfilter 的角度中， 這些規則是記錄在不同的鏈 (Chain) 中， 而鏈又會被歸納到不同的規則表 (Table) 中。 

封包會根據它在核心中不同的層次和狀態， 被送到一個或多個規則表和鏈中， 並和當中的每個規則作對比並執行相應的動作。 iptables 的功用就是讓管理員管理各個規則表和鏈中的規則。 

 核心中的規則表 

在核心中有三個規則表:  

filter  
這個規則表是最常用的規則表， 也是 iptables 的預設的規則表。 所有對封包進行過濾的規則都是加進這個規則表的鏈中。 這個規則表中有三個預設的鏈， 分別是： INPUT (給目的地是本機的封包)， FORWORD (給途經本機的封包)， OUTPUT (給由本機所發出的封包)  

nat 
 這個規則表主要是給予系統 網路位址轉換 (Network Address Translation) 的功能。顧名思義， 網路位址轉換就是把封包標頭的位址和通訊埠的資料更改。 這個功能主要的用處是：  

Internet 連線分享。 即使只得一個可用的 Internet 位址， 也可把整個內部網絡的電腦接上 Internet。 
隱蔽內部網絡的存在。 縱然有足夠的 Internet 位址可用， 但基於保安的理由我們有時會不希望其他人知到企業內部網絡的存在。 運用網路位址轉換就可把所有內部網絡對外的通訊轉換成看似是同一位址所發出的封包一樣。 
服務轉向 (Forwording )。 當有伺服器置於防火牆後， 但又須要對外提供時， 便可以把目的地位址是防火牆的封包轉向到真實的伺服器。這個規則表中有三個預設的鏈， 分別是： PREROUTING (給所有進入本機而未經路由處理 (Routing Decision)的封包)， POSTROUTING (給所有經過路由處理而目的地不是本機的封包)， OUTPUT (給由本機所發出的封包)   
mangle  
這個規則表用來更改封包的一些屬性 (Properties)， 這個規則表中有四個預設的鏈， 分別是： PREROUTEING， INPUT， FORWARD ， OUTPUT 和 POSTROUTING。  

Iptables 的基本語法  
iptables -t Table -Operation Chain Match -j Target 

Table 是所用的是個規則表 
Chain 指明是用規則表中的哪一個鏈 
Operation 是對鏈中的規則所進行的動作， 例如：增加，移除，清空 等 
Match 是一個對封包的描述， 例如：來源地址及通訊埠 
Target 是處置動作， 例如：ACCEPT， DROP， LOG等 
 

常用的描述語法  
語法 用途 
-p [!] protocol 指定所針對的通訊協定， 例如：tcp， udp， icmp 
-s [!] address[/mask] 指定所針對的來源位址。 這可以是一個IP位址， 主機名稱， 或加上網絡遮罩以表示一群 IP 位址。 
-d [!] address[/mask] 指定所針對的目的地位址。 這可以是一個IP位址， 主機名稱， 或加上網絡遮罩以表示一群IP位址。 
-i [!] name 指定從那個網絡介面進入的封包。 例如：eth0， ppp0 
-o [!] name 指定從那個網絡介面送出的封包。 例如：eth0， ppp0 
--sport [!] port[:port] 指定來源通訊埠。 這可以指明是那一個或那一組埠 
--dport [!] port[:port] 指定目的地通訊埠。 這可以指明是那一個或那一組埠 
[!] --syn 只限 TCP 協定所用， 這指定封包須為 TCP 連線要求封包 


 防火牆架設範例 

有了基本的認識後， 我們便開始架設防火牆。 我們假設企業Ａ 有一個 Internet 連線和足夠的合法 Internet 位址給所有電腦使用。 而企業Ａ 只希望員工使用 WWW 和 FTP。 

我們可以跟著以下的步驟制作一個 Shell Script， 來架設防火牆。 

設定網絡參數和載入相關的核心模組

$INTERNAL_NET=X.X.X.X/24 # Local LAN Subnet
$INTERNAL_NIC=eth0 # Local LAN interface


$EXTERNAL_NET=Y.Y.Y.Y/8 # Internet Subnet
$EXTERNAL_NIC=eth1 # Internet interface


echo 1 > /proc/sys/net/ipv4/ip_forward


/sbin/modprobe ip_conntrack
/sbin/modprobe ip_conntrack_ftp
/sbin/modprobe ipt_state  

清除現有的規則  
-F 動作會清除所指定的鏈中的所有規則， 如果沒有指明鏈則規則表中所有的鏈都會被清空。 

/sbin/iptables -t filter -F
/sbin/iptables -t nat -F
/sbin/iptables -t mangle -F 

-X 動作會移除指定規則表中所有由用者增加的鏈

/sbin/iptables -t filter -X
/sbin/iptables -t nat -X
/sbin/iptables -t mangle -X  

設定預設政策  
-P 動作會設定所指定的鏈的預設政策。 當一個封包進入鏈後， 但沒有規則能符合這個封包的資料和狀態時， 核心會以鏈的預設政策去處理該個封包。 

每一個良好的防火牆的預設政策都應設為 DROP。 正所謂寧枉無縱， 預設拒絕所有封包， 然後才讓真正有用封包通過。 能使防火牆更為堅固。 

/sbin/iptables -t filter -P INPUT DROP
/sbin/iptables -t filter -P OUTPUT DROP
/sbin/iptables -t filter -P FORWARD DROP  

不回應 ICMP 封包  
如要查看一部主機是否在線， 最簡單的方法是使用 ping 指令。 如果不想被 ping， 可以設定 Netfilter 不回應 ICMP 封包 

/sbin/iptables -t filter -A INPUT -p icmp --icmp-type echo-requested -j DROP
/sbin/iptables -t filter -A OUTPUT -p icmp --icmp-type echo-reply -j DROP
/sbin/iptables -t filter -A FORWARD -p icmp --icmp-type echo-requested -j DROP
/sbin/iptables -t filter -A FORWARD -p icmp --icmp-type echo-reply -j DROP  

防止 IP Spoofing 
 IP Spoofing 是把外來的封包假裝成是內部網絡所發出的， 試途讓防火牆誤認而允許其進入內部網絡。 而要防止 IP Spoofing， 我們只須要過濾那些從 Internet 進入而聲稱來源地址是內部網絡的封包便可。 

/sbin/iptables -t filter -A INPUT -i $EXTERNAL_NIC -s $INTERNAL_NET -j DROP
/sbin/iptables -t filter -A FORWARD -i $EXTERNAL_NIC -s $INTERNAL_NET -j DROP  

防止網絡掃描  
網絡掃描是利用一些不正常而又合法的封包去檢測伺服器所提供的服務和取得一些系統資訊。 亦有入侵者用這些封包企途繞過防火牆去入侵內部網絡， 所以必需過濾。 

/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL ALL -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL ALL -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL NONE -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL NONE -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags ALL FIN,URG,PSH -j DROP
/sbin/iptables -t filter -A INPUT -p tcp --tcp-flags SYN,RST SYN,RST -j DROP
/sbin/iptables -t filter -A FORWARD -p tcp --tcp-flags SYN,RST SYN,RST -j DROP  

允許內部網絡使用者瀏覽 Internet 網頁  
要允許瀏覽 Internet 網頁， 我們須要允許封包從內部網絡傳送到 Web Server 去， 並同時要允許封包從 Web Server返回內部網絡。 

/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 80 -j ACCEPT
/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 443 -j ACCEPT 

要允許封包從 Web Server返回內部網絡， 有兩個方法設定。 其一是利用狀態性機制去自動判斷相關的封包： 

/sbin/iptables -t filter -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT 

其次是加上相應的規則： 

/sbin/iptables -t filter -A FORWARD -p tcp -d $INTERNAL_NET -s 0/0 --sport 80 ! --syn -j ACCEPT
/sbin/iptables -t filter -A FORWARD -p tcp -d $INTERNAL_NET -s 0/0 --sport 443 ! --syn -j ACCEPT 

利用狀態性機制去自動判斷的好處是， 只須設定一次就能和其他規則分享使用 (象以下的 DNS 和 FTP)， 能減少規則的數量，方便管理。  

允許內部網絡查詢 DNS  
DNS 是主機名稱和 IP 位址互換的服務， 如果過濾了 DNS 查詢， 用戶便不能用主機名稱 (如：http://www.linuxpilot.net ) 來瀏覽網頁， 而是要直接用 IP 位址 (如： http://203.194.196.187)。 

/sbin/iptables -t filter -A FORWARD -p udp -s $INTERNAL_NET -d 0/0 --dport 53 -j ACCEPT 

如果已有固定的 DNS 伺服器， 可以以下規則去限制只可以查詢指定的 DNS 伺服器： 

$DNSSRV=202.181.230.106 # IP Address of the DNS Server
/sbin/iptables -t filter -A FORWARD -p udp -s $INTERNAL_NET -d $DNSSRV --dport 53 -j ACCEPT  

允許內部網絡使用者使用 FTP  
大部份的 Internet 服務的設定基本上和之前的大同小異， 讀者可以嚐試自行設定。 但可惜的是 FTP 不只用一個通訊埠來進行資料傳送， 而是要用兩個。 更甚的是其中一個通訊埠是次次不同的， 根本不可能預先在防火牆中設定。 

有幸的是 Netfilter 所提供的狀態性機制能解決這個問題。 由於 FTP 的第二個通訊埠的連線， 是透過在埠21已建立的連線來建立， 所以可以利用狀態性機制去允許所有由已建立的連線所衍生出來的連線。 

/sbin/iptables -t filter -A FORWARD -p tcp -s $INTERNAL_NET -d 0/0 --dport 21 -j ACCEPT  

允許管理員以 SSH 連線到防火牆修改設定  
最後， 開設一個通道給管理員以 SSH 連線到防火牆修改設定。 不然的話， 每當有設定要修改時， 管理員便要親身登入防火牆修改了。 

/sbin/iptables -t filter -A INPUT -i $INTERNAL_NIC -s $INTERNAL_NET --dport 22 -j ACCEPT  

最後的步驟  
當設計好所有的規則和相應的 Script 後， 把所有的 Script 集合起來製成一個 Shell Script， 然後於 /etc/rc.d/rc.local 中加入執行該 Script 的命令。 這樣每次系統啟動時便會自動啟動防火牆。  

Internet 連線分享 
雖然以上的防火牆是基於有足夠的合法位址而設計， 但只須多加一規則便可以讓內部網絡以一個合法位址分享Internet 連線。 

如果獲得一個固定的合法位址， 可以用： 

$FIREWALL_IP=y.y.y.z # IP Address that can connect to Internet
/sbin/iptables -t nat -A POSTROUTING -o $EXTERNAL_NIC -s $INTERNAL_NET -j SNAT –to $FIREWALL_IP 

如果位址是動態分佩的話， 則用： 

/sbin/iptables -t nat -A POSTROUTING -o $EXTERNAL_NIC -s $INTERNAL_NET -j MASQUERADE 

其實以上兩個規則，都是叫核心把由內部網絡所發出的封包內的來源位址， 先轉成防火牆的合法位址再送出 Internet。 只不過用 MASQUERADE 方法時, 因為要顧及動態位址分佩， 所以會比 SNAT 多用一點 CPU 資源。  

總結 
Linux 加上 Netfilter 的強大功能， 給予中小企一個低成本的防火牆的解決方案。 以保障企業的資源。 以上的範例雖已包含了一般防火牆的功能， 但單靠 Netfilter 是未能杜絕所有的入侵 (例如： 電郵病毒)的。 所以系統管理員仍是要綜合各種網絡保安的工具一起， 發揮最大的效能。 

作者Isaac Chau 

原文在 LinuxPilot 第 15 期刊登
http://www.linuxhall.org/modules.php?name=News&file=article&sid=108


参考
iptables实战记录   [一个小公司针对不同局域网机器网络访问控制的例子]
http://blog.csdn.net/lidaibin/archive/2004/09/27/118111.aspx
Iptables 中文 man 文档
http://blog.chinaunix.net/article.php?articleId=11351&blogId=4005
Iptables 指南 1.1.19
http://misc.bbgo.cn/linux/iptables-tutorial-cn-1.1.19.html

空穴来风 发表于 01:47 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
怎样用ipchains构建防火墙
提示：防火墙是提供网络安全性的重要手段之一，RedHat6.1提供了用于实现过滤型防火墙的工具包——ipchains。实现防火墙的策略一般有两种：在第一种方式下，首先允许所有的包，然后在禁止有危险的包通过防火墙；第二种方式则相反，首先禁止所有的包，然后再根据所需要的服务允许特定的包通过防火墙。相比较而言，第二种方式更能保证网络的安全性。但对于第二种方式，要求使用者知道Server/Client交互的基本原理和特定服务所对应的具体端口。本文将从一个具体的实列出发，讨论怎样采用第二种方式构建企业的防火墙系统。

一、Server/Client的交互原理

首先让我们看一下服务器/客户机的交互原理。服务器提供某特定功能的服务总是由特定的后台程序提供的。在TCP/IP网络中，常常把这个特定的服务绑定到特定的TCP或UDP端口。之后，该后台程序就不断地监听（listen)该端口，一旦接收到符合条件的客户端请求，该服务进行TCP握手后就同客户端建立一个连接，响应客户请求。与此同时，再产生一个该绑定的拷贝，继续监听客户端的请求。

举一个具体的例子：假设网络中有一台服务器A（IP地址为a.b.c.1)提供WWW服务，另有客户机B(a.b.c.4)、C(a.b.c.7)。首先，服务器A运行提供WWW服务的后台程序（比如Apache）并且把该服务绑定到端口80，也就是说，在端口80进行监听。当B发起一个连接请求时,B将打开一个大于1024的连接端口(1024内为已定义端口）,假设为1037。A在接收到请求后，用80端口与B建立连接以响应B的请求，同时产生一个80端口绑定的拷贝，继续监听客户端的请求。假如A又接收到C的连接请求（设连接请求端口为1071），则A在与C建立连接的同时又产生一个80端口绑定的拷贝继续监听客端的请求。如下所示，每个连接都是唯一的。

服务器 客户端
连接1：a.b.c.1:80 <=> a.b.c.4:1037
连接2：a.b.c.1:80 <=> a.b.c.7:1071

二、服务端口
每一种特定的服务都有自己特定的端口，一般说来小于1024的端口多为保留端口，或者说是已定义端口，低端口分配给众所周知的服务（如WWW、FTP等等），从512到1024的端口通常保留给特殊的UNIXTCP/IP应用程序，具体情况请参考/etc/services文件或RFC1700。

三、网络环境
假设网络环境如下：某一单位，租用DDN专线上网，网络拓扑如下：

+--------------+
| 内部网段     | eth1+--------+eth0 DDN
| +------------|firewall|<===============>Internet
| 198.168.80.0 | +--------+
+--------------+
eth0: 198.199.37.254
eth1: 198.168.80.254

以上的IP地址都是Internet上真实的IP，故没有用到IP欺骗。并且，我们假设在内部网中存在以下服务器：
dns服务器：dns.yourdomain.com 由firewall兼任
www服务器：www.yourdomain.com 198.168.80.11
ftp服务器：ftp.yourdomain.com 198.168.80.12
bbs服务器：bbs.yourdomain.com 198.168.80.13
email服务器：mail.yourdomain.com 198.168.80.14
下面我们将用ipchains一步一步地来建立我们的包过滤防火墙。

四、实现步骤
说明：有关ipchains的详细命令用法，请参考有关HOWTO文档。在本例中，我们将在eth0和eth1的input chain设置过滤规则。

1. 在/etc/rc.d/目录下用touch命令建立firewall文件，执行chmod u+x firewll以更改文件属性，编辑/etc/rc.d/rc.local文件，在末尾加上 /etc/rc.d/firewall 以确保开机时能自动执行该脚本。

2. 刷新所有的ipchains

 #!/bin/sh
 echo "Starting ipchains rules..."
 #Refresh all chains
 /sbin/ipchains -F
3.设置WWW包过滤
说明：WWW端口为80，采用tcp或udp协议。
规则为：eth1=>允许所有来自Intranet的WWW包；eth0=>仅允许目的为内部网WWW服务器的包。

#Define HTTP packets
#Allow www request packets from Internet clients to www servers
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.11/32 www -i eth0 -j ACCEPT
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 1024: -d 198.168.80.11/32 www -i eth0 -j ACCEPT
#Allow response from Intranet www servers to request Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.11/32 www -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
/sbin/ipchains -A input -p udp -s 198.168.80.11/32 www -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
#Allow www request packets from Intranet clients to Internet www servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 www -i eth1 -j ACCEPT
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 www -i eth1 -j ACCEPT
#Allow www response packets from Internet www servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 www -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 www -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
4.设置ftp包过滤

说明：ftp端口为21,ftp-data端口为20，均采用tcp协议。
规则为：eth1=>允许所有来自Intranet的ftp、ftp-data包；eth0=>仅允许目的为内部网ftp服务器的包。

#Define FTP packets
#Allow ftp request packets from Internet clients to Intranet ftp server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.12/32 ftp -i eth0 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.12/32 ftp-data -i eth0 -j ACCEPT
#Allow ftp response packets from Intranet ftp server to Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.12/32 ftp -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 198.168.80.12/32 ftp-data -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT
#Allow ftp request packets from Intranet clients to Internet ftp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 ftp -i eth1 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 ftp-data -i eth1 -j ACCEPT
#Allow ftp response packets from Internet ftp servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 ftp -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 ftp-data -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT
5.设置telnet包过滤 
说明：telnet端口为21，采用tcp协议。
规则为：eth1=>允许所有来自Intranet的telnet包；eth0=>仅允许目的为bbs服务器的包；为了提高网络安全性，禁止所有对firewall的telnet请求。 

#Define telnet packets 
#Allow telnet request packets from Internet clients to Intranet bbs server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.13/32 telnet -i eth0 -j ACCEPT 
#Allow telnet response packets from bbs server to Internet clients
/sbin/ipchains -A input -p tcp -s 198.168.80.13/32 telnet -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT 
#Allow telnet request packets from Intranet clients to Internet telnet servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 telnet -i eth1 -j ACCEPT 
#Allow telent response packets from Internet telnet servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 telnet -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
6.设置smtp包过滤 
说明：smtp端口为21，采用tcp协议。
规则为：eth1=>允许所有来自Intranet的smtp包；eth0=>仅允许目的为email服务器的smtp请求。

#Define smtp packets 
#Allow smtp request packets from Internet smtp servers to Intranet email server
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 1024: -d 198.168.80.14/32 smtp -i eth0 -j ACCEPT 
#Allow smtp response packets from Intranet email server to Internet smtp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.14/32 smtp -d 0.0.0.0/0 1024: -i eth1 -j ACCEPT 
#Allow smtp request packets from Intranet clients to Internet smtp servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 smtp -i eth1  -j ACCEPT 
#Allow smtp response packets from Internet smtp servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 smtp -d 198.168.80.0/24 1024: -i eth0  -j ACCEPT 
7.设置POP-3包过滤 
说明：POP-3端口为110，采用tcp或udp协议。
规则为：eth1=>允许所有来自Intranet的POP-3包；eth0=>允许所有目的为Intranet（email server 除外）的POP-3包。 

#Define pop-3 packets 
#Allow pop-3 request packets from Intranet clients to Internet pop-3 servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 pop-3 -i eth1 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1024: -d 0.0.0.0/0 pop-3 -i eth1 -j ACCEPT 
#Allow pop-3 response packets from Internet pop-3 servers to Intranet clients (except email server)
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 pop-3 -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 pop-3 -d 198.168.80.0/24 1024: -i eth0 -j ACCEPT 
9.设置domain包过滤 
说明：domain端口为53，采用tcp或udp协议。
规则为：允许所有来自Intranet和Internet的domain请求。笔者在用网络监视软件测试时，发现domain的请求端口都是大于1100的，但是找不到相关的解释。 

#Donmain name server 
#Allow domain request packets from Intranet clients to Internet domain servers
/sbin/ipchains -A input -p tcp -s 198.168.80.0/24 1100: -d 0.0.0.0/0 domain -i eth1 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 198.168.80.0/24 1100: -d 0.0.0.0/0 domain -i eth1 -j ACCEPT 
#Allow domain response packets from Internet domain servers to Intranet clients
/sbin/ipchains -A input -p tcp -s 0.0.0.0/0 domain -d 198.168.80.0/24 1100: -i eth0 -j ACCEPT 
/sbin/ipchains -A input -p udp -s 0.0.0.0/0 domain -d 198.168.80.0/24 1100: -i eth0 -j ACCEPT 
10.设置icmp包过滤 
说明：icmp包通常用于网络测试等，故允许所有的icmp包通过。（另：icmp包通常带来的危害为ping of death，但是高版本的linux内核已经包含了相应的措施来避免ping of death） 

#Define icmp packets 
/sbin/ipchains -A input -p icmp -j ACCEPT 
11.设置缺省包过滤规则 
说明:除了以上所允许通过的包以外,禁止其他包通过。 

#Define all rules on input chain 
/sbin/ipchains -A input -j DENY -l 
通过以上个步骤，我们建立了一个相对完整的防火墙。该防火墙禁止除了提供基本服务以外的包通过。但是该防火墙还有不完善的地方，比如，某些搜索引擎会打开一个小于1024的但不常用的端口的连接，这样的包就无法通过该防火墙，从而使用户不能使用该搜索引擎。但是提高了网络的安全性，消除了安全隐患，所谓鱼与熊掌不可兼得，安全性重要还是服务重要就要看不同的情况了。

空穴来风 发表于 01:42 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
iptables－－静态防火墙实例教程- -
    在网上寻找iptable 配置的时候,发现这一篇文章,感觉比man手册更容易上手.

1、iptables介绍
 iptables是复杂的，它集成到linux内核中。用户通过iptables，可以对进出你的计算机的数据包进行过滤。通过iptables命令设置你的规则，来把守你的计算机网络──哪些数据允许通过，哪些不能通过，哪些通过的数据进行记录（log）。接下来，我将告诉你如何设置自己的规则，从现在就开始吧。


2、初始化工作
 在shell提示符 # 下打入

#iptables -F
#iptables -X
#iptables -t nat -F 
#iptables -t nat -X
 以上每一个命令都有它确切的含义。一般设置你的iptables之前，首先要清除所有以前设置的规则，我们就把它叫做初始化好了。虽然很多情况下它什么也不做，但是保险起见，不妨小心一点吧！ 如果你用的是redhat 或fedora，那么你有更简单的办法

#service iptables stop
3、开始设置规则:
 接下下开始设置你的规则了

#iptables -P INPUT DROP

 这一条命令将会为你构建一个非常“安全”的防火墙，我很难想象有哪个hacker能攻破这样的机器，因为它将所有从网络进入你机器的数据丢弃(drop) 了。这当然是安全过头了，此时你的机器将相当于没有网络。如果你ping localhost，你就会发现屏幕一直停在那里，因为ping收不到任何回应。


4 、添加规则
 接着上文继续输入命令：

#iptables -A INPUT -i ! ppp0 -j ACCEPT

 这条规则的意思是：接受所有的，来源不是网络接口ppp0的数据。
 我们假设你有两个网络接口，eth0连接局域网，loop是回环网（localhost）。ppp0是一般的adsl上网的internet网络接口，如果你不是这种上网方式，那则有可能是eth1。在此我假设你是adsl上网，你的internet接口是ppp0.
 此时你即允许了局域网的访问，你也可以访问localhost,此时再输入命令 ping localhost，结果还会和刚才一样吗？
 到此我们还不能访问www,也不能mail，接着看吧。


5、我想访问www

#iptables -A INPUT -i ppp0 -p tcp -sport 80 -j ACCEPT

 允许来自网络接口ppp0(internet接口)，并且来源端口是80的数据进入你的计算机。80端口正是www服务所使用的端口。好了，现在可以看网页了。但是，你能看到吗？
 如果你在浏览器的地址中输入www.baidu.com，能看到网页吗？你得到的结果一定是：找不到主机www.baidu.com,但是，如果你再输入220.181.27.5,你仍然能够访问baidu的网页。为什么？如果你了解dns的话就一定知道原因了。因为如果你打入www.baidu.com,你的电脑无法取得www.baidu.com这个名称所能应的ip地址220.181.27.5。如果你确实记得这个ip，那么你仍然能够访问www,你当然可以只用ip来访问www，如果你想挑战你的记忆的话^ _ ^，当然，我们要打开DNS。


6、打开dns端口
 打开你的dns端口，输入如下命令：

#iptables -A INPUT -i ppp0 -p udp -sport 53 -j ACCEPT

 这条命令的含义是，接受所有来自网络接口ppp0,upd协议的53端口的数据。53也就是著名的dns端口。此时测试一下，你能通过主机名称访问www吗？你能通过ip访问www吗？当然，都可以！


7、查看防火墙
　此时可以查看你的防火墙了

iptables -L 

　如果你只想访问www，那么就可以到此为止，你将只能访问www了。 不过先别急，将上面讲的内容总结一下，写成一个脚本。

#!/bin/bash
# This is a script 
# Edit by liwei
# establish static firewall
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -P INPUT DROP
iptables -A INPUT -i ! ppp0 -j ACCEPT
iptables -A INPUT -i ppp0 -p tcp --sport 80 -j ACCEPT
iptables -A INPUT -i ppp0 -p udp --sport 53 -j ACCEPT


8、开发服务器www端口
 复杂吗?到此iptables可以按你的要求进行包过滤了。你可以再设定一些端口，允许你的机器访问这些端口。这样有可能，你不能访问QQ，也可能不能打网络游戏，是好是坏，还是要看你自己而定了。顺便说一下，QQ这个东西还真是不好控制，用户与服务器连接使用的好像是8888端口，而QQ上好友互发消息使用的又是udp的4444端口(具体是不是4444还不太清楚)。而且 QQ还可以使用www的80端口进行登录并发消息，看来学无止境，你真的想把这个家伙控制住还不容易呢？还是进入我们的正题吧。如果你的机器是服务器，怎么办？
 如果不巧你的机器是服务器，并且要提供www服务。显然，以上的脚本就不能符合我们的要求了。但只要你撑握了规则，稍作修改同样也能很好的工作。在最后面加上一句

#iptables -A INPUT -i ppp0 -p tcp --dport 80 -j ACCEPT
 这一句也就是将自己机器上的80端口对外开放了,这样internet上的其他人就能访问你的www了。当然，你的www服务器得工作才行。如果你的机器同时是smtp和pop3服务器，同样的再加上两条语句,将--dport后面的80改成25和110就行了。如果你还有一个ftp服务器，呵呵，如果你要打开100个端口呢……
 我们的工作好像是重复性的打入类似的语句，你可能自己也想到了，我可以用一个循环语句来完成，对，此处可以有效的利用shell脚本的功能，也让你体验到了shell脚本语言的威力。看下文：


9、用脚本简化你的工作
 阅读下面的脚本

#!/bin/sh
# This is a script 
# Edit by liwei
# establish a static firewall
# define const here
Open_ports="80 25 110 10" # 自己机器对外开放的端口
Allow_ports="53 80 20 21" # internet的数据可以进入自己机器的端口

#init
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -P INPUT DROP #we can use another method to instead it 
iptables -A INPUT -i ! ppp0 -j ACCEPT

# define ruler so that some data can come in.
for Port in "Allow_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -sport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -sport $Port -j ACCEPT 
done
for Port in "Open_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -dport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -dport $Port -j ACCEPT 
done

 这个脚本有三个部分（最前面的一段是注释，不算在这三部分中）
 第一部分是定义一些端口：访问你的机器"Open_ports"端口的数据，允许进入；来源是"Allow_ports"端口的数据，也能够进入。
 第二部分是iptables的初始化，第三部分是对定义的端口具体的操作。
 如果以后我们的要求发生了一些变化，比如,你给自己的机器加上了一个ftp服务器，那么只要在第一部分"Open_ports"的定义中，将ftp对应的20与21端口加上去就行了。呵呵，到此你也一定体会到了脚本功能的强大的伸缩性，但脚本的能力还远不止这些呢！


10、使你的防火墙更加完善
 看上面的脚本init部分的倒数第二句

#iptables -P INPUT DROP
 这是给防火墙设置默认规则。当进入我们计算机的数据，不匹配我们的任何一个条件时，那么就由默认规则来处理这个数据----drop掉，不给发送方任何应答。也就是说，如果你从internet另外的一台计算机上ping你的主机的话，ping会一直停在那里，没有回应。
 如果黑客用namp工具对你的电脑进行端口扫描，那么它会提示黑客，你的计算机处于防火墙的保护之中。我可不想让黑客对我的计算机了解太多，怎么办，如果我们把drop改成其他的动作，或许能够骗过这位刚出道的黑客呢。怎么改呢？将刚才的那一句( iptables -P INPUT DROP )去掉，在脚本的最后面加上

#iptables -A INPUT -i ppp0 -p tcp -j REJECT --reject-with tcp-reset
#iptables -A INPUT -i ppp0 -p udp -j REJECT --reject-with icmp-port-unreachable
 这样就好多了，黑客虽然能扫描出我们所开放的端口，但是他却很难知道，我们的机器处在防火墙的保护之中。如果你只运行了ftp并且仅仅对局域网内部访问, 他很难知道你是否运行了ftp。在此我们给不应该进入我们机器的数据，一个欺骗性的回答，而不是丢弃(drop)后就不再理会。这一个功能，在我们设计有状态的防火墙中(我这里讲的是静态的防火墙)特别有用。
 你可以亲自操作一下，看一看修改前后用namp扫描得到的结果会有什么不同？


11、
 这个教程我想到此就结束了，其中有很多东西在这里没有提到，如ip伪装，端口转发，对数据包的记录功能。还有一个很重要的东西就是：iptables处理数据包的流程.在这里我想告诉你，你设置的过滤规则的顺序很重要，在此不宜详细介绍，因为这样一来，这个教程就会拘泥于细节。
 iptables是复杂的，我在linuxsir上看过很多教程，它们往往多而全，反而让人望而生畏，希望我的这个教程，能够指导你入门。加油！
 最后，我把完整的脚本写出来如下，你只要修改常量定义部分，就能表现出较大的伸缩性^_^

#!/bin/bash
# This is a script 
# Edit by liwei
# establish a static firewall

# define const here
Open_ports="80 25 110 10" # 自己机器对外开放的端口
Allow_ports="53 80 20 21" # internet的数据可以进入自己机器的端口

#init
iptables -F 
iptables -X
iptables -t nat -F
iptables -t nat -X

# The follow is comment , for make it better
# iptables -P INPUT DROP 
iptables -A INPUT -i ! ppp0 -j ACCEPT

# define ruler so that some data can come in.
for Port in "Allow_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -sport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -sport $Port -j ACCEPT 
done
for Port in "Open_ports" ; do
 iptables -A INPUT -i ppp0 -p tcp -dport $Port -j ACCEPT 
 iptables -A INPUT -i ppp0 -p udp -dport $Port -j ACCEPT 
done

# This is the last ruler , it can make you firewall better
iptables -A INPUT -i ppp0 -p tcp -j REJECT --reject-with tcp-reset
iptables -A INPUT -i ppp0 -p udp -j REJECT --reject-with icmp-port-unreachable


参考:
iptables－－静态防火墙实例教程 
http://antlinux.blogchina.com/1466805.html

空穴来风 发表于 01:17 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
[Linux]ident的作用
曾听过有人形容 identd (及 Ident protocol RFC1413) 像猴群一样, "你抓抓我的背, 我也抓抓你的背, 大家互惠" :-) 

假设您是一个 BBS 的管理者, 今天发现有一封广告信贴在所有的版子, 您想查清楚这封信的来源, 如果发现它是某学校的一台 PC, 那很好办, 但是, 如果您发现对方的来源 IP 是一拥有几万个 user 的工作站, 
say, tpts1.seed.net.tw, 那该怎麽办? 

Identd (及 Ident protocol) 就是针对这个理由设计出来的, 假设现在有两主机都 support Ident protocol, 也就是说, 除了双方都安装了 identd 之外, 双方的 server 程式 (telnetd, sendmail, bbs...) 
都启动 ident 查询功能. 如果您在主机 A 上要去连主机 B, 主机 B在接受您的连接 request 时, 会向主机 A 上的 Identd 做身份查询, 也就是问问 "现在要连上我机器的伙, 在你那儿是什麽身份" , 而 
主机 A 就会把你的身份 (username/id) 报给主机 B. 这麽一来, 主机 B 就有了你的身份纪录, 要是发生什麽事, 秋後算帐就比较容易了 :-) 

比较细节的身份查询过程, 可以用下图表示出来 

HOST A                                        HOSTB 
=============================          ================== 
1. 使用者 xyz 要telnet到 HOST B 
  xyz% telnet host-B 

2. 假设这个 telnet connection 在 
  双方主机上的 port  number 是 
  1027 (A) 和 23 (B) 

                                      3. 在收到这个 telnet request 
                                         的时候, telnetd (or tcpwrapper 
                                         or whatever) 就先连到 HOST 
                                         A 的 identd (port 113) 

                                      4. HOST B 向 HOST A 说: 
                                          "1027, 23" 

5. HOST A检查一下自己机器, 看看 
  是谁在 port 1027 连到 host B 
  的 port 23, 结果发现是 xyz 

6. HOST A 回覆查询结果: 
  "1027, 23 : userid : UNIX : xyz" 

                                      7. HOST B 就可以记录下来: 
                                         某年某月某日, xyz@hostA连到我的 
                                         机器.... 

从上面的说明, 或许您会发现, identd 的运作似乎与一般的 telnet/www/bbs等应用没有什麽关联, 如果不用 identd , 似乎也可以活得好好的. 确实如此, 不过, 基於 "给人方便, 自己方便" 的原则, 如果你有一台多用户 
工作站, 装上 identd, 在别人发生意外事件时调查起来比较容易. 

重复一次, Identd 对你自己的系统安全并没有任何助益 (事实上, 它有时会造成效率上的影响, 有些人甚至认为它漏了用户的隐私性), 但是, 如果您装上了identd, 未来某些时候可能某主机的 SA 会非常感激您, 同样地, 
如果你自己上发生什麽安全事件的话, 您也会很感激那些有装 Identd 的管理者. 


空穴来风 发表于 01:20 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

October 27, 2005
syslog.conf
1: syslog.conf的介绍

    对于不同类型的Unix，标准UnixLog系统的设置，实际上除了一些关键词的不同，系统的syslog.conf格式是相同的。syslog采用可配置的、统一的系统登记程序，随时从系统各处接受log请求，然后根据/etc/syslog.conf中的预先设定把log信息写入相应文件中、邮寄给特定用户或者直接以消息的方式发往控制台。值得注意的是，为了防止入侵者修改、删除messages里的记录信息，可以采用用打印机记录或采用方式来挫败入侵者的企图。

2: syslog.conf的格式

    可以参考man [5] syslog.conf。这里是对syslog.conf的简单介绍。
    /etc/syslog.conf文件中的一项配置记录由“选项”(selector)和“动作”(action)两个部分组成，两者间用tab制表符进行分隔(使用空格间隔是无效的)。而“选项”又由一个或多个形如“类型.级别”格式的保留字段组合而成，各保留字段间用分号分隔。如下行所示：

        类型.级别 [；类型.级别] `TAB` 动作 
2.1 类型 

    保留字段中的“类型”代表信息产生的源头，可以是： 

    auth    认证系统，即询问用户名和口令
    cron    系统定时系统执行定时任务时发出的信息
    daemon  某些系统的守护程序的syslog,如由in.ftpd产生的log
    kern    内核的syslog信息
    lpr     打印机的syslog信息
    mail    邮件系统的syslog信息
    mark    定时发送消息的时标程序
    news    新闻系统的syslog信息
    user    本地用户应用程序的syslog信息
    uucp    uucp子系统的syslog信息
    local0..7 种本地类型的syslog信息,这些信息可以又用户来定义
    *       代表以上各种设备
2.2 级别

    保留字段中的“级别”代表信息的重要性，可以是： 

    emerg   紧急，处于Panic状态。通常应广播到所有用户； 
    alert   告警，当前状态必须立即进行纠正。例如，系统数据库崩溃； 
    crit    关键状态的警告。例如，硬件故障； 
    err     其它错误； 
    warning 警告； 
    notice  注意；非错误状态的报告，但应特别处理； 
    info    通报信息； 
    debug   调试程序时的信息； 
    none    通常调试程序时用，指示带有none级别的类型产生的信息无需送出。如*.debug;mail.none表示调试时除邮件信息外其它信息都送出。 
2.3 动作

    “动作”域指示信息发送的目的地。可以是： 

    /filename   日志文件。由绝对路径指出的文件名，此文件必须事先建立； 
    @host       远程主机； @符号后面可以是ip,也可以是域名，默认在/etc/hosts文件下loghost这个别名已经指定给了本机。
    user1,user2 指定用户。如果指定用户已登录，那么他们将收到信息； 
    *           所有用户。所有已登录的用户都将收到信息。 
3: 具体实例

    我们来看看/etc/syslog.conf文件中的实例： 

    …… 
    *.err;kern.debug;daemon.notice;mail.crit    [TAB]   /var/adm/messages 
    …… 
    这行中的“action”就是我们常关心的那个/var/adm/messages文件，输出到它的信息源头“selector”是： 
    *.err - 所有的一般错误信息； 
    kern.debug - 核心产生的调试信息； 
    daemon.notice - 守护进程的注意信息； 
    mail.crit - 邮件系统的关键警告信息 




空穴来风 发表于 08:51 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
[Debian] Exim4 邮件服务器配置
    使用PHP的mail函数发送邮件的时候发现竟然没有接收到邮件.好像用Redhat的时候不需要配置就可以直接使用了.Debian的这个以前都没有怎么注意过.既然碰到了问题.当然今天要把它解决了.lol.

    1.首先安装配置exim4(sarge下默认为exim4).

apt-get install exim4 ##如果需要安装exim4
dpkg-reconfigure exim4-config 
    2.上面设置完后,得到的配置文件/etc/exim4/update-exim4.conf.conf 内容如下 

# /etc/exim4/update-exim4.conf.conf
#
# Edit this file and /etc/mailname by hand and execute update-exim4.conf
# yourself or use 'dpkg-reconfigure exim4-config'
#
# Please note that this is _not_ a dpkg-conffile and that automatic changes
# to this file might happen. The code handling this will honor your local
# changes, so this is usually fine, but will break local schemes that mess
# around with multiple versions of the file.
#
# update-exim4.conf uses this file to determine variable values to replace
# the DEBCONFsomethingDEBCONF strings in the configuration template files.
#
# Most settings found in here do have corresponding questions in the
# Debconf configuration, but not all of them.
#
# This is a Debian specific file

dc_eximconfig_configtype='internet'
dc_other_hostnames='bbgo.cn'
dc_local_interfaces='127.0.0.1'
dc_readhost=''
dc_relay_domains='localhost'
dc_minimaldns='false'
dc_relay_nets='222.36.45.20/32'
dc_smarthost=''
CFILEMODE='644'
dc_use_split_config='false'
dc_hide_mailname=''
dc_mailname_in_oh='true'

    3.然后重新启动服务器就可以了.

/etc/init.d/exim4 restart

    4.测试一下

echo "my test" | mail -s "test message" tommy
tail -f /var/log/exim4/mainlog
    如果显示complete，就表示成功了。用tommy用户登陆 

mail
    看看有没有信。 

    5.后记
    #1 在测试的时候,我发邮件给用户tommy,然后直接su过去,发现使用mail的时候没有显示有邮件.但是login的话,却有邮件提示.这个害我以为邮件服务器出错呢:(
    #2 /etc/exim4/update-exim4.conf.conf中的dc_relay_domains='localhost'这行之前我设置为其他的,不知道为什么出错:( 改为这个就ok了.
    #3 /var/log/exim4/mainlog 这个文件有丰富的信息,如果邮件服务器出错的话,可以参考这个文件对配置进行修改.

参考:
Debian exim4 设置
http://www.wasai.org/wiki/index.php/Debian_exim4_%E8%AE%BE%E7%BD%AE
安装 Exim 邮件服务器 
http://www.linuxforum.net/forum/gshowflat.php?Board=debian&Number=427997
Debian服务器设置入门 - 在Debian上用Exim配置邮件服务器
http://www.lslnet.com/linux/docs/linux-3895.htm


 

空穴来风 发表于 01:24 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

October 20, 2005
[Debian] 升级PHP4到PHP5
安装了Sarge以后,发现Vanilla和PhpWind这两个论坛不能使用了.可能是PHP4的问题吧.不过Debian官方没有发布PHP5的Debian包.还好Dotdeb 提供了PHP5以及相应的Module.

安装如下:

##在/etc/apt/source.list 添加下面两行
deb http://packages.dotdeb.org stable all
deb-src http://packages.dotdeb.org stable all
##运行命令
#apt-get update
#apt-get install php5 libapache2-mod-php5 php5-mysql 
安装以后可能需要重新修改php.ini 以及 php5.conf文件.

参考:
Dotdeb [提供包括供Sarge使用PHP4&5,mysql 4.1&5.0,Qmail,Vpopmail等]
http://dotdeb.org/


空穴来风 发表于 03:02 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 30, 2005
Redhat 下的yum
一. yum是什么
yum = Yellow dog Updater, Modified
主要功能是更方便的添加/删除/更新RPM包.
它能自动解决包的倚赖性问题.
它能便于管理大量系统的更新问题
注:为什么要使用yum而不用apt,最简单的原因,Fedora自带

二. yum特点
*可以同时配置多个资源库(Repository)
*简洁的配置文件(/etc/yum.conf)
*自动解决增加或删除rpm包时遇到的倚赖性问题
*使用方便
*保持与RPM数据库的一致性

三. yum安装
Fedora自带
#rpm -ivh yum-2.0.4-2.noarch.rpm

四. yum配置
注:修改和增加配置文件中的资源库,加快下载速度和拥有更多可更新的rpm包
将/etc/yum.conf的内容全部替换为

[main]
    cachedir=/var/cache/yum
    debuglevel=2
    logfile=/var/log/yum.log
    pkgpolicy=newest
    distroverpkg=fedora-release
    tolerant=1
    exactarch=1

[fedora-us-1]
    name=Fedora Core 1 -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/os

[fedora-us-1-updates]
    name=Fedora Core 1 updates -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/updates

[fedora-us-1-stable]
    name=Fedora Linux (stable) for Fedora Core 1 -- Fedora US mirror
    baseurl=ftp://mirrors.kernel.org/fedora.us/fedora/fedora/1/i386/yum/stable

[freshrpms]
    name=Fedora Linux $releasever - $basearch - freshrpms
    baseurl=http://ayo.freshrpms.net/fedora/linux/$releasever/$basearch/freshrpms

五. yum应用
注:当第一次使用yum或yum资源库有更新时,yum会自动下载所有所需的headers放置于/var/cache/yum目录下,所需时间可能较长.

//检查有哪些可更新的rpm包
#yum check-update
//安装rpm包,使xmms可以播放mp3
#yum install xmms-mp3
//安装mplayer,同时自动安装相关的软件
#yum install mplayer
//删除licq包,同时删除与该包有倚赖性的包
#yum remove licq
注:同时会提示删除licq-gnome,licq-qt,licq-text,非常方便
//系统更新(更新所有可以升级的rpm包,包括kernel)
#yum -y update
//每天定期执行系统更新
#chkconfig yum on
#service yum start
六. yum指令详解
*rpm包的更新

//检查可更新的rpm包
#yum check-update
//更新所有的rpm包
#yum update
//更新指定的rpm包,如更新kernel和kernel source
#yum update kernel kernel-source
//大规模的版本升级,与yum update不同的是,连旧的淘汰的包也升级
#yum upgrade

*rpm包的安装和删除

//安装rpm包,如xmms-mp3
#yum install xmms-mp3
//删除rpm包,包括与该包有倚赖性的包
#yum remove licq
注:同时会提示删除licq-gnome,licq-qt,licq-text

*yum暂存(/var/cache/yum/)的相关参数

//清除暂存中rpm包文件
#yum clean packages
//清除暂存中rpm头文件
#yum clearn headers
//清除暂存中旧的rpm头文件
#yum clean oldheaders
//清除暂存中旧的rpm头文件和包文件
#yum clearn 或#yum clearn all
注:相当于yum clean packages + yum clean oldheaders

*rpm包列表

//列出资源库中所有可以安装或更新的rpm包
#yum list
//列出资源库中特定的可以安装或更新以及已经安装的rpm包
#yum list mozilla
#yum list mozilla*
注:可以在rpm包名中使用匹配符,如列出所有以mozilla开头的rpm包
//列出资源库中所有可以更新的rpm包
#yum list updates
//列出已经安装的所有的rpm包
#yum list installed
//列出已经安装的但是不包含在资源库中的rpm包
#yum list extras
注:通过其它网站下载安装的rpm包

*rpm包信息显示(info参数同list)

//列出资源库中所有可以安装或更新的rpm包的信息
#yum info
//列出资源库中特定的可以安装或更新以及已经安装的rpm包的信息
#yum info mozilla
#yum info mozilla*
注:可以在rpm包名中使用匹配符,如列出所有以mozilla开头的rpm包的信息
//列出资源库中所有可以更新的rpm包的信息
#yum info updates
//列出已经安装的所有的rpm包的信息
#yum info installed
//列出已经安装的但是不包含在资源库中的rpm包的信息
#yum info extras
注:通过其它网站下载安装的rpm包的信息

*搜索rpm包

//搜索匹配特定字符的rpm包
#yum search mozilla
注:在rpm包名,包描述等中搜索
//搜索有包含特定文件名的rpm包
#yum provides realplay
七. 安全的更新freshrpms.net的rpm包
安装freshrpms.net的GPG key

#rpm --import http://freshrpms.net/packages/build...G-KEY.freshrpms

编辑/etc/yum.conf,增加以下信息到尾部

[freshrpms]
name=Fedora Linux $releasever - $basearch - freshrpms
baseurl=http://ayo.freshrpms.net/fedora/linux/$releasever/$basearch/freshrpms
gpgcheck=1
注: 

  //检查GPG Key
# rpm -qa gpg-pubkey*
//显示Key信息
#rpm -qi gpg-pubkey-e42d547b-3960bdf1
//删除Key
#rpm -e gpg-pubkey-e42d547b-3960bdf1
参考:
Linux RPM包使用指南 


空穴来风 发表于 03:59 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
Baidu Top 500 歌曲下载
很早以前就有根据百度MP3_歌曲TOP500 来获取对应的mp3的脚本,在电脑中也放着这么一个,今天整理硬盘的时候才好好的看了一看:)其实原理就这么简单,呵呵.看脚本的时候最好对应着相应页面分析一下.

#!/bin/sh
# By 6e sixwings@gmail.com
#分析得出歌曲对应的页面
wget http://list.mp3.baidu.com/topso/mp3topsong.html
cat mp3topsong.html  | tr \" \\n | pcregrep tsomp3.htm$ > list.raw
#获取所有页面-每个里面包含了歌曲对应的mp3下载地址
#保存在[1-500].html文件中
CC=1
for VAL in `cat list.raw` do
wget http://list.mp3.baidu.com/topso/$VAL -O $CC.html &
usleep 100
CC=`expr $CC + 1`
done
#分析上面获取的页面来得到mp3文件地址
NUM=`cat list.raw | wc -l`
CC=1
while [ $CC -le $NUM ] do
#获取mp3列表的第一个地址
URL=`cat $CC.html  | tr \" \\\n | pcregrep mp3$ | pcregrep ^http:// | head -1`
#获取mp3文件名
TITLE=`head -8 $CC.html | pcregrep '^空穴来风 发表于 03:10 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 25, 2005
一个新的版本控制系统 GNU-arch
在搜索资料的时候发现了这个东东..

1.特点 
与其他版本控制系统最大差异:
1.可以控制整个目录结构,而不善只有单一档案的版本
2.在改版时不只是记录目录结构,还会包括所有异动的描述
3.不再透过统一的档案库控制,每个开发人员可以控制自己负责的范围,Arch会将其串联起来.

2.安装
在Debian下

apt-get install tla tla-doc

3.下载一个Archive
要下载一个Project的源码,你需要三个信息
-the archive's name (ex. tom@example.org--2004)
-the version name (ex. hello--main--1.0)
-the URI of that archive (ex. http://www.example.org/~tom/archives/2004)

First, you need to use register-archive to register the archive: 

$ tla register-archive http://www.example.org/~tom/archives/2004
Registering archive: tom@example.org--2004

You can verify that the archive was actually registered using archives. 

$ tla archives
tom@example.org--2004
    http://www.example.org/~tom/archives/2004


Now you can use get to get a copy of the current revision. 

$ tla get tom@example.org--2004/hello--main--1.0 hello
* from revision library: tom@example.org--2004/hello--main--1.0--patch-23
* making pristine copy
* tree version set tom@example.org--2004/hello--main--1.0

The exact output will vary, but after executing this command, you will have a copy of the latest revision of the hello--main--1.0 branch in the hello directory.



参考:
1.http://www.gnuarch.org/ -- GNU Arch 
2.http://www.linuxjournal.com/article/5928 -- An Introduction to the arch Version Control System
3.ftp://ftp.gnu.org/pub/gnu/gnu-arch -- the primary distribution site for GNU Arch.]
4.http://lists.gnu.org/mailman/listinfo/gnu-arch-users -- the gnu-arch-users mailing list. 
5.http://lists.seyza.com/cgi-bin/mailman/listinfo/gnu-arch-dev -- the gnu-arch-dev mailling list. 
6.http://wiki.gnuarch.org -- the Arch Wiki, maintained by users.

空穴来风 发表于 06:45 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 11, 2005
Linux RPM包使用指南
通常Linux应用软件的安装包有三种：tar包、rpm包和dpkg包。本文主要提到的rpm包是Redhat Linux提供的一种包封装格式。RPM 有五种基本的操作方式(不包括创建软件包): 安装，卸载，升级，查询和验证。下面我们就来逐一的讲解。 

一、安装RPM包 
　　 RPM 软件包通常具有类似foo-1.0-1.i386.rpm 的文件名。其中包括 软件包的名称(foo)，版本号(1.0)，发行号(1)， 和 硬件平台(i386)。安装一个软件包只需简单的键入以下命令： 

　　 $ rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　　　　　　　 #################################### 

　　 RPM安装完毕后会打印出软件包的名字(并不一定与文件名相同)， 而后打印一连串的#号以表示安装进度。虽然软件包的安装被设计的尽量简单易行， 但还是可能会发生如下的错误： 

　　 1、软件包已被安装 
　　 如果您的软件包已被安装, 将会出现以下信息： 

　　 $ rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　　　　　　　 package foo-1.0-1 is already installed 
　　 error: foo-1.0-1.i386.rpm cannot be installed 

　　 如果您仍旧要安装该软件包，可以在命令行上使用--replacepkgs 选项，RPM将忽略该错误信息强行安装。 

　　 2、文件冲突 
　　 如果您要安装的软件包中有一个文件已在安装其它软件包时安装，会出现以下错误信息： 

　　 # rpm -ivh foo-1.0-1.i386.rpm 
　　 foo　　　　 /usr/bin/foo conflicts with file from bar-1.0-1 
　　 error: foo-1.0-1.i386.rpm cannot be installed 

　　 要想让RPM 忽略该错误信息， 请使用--replacefiles 命令行选项。 

　　 3、未解决依赖关系 
　　 RPM软件包可能依赖于其它软件包，也就是说要求在安装了特定的软件包之后才能安装该软件包。如果在您安装某个软件包时存在这种未解决的依赖关系。会产生以下信息： 

　　 $ rpm -ivh bar-1.0-1.i386.rpm 
　　 failed dependencies: foo is needed by bar-1.0-1 

　　 您必须安装完所依赖的软件包，才能解决这个问题。如果您想强制安装(这是个坏主意， 因为安装后的软件包未必能正常运行)， 请使用--nodeps 命令行选项。 

二、卸载RPM包 
　　 卸载软件包就象安装软件包时一样简单： 

　　 $ rpm -e foo 

　　 注意这里使用软件包的名字name “foo”， 而不是软件包文件的名字file “foo-1.0-1.i386.rpm”。 

　　 如果其它软件包依赖于您要卸载的软件包，卸载时则会产生错误信息。如： 

　　 $ rpm -e foo 
　　 removing these packages would break dependencies:foo is needed by bar-1.0-1 

　　 若让RPM忽略这个错误继续卸载(这可不是一个好主意，因为依赖于该软件包的程序可能无法运行)，请使用--nodeps 命令行选项。 

三、升级RPM包 
　　 升级软件包和安装软件包十分类似： 

　　 $ rpm -Uvh foo-2.0-1.i386.rpm 
　　 foo　　　　　　　　　　 #################################### 

　　 RPM将自动卸载已安装的老板本的foo 软件包，您不会看到有关信息。事实上您可能总是使用 -U 来安装软件包，因为即便以往未安装过该软件包，也能正常运行。因为RPM 执行智能化的软件包升级，自动处理配置文件，您将会看到如下信息： 

　　 saving /etc/foo.conf as /etc/foo.conf.rpmsave 

　　 这表示您对配置文件的修改不一定能向上兼容。 因此，RPM 会先备份老文件再安装新文件。您应当尽快解决这两个配置文件的不同之处，以使系统能持续正常运行。 

　　 因为升级实际包括软件包的卸载与安装两个过程，所以您可能会碰到由这两个操作引起的错误。另一个你可能碰到的问题是：当您使用旧版本的软件包来升级新版本的软件时，RPM会产生以下错误信息： 


　　 $ rpm -Uvh foo-1.0-1.i386.rpm 
　　 foo　　package foo-2.0-1 (which is newer) is already installed 
　　 error: foo-1.0-1.i386.rpm cannot be installed 


　　 如果你确有需要将该软件包”降级，加入 --oldpackage 命令选项就可以了。 

四、查询已安装的软件包 
　　 使用命令rpm -q来查询已安装软件包的数据库。简单的使用命令 rpm -q foo 会打印出foo软件包 的包名 ，版本号，和发行号： 


　　 $ rpm -q foo 
　　 foo-2.0-1 


　　 除了指定软件包名以外，您还可以使用以下选项来指明要查询哪些软件包的信 息。 这些选项被称之为 “软件包指定选项“。 

　　 ●-a 查询所有已安装的软件包 
　　 ●-f 将查询包含有文件 . 的软件包 
　　 ●-p 查询软件包文件名为 的软件包 

　　 还可以指定查询软件包时所显示的信息。它们被称作信息选择选项： 

　　 ●-i 显示软件包信息，如描述, 发行号, 尺寸, 构建日期, 安装日期, 平台, 以及其它一些各类信息。
　　 ●-l 显示软件包中的文件列表。 
　　 ●-s 显示软件包中所有文件的状态。 
　　 ●-d 显示被标注为文档的文件列表(man 手册, info 手册, README's, etc)。 
　　 ●-c 显示被标注为配置文件的文件列表。这些是您要在安装完毕以后加以定制的文件(sendmail.cf, passwd, inittab, etc)。 

　　 对于那些要显示文件列表的文件, 您可以增加-v 命令行选项以获得如同 ls -l 格式的输出。 

五、验证软件包 
　　 验证软件包是通过比较已安装的文件和软件包中的原始文件信息来进行的。验证主要是比较文件的尺寸, MD5 校验码, 文件权限, 类型, 属主和用户组等。 

rpm-V命令用来验证一个软件包。您可以使用任何包选择选项来查询您要验证的软件包。 命令rpm -V foo 将用来验证foo软件包。又如： 

　　 ●验证包含特定文件的软件包：rpm -Vf /bin/vi； 
　　 ●验证所有已安装的软件包：rpm -Va； 
　　 ●根据一个RPM包来验证：rpm -Vp foo-1.0-1.i386.rpm。 

　　 如果您担心你的RPM数据库已被破坏，就可以使用这种方式。 

如果一切均校验正常将不会产生任何输出。如果有不一致的地方，就会显示出来。 输出格式是8位长字符串, “c” 用以指配置文件, 接着是文件名. 8位字符的每一个 用以表示文件与RPM数据库中一种属性的比较结果。“.” (点) 表示测试通过。下面的字符表示对RPM软件包进行的某种测试失败： 


　　 显示字符　　　　　　　　 错误源 
　　 5　　　　　　　　　　　　MD5 校验码 
　　 S　　　　　　　　　　　　文件尺寸 
　　 L　　　　　　　　　　　　符号连接 
　　 T　　　　　　　　　　　　文件修改日期 
　　 D　　　　　　　　　　　　设备 
　　 U　　　　　　　　　　　　用户 
　　 G　　　　　　　　　　　　用户组 
　　 M　　　　　　　　　　　　模式e (包括权限和文件类型) 


　　 如果有错误信息输出, 您应当认真加以考虑，是通过删除还是重新安装来解决出现的问题。 

六、教你一招 
　　 RPM不仅是安装/卸载程序的工具，它还是系统维护和诊断的一把好手。看过下面几个例子你就会领教它的厉害了。 

　　 ●如果您误删了一些文件，但您不能肯定到底都删除了那些文件，怎么办？您可以键入：rpm -Va。 
　　 rpm会在屏幕上显示出文件删除的情况。若你发现一些文件丢失了或已被损坏, 您就可以重新安装或先卸载再安装该软件包。 

　　 ●如果您碰到了一个自己不认识的文件，要想查处它属于哪个软件包，您可以输入以下命令： 

　　 rpm -qf /usr/X11R6/bin/xjewel 
　　 输出的结果会是：xjewel-1.6-1。 


　　 ●如果发生综合以上两个例子的情况，如文件/usr/bin/paste出了问题。您想知道哪个软件包中包含该文件，您这时可以简单的键入：rpm -Vf /usr/bin/paste。 

　　 ●如果您想了解正在使用的程序的详细信息, 您可以键入如下命令来获得软件包中关于该程序的文档信息： 


　　 rpm -qdf /usr/bin/ispell 
　　 输出结果为: 
　　 /usr/man/man4/ispell.4 
　　 /usr/man/man4/english.4 
　　 /usr/man/man1/unsq.1 
　　 /usr/man/man1/tryaffix.1 
　　 /usr/man/man1/sq.1 
　　 /usr/man/man1/munchlist.1 
　　 /usr/man/man1/ispell.1 
　　 /usr/man/man1/findaffix.1 
　　 /usr/man/man1/buildhash.1 
　　 /usr/info/ispell.info.gz 
　　 /usr/doc/ispell-3.1.18-1/README 


　　 ●您发现了一个新的koules RPM，但您不知道它是做什么的，您可以键入如下命令： 


　　 rpm -qip koules-1.2-2.i386.rpm 


　　 ●现在您想了解koules的 RPM包在系统里安装了哪些文件，您可以键入： 


　　 rpm -qlp koules-1.2-2.i386.rpm，输出结果为： 
　　 /usr/man/man6/koules.6 
　　 /usr/lib/games/kouleslib/start.raw 
　　 /usr/lib/games/kouleslib/end.raw 
　　 /usr/lib/games/kouleslib/destroy2.raw 
　　 /usr/lib/games/kouleslib/destroy1.raw 
　　 /usr/lib/games/kouleslib/creator2.raw 
　　 /usr/lib/games/kouleslib/creator1.raw 
　　 /usr/lib/games/kouleslib/colize.raw 
　　 /usr/lib/games/kouleslib 
　　 /usr/games/koules 


　　 以上只是几个常见例子。随着您进一步的使用RPM，您会发现它的各种功能选项组合可以实现更为强大的RPM包管理功能。 
空穴来风 发表于 01:37 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 06, 2005
配置squid加速Apache Web服务器
一 安装与配置

首先你得有squid代理服务器.不过在这里只讲述如何配置squid的配置文件，使其支持httpd加速器工作方式。编辑“squid.conf”文件（vi /etc/squid/squid.conf），增加下面内容：

http_port 80
visible_hostname hostname
cache_mgr mgr_email

acl all src 0.0.0.0/0.0.0.0
http_access allow all

########## Accelator control ############
httpd_accel_host virtual
httpd_accel_port 8088
httpd_accel_with_proxy on
httpd_accel_uses_host_header    on
cache_dir ufs /tmp 256 16 256 

http_port 参数指定Squid监听浏览器客户请求的端口号，这里当然是80了 

cache_dir参数设定使用的存储系统的类型。一般情况下都类型应该是ufs，目录应该是“/tmp”，在该目录下使用的缓冲值为256MB，允许在“/tmp”下创建的第一级子目录数为16，每个第一级子目录下可以创建的第二级子目录数量为256
选项“httpd_accel_host”和“httpd_accel_port”定义了真正的Web服务器的主机名和端口号。在这里的配置中，真正的HTTP服务器运行在virtual主机上，运行端口为8088。

ok，squid设置完毕。

接着设置apache，很简单，只要把你的httpd监听端口设置成8088就成，然后重启你的apache。

接着重启你的squid服务，现在你访问你的web网站，已经是用了squid的http加速工作模式，你可以通过看squid的log日记看到他的运行情况。

更详细的squid设置,参照
缓存代理服务器Squid 
http://pangty.ta139.com/MyLinux/squid.htm
利用squid实现反向代理（同时具备内网代理） 
http://www.cnfug.org/journal/archives/000079.html
传统代理,透明代理,plug-gw,Apache反向代理,IP伪装,端口转发[Jephe Wu] 
http://www.linuxforum.net/docnew/showthreaded.php?Cat=&Board=server&Number=169&page=4&view=collapsed&sb=5&o=all&fpart=
基于反向代理的Web缓存加速—可缓存的CMS系统设计 
http://www.chedong.com/tech/cache.html
基于反向代理的Web缓存加速 
http://www.uplinux.com/www/sys/02/89.shtml
为 LAMP 加速 
http://blog.supercn.net/archives/2005/02/08/204/
高效配置Linux代理服务器――Squid
http://www.sowarm.com/newyk/1164.htm

二 使用中的问题以及解决

1.Running out of filedescriptors

    在使用的时候会出现错误

WARNING! Your cache is running out of filedescriptors
    在google后发现这个是因为linux对每个程序进行了filedescriptors限制的缘故.

文件描述符是一个简单的整数，用以标明每一个被进程所打开的文件和socket。第一个打开的文件是0，第二个是1，依此类推。Unix 操作系统通常给每个进程能打开的文件数量强加一个限制。更甚的是，unix 通常有一个系统级的限制。

因为squid 的工作方式，文件描述符的限制可能会极大的影响性能。当squid 用完所有的文件描述符后，它不能接收用户新的连接。也就是说，用完文件描述符导致拒绝服务。直到一部分当前请求完成，相应的文件和socket 被关闭，squid 不能接收新请求。当squid发现文件描述符短缺时，它会发布警告。

在运行./configure 之前，检查你的系统的文件描述符限制是否合适，能给你避免一些麻烦。大多数情况下，1024 个文件描述符足够了。非常忙的cache可能需要4096或更多。在配置文件描述符限制时，我推荐设置系统级限制的数量为每个进程限制的2 倍。
    在Linux下可以运行下面命令来查看进程的filedescriptors限制.

# ulimit -n
1024
    可以通过下面的命令进行修改.从而解决出现的错误!

# ulimit -HSn 65536
# ulimit -n
65536
2.日志中一些错误信息分析(不是很重要的提示)

> 2005/10/25 14:30:17| storeDirClean: WARNING: Creating 
> /cache0/00/FD 

Seems your cache directory is only partially created, or that you deleted the 
cache while Squid was running.. 


> 2005/10/25 15:26:15| storeLateRelease: released 0 
> objects 
> 2005/10/25 15:26:52| Preparing for shutdown after 0 
> requests 

Looks like a normal restart. 


> 2005/11/05 21:18:58| assertion failed: 
> store_client.c:213: "sc->cmp_offset == copy_offset" 

Internal error. For some unknown reason the store client is out of synch with 
itself. 

更详细的问题解决,参考:
SQUID Frequently Asked Questions: Troubleshooting
http://www.unix.org.ua/squid/FAQ-10.html

 




空穴来风 发表于 03:37 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 
Linux Time zone 的调整
对Linux的Time Zone以前都没有一个很好的认识.为了调整服务器的时间.看了一下相关的资料.

1.Linux下的时间区域好像存在误区. 
从worldtimezone.com上得知，一个时区缩写，的确是有多种含义的，CST可代表：

Central Standard Time (USA) Heure Normale du Centre (french)  UTC-06
Central Standard Time (Australia)  UTC+0930
China Time  UTC+08
Cuba Summer Time UTC-04 
因此，通过时区缩写设置时间，是不科学的。很容易导致zope等程序出现问题。
那么使用绝对时区，应该更加安全了。中国是东8区：+0800，那是否应该把时区设置为GMT+8呢？
答案居然是否！应该设置为GMT-8，这是非常奇怪的，相信是很多linux用户容易犯的错误。可以使用下面的命令测试：

# date +%z%Z
+0800GMT-8


这原来是posix规范的一个bug，而且没有人愿意去调整了。
Debian下使用dpkg-reconfigure timezoneconf时，不要使用etc中的GMT时区。那些时区是老的、过时的、很奇怪的东东，还是应该使用三个英文字母的缩写。但既然CST这么 不确定，就不能用。幸好有一个HKT，是表示香港的时间，也是东8区，这个没有错。托香港的福，就用这个好了。

2.Linux时间命令参考

Linux时间命令参考：

date -s "2004-08-16 GMT8"
date -s 8:46


3.手动修改Linux的Time Zone

手动调整Timezone,你需要修改/etc/sysconfig/clock文件,并且创建一个/etc/localtime到指定Timezone的软链接.下面将介绍如何手动设置Time Zone到"America/Denver":

1. 在/usr/share/zoneinfo 目录下选择相应的Time Zone. Time zone 相对于这个目录. 在这里我们选择 "America/Denver"

2. 编辑文件/etc/sysconfig/clock text  :

ZONE="America/Denver"
UTC=true
ARC=false
Of course, this assumes that your hardware clock is running UTC time...

3. 删除下面的文件: /etc/localtime

4. 创建一个软连接/etc/localtime. 链接到/usr/share/zoneinfo/目录下的Time Zone的一个文件.下面是3,4两步的示范:

# cd /etc
# ls -al localtime
lrwxrwxrwx 1 root root 39 Mar 28 07:00 localtime -> /usr/share/zoneinfo/America/Los_Angeles

# rm /etc/localtime

# ln -s /usr/share/zoneinfo/America/Denver /etc/localtime
# ls -al localtime
lrwxrwxrwx 1 root root 34 Mar 28 08:59 localtime -> /usr/share/zoneinfo/America/Denver

# date
Fri Mar 28 09:00:04 MST 2003





 


--------------------------------------------------------------------------------

 

Time, Date, and Time Zones for Red Hat Linux
A Practical Guide
http://www.vanemery.com/Linux/RH-Linux-Time.html

zope的时间bug
http://blog.czug.org/panjunyong/zope-datetime-bug

Linux上让人迷惑的时间设置
http://blog.czug.org/panjunyong/linux-date-cmd/



 

空穴来风 发表于 10:31 AM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

September 05, 2005
为 LAMP 加速
本技巧不仅仅可以为 PHP 提供加速的技巧，对于 Perl 和 Python 也有同样的效果。 

为了得到完整的调试结果，建议你采用 ApacheBench 或者 httperf之类的软件。如果你对非 LAMP 架构的服务器测试有兴趣的话，建议你采用微软的免费软件： Web Application Stress Tool（需要 NT 或者 2000）。 

检测 Apache ，采用 top d 1 显示所有进程的 CPU 和内存情况。另外，还采用 apachectl status 命令。 

1、升级硬件的一般规则：对于 PHP 脚本而言，主要的瓶颈是 CPU ，对于静态页面而言，瓶颈是内存和网络。一台 400 Mhz 的普通奔腾机器所下载的静态页面就能让 T3 专线（45Mbps）饱和。 

2、Apache 处理 PHP 脚本的速度要比静态页面慢 2-10 倍，因此尽量采用多的静态页面，少的脚本。 

3、PHP 脚本如果不做缓冲，每次调用都需要编译，因此，安装一个 PHP 缓冲产品能提升 25-100% 的性能。 

4、把基于文件的会话切换到基于共享内存的会话。编译 PHP 时采用 –with-mm 选项，在 php.ini 中设置 set session.save_handler=mm 。这个简单的修改能让会话管理时间缩短一半。 

5、另外一项缓冲技术是把不常修改的 PHP 页面采用 HTML 缓冲输出，这些缓冲工具可以参考这里。 

6、如果你采用了 Linux 系统，建议升级内核到 2.4，因为静态页面由内核服务。 

7、采用最新版本的 Apache ，并把 PHP 编译其中，或者采用 DSO 模式，不要采用 CGI 方式。 

8、采用输出缓冲（请参考ob_start），如果你的代码有很多的 print 和 echo 语句，能提速 5-15% 。 

9、不要在 Web 服务器上运行 X-Windows ，关掉没有必要运行的进程。 

10、如果能够用文本就不要用图像，尽量减小图片的尺寸。 

11、分散负载，把数据库服务器放到另外的机器上去。采用另外低端的机器服务图片和 HTML 页面，如果所有的静态页面在另外一台服务器上处理，可以设置 httpd.conf 中的 KeepAlives 为 off ，来减少断开连接的时间。 

12、采用 hdparm 来优化磁盘，一般能提升 IDE 磁盘读写性能 200%，但是对 SCSI 硬盘也有效果。 

13、修改 httpd.conf ： 
# 关闭 DNS lookups，PHP 脚本只拿 IP 地址
HostnameLookups off 

# 关闭 htaccess 检测
<Directory /> 
AllowOverride none 
</Directory> 

打开 FollowSymLinks ，关闭 SymLinksIfOwnerMatch 以防 lstat() 系统调用：
Options FollowSymLinks 
#Options SymLinksIfOwnerMatch
下面还有很多关于 httpd.conf 参数的调整。 

14、Kurt 简洁而完整的 Apache Tuning Tips。 

15、如果喜欢从修改 Apache 源码入手，可以安装 lingerd。在页面产生和发送后，每个 Apache 进程都会浪费一段时光在客户连接上，Lingerd 能接管这项工作，让 Apache 迅速服务下一个客户请求。 

16、如果网络拥挤，CPU 资源不够用，采用 PHP 的 HTML 压缩功能：
output_handler = ob_gzhandler
PHP 4.0.4 的用户请不要使用，因为存在内存泄漏问题。 

17、修改 httpd.conf 中的 SendBufferSize 为你最大的页面文件的大小。加大内核的 TCP/IP 写缓冲大小。 

18、另外一篇文章：Tuning Apache Web Servers for Speed，一篇 97 年的很古老的文章。 

19、采用数据库的持久连接时，不要把 MaxRequestsPerChild 设置得太大。 

20、Caching Tutorial for Web Authors and Webmasters 教你怎样实现浏览器缓冲。 

21、如果你足够勇敢的话，还可以采用 Silicon Graphics 的 Accelerated Apache 补丁。这个工程能使 Apache 1.3 快 10 倍，使 Apache 2.0 快 4 倍。 

22、来自Professional Apache的技巧。 

23、官方的Performance Tuning 文档，很好的资料，但是十分繁琐。 

24、编译 PHP 时，建议采用如下的参数：
–enable-inline-optimization –disable-debug 

25、优化 Linux ，more Linux 以及Solaris。 

26、以上所有的方法都是针对单机而言的，如果你觉得系统还是不够快，可以采用集群，负载均衡，缓冲技术。采用 Squid 作为缓冲，配置 Squid 的方法。 

空穴来风 发表于 03:55 PM | 本文固定地址 | 评论 (0) | 引用通告 (0) 

用iptables封杀内网的bt软件! 
 
用iptables封杀内网的bt软件! 

--------------------------------------------------------------------------------


我所在的网络情况是这样的!1台FC3和3台win2000组成一个局域网!四台机都接在100m的交换机上.在FC3上有两个网卡eth0接外网adsl eth1接在交换机.FC3做nat带3台win2000上网!由于ADSL的带宽本来就慢如果内网有人用BT的话那就更慢啦!所有找了一下资料!决定封杀内网的bt软件!
用到cvs版本的iptables在ftp://ftp.netfilter.org/pub/iptables/snapshot/有下载 还要iptables的扩展包
patch-o-matic-ng在ftp://ftp.netfilter.org/pub/patch-o...snapshot/有下载.
把patch-o-matic-ng-20041231.tar.bz2和 iptables-1.3.0-20041231.tar.bz2 拷贝到/usr/local/src目录下
首先先卸载了系统原先的iptables软件包
rpm -qa |grep iptables
rpm -e --nodeps iptables-devel
rpm -e --nodeps iptables
为了安装方便用 root用户登录
然后
tar -jxvf iptables-1.3.0-20041231.tar.bz2
tar -jxvf patch-o-matic-ng-20041231.tar.bz2
cd patch-o-matic-ng-20041231
./runme extra
输入你内核源代码的路径/usr/src/linux-2.6.10 
输入你iptables源代码的路径/usr/local/src/iptables-1.3.0-20041231
然后按你自己的需要把iptables的扩展补丁打到内核(要实现封杀bt一定要选上ipp2p这扩展)
cd /usr/src/linux-2.6.10
make xconfig
把networking support-->networking options-->networking packet filtering-->IP:netfilter configruation-->ipp2p match选上
make
make modules_install
make install
新得带有ipp2p模块的新内核就安装好了
现在iptables有安装
cd /usr/local/src/iptables-1.3.0-20041231
make KERNEL_DIR=/usr/src/linux-2.6.10 
make install KERNEL_DIR=/usr/src/linux-2.6.10 
make install-devel
reboot
重启后选新内核进入系统
如果你的系统内核选了自动挂载模块功能就直接用下面的命令就可以沣锁p2p软件啦
用iptables -A FORWARD -p tcp -m ipp2p --ipp2p --bit --apple--winmx --soul -j DROP
如果你的系统内核没有选自动挂载模块功能你要先
modprobe ipt_ipp2p

  
            

{{$创Linux标准,做Linux先锋...}}
 

  CSDNBlog  |  我的首页  |  联系作者  |  聚合   |  登录      768篇文章 :: 16篇收藏:: 118篇评论:: 11个Trackbacks  
 

公告
收藏此页到新浪ViVi收藏夹


--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
ZCLinux导航 
首 页 
资讯与技术 
开源软件下载 
新茂购物商城NEW 
 

--------------------------------------------------------------------------------
新闻资讯 
Linux产业<8篇> (rss)  
软件厂商<21篇> (rss)  
Linux新闻<192篇> (rss)  
IT资讯<49篇> (rss)  
综合报道<77篇> (rss)  
 
技术文档 
系统安全<22篇> (rss)  
数据库<3篇> (rss) 
应用案例<7篇> (rss)  
UCLinux<14篇> (rss) 
Linux<58篇> (rss)  
Solaris<3篇> (rss)  
LAMP<11篇> (rss)  
ZCLinuxBLog<35篇> (rss)  
 
开源世界 
Iptables<4篇> (rss)  
Kernel<10篇> (rss)  
Shell<10篇> (rss)  
共享开源<12篇> (rss)  
 
杂文 
程序员<5篇> (rss) 
仙人指路<1篇>  
大话IT SHOW<1篇>  
用脑袋来经营<13篇> 
 

--------------------------------------------------------------------------------

--------------------------------------------------------------------------------

ZCLinux服务宗旨：
      让更多的人了解Linux、使用Linux，欢迎更多的人进入Open Source World！ M:zcatlinux@yahoo.com.cn


--------------------------------------------------------------------------------

ZCLinux 声明：
      ZCLinux为纯技术类网站，本站所有转载文档等信息均来自互联网，其版权属于原作者，仅供学习参考使用，不作任何商业用途。
      如本站发布的内容触犯了您的版权，恳请来信告知。


--------------------------------------------------------------------------------

ZCLinux统计：


  14:39:40
自2004年07月25日起 

 
文章
Iptables(RSS)
IT资讯(RSS)
Kernel(RSS)
LAMP(RSS)
Linux(RSS)
Linux产业(RSS)
Linux新闻(RSS)
Linux应用案例(RSS)
Oracle(RSS)
Shell(RSS)
Solaris(RSS)
UCLinux(RSS)
ZCLinux BLog(RSS)
ZCLinux 开源世界(RSS)
程序员(RSS)
软件厂商(RSS)
设备硬件(RSS)
数据库(RSS)
系统安全(RSS)
综合报道(RSS)
收藏
★ 大话IT Show <1篇>
★ 仙人指路（study） <1篇>
★ 用脑袋来经营 <13篇>
Windows 类收藏
相册
Other_IMG
ZCLinux_img
Linux 技术世界

Linuxaid
ZCLinux @ CSDN
Open Source Code
myhan(RSS)
Qmailcn
UCLinux
TomLinux
本站LOGO


友情链接

ProgramLife's Blog(RSS)
Start@WinYi.com (RSS)
Tsung's Blog
YaLeiSoft
仔仔和朋友的家
孔曰成仁,孟曰取E(RSS)
存档
2005年11月(3)
2005年08月(9)
2005年07月(1)
2005年06月(7)
2005年04月(10)
2005年02月(64)
2005年01月(46)
2004年12月(9)
2004年11月(71)
2004年10月(150)
2004年09月(207)
2004年08月(191)
最近评论
Allen：实话,我做这个的我清楚.
韩磊：good!
xlyou：上来看了看！加油，加油，加油！￥
sphinx135：挺好的，清晰简单，适合我们这样的初学者看 
期待中下篇
韩磊：欢迎回来！我已经把你的的Blog加入CSDN首页的“Blog直通车”和“CSDN专家群”电子报（http://blog.csdn.net/group/experts/）。请加油为大家提供更多Linux/Unix资讯哦！


Linux 服务器安全配置（上篇） 
下面是我最近新整理出的一份日志，希望大家喜欢！
虽然这些都是老声常谈，但都是我亲手整理过的，我愿意奉献给大家！
希望大家多提意见！
----zcatlinux
第一部分：RedHat Linux篇
1．概述
Linux服务器版本：RedHat Linux AS 2.1













对于开放式的操作系统---Linux，系统的安全设定包括系统服务最小化、限制远程存取、隐藏重要资料、修补安全漏洞、采用安全工具以及经常性的安全检查等。本文主要从用户设置、如何开放服务、系统优化等方面进行系统的安全配置，以到达使Linux服务器更安全、稳定。














 


 


 


 


 


 


2．用户管理
在Linux系统中，用户帐号是用户的身份标志，它由用户名和用户口令组成。系统将输入的用户名存放在/etc/passwd文件中，而将输入的口令以加密的形式存放在/etc/shadow文件中。在正常情况下，这些口令和其他信息由操作系统保护，能够对其进行访问的只能是超级用户(root)和操作系统的一些应用程序。但是如果配置不当或在一些系统运行出错的情况下，这些信息可以被普通用户得到。进而，不怀好意的用户就可以使用一类被称为“口令破解”的工具去得到加密前的口令。













2．1 删除系统特殊的的用户帐号和组帐号：

    #userdel username













userdel adm













userdel lp













userdel sync













userdel shutdown













userdel halt













userdel news













userdel uucp













userdel operator













userdel games













userdel gopher













以上所删除用户为系统默认创建，但是在常用服务器中基本不使用的一些帐号，但是这些帐号常被黑客利用和攻击服务器。













#groupdel username













groupdel adm













groupdel lp













groupdel news













groupdel uucp













groupdel games













groupdel dip













同样，以上删除的是系统安装是默认创建的一些组帐号。这样就减少受攻击的机会。













2．2 用户密码设置：
安装linux时默认的密码最小长度是5个字节，但这并不够，要把它设为8个字节。修改最短密码长度需要编辑login.defs文件（vi /etc/login.defs）













PASS_MAX_DAYS   99999    ##密码设置最长有效期（默认值）













PASS_MIN_DAYS   0        ##密码设置最短有效期













PASS_MIN_LEN    5        ##设置密码最小长度













PASS_WARN_AGE   7        ##提前多少天警告用户密码即将过期。













2．3 修改自动注销帐号时间：
自动注销帐号的登录，在Linux系统中root账户是具有最高特权的。如果系统管理员在离开系统之前忘记注销root账户，那将会带来很大的安全隐患，应该让系统会自动注销。通过修改账户中“TMOUT”参数，可以实现此功能。TMOUT按秒计算。编辑你的profile文件（vi /etc/profile）,在"HISTSIZE="后面加入下面这行： 
　　TMOUT=300 
　　300，表示300秒，也就是表示5分钟。这样，如果系统中登陆的用户在5分钟内都没有动作，那么系统会自动注销这个账户。













2．4 给系统的用户名密码存放文件加锁：
              chattr +i /etc/passwd













              chattr +i /etc/shadow













chattr +i /etc/gshadow













chattr +i /etc/group













注：chattr是改变文件属性的命令，参数i代表不得任意更动文件或目录,此处的i为不可修改位(immutable)。查看方法：lsattr /etc/passwd













3．服务管理
在Linux系统的服务管理方面，如果想做到服务的最好安全，其中主要的就是升级服务本身的软件版本，另外一个就是关闭系统不使用的服务，做到服务最小化。













3．1 关闭系统不使用的服务：
cd /etc/init.d      ##进入到系统init进程启动目录













在这里有两个方法，可以关闭init目录下的服务，一、将init目录下的文件名mv成*.old类的文件名，即修改文件名，作用就是在系统启动的时候找不到这个服务的启动文件。二、使用chkconfig系统命令来关闭系统启动等级的服务。













注：在使用以下任何一种方法时，请先检查需要关闭的服务是否是本服务器特别需要启动支持的服务，以防关闭正常使用的服务。













第一种：修改文件名的方法













              Cd  /etc/init.d/













              mv apmd apmd.old                    ##笔记本需要













              mv netfs netfs.old                       ## nfs客户端













              mv yppasswdd yppasswdd.old   ## NIS服务器，此服务漏洞很多       













              mv ypserv ypserv.old                  ## NIS服务器，此服务漏洞很多
              mv dhcpd dhcpd.old                    ## dhcp服务













              mv portmap portmap.old                     ##运行rpc(111端口)服务必需













              mv lpd lpd.old                             ##打印服务













              mv nfs nfs.old                                   ## NFS服务器，漏洞极多













              mv sendmail sendmail.old             ##邮件服务, 漏洞极多













              mv snmpd snmpd.old                  ## SNMP，远程用户能从中获得许多系统信息













              mv rstatd rstatd.old                     ##避免运行r服务，远程用户可以从中获取很多信息













              mv atd atd.old                             ##和cron很相似的定时运行程序的服务













              第二种：使用chkcofig命令来关闭不使用的系统服务













              chkconfig –level 35 apmd off













chkconfig –level 35 netfs off













chkconfig –level 35 yppasswdd off













chkconfig –level 35 ypserv off













chkconfig –level 35 dhcpd off













chkconfig –level 35 portmap off













chkconfig –level 35 lpd off













chkconfig –level 35 nfs off













chkconfig –level 35 sendmail off













chkconfig –level 35 snmpd off













chkconfig –level 35 rstatd off













chkconfig –level 35 atd off













注：以上chkcofig 命令中的3和5是系统启动的类型，3代表系统的多用启动方式，5代表系统的X启动方式。













3．2 给系统服务端口列表文件加锁
主要作用：防止未经许可的删除或添加服务













chattr +i /etc/services













3．3 修改ssh服务的root登录权限
修改ssh服务配置文件，使的ssh服务不允许直接使用root用户来登录，这样建设系统被恶意登录攻击的机会。













vi /etct/ssh/sshd_config













PermitRootLogin yes













将这行前的＃去掉后，修改为：PermitRootLogin no













4．系统文件权限
Linux文件系统的安全主要是通过设置文件的权限来实现的。每一个Linux的文件或目录，都有3组属性，分别定义文件或目录的所有者，用户组和其他人的使用权限（只读、可写、可执行、允许SUID、允许SGID等）。特别注意，权限为SUID和SGID的可执行文件，在程序运行过程中，会给进程赋予所有者的权限，如果被黑客发现并利用就会给系统造成危害。













4．1 修改init目录文件执行权限：
chmod -R 700 /etc/init.d/*













4．2 修改部分系统文件的SUID和SGID的权限：
chmod a-s /usr/bin/chage













chmod a-s /usr/bin/gpasswd













chmod a-s /usr/bin/wall













chmod a-s /usr/bin/chfn













chmod a-s /usr/bin/chsh













chmod a-s /usr/bin/newgrp













chmod a-s /usr/bin/write













chmod a-s /usr/sbin/usernetctl













chmod a-s /usr/sbin/traceroute













chmod a-s /bin/mount













chmod a-s /bin/umount













chmod a-s /bin/ping













chmod a-s /sbin/netreport













4．3 修改系统引导文件
chmod 600 /etc/grub.conf













chattr +i /etc/grub.conf













5．系统优化
5．1 虚拟内存优化：
一般来说，linux的物理内存几乎是完全used。这个和windows非常大的区别，它的内存管理机制将系统内存充分利用，并非windows无论多大的内存都要去使用一些虚拟内存一样。













在/proc/sys/vm/freepages中三个数字是当前系统的:最小内存空白页、最低内存空白页和最高内存空白。













注意，这里系统使用虚拟内存的原则是:如果空白页数目低于最高空白页设置，则使用磁盘交换空间。当达到最低空白页设置时，使用内存交换。内存一般以每页4k字节分配。最小内存空白页设置是系统中内存数量的2倍;最低内存空白页设置是内存数量的4倍;最高内存空白页设置是系统内存的6倍。













以下以1G内存为例修改系统默认虚拟内存参数大小：













echo "2048 4096 6444" >/proc/sys/vm/freepages














 


 


 


 


 


 


6．日志管理
6．1 系统引导日志：
dmesg 
使用 dmesg 命令可以快速查看最后一次系统引导的引导日志。通常它的













内容会很多，所以您往往会希望将其通过管道传输到一个阅读器。













6．2 系统运行日志：
A、Linux 日志存储在 /var/log 目录中。这里有几个由系统维护的日志文件，但其他服务和程序也可能会把它们的日志放在这里。大多数日志只有 root 才可以读，不过只需要修改文件的访问权限就可以让其他人可读。













以下是常用的系统日志文件名称及其描述：













lastlog 记录用户最后一次成功登录时间 













loginlog 不良的登陆尝试记录 













messages 记录输出到系统主控台以及由syslog系统服务程序产生的消息













utmp 记录当前登录的每个用户 













utmpx 扩展的utmp 













wtmp 记录每一次用户登录和注销的历史信息 wtmpx 扩展的wtmp













vold.log 记录使用外部介质出现的错误 













xferkig 记录Ftp的存取情况 sulog 记录su命令的使用情况 













acct 记录每个用户使用过的命令 













aculog 拨出自动呼叫记录













B、/var/log/messages
messages 日志是核心系统日志文件。它包含了系统启动时的引导消息，以及系统运行时的其他状态消息。IO 错误、网络错误和其他系统错误都会记录到这个文件中。其他信息，比如某个人的身份切换为 root，也在这里列出。如果服务正在运行，比如 DHCP 服务器，您可以在 messages 文件中观察它的活动。通常，/var/log/messages 是您在做故障诊断时首先要查看的文件。













C、/var/log/XFree86.0.log
这个日志记录的是 Xfree86 Xwindows 服务器最后一次执行的结果。如果您在启动到图形模式时遇到了问题，一般情况从这个文件中会找到失败的原因。













D、在/var/log 目录下有一些文件以一个数字结尾，这些是已轮循的归档文件。日志文件会变得特别大，特别笨重。Linux 提供了一个命令来轮循这些日志，以使您的当前日志信息不会淹没在旧的无关信息之中。 logrotate 通常是定时自动运行的，但是也可以手工运行。当执行后，logrotate 将取得当前版本的日志文件，然后在这个文件名最后附加一个“.1”。其他更早轮循的文件为“.2”、“.3”，依次类推。文件名后的数字越大，日志就越老。 













可以通过编辑 /etc/logrotate.conf 文件来配置 logrotate 的自动行为。通过 man logrotate 来学习 logrotate 的全部细节。 













其中：













# rotate log files weekly













weekly













这里代表每个日志文件是每个星期循环一次，一个日志文件保存一个星期的内容。













# keep 4 weeks worth of backlogs













rotate 4













这里代表日志循环的次数是4次，即可以保存4个日志文件。













E、定制日志













可以通过编辑 /et/syslog.conf 和 /etc/sysconfig/syslog 来配置它们的行为，可以定制系统日志的存放路径和日志产生级别。













6．3 系统各用户操作日志：
              last













单独执行last指令，它会读取位于/var/log目录下，名称为wtmp的文件，并把该给文件的内容记录的登入系统的用户名单全部显示出来。













       history













    history命令能够保存最近所执行的命令。如果是root命令所保存的命令内容在/root/.bash_history文件中，如果是普通用户，操作所命令保存在这个用户的所属目录下，即一般的/home/username/.bash_history。这个history的保存值可以设置，编辑/etc/profile文件，其中的HISTSIZE=1000的值就是history保存的值。

7．防火墙
7．1  iptables类型防火墙：
7．1．1 iptables概念：
Iptalbes（IP包过滤器管理）是用来设置、维护和检查Linux内核的IP包过滤规则的。 













可以定义不同的表，每个表都包含几个内部的链，也能包含用户定义的链。每个链都是一个规则列表，对对应的包进行匹配：每条规则指定应当如何处理与之相匹配的包。这被称作'target'（目标），也可以跳向同一个表内的用户定义的链。













通过使用用户空间，可以构建自己的定制规则，这些规则存储在内核空间的信息包过滤表中。这些规则具有目标，它们告诉内核对来自某些源、前往某些目的地或具有某些协议类型的信息包做些什么。如果某个信息包与规则匹配，那么使用目标 ACCEPT 允许该信息包通过。还可以使用目标 DROP 或 REJECT 来阻塞并杀死信息包。对于可对信息包执行的其它操作，还有许多其它目标。 













根据规则所处理的信息包的类型，可以将规则分组在链中。处理入站信息包的规则被添加到 INPUT 链中。处理出站信息包的规则被添加到 OUTPUT 链中。处理正在转发的信息包的规则被添加到 FORWARD 链中。这三个链是基本信息包过滤表中内置的缺省主链。另外，还有其它许多可用的链的类型（如 PREROUTING 和 POSTROUTING），以及提供用户定义的链。每个链都可以有一个策略，它定义“缺省目标”，也就是要执行的缺省操作，当信息包与链中的任何规则都不匹配时，执行此操作。 













建立规则并将链放在适当的位置之后，就可以开始进行真正的信息包过滤工作了。这时内核空间从用户空间接管工作。当信息包到达防火墙时，内核先检查信息包的头信息，尤其是信息包的目的地。我们将这个过程称为路由。 













如果信息包源自外界并前往系统，而且防火墙是打开的，那么内核将它传递到内核空间信息包过滤表的 INPUT 链。如果信息包源自系统内部或系统所连接的内部网上的其它源，并且此信息包要前往另一个外部系统，那么信息包被传递到 OUTPUT 链。类似的，源自外部系统并前往外部系统的信息包被传递到 FORWARD 链。


7．1．2 iptables实例1：
       #!/bin/sh


# 禁止系统的转发包功能













echo 0 > /proc/sys/net/ipv4/ip_forward


# 清楚iptables原有规则，并设置iptables默认规则













iptables -t nat -F POSTROUTING













iptables -t nat -F PREROUTING













iptables -t nat -F OUTPUT













iptables -F


iptables -P INPUT DROP













iptables -P FORWARD ACCEPT













iptables -P OUTPUT ACCEPT


# 在input规则中需要打开的tcp、upd端口













iptables -A INPUT -j ACCEPT -p tcp --dport 80













iptables -A INPUT -j ACCEPT -p tcp --dport 22













iptables -A INPUT -j ACCEPT -p tcp --dport 25













iptables -A INPUT -j ACCEPT -p tcp --dport 1352


iptables -A INPUT -p udp --destination-port 53 -j ACCEPT


# 在input规则中状态为：STATE RELATED 的包都接受













iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT


# 启用系统ip转发功能













echo 1 > /proc/sys/net/ipv4/ip_forward


< --end-- >













7．1．3 iptables实例2：
       注：这个实例中，只需要设置tcp、udp端口和服务器网络段ip范围即可，其他已经默认设置好。













#!/bin/sh













# make:yongzhang













# time:2004-06-18













# e-mail: yongzhang@wiscom.com.cn














 


 


 


PATH=/sbin:/bin:/usr/sbin:/usr/bin


##tcp allow ports













TPORTS="80 22"


##udp allow ports













UPORTS="53"


##internal server_ip range













SERVER_IP="172.18.10.0/24"


##disable forwarding













echo 0 > /proc/sys/net/ipv4/ip_forward


##reset default policies













iptables -P INPUT ACCEPT













iptables -P FORWARD ACCEPT













iptables -P OUTPUT ACCEPT













iptables -t nat -P PREROUTING ACCEPT













iptables -t nat -P POSTROUTING ACCEPT













iptables -t nat -P OUTPUT ACCEPT


##del all iptables rules













iptables -F INPUT













iptables -F FORWARD













iptables -F OUTPUT


##clean all non-default chains













iptables -X













iptables -t nat -X


##iptables default rules













iptables -P INPUT DROP













iptables -P FORWARD DROP













iptables -P OUTPUT ACCEPT


##allow ping packets













iptables -A INPUT -p ICMP -s 0/0 --icmp-type 0 -j ACCEPT













iptables -A INPUT -p ICMP -s 0/0 --icmp-type 3 -j ACCEPT













iptables -A INPUT -p ICMP -s 0/0 --icmp-type 5 -j ACCEPT













iptables -A INPUT -p ICMP -s 0/0 --icmp-type 8 -j ACCEPT













iptables -A INPUT -p ICMP -s 0/0 --icmp-type 11 -j ACCEPT













#iptables -A INPUT -p ICMP -s 0/0 --icmp-type 11 -m limit --limit 5/s -j ACCEPT













iptables -A FORWARD -p ICMP -j ACCEPT


##enable forwarding













iptables -A FORWARD -m state --state ESTABLISHED,RELATED -j ACCEPT


##STATE RELATED for router













iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT


##accept internal packets on the internal i/f













iptables -A INPUT -s $SERVER_IP -p tcp -j ACCEPT


##open ports on router for server/services













##TCP PORTS













for ATP in $TPORTS













do













iptables -A INPUT ! -s $SERVER_IP -d $SERVER_IP -p tcp --destination-port $ATP -j ACCEPT













          iptables -A FORWARD -p tcp --destination-port $ATP -j ACCEPT













done


##UDP PORTS













for AUP in $UPORTS













do













          iptables -A INPUT -p udp --destination-port $AUP -j ACCEPT













          iptables -A FORWARD -p udp --destination-port $AUP -j ACCEPT













done


##bad_packets chain













##drop INVALID packets immediately













iptables -A INPUT -p ALL -m state --state INVALID -j DROP


##limit SYN flood













#iptables -A INPUT -f -m limit --limit 100/s --limit-burst 100 -j ACCEPT













#iptables -A FORWARD -f -m limit --limit 100/s --limit-burst 100 -j ACCEPT


##deny all ICMP packets,eth0 is external net_eth













#iptables -A INPUT -i eth0 -s  0.0.0.0/0 -p ICMP -j DROP


##allow loopback













iptables -A INPUT -i lo -p all -j ACCEPT













iptables -A OUTPUT -o lo -p all -j ACCEPT


##enable forwarding













echo 1 > /proc/sys/net/ipv4/ip_forward


< --end-- >













7．2 ipchains类型防火墙：
7．2．1 ipchains概念：
Ipchains 被用来安装、维护、检查Linux内核的防火墙规则。规则可以分成四类：IP input链、IP output链、IP forward链、user defined 链。













一个防火墙规则指定包的格式和目标。当一个包进来时, 核心使用input链来决定它的命运。 如果它通过了, 那么核心将决定包下一步该发往何处(这一步叫路由)。假如它是送往另一台机器的, 核心就运用forward链。如果不匹配，进入目标值所指定的下一条链，那有可能是一条user defined链，或者是一个特定值: ACCEPT，DENY，REJECT，MASQ，REDIRECT，RETURN。













ACCEPT意味着允许包通过，DENY 扔掉包就象没有受到过一样，REJECT也把包扔掉，但(假如它不是 ICMP 包)产生一个 ICMP 回复来告诉发包者，目的地址无法到达（请注意DENY和REJECT对于ICMP包是一样的）。 
　　MASQ 告诉核心伪装此包，它只对forward 链和user defined链起作用，想让它起作用, 编译核心时必需让 IP Masquerading 起作用。 
　　REDIRECT只对input链和user defined链起作用。它告诉核心把无论应送到何处的包改送到一个本地端口. 只有 TCP 和 UDP 协议可以使用此指定. 任意用 '-j REDIRECT' 指定一个端口(名字或编号)可以使送往此的包被重定向到某个特殊的端口, 即使它被标记为送到其它端口。想让它起作用，编译内核时，必须让CONFIG_IP_TRANSPARENT_PROXY起作用。 
　　最后的一个目标指定是 RETURN, 它跳过它下面的所有规则, 直到链的末尾。 
　　任何其它的目标指定表示一个用户自定义的链。包将在那个链中通过. 假如那个链没有决定此包的命运, 那么在那个链中的传输就完成了，包将通过当前链的下一个规则。 













7．2．2 ipchains实例：
    ##清除input规则的规则，并改变input默认的规则链策略为REJECT













-F input













-P input REJECT


##以下是允许input规则链的tcp端口为：80 81 22 123













-A input -s 0/0 -d 0/0 80 -p tcp -y -j ACCEPT













-A input -s 0/0 -d 0/0 81 -p tcp -y -j ACCEPT













-A input -s 0/0 -d 0/0 22 -p tcp -y -j ACCEPT













-A input -s 0/0 -d 0/0 123 -p udp -j ACCEPT













       













        ##设置除了以上允许的input规则链以为，拒绝0－1023、2049、6000－6009、7100的tcp和upd端口，













-A input -p tcp -s 0/0 -d 0/0 0:1023 -y -j REJECT













-A input -p tcp -s 0/0 -d 0/0 2049 -y -j REJECT













-A input -p udp -s 0/0 -d 0/0 0:1023 -j REJECT













-A input -p udp -s 0/0 -d 0/0 2049 -j REJECT













-A input -p tcp -s 0/0 -d 0/0 6000:6009 -y -j REJECT













-A input -p tcp -s 0/0 -d 0/0 7100 -y -j REJECT


##允许系本身统网卡上发生的所有包通过













-A input -s 0/0 -d 0/0 -i lo -j ACCEPT













-A input -s 0/0 -d 0/0 -i eth0 -j ACCEPT













-A input -s 0/0 -d 0/0 -i eth1 -j ACCEPT


        ##清除output规则的规则，并改变output默认的规则链策略为ACCEPT













-F output













-P output ACCEPT













##清除forward规则的规则，并改变forward默认的规则链策略为DENY,设置了forward规则链允许对10.10.11.0/24网段的包可以转发并且做伪装处理。













-F forward













-P forward DENY













-A forward -s 10.10.11.0/24 -j MASQ













       < --end-- >
















Trackback: http://tb.blog.csdn.net/TrackBack.aspx?PostId=529362

[点击此处收藏本文]   发表于 2005年11月14日 8:42 PM 


 
sphinx135 发表于2005-11-16 12:57 AM  IP: 222.216.18.*
挺好的，清晰简单，适合我们这样的初学者看 
期待中下篇


发表评论
  
大名：  
请输入尊姓大名  
网址：   
验证码    
评论  
请输入评论 
  
    记住我？ 
 


--------------------------------------------------------------------------------
网站简介－广告服务－网站地图－帮助信息－联系方式－English－问题报告

CSDN北京百联美达美数码科技有限公司  版权所有  京 ICP 证 020026 号 CSDN

? 2000-04, CSDN.NET, All Rights Reserved

--------------------------------------------------------------------------------
 

Copyright ? ZCLinux Powered By .Text

