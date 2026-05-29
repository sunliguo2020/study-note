命令索引:
background	设置图形模式下的背景色。
blocklist	输出文件的块清单标记。
boot	引导已加载的操作系统或扇区链式加载器。
bootp	通过BOOTP初试化网络设备。
cat	显示指定文件的内容。
chainloader	加载扇区链式加载器。
clear	清屏幕。
cmp	比较两个文件, 并且报告两者之间的不同的信息。
color	改变菜单的颜色。
configfile	将指定文件作为配置文件予以加载。
debug	打开/关闭除错模式。
default	把 NUM 项菜单设为缺省值。
device	声明BIOS驱动器对应的实际物理设备。
dhcp	通过DHCP初试化网络设备。
displayapm	显示 APM BIOS 的相关信息。
displaymem	显示 GRUB 所判断到的当前系统的内存分布，包括所有物理内存区域。
dump	显示诸多文件的内容。
embed	如果设备是个驱动器, 则将Stage 1.5嵌入到主引导扇区之后。
fallback	如果调用当前的菜单项时出现错误，则转移到 NUM 项后重试
find	在所有分区上查找文件名, 并显示包含该文件的设备。如果设置了参数 --set-root，则在找到第一个匹配后马上停止，并且把该设备设为根。
fontfile	指定中文字体文件，并切换到简体中文显示方式。
foreground	设置图形模式下的前景色。
fstest	切换文件系统的试验模式。
geometry	输出驱动器的相关信息。
gfxmenu	使用 FILE 中的图形菜单。
halt	关闭系统。
help	显示内部命令的帮助信息。
hiddenmenu	隐藏菜单。
hide	通过在分区类型上置隐藏标志，隐藏指定分区。
ifconfig	指定 IP 地址, 子网掩码, 网关和服务器地址。不带参数时，将显示当前的网络配置。
impsprobe	通过一些循环操作，侦测出符合 Intel 多处理器规范 1.1/1.4 的 CPUs，以便于发挥其更好的效能。
initrd	加载Linux格式的初始化虚拟盘, 并设置必要的参数。
install	安装STAGE1到指定设备上,安装加载STAGE2需要的块列表到STAGE2上。
ioprobe	侦测指定设备的 I/O 端口号。
kernel	尝试载入主引导影像文件。
lock	如果用户未被认证，则终止命令的执行。
makeactive	将 root 设备置为活动分区。
map	对设备进行映射。
md5crypt	产生一个 MD5 格式的密码。
module	对多重启动影像, 加载启动模块文件 (不处理该文件的内容, 用户必须自己确定核心的要求)。
modulenounzip	与 'module' 类似, 但是自动禁用了解压缩。
pager	没有参数时，切换页模式。
partnew	创建一个新的主分区。
parttype	改变指定分区(PART)的分区类型(TYPE)。
password	设置密码。
pause	终止命令的运行，并给出一段信息。任意键按下后，将继续。
portmap	进行端口映射。
quit	从 GRUB 命令行中退出。
rarp	用 RARP 初始化网络设备。
read	从内存的指定位置读取一个 32-bit 的值，并以十六进制形式显示出来。
reboot	重启系统。
root	设置根分区。
rootnoverify	类似`root'指令, 但不测试安装该分区。这用于有些系统装在 GRUB 能访问的磁盘区之外, 但仍需要设置正确的根分区的情况。有些需要安装分区才能确定的参数可能会有问题。
run	运行一个为光盘启动而设计的引导文件（非模拟方式的）
savedefault	将当前项设置为默认的引导项。
scdrom	寻找系统的第一个 CD-ROM 驱动器，然后为其分配一个驱动器号以备后续使用(--install)。或者，用该驱动器中的可引导光盘启动系统。(--boot)。
serial	初始化一个串口设备。
setkey	改变键盘映射关系。
setup	自动安装GRUB.
splashimage	图形模式下载入背景图片文件。
terminal	选择一个终端。
terminfo	指定终端的功能。
testload	以多种不同的方式读取文件(由FILE指定)的整个内容，并予以比较，以测试文件系统的代码。
testvbe	测试所指定(MODE)的 VBE 模式。
tftpserver	指定 TFTP 服务器的 IP 地址。
timeout	设置在自动启动缺省菜单前所等待的秒数。
title	命名菜单项。
unhide	通过清除隐藏标志，解除指定分区(PARTITION)的隐藏。
uppermem	强制指定仅有(KBYTES) KB 的上位内存。
vbeprobe	侦测 VBE 的信息。
blocklist
用法: blocklist FILE
描述:
输出文件的块清单标记。
boot
用法: boot
描述:
引导已加载的操作系统或扇区链式加载器。
bootp
用法: bootp [--with-configfile]
描述:
通过BOOTP初试化网络设备。如果使用了`--with-configfile'参数，此命令将会试图去加载一个特定的配置文件。
cat
用法: cat FILE
描述:
显示指定文件的内容。
chainloader
用法: chainloader [--force] FILE
描述:
加载扇区链式加载器。若使用了--force参数, 则忽略该扇区的启动标识的有效性。
cmp
用法: cmp FILE1 FILE2
描述:
比较两个文件, 并且报告两者之间的不同的信息。
color
用法: color NORMAL [HIGHLIGHT]
描述:
改变菜单的颜色。Normal 用于指定菜单项的未选中时的颜色，HIGHLIGHT 则用于指定菜单项的被选中时的颜色。如果你未指定 HIGHLIGHT 色，那么我们将使用 NORMAL 的反色值。颜色值的格式是 "FG/BG"。FG 和 BG 是颜色的名称，如下：black(黑), blue(蓝), green(绿), cyan(青), red(红), magenta(粉红), brown(棕), light-gray(亮灰),dark-gray(暗灰), light-blue(浅蓝), light-green(淡绿), light-cyan(淡青), light-red(明红), light-magenta(浅红), yellow(黄) 和 white(白)。注意，BG 的值只能是前八个。另外，若想使用闪烁的前景色，你在 FG 前使用前缀 "blink-" 即可。
configfile
用法: configfile FILE
描述:
将指定文件作为配置文件予以加载。
debug
用法: debug
描述:
打开/关闭除错模式。
default
用法: default [NUM | `saved']
描述:
把 NUM 项菜单设为缺省值。
device
用法: device DRIVE DEVICE
描述:
声明BIOS驱动器对应的实际物理设备。这条命令只用于grub命令行。
portmap
用法: portmap prog_number vers_number
描述:
进行端口映射。
dhcp
用法: dhcp
描述:
通过DHCP初试化网络设备。
splashimage
用法: splashimage FILE
描述:
图形模式下载入背景图片文件。
foreground
用法: foreground RRGGBB
描述:
设置图形模式下的前景色。RR 代表红色, GG 代表绿色, BB 代表蓝色。注意他们都使用十六进制的值。
background
用法: background RRGGBB
描述:
设置图形模式下的背景色。RR 代表红色, GG 代表绿色, BB 代表蓝色。注意他们都使用十六进制的值。
clear
用法: clear
描述:
清屏幕。
displayapm
用法: displayapm
描述:
显示 APM BIOS 的相关信息。
displaymem
用法: displaymem
描述:
显示 GRUB 所判断到的当前系统的内存分布，包括所有物理内存区域。
dump
用法: dump FROM TO
描述:
显示诸多文件的内容。注意，FROM 所指定的必须是一个 GRUB 文件，TO 所指定的必须是一个 OS 文件。
embed
用法: embed STAGE1_5 DEVICE
描述:
如果设备是个驱动器, 则将Stage 1.5嵌入到主引导扇区之后。如果是个FFS分区, 则可嵌入到该设备饿`引导代码'区中。并输出 Stage 1.5所占的扇区数。
fallback
用法: fallback NUM
描述:
如果调用当前的菜单项时出现错误，则转移到 NUM 项后重试
find
用法: find [--set-root] FILENAME
描述:
在所有分区上查找文件名, 并显示包含该文件的设备。如果设置了参数 --set-root，则在找到第一个匹配后马上停止，并且把该设备设为根。
fstest
用法: fstest
描述:
切换文件系统的试验模式。
gfxmenu
用法: gfxmenu FILE
描述:
使用 FILE 中的图形菜单。
geometry
用法: geometry DRIVE [CYLINDER HEAD SECTOR [TOTAL_SECTOR]]
描述:
输出驱动器的相关信息。在grub壳程序中, 你可以用这条命令设置驱动器参数为任意值。如果你省略了总扇区数, 则该值缺省有其它参数决定。
halt
用法: halt [--no-apm]
描述:
关闭系统。如果APM(高级电源管理)功能存在，将使用 APM BIOS 关闭系统，除非指定了　`--no-apm' 选项。
help
用法: help [--all] [PATTERN ...]
描述:
显示内部命令的帮助信息。要查看所有命令的帮助，请使用 `--all' 参数。
hiddenmenu
用法: hiddenmenu
描述:
隐藏菜单。
hide
用法: hide PARTITION
描述:
通过在分区类型上置隐藏标志，隐藏指定分区。
ifconfig
用法: ifconfig [--address=IP] [--gateway=IP] [--mask=MASK] [--server=IP]
描述:
指定 IP 地址, 子网掩码, 网关和服务器地址。不带参数时，将显示当前的网络配置。
impsprobe
用法: impsprobe
描述:
通过一些循环操作，侦测出符合 Intel 多处理器规范 1.1/1.4 的 CPUs，以便于发挥其更好的效能。
initrd
用法: initrd FILE [ARG ...]
描述:
加载Linux格式的初始化虚拟盘, 并设置必要的参数。
install
用法: install [--stage2=STAGE2_FILE] [--force-lba] STAGE1 [d] DEVICE STAGE2 [ADDR] [p] [CONFIG_FILE] [REAL_CONFIG_FILE]
描述:
安装STAGE1到指定设备上,安装加载STAGE2需要的块列表到STAGE2上。如果使用了选项'd', STAGE1总是试图使用安装STAGE2的驱动器, 而不是启动盘。STAGE2将加载在指定地址上, 如果未声明地址, 则自动检测。如果使用了选项 'p' 或给出了配置文件, 将修改STAGE2的第一个数据块, 修正实际Stage2启动时使用的配置文件位置。对于Stage 1.5, 该值为Stage 2的路径。如果安装的是Stage 1.5, 且指定了实际配置文件, 则将该配置文件路径写入Stage2中。
ioprobe
用法: ioprobe DRIVE
描述:
侦测指定设备的 I/O 端口号。
kernel
用法: kernel [--no-mem-option] [--type=TYPE] FILE [ARG ...]
描述:
尝试载入主引导影像文件。其它项将被作为内核的命令行参数而传递给内核。使用此命令以前，内核所用到的模块应该被重新载入。参数 --type 用于说明内核的类型，包括 "netbsd", "freebsd", "openbsd", "linux", "biglinux" 和 "multiboot"。参数 --no-mem-option 用于说明不必自动传递 Linux 的内存参数。
lock
用法: lock
描述:
如果用户未被认证，则终止命令的执行。
makeactive
用法: makeactive
描述:
将 root 设备置为活动分区。当然，此命令只对 PC 的硬盘主分区有效。
map
用法: map [--status] [--hook] [--unhook] [--rehook] [[--read-only] [--fake-write] [--unsafe-boot] [--disable-chs-mode] [--disable-lba-mode] [--heads-per-cylinder=H] [--sectors-per-track=S] TO_DRIVE FROM_DRIVE]
描述:
对设备进行映射。这对于扇区链式引导是很有用的功能，比如 DOS。这里，目的驱动器(TO_DRIVE)可以是一个磁盘文件，即使用磁盘虚拟功能。注意，这要求磁盘文件是连续存放于分区中的。另外，若使用了 --read-only 参数，该功能将使`磁盘'处于只读;若使用了 --fake-write 参数，该功能将使`磁盘'处于假写，即可以"写入"数据，但是却并未记录到真实磁盘上; 若使用了 --unsafe-boot 参数，该功能将使`磁盘'处于真实可写; 若使用了 --disable-chs-mode 参数，CHS 访问功能将被禁用; 若使用了 --disable-lba-mode 参数， LBA访问功能将被禁用; H 和 S 指定了虚拟磁盘的物理参数。若使用了 --status, --hook, --unhook,--rehook 诸参数之一, 那么其它的命令行参数将被忽略。
md5crypt
用法: md5crypt
描述:
产生一个 MD5 格式的密码。
module
用法: module FILE [ARG ...]
描述:
对多重启动影像, 加载启动模块文件 (不处理该文件的内容, 用户必须自己确定核心的要求)。剩余参数作为`模快命令行`传递, 象`kernel'命令一样。
modulenounzip
用法: modulenounzip FILE [ARG ...]
描述:
与 'module' 类似, 但是自动禁用了解压缩。
pager
用法: pager [FLAG]
描述:
没有参数时，切换页模式。如果使用了 FLAG 参数，那么它为`on' 时为开启, 为 `off' 时为关闭。
partnew
用法: partnew PART TYPE START LEN
描述:
创建一个新的主分区。START 为起始扇区号，LEN 为其包含的扇区数，TYPE 为其分区类型。
parttype
用法: parttype PART TYPE
描述:
改变指定分区(PART)的分区类型(TYPE)。
password
用法: password [--md5] PASSWD [FILE]
描述:
设置密码。当其处于菜单文件的首项时，将禁用所有的交互式菜单编辑功能，包括编辑菜单项(`e`)/进入命令行(`c`)。当正确输入密码 (由PASSWD指定)后，载入新的菜单文件(由FILE指定)。如果你没有指定 FILE 项，那么上述被禁用的功能将被启用了。当然，你也可以将此命令用到某个菜单项里，用以提高系统安全性。参数 --md5 说明密码(PASSWD)是使用md5crypt 加密的。
pause
用法: pause [MESSAGE ...]
描述:
终止命令的运行，并给出一段信息。任意键按下后，将继续。
quit
用法: quit
描述:
从 GRUB 命令行中退出。
rarp
用法: rarp
描述:
用 RARP 初始化网络设备。
read
用法: read ADDR
描述:
从内存的指定位置读取一个 32-bit 的值，并以十六进制形式显示出来。
reboot
用法: reboot
描述:
重启系统。
fontfile
用法: fontfile FILE
描述:
指定中文字体文件，并切换到简体中文显示方式。
scdrom
用法: scdrom [--install], [--bootcd]
描述:
寻找系统的第一个 CD-ROM 驱动器，然后为其分配一个驱动器号以备后续使用(--install)。或者，用该驱动器中的可引导光盘启动系统。(--boot)。
run
用法: run FILE
描述:
运行一个为光盘启动而设计的引导文件（非模拟方式的）
root
用法: root [DEVICE [HDBIAS]]
描述:
设置根分区。设置根分区为指定设备(DEVICE), 然后尝试挂接该分区以得到分区大小(用于在ES:ESI中传递, 扇区链式启动方式要求这样)。BSD 驱动类型用于启动 BSD 的核心启动), 和确定 BSD 子分区所在的 PC 分区。可选的磁盘偏移参数, 用于 BSD 核心确定有多少个控制器在当前控制器前。比如: 假设同时有一个IDE和SCSI盘, 而BSD根分区在 SCSI盘上, 那么磁盘偏移就为1。
rootnoverify
用法: rootnoverify [DEVICE [HDBIAS]]
描述:
类似`root'指令, 但不测试安装该分区。这用于有些系统装在 GRUB 能访问的磁盘区之外, 但仍需要设置正确的根分区的情况。有些需要安装分区才能确定的参数可能会有问题。
savedefault
用法: savedefault
描述:
将当前项设置为默认的引导项。
serial
用法: serial [--unit=UNIT] [--port=PORT] [--speed=SPEED] [--word=WORD] [--parity=PARITY] [--stop=STOP] [--device=DEV]
描述:
初始化一个串口设备。UNIT 用于指定要使用的串口设备 (如，0 == COM1); PORT 用于指定端口号; SPEED 用于指定通讯的数率; WORD 为字长; PARITY 为奇偶类型(取 `no', `odd' 和 `even' 之一的值。); STOP 是停止位的长度值; 选项 --device 仅用于命令行模式，用以指定 tty 设备的文件名。默认值是这样的，COM1, 9600, 8N1。
setkey
用法: setkey [TO_KEY FROM_KEY]
描述:
改变键盘映射关系。把FROM_KEY映射为TO_KEY。这里的键必须是字母, 数字, 和以下特殊键: escape(转义), exclam(!), at(@), numbersign(#), dollar($), parenright ()) , caret(^), ampersand(&), asterisk(*), plus(+), percent(%), minus(-), underscore(_), equal(=), parenleft[(], backspace(退格), tab(制表), bracketleft([), braceleft({), bracketright(]), braceright(}), enter(回车), control(控制), semicolon(;), colon(:), quote('), doublequote("), slash(/), backquote(`), tilde(~), shift(换档), backslash(\), bar(|), comma(,), less(<), period(.), greater(>), question(?), alt(交互), space(空格), capslock(大写), Fx(功能键) 和 delete(删除)。
setup
用法: setup [--prefix=DIR] [--stage2=STAGE2_FILE] [--force-lba] INSTALL_DEVICE [IMAGE_DEVICE]
描述:
自动安装GRUB. 这条命令使用更灵活的install命令将GRUB安装到指定设备上。如果给出了映象设备,将在该设备寻找GRUB,否则使用缺省的根设备。根设备可用 root指令指定。如果你确认系统的 BIOS 应该支持 LBA 模式, 但是 GRUB 却没有工作于该模式, 则请指定 `--force-lba' 参数。如若你在命令行中已安装了一次 GRUB 可是，你却无法卸载 GRUB 程序所在的分区，请指定 `--stage2' 参数。
terminal
用法: terminal [--dumb] [--no-echo] [--no-edit] [--timeout=SECS] [--lines=LINES] [--silent] [console] [serial] [hercules] [graphics]
描述:
选择一个终端。当指定了多个终端以后, 按任意键方可继续操作。如果控制台和串口都被指定了, 那么你首先在其中按下键盘的终端将被首先选中。如果没有指定任何参数, 那么此命令将显示出当前的终端设置; 参数 --dumb 用以指定一个哑终端, 否则即为 vt100 兼容型; 若使用了 --no-echo 参数, 屏幕上将不会回显输入的字符; 若使用了 --no-edit 参数, the BASH-like 的编辑功能将被禁用; 若使用了 --timeout 参数, 该命令将等待数秒钟(由SECS指定); 可使用 --lines 指定最大的行数; 可使用 --silent 选项关闭消息显示。
terminfo
用法: terminfo [--name=NAME --cursor-address=SEQ [--clear-screen=SEQ] [--enter-standout-mode=SEQ] [--exit-standout-mode=SEQ]]
描述:
指定终端的功能。如果此终端为 vt100 兼容型的，则可指定换码顺序 (即使用 \e 代表 ESC, ^X　代表控制码); 在未给任何参数的情况下，将给出当前配置信息。
testload
用法: testload FILE
描述:
以多种不同的方式读取文件(由FILE指定)的整个内容，并予以比较，以测试文件系统的代码。输出看起来会有点儿混乱，但是，如果没有错误的话，`i=X, filepos=Y' 里的 X 和 Y 最后必得相等。如果测试即告成功，下一步即可试图载入内核了。
testvbe
用法: testvbe MODE
描述:
测试所指定(MODE)的 VBE 模式。
tftpserver
用法: tftpserver IPADDR
描述:
指定 TFTP 服务器的 IP 地址。
timeout
用法: timeout SEC
描述:
设置在自动启动缺省菜单前所等待的秒数。
title
用法: title [NAME ...]
描述:
命名菜单项。
unhide
用法: unhide PARTITION
描述:
通过清除隐藏标志，解除指定分区(PARTITION)的隐藏。
uppermem
用法: uppermem KBYTES
描述:
强制指定仅有(KBYTES) KB 的上位内存。任何系统的地址变换将被取消。
vbeprobe
用法: vbeprobe [MODE]
描述:
侦测 VBE 的信息。如果指定了一个模式(MODE 不为空)，则仅显示其信息。



















关于grub
2004-04-19, by flyonsnow

本文档归属linuxsir-probing!转载请注明出处!更不能被用到商业用途上!

1 首先要了解的几个概念

1.1 启动管理器
启动管理器是存储在磁盘开始扇区中的一段程序，例如，硬盘的MBR(Master Boot Record)，在系统完成启动测试后，如果系统是从MBR启动，则BIOS(Basic Input/Output System)将控制传送给MBR。然后存储在MBR中的这段程序将运行。这段程序被称为启动管理器。它的任务就是将控制传送给操作系统，完成启动过程》有许多可用的启动管理器，包括GNU GRUB (Grand Unified Boot Loader),Bootmanager, LILO (LInux LOader), NTLDR (boot loader for Windows NT systems)，等等等.
1.2 什么是GRUB?
grub 是一个多重启动管理器。grub是GRand Unified Bootloader的缩写，它可以在多个操作系统共存时选择引导哪个系统。它可以引导的操作系统包括：
Linux,FreeBSD,Solaris,NetBSD,BeOSi,OS/2,Windows95/98,Windows NT,Windows2000，WinXP。它可以载入操作系统的内核和初始化操作系统（如Linux,FreeBSD），或者把引导权交给操作系统（如 Windows 98）来完成引导。
1.3 GRUB的特点
特别适用于linux与其它操作系统共存情况。
支持大硬盘现在大多数Linux发行版本的lilo都有同样的一个问题：根分区(/boot分区)不能分在超过1024柱面的地方，一般是在8.4G左右的地方，否则lilo不能安装，或者安装后不能正确引导系统。而grub就不会出现这种情况，只要安装时你的大硬盘是在LBA模式下，grub就可以引导根分区在 8G以外的操作系统。
支持开机画面 　 grub支持在引导开机的同时显示一个开机画面。对于玩家来说，这样可以制作自己的个性化开机画面；对于PC厂商，这样可以在开机时显示电脑的一些信息和厂商的标志等。grub支持640x480,800x600,1024x768各种模式的开机画面，而且可以自动侦测选择最佳模式，与Windows那 320x400的开机画面不可同日而语。
两种执行模式 grub不但可以通过配置文件进行例行的引导，还可以在选择引导前动态改变引导时的参数，还可以动态加载各种设备。例如你在Linux下编译了一个新的核心，但不能确定它能不能工作，你就可以在引导时动态改变grub的参数，尝试装载这个新的核心进行使用。Grub的命令行有非常强大的功能，而且支持如 bash或doskey一样的历史功能，你可以用上下键来寻找以前的命令。
菜单式选择 　 grub使用一个菜单来选择不同的系统进行引导。你还可以自己配置各种参数，如延迟时间，默认操作系统等。
分区大小改变后不必重新配置 　　grub是通过文件系统直接把核心读取到内存，因此只要操作系统核心的路径没有改变，grub就可以引导系统。
除此之外，Grub还有许多非常强大的功能。例如支持多种外部设备，动态装载操作系统内核，甚至可以通过网络装载操作系统核心。Grub支持多种文件系统，支持多种可执行文件格式，支持自动解压，可以引导不支持多重引导的操作系统,支持网络启动等。
1.4 MBR和第一扇区
你可以简单的理解为MBR是整个硬盘的物理第一位置,而第一扇区是硬盘的物理第二位置.
1.5 一个GRUB配置文件
基于本例的分区如下：
hda 15G
hda1 8G / RED HAT LINUX8.0
hda5 7G /home
hdc 20G
hdc1 6.4G WinXP
hdc5 6.4G
hdc6 6.4G
hdc7 6.4G
#fdisk -l
# Disk /dev/hdc: 255 heads, 63 sectors, 2434 cylinders
Units = cylinders of 16065 * 512 bytes

Device Boot Start End Blocks Id System
/dev/hdc1 * 1 894 7181023+ b Win95 FAT32
/dev/hdc2 895 2434 12370050 f Win95 Ext'd (LBA)
/dev/hdc5 895 1787 7172991 b Win95 FAT32
/dev/hdc6 1788 2434 5196996 b Win95 FAT32

Disk /dev/hda: 255 heads, 63 sectors, 1867 cylinders
Units = cylinders of 16065 * 512 bytes

Device Boot Start End Blocks Id System
/dev/hda1 * 1 1020 8193118+ 83 Linux
/dev/hda2 1021 1802 6281415 83 Linux
/dev/hda3 1803 1867 522112+ 82 Linux swap

grub.conf,这个文件位于;/boot/grub/grub.conf
# grub.conf generated by anaconda
#
# Note that you do not have to rerun grub after making changes to this file
# NOTICE: You do not have a /boot partition. This means that
# all kernel and initrd paths are relative to /, eg.
# root (hd0,0)
# kernel /boot/vmlinuz-version ro root=/dev/hda1
# initrd /boot/initrd-version.img
#boot=/dev/hda
default=0
timeout=3
splashimage=(hd0,0)/boot/grub/splash.xpm.gz
title Red Hat Linux (2.4.18-14)
root (hd0,0)
kernel /boot/vmlinuz-2.4.18-14 ro root=LABEL=/
initrd /boot/initrd-2.4.18-14.img
title Microsoft Windows XP
map (hd0) (hd1)
map (hd1) (hd0)
root (hd1,0)
chainloader (hd1,0)+1
makeactive
boot

2 解读grub.conf文件

我们将来看看grub.conf文件内语句,(注:...)内的东西是我们的解读内容.
# grub.conf generated by anaconda
#
# Note that you do not have to rerun grub after making changes to this file
# NOTICE: You do not have a /boot partition. This means that
# all kernel and initrd paths are relative to /, eg.
# root (hd0,0)
# kernel /boot/vmlinuz-version ro root=/dev/hda1
# initrd /boot/initrd-version.img
#boot=/dev/hda (注:以上以符号井＂＃＂开头的行表示被注释掉，没有任何意义)
default=0 (注:默认的操作系统就是由default控制的。default后加一个数字n，表明是第 n＋1个。需要注意的是，GRUB中，计数是从0开始的，第一个硬盘是hd0，第一 个软驱是fd0，等等。所以，default 0 表示默认的操作系统在这儿是 Red Hat Linux (2.4.18-14)如果你修改成1就是WinXP了)
timeout=3 (注:timeout表示默认等待的时间，这儿是3秒钟。超过3秒，用户还没有作出选 择的话，系统将自动选择默认的操作系统;当然你可以改成任何你乐意的时间)
splashimage=(hd0,0)/boot/grub/splash.xpm.gz (注:指定开机画面文件splash.xpm.gz的位置)
title Red Hat Linux (2.4.18-14) (注:表示Red Hat Linux的菜单项)
root (hd0,0) (注:表示第一个硬盘第一个分区,这里的root和系 统内的root不是一码事!详细如下说明)
kernel /boot/vmlinuz-2.4.18-14 ro root=LABEL=/ (注:指定内核的位置,详细说明如下 文)
initrd /boot/initrd-2.4.18-14.img (注:初始化)
title Microsoft Windows XP (注:表示Microsoft Windows XP的菜单项)
map (hd0) (hd1) (注:map是命令,详细如下)
map (hd1) (hd0)
root (hd1,0) (注:这是指第二个硬盘(从硬盘)上第一个分区)
chainloader (hd1,0)+1 (注:链式装入器,装入一个扇区的数据然后把引导 权交给它。详细说明如下)
makeactive
boot

(注: 在 Linux 中，当谈到 "root" 文件系统时，通常是指主 Linux 分区。但是，GRUB 有它自己的 root 分区定义。GRUB 的 root 分区是保存 Linux 内核的分区。这可能是您的正式 root 文件系统，也可能不是。我们讨论的是 GRUB，需要指定 GRUB 的 root 分区。进入 root 分区时，GRUB 将把这个分区安装成只读型，这样就可以从该分区中装入 Linux 内核。GRUB 的一个很“酷”的功能是它可以读取本机的 FAT、FFS、minix、ext2 和 ReiserFS 分区.到目前为止，您可能会感到一点疑惑，因为 GRUB 所使用的硬盘／分区命名约定与 Linux 使用的命名约定不同。在Linux 中，第一个硬盘的第五个分区称作 "hda5"。而 GRUB 把这个分区称作 "(hd0,4)"。GRUB 对硬盘和分区的编号都是从 0 开始计算。另外，硬盘和分区都用逗号分隔，整个表达式用括号括起。现在，可以发现如果要引导 Linux 硬盘 hda5，应输入 "root (hd0,4)"。
知道了内核在哪儿，还要具体指出哪个文件是内核文件，这就是kernel的工作。
kernel /boot/vmlinuz-2.4.18-14 ro root=LABEL=/说明/boot/vmlinuz-2.4.18-14就是要载入的内核。后面的都是传递给内核的参数。root=LABEL=/ 就是linux的硬盘分区表示法，ro是readonly的意思。initrd用来初始的linux image，并设置相应的参数。
命令map:当你有两块硬盘，一个无法从第二块硬盘启动的操作系统，例如Windowsxp，就可以使用map命令.你能够将hd0映射为hd1，将hd1映射为hd0。换句话说，你可以虚拟的交换两个硬盘而启动所需要的操作系统 。命令形式如下：
grub> map (hd0) (hd1)
grub> map (hd1) (hd0)
GRUB 使用了“链式装入器”(chainloader)。链式装入器从分区 (hd1,0) 的引导记录中装入winxp自己的引导装入器，然后引导它。这就是这种技术叫做链式装入的原因 -- 它创建了一个从引导装入器到另一个的链。这种链式装入技术可以用于引导任何版本的 DOS 或 Windows。
GRUB的配置文件要简单就这么简单，如果你要更个性化一点，试一试把“color light-gray/blue ”加在default语句的下面，下一次启动GRUB时，看看有什么变化，再试一试“color light-blue/red",惊喜吗？ 有趣吧! )

3 如何使用grub?

3.1 安装
你可以从ftp://alpha.gnu.org/pub/gnu/grub 下载GRUB的源代码。
得到文件grub-0.5.96.1.tar.gz，所以这样做：
# tar -xvzf grub-0.5.96.1.tar.gz
这个命令将解开的文件和目录放在一个名为grub-0.5.96.1的目录中。现在运行如
下命令：
#cd grub-0.5.96.1
# ./configure
如果你想定制GRUB，使之包含流行的文件系统和对网卡的支持，或者删除你不需要的网卡，可以运行如下命令：
# ./configure --help
这个命令将输出所有的命令选项。现在可以使用—enable和—disable选项增加或
删除对特定网卡的支持。（注意：GRUB支持网络启动）
为了开始编译过程，键入如下命令：
# make
# make install
至此你已经为安装GRUB真正做好了准备。
将GRUB的相关文件保存在诸如/boot/grub的目录中是一个好主意。为此，按如下步骤：
1．默认状态下，GRUB所有文件将安装在/usr/share/grub/i386-pc(或者在
/usr/local/share/grub/i386-pc目录下，这只取决于你的shell变量的设置。)
2．建立一个叫做/boot/grub的目录，然后拷贝下列文件到这个目录：
stage1 stage2 * stage1 5
稍候将解释这些文件。同时也要把GRUB(可能在/usr/sbin或者/usr/local/sbin
目录下)拷贝到/boot/grub目录下。
安装GRUB可以分为三个单独的步骤：
1．将“stage1”安装到MBR中。
2．设置“stage2”的地址或者位置。
3．设置一个菜单或选项，用来决定启动哪一个操作系统。
使用下面的命令开始安装GRUB。
#cd /boot/grub
# ./grub
这个命令根据BIOS的设置检测硬件设备，同时产生一些输出信息。这会花较长的时间。
end_request: I/O error, dev 02:00 (floppy), sector 0
GRUB version 0.5.96.1 (640K lower / 3072K upper memory)
TAB键可列出可能的命令列表。其它情况下TAB会列出设备或文件名。类似下面的提示会出现：
grub>
现在，假设你将Linux安装在了第一块硬盘的第一个分区中或者/dev/hda1中。记住GRUB的命名规则，将上面的名字改为(hd0,0)。键入下面的命令：
grub> install (hd0,0)/boot/grub/stage1 (hd0) (hd0,0)/boot/grub/stage2
p (hd0,0)/boot/grub/menu.conf
现在分析一下这个命令的细节。
install
一个内置的命令，它告诉GRUB将(hd0,0)/boot/grub/stage1安装到hd0的主引导纪录中。
(hd0,0)/boot/grub/stage2
告诉GRUB stage2映象的位置。
p with the the following options: (hd0,0)/boot/grub/menu.conf
为菜单的显示设置配置文件。
下面是对这个命令用法的总结：
1．install
2．ource_of_stage1
3．where_to_install
4．source_of_stage2
5．p source_of_configuration_file
现在，你完成了硬盘上的基本安装工作。
在软盘上的安装：
为了在软盘上安装GRUB，你要会用“dd”命令，并且了解它是如何工作的。为了做一张GRUB启动盘，你要将stage1和stage2文件放到软盘的开始扇区中。
安装stage1到软盘上：
插入一张已格式化的软盘，键入命令：
# dd if=stage1 of=/dev/fd0 bs=512 count=1
命令的详细说明如下：
if=input file
i.e., stage1
of=output file
i.e., floppy drive (this may be different on your computer)
bs=bytes to read and write
Here it is 512 bytes.
count=how many times to perform this operation
每次拷贝“bs”数目的块到目标地址。
安装stage2到软盘
# dd if=stage2 of=/dev/fd0 bs=512 seek=1
这里的步骤同stage1的相同，除了一个seek选项外。Seek选项将调过一个“bs”。例如，在上面的命令中bs的值是512,这样seek=1意味着将跳过软盘上前512个字节 ，从513字节开始。这将使得第一步操作不会覆盖stage1的前512字节。
现在你完成了基本的软盘驱动器安装。

如果已经安装了grub要把grub重新安装到主引导扇区上，只需要简单打入makebootable命令就可以了。

3.2 配置grub
grub启动时会在/boot/grub/中寻找一个名字为menu.lst的配置文件，如果找不到此文件则不进入菜单模式而直接进入命令行模式。
现在，我们来看一下如何在启动后进入各种操作系统，如何建立menu.conf文件。我们就从GRUB支持的启动过程开始。可以有两种方法来完成启动过程：
·A.通过调用内核本地启动
·B.连续启动或者将控制转给另一个引导器
A模式启动过程
1．配置跟设备或者告诉GRUB你的根文件系统。
2．告诉GRUB你的内核影像的位置，然后将参数传送给内核。
3．重新启动，试一下。
为了启动Linux，将内核以bzImage的文件名放在/boot/目录中，跟文件系统是
/dev/hda1，或者GRUB中的(hd0,0)。启动过程如下：
1.root (hd0,0) [This sets the root partition]
2.kernel /boot/bzImage root=/dev/hda1 [This sets the kernel]
B模式启动过程（这种模式假设当前的分区中安装了另一个启动管理器，例如LILO
或者NTLDR）：
1．设置根分区但不要安装它
2．激活这个分区
3．配置需要启动的分区的第一个扇区
4．重新启动，看一下效果。
我们在试试启动安装在/dev/hdc1或者(hd1，0)的widows。启动windows的过程如下:
1.rootnoverify (hd1,0)
2.makeactive
3.chainloader +1 [+1 sets the first sector of the current root
partition]
4.boot [transfers the control and quits GRUB]
menu.conf文件：它用于建立启动多操作系统时的菜单。建立menu.conf并不难。它使用简单的英语，就象你在这一节看到的那样。
所有的菜单项目都以没有逗号分隔的“title TITLENAME”开头。你可以随意设置
TITLENAME。
设置Linux启动菜单步骤如下：
1．设置标题
2．设置根分区
3．设置内核的相应参数
4．启动
一个菜单例子：
title Red Hat Linux (2.4.18-14)
root (hd0,0)
kernel /boot/vmlinuz-2.4.18-14 ro root=LABEL=/
initrd /boot/initrd-2.4.18-14.img
前面有#的行是一个注释。
建立启动Windows 或者 DOS的菜单：
title Windoze
rootnoverify (hd0,0)
makeactive
chainloader +1
boot
#----
又或者:
title Microsoft Windows XP
map (hd0) (hd1)
map (hd1) (hd0)
root (hd1,0)
chainloader (hd1,0)+1
makeactive
boot
----
注意:root和rootnoverify都是一样的，把rootnoverify改成root也行。不过经过实践来看。有时引导win时，系统安装好后，是rootnoverify (hdX.Y)这样形式的，这样会出现windows起不来，出现什么windows什么文件损坏的情况。这时，我们就要把在grub中，引导 windows的那段中的rootnoverify改为root
root英文的意思就是根的意思，在这里是让linux知道自己所处的位置，也就是我们所安装linux的／根分区所在的位置 。
----
如果你安装了两个版本的Windows—一个是你自己用的，另一个给你的家人用的—这样第二个就无法安装，因为有提示说Windows已经安装了。
有一种简单的方法可以安装两个版本的Windows，即在启动时隐藏一个分区而使用另一个。你甚至可以为你的分区设置密码保护，这样可以避免别人错误的加载你的分区。下面介绍如何完成两个Windows的安装，hda1和hda2 或者 (hd0,0) 和(hd0,1)，用到的命令有lock, password, hide 和 unhide。
建立windows 项目"My Entry":
title My Entry
lock
unhide (hd0,0)
hide (hd0,1)
rootnoverify (hd0,0)
makeactive
chainloader +1
boot
#----
为了更好的使用lock命令，你需要在配置文件开头使用password命令。Password命令的语法如下：password secret(“secret”就是密码)。任何时候你都可以通过按p键儿输入密码。
建立Windows 项目"Family Entry"
title Family Entry
unhide (hd0,1)
hide (hd0,0)
rootnoverify (hd0,1)
makeactive
chainloader +1
boot

任何人都可以启动这个项目，而无须输入密码。
这有一个使用password命令的有趣的窍门。为了在缺省菜单列表或配置文件中隐藏某些项目，你可以使用下面的命令加载一个定制的列表：
password secret
在这个命令中，“secret”是密码，而/boot/grub/secret-list.conf是密码文件。这样做之前，你要先进入到根目录或者给出全路径名。例如：
password secret (hd0,4)/boot/grub/secret-list.conf
还有一个更重要的命令是“map”。当你有两块硬盘，一个无法从第二块硬盘启动的操作系统，例如Windows，就可以使用map命令。例如，你能够将 hd0映射为hd1，将hd1映射为hd0。换句话说，你可以虚拟的交换两个硬盘而启动所需要的操作系统 。命令形式如下：
grub> map (hd0) (hd1)
grub> map (hd1) (hd0)
启动FreeBSD：
title FreeBSD 4.0
root (hd0,4,a)
kernel /boot/loader
boot
#----
这里我们调用了FreeBSD的启动管理器。Root (hd0,4,a)由四个参数，是因为
FreeBSD对一个单独分区进行了虚拟分割。我们称根分区为“a”。如果FreeBSD占
据了整个第二块硬盘，这里就应该是root (hd0,a)。这样，就不是调用内核而是调用FreeBSD的启动管理器，它要比调用内核更易使用。
（注意：推荐在使用OpenBSD和GNU/Hurd之前，要先试一下链式加载。）
现在你已经完成了基本的GRUB编译、安装和配置。你对GRUB了解的越多，就越会发现GRUB是一种控制启动的易用和高效的方法。
各种GRUB命令：
default xx
表明xx是缺省的启动项目
timeout yy
表明在yy秒后缺省启动项目将启动
fallback zz
在第一个启动项目失败后，过了timeout时间后，就将启动zz项目。
color
这个命令将生成彩色菜单。它的语法是：color normal current_selection。这两个域都可以有两个值，形如foreground/background。例如：
color green/black or light-gray/blue
你也可以使用相关的数字。
记住：所有的值都是从0开始，所以0是第一个

3.3 GRUB启动盘
要制作引导盘，需执行一些简单的步骤。首先，在新的软盘上创建 ext2 文件系统。然后，将其安装，并将一些 GRUB 文件复制到该文件系统，最后运行 "grub" 程序，它将负责设置软盘的引导扇区。
将一张空盘插入 1.44MB 软驱，输入：
# mke2fs /dev/fd0
创建了 ext2 文件系统后，需要安装该文件系统：
# mount /dev/fd0 /mnt/floppy
现在，需要创建一些目录，并将一些关键文件（原先安装 GRUB 时已安装了这些文件）复制到软盘：
# mkdir /mnt/floppy/boot
# mkdir /mnt/floppy/boot/grub
# cp /boot/grub/stage1 /mnt/floppy/boot/grub
# cp /boot/grub/stage2 /mnt/floppy/boot/grub
再有一个步骤，就能得到可用的引导盘。
在linux bash中，从 root 用户运行“grub”，该程序非常有趣并值得注意，因为它实际上是GRUB 引导装入器的半功能性版本。尽管 Linux 已经启动并正在运行，您仍可以运行 GRUB 并执行某些任务，而且其界面与使用 GRUB 引导盘或将 GRUB 安装到硬盘 MBR 时看到的界面(即GRUB控制台)完全相同。
在 grub> 提示符处，输入：
grub> root (fd0)
grub> setup (fd0)
grub> quit
现在，引导盘完成了。
如果要把GRUB装到硬盘上，也很容易。这个过程几乎与引导盘安装过程一样。首先，需要决定哪个硬盘分区将成为 root GRUB 分区。在这个分区上，创建 /boot/grub 目录，并将 stage1 和 stage2 文件复制到该目录中，可以通过重新引导系统并使用引导盘，或者使用驻留版本的 GRUB 来执行后一步操作。在这两种情况下，启动 GRUB，并用 root 命令指定 root 分区。例如，如果将 stage1 和 stage2 文件复制到 hda5 的 /boot/grub 目录中，应输入 "root (hd0,4)"。接着，决定在哪里安装 GRUB -- 在硬盘的 MBR，或者如果与 GRUB 一起使用另一个“主”引导装入器，则安装在特定分区的引导记录中。如果安装到 MBR，则可以指定整个磁盘而不必指定分区，如下（对于 hda）：
grub> setup (hd0)
如果要将 GRUB 安装到 /dev/hda5 的引导记录中，应输入：
grub> setup (hd0,4)
现在，已安装 GRUB。引导系统时，应该立即以 GRUB 的控制台方式结束（如果安装到 MBR）。现在，应创建引导菜单，这样就不必在每次引导系统时都输入那些命令。

从软盘启动grub
制作启动盘后可以用软盘启动引导硬盘上的操作系统, 插入制作好的启动软盘，进入BIOS设定软盘启动。软盘启动成功后就会进入grub的命令行模式
grub>
要启动一个操作系统，首先指定引导哪个分区上的系统，例如要引导指第一个硬盘上的第一个分区的操作系统，先键入
grub>root (hd0,0)
接着如果要启动的是Windows系统，键入
grub>chainloader (hd0,0)+1
注意(hd0,0)要随着硬盘和分区的不同而改变数字。
如果要引导Linux或其他系统，应键入
grub>kernel （hd0,0）/boot/vmlinuz root=/dev/hda1
注意hda1参数也要随着硬盘和分区的不同而改变，如从第二个硬盘的第一个分区引导则用hdb1。
最后敲入boot就可以启动系统了。
在任何时候不能确定命令或者命令的参数都可以按Tab获得相关的帮助。用上下键可以获得命令的历史记录。其实这些命令就是menu.lst的启动描述，您也可以根据那些描述来自己键入启动命令，最后敲入boot就可以引导系统了。

4 GRUB的交互性

GRUB 最好的优点之一就是其强健的设计 -- 在不断使用它时请别忘了这点。如果更新内核或更改它在磁盘上的位置，不必重新安装 GRUB。事实上，如有必要，只要更新 menu.lst 文件即可，一切将保持正常。
只有少数情况下，才需要将 GRUB 引导装入器重新安装到引导记录。首先，如果更改 GRUB root 分区的分区类型（例如，从 ext2 改成 ReiserFS），则需要重新安装。或者，如果更新 /boot/grub 中的 stage1 和 stage2 文件，由于它们来自更新版本的 GRUB，很有可能要重新安装引导装入器。其它情况下，可以不必理睬！
GRUB的最大的特点就是交互性特别强。在开机时，按一下“c”，将进入GRUB 控制台。显示如下：
GRUB version 0.5.96.1 (640K lower / 3072K upper memory)
[ Minimal BASH-like line editing is supported. For the first word, TAB
lists possible command completions. Anywhere else TAB lists the possible
completions of a device/filename. ]
grub>
欢迎使用 GRUB 控制台。现在，再研究命令：
将通过GRUB 控制台绕过lilo来启动RedHat linux，
grub> root (h
现在，按一次 Tab 键。如果系统中有多个硬盘，GRUB 将显示可能完成的列表，从 "hd0" 开始。如果只有一个硬盘，GRUB 将插入 "hd0,"。如果有多个硬盘，继续进行，在 ("hd2") 中输入名称并在名称后紧跟着输入逗号，但不要按 Enter 键。部分完成的 root 命令看起来如下：
grub> root (hd0,
现在，继续操作，再按一次 Tab 键。GRUB 将显示特定硬盘上所有分区的列表，以及它们的文件系统类型。在我的系统中，按 Tab 键时得到以下列表：
grub> root (hd0, (tab，按tab一下键)
Possible partitions are:
Partition num: 0, Filesystem type is fat, partition type 0x6
Partition num: 2, Filesystem type is ext2fs, partition type 0x83
Partition num: 4, Filesystem type unknown, partition type 0x7
Partition num: 5, Filesystem type is ext2fs, partition type 0x83
Partition num: 6, Filesystem type is fat, partition type 0xb
Partition num: 7, Filesystem type is fat, partition type 0xb
Partition num: 8, Filesystem type is ext2fs, partition type 0x83
Partition num: 9, Filesystem type unknown, partition type 0x82
如您所见，GRUB 的交互式硬盘和分区名称实现功能非常有条理。这些，只需要好好理解 GRUB 新奇的硬盘和分区命名语法，然后就可以继续操作了
grub> root (hd0,8)
现在已安装了 root 文件系统，到装入内核的时候了
grub> kernel /boot/vmlinuz-2.4.2 root=/dev/hda5 ro
[Linux-bzImage, setup=0x1200, size=0xe1a30]
您已经安装了 root 文件系统并装入了内核。现在，可以引导了。只要输入 "boot"，Linux 引导过程就将开始。是不是很cool啊，GRUB的menu.lst更像一个linux下的脚本程序。

5 常见grub除错方法的思路

首先进去Linux的rescue模式！
用软盘或光盘启动，然后在启动的提示符输入:linux rescue
按照提示进入一个Shell状态，你可以到/mnt/下面看到一个sysimage这么目录，进去以后，就是你安装linux的/分区.
使用命令将根分区变为当前目录的根分区:chroot /mnt/sysimage
然后转到/sbin/这个目录中.
使用fdisk -l 显示当前分区情况，然后使用#grub-install /dev/hdx(x为你使用的是那块硬盘安装的，一般情况下是hda)
使用exit推出chroot，再使用exit退出linux rescue模式，系统将重新启动！取出光盘，应该可以看到grub安装好了.
在具体的环境中，编辑/boot/grub/grub.conf文件和menu.lst文件.

