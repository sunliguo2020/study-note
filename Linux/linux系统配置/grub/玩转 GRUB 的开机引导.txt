玩转 GRUB 的开机引导 

相信很多使用Red Hat的用户都对GRUB默认的引导画面感到厌倦了，这里向大家提供一个较好的方法来实现每次都使用不同的开机引导画面。 
　　  一幅背景 
　 　首先，需要一幅图片，要求它的解析度在640×480或之上。虽然从道理上讲小于这个尺寸也没关系，因为可以把它扩张为640×480，但是这样会造成 比较严重的画质损失，所以最好不要小于这个尺寸。选好图片后，需要在GRUB的目录中建立一个存放图片的文件夹，一般情况可以通过以下命令来做：

＃cd /boot/grub && mkdir image

　 　但是仅仅这么做是不够的，因为一是没有修改grub.conf，使所做的设置生效；二是GRUB使用压缩了的XPM图像格式，而比较常见的图片格式是 BMP、JPG、GIF和PNG之类的，所以需要将图片格式转换成XPM。可能有人想到了使用GIMP，但是GIMP使用起来相对麻烦，而且如果没有安装 X-Window的话就无法使用GIMP了。所以这里建议使用命令convert进行图片格式转换（可以使用man convert命令详细阅读其使用手册）。简单说一下convert使用方法，比如要将image.jpg转换为image.xpm，使用命令如下：

＃convert -geometry 640x480 -colors 14 image.jpg image.xpm

　 　convert命令在Red Hat Linux 9.0上默认是安装的。这个命令是把image.jpg转变尺寸为640×480，色深是14的image.xpm。注意，命令行中的640和480之间 是小写字母“x”，不要写错。另外，GRUB要求图片色深必须是14，一般可以这样来证明：
＃cd /boot/GRUB && gunzip splash.xpm.gz && less splash.xpm
　　在文件头部可以找到这些信息： 
 
　　所以需要进行上述的转换步骤以达到GRUB的要求。接下来压缩这幅图片,使用下面的命令：
＃gzip -9 image.xpm
　　结果生成了image.xpm.gz，然后把这个文件拷贝到image目录，再修改grub.conf。注意，grub.conf是重要的启动文件，如果用户没有把握在GRUB引导失效后记住该文件内容，最好备份一下。使用vi编辑器找到类似于这样的行：
splashimage=(hd0,1)/GRUB/splash.xpm.gz
　　把它改为：
splashimage=(hd0,1)/GRUB/image/image.xpm.gz
　　然后使用命令wq存盘退出。这时不要着急删掉splash.xpm.gz，因为如果修改失败的话，还能有个引导画面，否则的话每次进入GRUB就只有一个光秃秃的黑色背景了。 
　 　这样就大功告成了，赶快重启试试，看看自己的修改成果。虽然画质有所下降，但是比起以前的单调画面还是耳目一新的。如果重启后进入GRUB引导画面时图 像严重失真，无背景或黑屏，则证明修改grub.conf有错或图片没有转化正确。如果GRUB没有错误，进入系统后像上面那样使用less检查图像信 息；如果进不去系统的话使用系统盘进入单用户模式，然后恢复grub.conf就行了。 


Debian中Grub安装和修改Grub启动时的背景图片简单步骤

1 apt-get install grub
2 grub-install /dev/hda
3 update-grub
4 reboot

修改grub启动时的背景图片
1 将一图片转化成640*480,14色的XPM文件：
#convert abc.jpg -colors 14 -geometry 640x480! abc.xpm
2 压缩生成的xpm文件，使用gzip
#gzip -9 abc.xpm
3 将abc.xpm.gz拷到/boot/grub下
4 修改/boot/grub/menu.lst
splashimage /boot/grub/abc.xpm.gz
5 存盘退出menu.lst片断

源码:timeout 15

splashimage /boot/grub/Deb_GNOME2_1600x1200.xpm.gz
title Windows[2003]
root (hd0,0)
chainloader +1

title Debian[2.4.26-1-k7]
root (hd0,5)
kernel /boot/vmlinuz-2.4.26-1-k7 root=/dev/hda6 ro
initrd /boot/initrd.img-2.4.26-1-k7
savedefault
boot
......

改变启动画面字体前景和背景:

vi /boot/grub/menu.lst
加入
foreground = ffffff
background = 000000

这一步是非必须的哦,我喜欢完美点,美化一下字体,配合配合图片.你可以用你要的色调,把色代码改了就是






#########grub
1 apt-get install grub
2 grub-install /dev/hda
3 update-grub
4 reboot


自已动手制作grub启动菜的单背景
作者:Linux伊甸园论坛 叶筱宇 文件/boot/grub/splash.xpm.gz 就是GRUB启动后的背景图象。 gzip -d splash.xpm.gz 然后再 more splash.xpm /* XPM */ static char * splash_xpm[] = { “640 480 15 1″, ” c None”, 发现了什么？我是从中知道了，这个图象是640*480象素的。１５，１，不太明白什么意思但大概和色位色深有关系（专业术语不太懂）。剩下的事，就是把自已喜欢的图片做成的640*480的，然后再用ＧＩＭＰ修改一下色深，好像是１４还是16 ，我记不太清了，自己试一下吧。最后将图片保存成*.xpm格式，而且要保证当用more查看该图片时，得到的信息为“640 480 15 1″（记得千成不能弄错了，因为错了的话，有可能会使GRUB垮掉而不能启动系统哦！）最后将制作成的图片改名为splash.xpm，放在/boot/grub文件夹下(不用管splash.xpm.gz) 怎么样，是不是觉得很棒呢！ 






修改grub启动时的背景图片

1　将一图片转化成640*480,14色的XPM文件：
　　　#convert abc.jpg -colors 14 -geometry 640x480! abc.xpm
2 压缩生成的xpm文件，使用gzip
#gzip -9 abc.xpm
3 将abc.xpm.gz拷到/boot/grub下
4　修改/boot/grub/menu.lst
splashimage=(hd0,0)/boot/grub/abc.xpm.gz 

引导装入工具Grub入门到精通

什么是 GRUB？

GRUB 是引导装入器 -- 它负责装入内核并引导 Linux 系统。GRUB 还可以引导其它操作系统，如 FreeBSD、NetBSD、OpenBSD、GNU HURD 和 DOS，以及 Windows 95、98、NT 和  2000。尽管引导操作系统看上去是件平凡且琐碎的任务，但它实际上很重要。如果引导装入器不能很好地完成工作或者不具有弹性，那么就可能锁住系统，而无法引导计算机。另外，好的引导装入器可以给您灵活性，让您可以在计算机上安装多个操作系统，而不必处理不必要的麻烦。
GRUB 是一个很棒的引导装入器。它有许多功能，可以使引导过程变得非常可靠。例如，它可以直接从 FAT、minix、FFS、ext2 或 ReiserFS 分区读取  Linux 内核。（AIX、SUN的系统？我还不知道能不能支持）这就意味着无论怎样它总能找到内核。另外，GRUB 有一个特殊的交互式控制台方式，可以让您手工装入内核并选择引导分区。这个功能是无价的：假设 GRUB 菜单配置不正确，但仍可以引导系统。哦，对了 -- GRUB 还有一个彩色引导菜单
Linux 世界在很长一段时间里一直使用 LILO 引导装入器，而且它可以让上百万的 Linux 用户引导系统。是的，的确是这样，LILO 很有效。但是，LILO 的维修率很高，而且很不灵活。与其花很多时间来描述 GRUB 的优点，还不如演示如何创建自己的  GRUB 引导盘以及如何使用它来引导系统。然后，我将说明 GRUB 的一些很“酷”的技术细节，并指导您完成将 GRUB 安装到 MBR（主引导记录）的过程，以使它成为缺省引导装入器。 
如果您有点胆小，不必害怕。可以学习前半部分，创建 GRUB 引导盘，尝试使用 GRUB 而不必弄乱现有的引导装入器。或者，可以用其安全的“驻留”方式来熟悉 GRUB。那么，让我们立即开始吧。
   
下载 GRUB

要开始探究 GRUB 的精妙之处，首先需要下载、编译和安装它。但不要害怕 -- 根本不会修改您的引导记录 -- 我们只是要编译和安装 GRUB，就像其它程序一样，在此过程中我们可以创建 GRUB 引导盘。请不要担心；在修改引导过程之前，我会告诉您。 
现在开始。访问 ftp://alpha.gnu.org/gnu/grub/ 并下载可以找到的最新版本的 GRUB tar 压缩包。我编写本教程时，最新的 tar 压缩包是 grub-0.5.96.1.tar.gz。下载了最新版本后，就可以安装了。

安装期

这里是从 tar 压缩包安装 GRUB 所需输入的命令。我将在 /tmp 中编译源文件，并将所有部分都安装到硬盘的 /usr 目录下。从 root 用户，输入以下命令： 
# cd /tmp
# tar zxvf /path/to/archive/here/grub-0.5.96.1.tar.gz
# cd grub-0.5.96.1
# ./configure --prefix=/usr
# make
# make install

现在已经安装了 GRUB，准备开始使用它。
 
制作引导盘

要制作引导盘，需执行一些简单的步骤。首先，在新的软盘上创建 ext2 文件系统。然后，将其安装，并将一些 GRUB 文件复制到该文件系统，最后运行 "grub" 程序，它将负责设置软盘的引导扇区。准备好了吗？


制作引导盘，第二部分

好，将一张空盘插入 1.44MB 软驱，输入： 
# mke2fs /dev/fd0
创建了 ext2 文件系统后，需要安装该文件系统： 
# mount /dev/fd0 /mnt/floppy
现在，需要创建一些目录，并将一些关键文件（原先安装 GRUB 时已安装了这些文件）复制到软盘： 
# mkdir /mnt/floppy/boot
# mkdir /mnt/floppy/boot/grub
# cp /usr/share/grub/i386-pc/stage1 /mnt/floppy/boot/grub
# cp /usr/share/grub/i386-pc/stage2 /mnt/floppy/boot/grub
只需要再有一个步骤，就能得到可用的引导盘。


制作引导盘，第三部分

解压、编译和安装 GRUB 源 tar压缩包时，会将程序 grub 放到 /usr/sbin 中。该程序非常有趣并值得注意，因为它实际上是  GRUB 引导装入器的半功能性版本。是的，尽管 Linux 已经启动并正在运行，您仍可以运行 GRUB 并执行某些任务，而且其界面与使用  GRUB 引导盘或将 GRUB 安装到硬盘 MBR 时看到的界面完全相同。 
这是有趣的设计策略，现在该使用驻留版本的 GRUB 来设置引导盘的引导扇区了。从 root 用户，输入 "grub"。GRUB 控制台将启动，显示如下： 
     GRUB  version 0.5.96.1  (640K lower / 3072K upper memory)
 [ Minimal BASH-like line editing is supported.  For the first word, TAB
   lists possible command completions.  Anywhere else TAB lists the possible
   completions of a device/filename. ]
grub> 
欢迎使用 GRUB 控制台。现在，研究命令。

  
制作引导盘，第四部分

在 grub> 提示符处，输入： 

grub> root (fd0)
grub> setup (fd0)
grub> quit

现在，引导盘完成了。在继续下一步骤之前，在看一下刚才输入的命令。第一个 "root" 命令告诉 GRUB 到哪里查找辅助文件 stage1 和  stage2。缺省情况下，GRUB 会在指定的分区或磁盘上的 /boot/grub 目录中进行查找。在安装引导盘时，也就是几分钟以前，我们已将这些文件复制到正确的位置。接着，输入了 setup 命令，它告诉 GRUB 将引导装入器安装到软盘的引导记录上；我们将在以后详细讨论这一过程。然后退出。现在，已经制作好引导盘，可以开始使用 GRUB 了。
使用 GRUB 引导系统之前，需要知道一些信息。首先，应知道哪个分区保存了 Linux 内核，以及 root 文件系统的分区名称。然后，应查看现有 LILO 配置来寻找需要传递给内核的变量，如 "mem=128M"。一旦获取了这些信息，就可以开始了?
要启动 GRUB，需要关闭系统并退出引导盘。如果由于某些原因而不能立即关闭系统（比如上班时在部门的服务器上测试 GRUB），那么只要在提示中输入 "grub" 并继续操作。所有程序的运行情况都不会改变，只是您不能执行引导（因为 Linux 正在运行）。
装入引导盘时，在屏幕顶部将出现一条消息，告诉您正在装入第一阶段和第二阶段。几秒后，将会出现一个熟悉的屏幕，显示如下： 
    GRUB  version 0.5.96.1  (640K lower / 3072K upper memory)
 [ Minimal BASH-like line editing is supported.  For the first word, TAB
   lists possible command completions.  Anywhere else TAB lists the possible
   completions of a device/filename. ]
grub> 
可以看到，这些内容与在 Linux 中以驻留方式运行 GRUB 时出现的消息完全相同 -- 只不过现在我们是使用 GRUB 来引导 Linux。
在 Linux  中，当谈到 "root" 文件系统时，通常是指主 Linux 分区。但是，GRUB 有它自己的 root 分区定义。GRUB 的 root 分区是保存 Linux 内核的分区。这可能是您的正式 root 文件系统，也可能不是。例如，在 Gentoo Linux 中，有一个单独的小分区专用于保存 Linux 内核与引导信息。大多数情况下，我们不安装这个分区，这样在系统意外崩溃或重新引导时，就不会把它弄乱。
这些，我们讨论的是 GRUB，需要指定 GRUB 的 root 分区。进入 root 分区时，GRUB 将把这个分区安装成只读型，这样就可以从该分区中装入  Linux 内核。GRUB 的一个很“酷”的功能是它可以读取本机的 FAT、FFS、minix、ext2 和 ReiserFS 分区，我们很快就会讨论这个功能。但现在，让我们输入 root 分区。在提示中输入 root，但不要按 Enter 键： 
 grub> root (
现在，按一次 Tab 键。如果系统中有多个硬盘，GRUB 将显示可能完成的列表，从 "hd0" 开始。如果只有一个硬盘，GRUB 将插入  "hd0,"。如果有多个硬盘，继续进行，在 ("hd2") 中输入名称并在名称后紧跟着输入逗号，但不要按 Enter 键。部分完成的  root 命令看起来如下： 
 grub> root (hd0,
现在，继续操作，再按一次 Tab 键。GRUB 将显示特定硬盘上所有分区的列表，以及它们的文件系统类型。在我的系统中，按 Tab 键时得到以下列表： 
 grub> root (hd0, (tab)
 Possible partitions are:
   Partition num: 0,  Filesystem type is ext2fs, partition type 0x83
   Partition num: 1,  Filesystem type unknown, partition type 0x82
   Partition num: 2,  Filesystem type unknown, partition type 0x7
   Partition num: 4,  Filesystem type is reiserfs, partition type 0x83
   Partition num: 5,  Filesystem type is reiserfs, partition type 0x83
如您所见，GRUB 的交互式硬盘和分区名称实现功能非常有条理。这些，只需要好好理解 GRUB 新奇的硬盘和分区命名语法，然后就可以继续操作了。

GRUB 命名约定
到目前为止，您可能会感到一点困惑，因为 GRUB 所使用的硬盘／分区命名约定与 Linux 使用的命名约定不同。在 Linux 中，第一个硬盘的第五个分区称作 "hda5"。而 GRUB 把这个分区称作 "(hd0,4)"。GRUB 对硬盘和分区的编号都是从 0 开始计算。另外，硬盘和分区都用逗号分隔，整个表达式用括号括起。现在，回来看一下 GRUB 提示，可以发现如果要引导 Linux 硬盘 hda5，应输入 "root  (hd0,4)"。如果已经明白了 GRUB 硬盘／分区命名，您也许要调整当前 root 命令行，以使它指向保存 Linux 内核的分区。按以下格式输完命令，然后按 Enter 键： 
 grub> root (hd0,4) (hit enter)
 Filesystem type is reiserfs, partition type 0x83

装入内核

现在已安装了 root 文件系统，到装入内核的时候了。在 GRUB 提示中，依次输入 "kernel"、空格、到内核的路径、空格、内核参数，如 root 参数（GRUB 将自动插入适当的 "mem=" 参数）。我在我的系统中输入： 
 grub> kernel /boot/bz2.4 root=/dev/hda5
   [Linux-bzImage, setup=0x1200, size=0xe1a30]
请留意 "root=" 内核参数，它非常重要。它应该指向保存 root 文件系统的 Linux 分区。您也许要写下到目前为止输入的命令，这样在教程后面讲述如何创建 GRUB 引导菜单时，就可以迅速找到它们。

Root，内核，引导！
您已经安装了 root 文件系统并装入了内核。现在，可以引导了。只要输入 "boot"，Linux 引导过程就将开始。

重新调查引导软盘
如果一切正常，就可以使用使用 GRUB 引导盘来引导当前 Linux 发行版。如您所见，GRUB 是功能非常强大的引导装入器，它让您可以随意动态配置以进行引导。我将向您介绍如何创建 GRUB 引导菜单，这样就可以从菜单中进行 OS 选择，而不是输入三行命令来引导 Linux。但在动手之前，现在是深入了解 GRUB 幕后是如何工作的好时机。我将说明引导盘引导过程的工作原理，这样您就可以对 GRUB 有一个更好的评价和了解。

两阶段过程
要制作引导软盘，需要做两件事 -- 将文件复制到软盘的 ext2 文件系统的 /boot/grub 目录中，运行 GRUB 的安装程序。运行  GRUB 安装程序时，GRUB 将 "stage 1" 装入器安装到软盘的引导记录中。它还将 stage 1 装入器配置成从 ext2 文件系统直接装入 stage2。通常，GRUB 通过在包含 stage2 数据的软盘上创建一列块来完成此操作，这样 stage1 装入 stage2  时不必知道 ext2 文件系统的任何情况。 
但是，大多数情况下，GRUB 在安装完 stage1 之后，会立即将 stage1.5  装入器安装到引导记录中。这个特殊的 stage1.5 允许无需使用原始块列表就能从 ext2 文件系统装入 stage2，却要更灵活的标准基于路径的方法。GRUB 理解文件系统结构的这一能力使 GRUB 比 LILO 更强壮。例如，如果正好在整理引导盘文件系统的碎片，stage1 就可以找到 stage2（归功于 ext2 stage1.5）。而 LILO 就不能完成此项操作。因为 LILO 只能依赖于映射文件，每次更新内核或在磁盘上物理移动数据时，即使不更改路径，也需要重新运行它。

阶段 1、1.5 和 2 第 3 页
您也许会想知道：如果使用 FAT 而不是 ext2 文件系统创建引导盘，GRUB 是否可以工作。是的，它可以工作，因为在输入 "setup (fd0)" 时， GRUB 会安装与 root 文件系统类型匹配的 stage1.5。即使没有没有空间可以安装 stage1.5，GRUB 仍可以通过追溯到更原始的块列表，来装入 stage2
搜索和恢复
在继续讨论之前，先研究一个与引导软盘相关的实用提示。由于 GRUB 的交互式性质，它为恢复软盘生成了一个很好的引导装入器。但是，如果将好的内核复制到引导盘上，那它就更好了。那样，即使硬盘上的内核坏了或者被意外删除了，也可以追溯到引导盘内核，并启动和运行系统。要将备用内核复制到引导盘，执行以下操作： 
# mount /dev/fd0 /mnt/floppy
# cp /path/to/bzImage /mnt/floppy/boot
# umount /dev/fd0
现在，软盘已包含备用内核，可以在 GRUB 中使用它来引导 Linux 发行版，操作如下： 
grub> root (fd0)
grub> kernel /boot/bzImage root=/dev/hda5 （将 /dev/hda5 更改成想要引导的分区名称）
grub> boot

硬盘引导
好，现在如何将 GRUB 安装到硬盘上？这个过程几乎与引导盘安装过程一样。首先，需要决定哪个硬盘分区将成为 root GRUB 分区。在这个分区上，创建 /boot/grub 目录，并将 stage1 和 stage2 文件从 /usr/share/grub/i386-pc 复制到该目录中。可以通过重新引导系统并使用引导盘，或者使用驻留版本的 GRUB 来执行后一步操作。在这两种情况下，启动 GRUB，并用 root 命令指定  root 分区。例如，如果将 stage1 和 stage2 文件复制到 hda5 的 /boot/grub 目录中，应输入 "root  (hd0,4)"。现在，只差一步。
接着，决定在哪里安装 GRUB -- 在硬盘的 MBR，或者如果与 GRUB 一起使用另一个“主”引导装入器，则安装在特定分区的引导记录中。如果安装到 MBR，则可以指定整个磁盘而不必指定分区，如下（对于 hda）： 
 grub> setup (hd0)
如果要将 GRUB 安装到 /dev/hda5 的引导记录中，应输入： 
 grub> setup (hd0,4)
现在，已安装 GRUB。引导系统时，应该立即以 GRUB 的控制台方式结束（如果安装到 MBR）。现在，应创建引导菜单，这样就不必在每次引导系统时都输入那些命令。

引导菜单

要创建菜单，只需在 /boot/grub 中创建一个简单的文本文件 menu.lst。如果将它放在正确位置，它将在 root GRUB 驱动器的  stage1 和 stage2 文件的旁边。这里是一个样本 menu.lst 文件，可以将它作为一个您的菜单的基础： 
default 0
timeout 30
color white/blue blue/green 

title=Boot Linux
root (hd0,4)
kernel /boot/bzImage root=/dev/hda5

title=Boot Linux using initrd
root (hd0,5)
kernel /boot/bzImage root=/dev/loop0 init=/initdisk.gz
initrd /initdisk.gz

title=Windows NT
root (hd0,3)
chainloader +1

我将在以下的屏面中说明 menu.lst 格式。

理解引导菜单
引导菜单很容易理解。前三行设置缺省菜单项（项目号 0，第一个）、设置超时值（30 秒），并选择整个菜单的一些颜色。 
接着的三行配置 "Boot Linux" 菜单项。要创建手工引导命令系列之外的菜单项，只要添加一行 "title=" 作为第一行，并从最后一行中除去 "boot" 命令（GRUB 会自动添加这个命令）。 
接着的四行显示了如何使用 GRUB 来引导 initrd（初始 root 磁盘），如果您愿意的话。现在，讨论最后三行……

链式装入器

这里是示例 menu.lst 的最后三行……
title=Windows NT
root (hd0,3)
chainloader +1
这里，我添加了一项来引导 Windows NT。要完成此操作，GRUB 使用了“链式装入器”。链式装入器从分区 (hd0,3) 的引导记录中装入  NT 自己的引导装入器，然后引导它。这就是这种技术叫做链式装入的原因 -- 它创建了一个从引导装入器到另一个的链。这种链式装入技术可以用于引导任何版本的 DOS 或 Windows。

GRUB 的弹性
GRUB 最好的优点之一就是其强健的设计 -- 在不断使用它时请别忘了这点。如果更新内核或更改它在磁盘上的位置，不必重新安装 GRUB。事实上，如有必要，只要更新 menu.lst 文件即可，一切将保持正常。 
只有少数情况下，才需要将 GRUB 引导装入器重新安装到引导记录。首先，如果更改 GRUB root 分区的分区类型（例如，从 ext2 改成  ReiserFS），则需要重新安装。或者，如果更新 /boot/grub 中的 stage1 和 stage2 文件，由于它们来自更新版本的  GRUB，很有可能要重新安装引导装入器。其它情况下，可以不必理睬！

在这里只是介绍了 GRUB 的一部分。如需所有 GRUB 功能的完整描述，请阅读 GRUB 出色的 GNU 文档。只要在 bash 提示中输入 "info grub" 就可以阅读该文档。 
希望fans喜欢本教程，喜欢 GRUB (Grand Unified Boot Loader) 的强大功能和灵活性！



 

　　grub> install (hd0,0)/boot/grub/stage1 (hd0) (hd0,0)/boot/grub/stage2
　　p (hd0,0)/boot/grub/menu.conf
GRUB学习笔记
作者：本站收集  来源：本站收集  发布时间：2005-11-13 23:11:43  发布人：21codes

减小字体 增大字体

　　声明:本笔记并非原创,只是我个人的学习笔记!
　　很多的内容来自www.linuxsir.com www.linuxfans.org www.linuxAID.com
　　非常感谢以上网站对我的学习提供的莫大的帮助,本着学习和分享的原则我贴出我的学习笔记,更希望兄弟们能给我指出其中错误的地方.谢谢!!!
　　学习这部分知识,首先要学到问题的思路,其次你还要记住一些东西,是死记硬背下来!你会发现这点东东的确是很有用的!
　　尽管如此,本文档归属linuxsir-probing!转载请注明出处!更不能被用到商业用途上!
　　1 首先要了解的几个概念
　　1.1 启动管理器
　　启动管理器是存储在磁盘开始扇区中的一段程序，例如，硬盘的MBR(Master Boot Record)，在系统完成启动测试后，如果系统是从MBR启动，则BIOS(Basic Input/Output System)将控制传送给MBR。然后存储在MBR中的这段程序将运行。这段程序被称为启动管理器。它的任务就是将控制传送给操作系统，完成启动过程》有许多可用的启动管理器，包括GNU GRUB (Grand Unified Boot Loader),Bootmanager, LILO (LInux LOader), NTLDR (boot loader for Windows NT systems)，等等等.
　　1.2 什么是GRUB?
　　grub 是一个多重启动管理器。grub是GRand Unified Bootloader的缩写，它可以在多个操作系统共存时选择引导哪个系统。它可以引导的操作系统包括：
　　Linux,FreeBSD,Solaris,NetBSD,BeOSi,OS/2,Windows95/98,Windows NT,Windows2000，WinXP。它可以载入操作系统的内核和初始化操作系统（如Linux,FreeBSD），或者把引导权交给操作系统（如Windows 98）来完成引导。
　　1.3 GRUB的特点
　　特别适用于linux与其它操作系统共存情况。
　　支持大硬盘 现在大多数Linux发行版本的lilo都有同样的一个问题：根分区(/boot分区)不能分在超过1024柱面的地方，一般是在8.4G左右的地方，否则lilo不能安装，或者安装后不能正确引导系统。而grub就不会出现这种情况，只要安装时你的大硬盘是在LBA模式下，grub就可以引导根分区在8G以外的操作系统。
　　支持开机画面 　 grub支持在引导开机的同时显示一个开机画面。对于玩家来说，这样可以制作自己的个性化开机画面；对于PC厂商，这样可以在开机时显示电脑的一些信息和厂商的标志等。grub支持640x480,800x600,1024x768各种模式的开机画面，而且可以自动侦测选择最佳模式，与Windows那 320x400的开机画面不可同日而语。
　　两种执行模式 grub不但可以通过配置文件进行例行的引导，还可以在选择引导前动态改变引导时的参数，还可以动态加载各种设备。例如你在Linux下编译了一个新的核心，但不能确定它能不能工作，你就可以在引导时动态改变grub的参数，尝试装载这个新的核心进行使用。Grub的命令行有非常强大的功能，而且支持如bash或doskey一样的历史功能，你可以用上下键来寻找以前的命令。
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
　　(注:在 Linux 中，当谈到 "root" 文件系统时，通常是指主 Linux 分区。但是，GRUB 有它自己的 root 分区定义。GRUB 的 root 分区是保存 Linux 内核的分区。这可能是您的正式 root 文件系统，也可能不是。我们讨论的是 GRUB，需要指定 GRUB 的 root 分区。进入 root 分区时，GRUB 将把这个分区安装成只读型，这样就可以从该分区中装入 Linux 内核。GRUB 的一个很“酷”的功能是它可以读取本机的 FAT、FFS、minix、ext2 和 ReiserFS 分区.到目前为止，您可能会感到一点疑惑，因为 GRUB 所使用的硬盘／分区命名约定与 Linux 使用的命名约定不同。在Linux 中，第一个硬盘的第五个分区称作 "hda5"。而 GRUB 把这个分区称作 "(hd0,4)"。GRUB 对硬盘和分区的编号都是从 0 开始计算。另外，硬盘和分区都用逗号分隔，整个表达式用括号括起。现在，可以发现如果要引导 Linux 硬盘 hda5，应输入 "root (hd0,4)"。
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
　　这个命令将输出所有的命令选项。现在可以使用????nable和????isable选项增加或
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
　　??A.通过调用内核本地启动
　　??B.连续启动或者将控制转给另一个引导器
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
　　注意:root和rootnoverify都是一样的，把rootnoverify改成root也行。不过经过实践来看。有时引导win时，系统安装好后，是rootnoverify (hdX.Y)这样形式的，这样会出现windows起不来，出现什么windows什么文件损坏的情况。这时，我们就要把在grub中，引导windows的那段中的rootnoverify改为root
　　root英文的意思就是根的意思，在这里是让linux知道自己所处的位置，也就是我们所安装linux的／根分区所在的位置 。
　　----
　　如果你安装了两个版本的Windows??????个是你自己用的，另一个给你的家人用的??????样第二个就无法安装，因为有提示说Windows已经安装了。
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
　　还有一个更重要的命令是“map”。当你有两块硬盘，一个无法从第二块硬盘启动的操作系统，例如Windows，就可以使用map命令。例如，你能够将hd0映射为hd1，将hd1映射为hd0。换句话说，你可以虚拟的交换两个硬盘而启动所需要的操作系统 。命令形式如下：
　　grub> map (hd0) (hd1)
　　grub> map (hd1) (hd0)
　　启动FreeBSD：
　　title FreeBSD 4.0
　　root (hd0,4,a)
　　kernel /boot/loader
　　boot
　　#----
　　这里我们调用了FreeBSD的启动管理器。Root (hd0,4,a)由四个参数，是因为FreeBSD对一个单独分区进行了虚拟分割。我们称根分区为“a”。如果FreeBSD占据了整个第二块硬盘，这里就应该是root (hd0,a)。这样，就不是调用内核而是调用FreeBSD的启动管理器，它要比调用内核更易使用。
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
　
