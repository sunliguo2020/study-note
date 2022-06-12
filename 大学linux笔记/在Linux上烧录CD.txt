 在Linux上烧录CD

    Linux 为创建 CD 提供了功能强大且灵活的工具。您可以创建在几乎任何平台上都可读的盘，还可以创建 .iso 文件以供下载和分发。

在任何平台上从命令行烧录 CD 都是一件令人费解且烦躁的事情，Linux 当然也不例外。不过，由于在各平台上所用到的命令和术语都十分相似，因此学习一下如何在 Linux 上刻录 CD 还是十分有用的。许多 Linux 软件都是通过 .iso 映像分发的，因此如果您知道如何烧录 CD，就可以下载 .iso 来创建您自己的安装盘。

Linux 和 Windows 都有可录 CD 的程序可用，但 Linux 版本比起 Windows 版本来功能更强大通用性也更好。在本文中，我们将研究 Linux CD 刻录命令中的两个主力： mkisofs 和 cdrecord 。 mkisofs 创建预先录制的映像，来生成 ISO9660/JOLIET/HFS 混合文件系统。它同时创建和填充文件系统。与其它数据存储介质（如硬盘驱动器和软盘驱动器）不同，CD 上的文件系统并不是先创建后填充数据的。CD-R 只有一次机会：首先格式化将会创建一个带有空文件系统的盘。 cdrecord 命令在 橙皮书（Orange Book）CD-R/RW 上刻录数据，这差不多就是其全部工作了。

由于采用了诸如 CD 刻录之类的新兴技术，最好使用这些程序的较新版本。 mkisofs 和 cdrecord 的版本都应该至少已经达到了 1.10。 cdrecord 的最新版本 V2.0 已经被重命名为 cdrtools 。要查明机器上所安装的版本，请输入：
$ cdrecord --version

和
$ mkisofs --version

对于那些刚接触可刻录 CD 的人而言，在我们继续之前，有几样东西是值得先了解一下的：

    * CD-R：可刻录 CD（CD-Recordable）。它们是 WORM（写一次，读多次，Write Once, Read Many）。
    * CD-RW：可重写 CD（CD-Rewritable）。它们是 WMRM（写多次，读多次，Write Many, Read Many）。
    * CD-R 的使用很广泛，在任何 CD-ROM 驱动器上都应该可读。
    * CD-RW 在所有现代驱动器上都应该可读。驱动器必须是“多格式读取的（multiread）”，以便能够读取 CD-R 和 CD-RW 盘。较老的驱动器会出问题。扔掉那个 4 倍速的旧驱动器，买个新的；用不着发火。
    * 商用 CD 不是用激光烧录成的，而是压制而成的。
    * 哪一种 CD-R/RW 驱动器最好呢？随便请教普通的硬件评论员，让他们给您一些建议。

下面是与文件格式有关的一些术语：

    * 黄皮书（Yellow Book）：数据 CD 的物理格式
    * 橙皮书：可刻录 CD 的物理格式：
          o 第一部分：CD-MO（磁-光，Magneto-Optical）
          o 第二部分：CD-WO（写一次，Write-Once；包括 PhotoCD 的“混合”规范）
          o 第三部分：CD-RW（可重写，Re-writable） 
    * ISO-9660：旧的文件布局标准，它只允许 8.3 格式的文件名
    * Rock Ridge：是对 ISO-9660 的扩展，它允许长文件名和 UNIX 样式的符号链接；保留了所有文件属性，如所有权和许可权。在 Windows 系统上读盘时，不会显示 UNIX 文件的属性。
    * Joliet：Microsoft 对 ISO 9660 文件系统的扩展，它允许在文件名中使用 Unicode 字符，同样也允许长文件名。为了与 MS-DOS 兼容，它还创建截断的文件名（这些看起来怪怪的样子：FILENA~1.TXT）。它允许文件名长达 64 个字符（包括空格），Windows 95 或更高版本以及运行 Joliet 卷访问（Joliet Volume Access）扩展的 Macintosh 计算机都可以读取它。Macs 不会读取长度超过 31 个字符的 Joliet 文件名。
    * El Torito：可引导 CD-ROM（Bootable CD-ROM）格式规范
    * HFS（分层文件系统，Hierarchical File System）：Macintosh 使用的本机文件系统
    * 多段刻录（Multisession）：允许多次添加文件，而不是只允许在单个段中添加文件。要使盘可读，就必须“关闭”段。但是，这却导致不能向盘中添加更多文件。多段刻录将单个段链接起来，然后更新盘的目录，使得它好象一个目录一样。
    * CD-UDF（通用盘格式，Universal Disk Format）：业界标准递增包写文件系统（incremental packet-writing filesystem） 

对 UDF 的一点简单说明：UDF 意味着能够直接将文件放入盘。目前，这是在软件级别上完成的。读取该盘需要用来创建该盘的软件。计划将 UDF 添加到 Linux 内核（可能是 2.6）。要实现这一点，CD 驱动器需要具有 CD-MRW 电路（“CD Mount Rainier ReWrite”；不要问我他们为什么取这么个名字），因此它将是新型驱动器的一项功能。当这一点得到实现时，向 CD-R/RW 中复制文件将和向软盘中复制文件一样容易，而且这些盘将普遍可读。而且，它还被吹捧为古老的 3.5" 软盘的另一种替代品。我们将拭目以待。（请参阅参考资料以获取到更多有关 Mount Rainier 的信息的链接。）

Linux SCSI 仿真冒险

如果可以的话，请使用 IDE/ATAPI 或 SCSI CD 刻录机。并口接口是一种会给您添麻烦的棘手玩意儿，而 USB 驱动器则很慢。在 Linux 中它们都得不到很好的支持（虽然对于较新的 USB 2.0 驱动器，您的运气可能会好一些）。

IDE/ATAPI 驱动器最为常见，但使用起来却需要做些调整。那么，如果 cdrecord 显示没有配置任何驱动器，会发生什么事情呢？要想检查是否配置有驱动器，请输入以下命令：
$ cdrecord -scanbus

如果命令显示了 CD-RW 驱动器（请参阅后面的 烧录盘），那么您可以跳过这一节的大部分，尽管您可能还是都想浏览一下这些内容，以便有所了解。

Linux 使用 SCSI 仿真子系统，因此 IDE/ATAPI CD 刻录机需要兼容性驱动程序。如果同一台 PC 上既有 CD-ROM 也有 CD-R/RW，那么二者都需要 ide-scsi 伪设备驱动程序来支持盘的复制。在 CD-ROM 上使用 SCSI 仿真没有什么不利之处；它同样能工作；只是名称会改变。驱动器的名称将会随 Linux 的具体分发版而有所不同，其名称可以是 /dev/cdrom0、/dev/hdc 或 /dev/scd0（要获得 IDE/ATAPI 设备名列表，请参阅表 1）。

表 1. IDE/ATAPI 设备名
名称 	设备
hda 	IDE 总线／连接器 0 主设备
hdb 	IDE 总线／连接器 0 从属设备
hdc 	IDE 总线／连接器 1 主设备
hdd 	IDE 总线／连接器 1 从属设备

要找到系统上的驱动器，请输入：
$ dmesg | grep '^hd.:'

hda: IBM-DTLA-305020, ATA DISK drive
hdb: TOSHIBA DVD-ROM SD-M1202, ATAPI CD/DVD-ROM drive
hdc: LITE-ON LTR-24102B, ATAPI CD/DVD-ROM drive
hda: 40188960 sectors (20577 MB) w/380KiB Cache, CHS=2501/255/63, UDMA(66)

大多数现代 Linux 都包含了已编译进内核的 SCSI 仿真：
$ locate ide-scsi.o

/lib/modules/2.4.19/kernel/drivers/scsi/ide-scsi.o

如果您的系统不是这样的，那么您就必须将它编译到您的内核中。对于这篇篇幅有限的文章来说，那是一个过大的主题，因此请参阅 参考资料（当您知道如何做时，您会发现它并不难）。

您需要编辑两个文本文件来配置系统，让它使用 ide-scsi 驱动程序。第一个是 /etc/modules.conf（在 Debian 中是 /etc/modules）。我的系统有一个 CD-ROM 和一个 CD-R/RW 驱动器，设备分别是 hdb 和 hdc。使用适合于您系统的值，将这两行添加到 /etc/modules.conf（或 /etc/modules）：
ide-cd ignore=\"hdb hdc\"
ide-scsi

缺省情况下，IDE 子系统将所有的 ATA 设备声明为它自己的设备，因此 ignore 这一行使得 SCSI 子系统既能抓取 CD-R/RW 也能抓取 CD-ROM。

接下来，为您的引导装载程序（GRUB 或 LILO）编辑配置文件。对于 LILO 用户，请将下面两行添加到 lilo.conf 的末尾：
append="hdb=ide-scsi"
append="hdc=ide-scsi"

对于 GRUB 用户，请将下面这行添加到 /etc/grub.conf（或者 Debian 中的 /boot/grub/menu.lst）中 kernel 这行的末尾：
hdb=scsi hdc=scsi

现在重新引导，并验证它是否已装入：
$ lsmod

这条命令将返回一个长列表；请查找 ide-scsi。

创建 .iso 文件

一旦选择了您想复制的文件，对 CD 进行刻录就只有两步：用 mkisofs 创建 .iso，然后用 cdrecord 将这些文件烧录进盘中。使用以下命令来创建 .iso 文件：

$ mkisofs -o test.iso -Jrv -V test_disk /home/carla/

在上面的示例中：

    * -o 为新的 .iso 映像文件命名（test.iso）
    * -J 为了与 Windows 兼容而使用 Joliet 命名记录
    * -r 为了与 UNIX/Linux 兼容而使用 Rock Ridge 命名约定，它使所有文件都公共可读
    * -v 设置详细模式，以便在创建映像时获得运行注释
    * -V 提供了卷标识（test_disk）；该标识就是出现在 Windows 资源管理器中的盘名
    * 列表中的最后一项是选择要打包到 .iso 中的文件（都在 /home/carla/ 中）

现在，挂装 .iso 来进行验证；我喜欢创建一个测试目录：

$ mkdir /test_iso
$ mount -t iso9660 -o ro,loop=/dev/loop0 test.iso /test_iso

查看目录的内容；所有的文件都应该在那里，并且都可读。否则，就是映像坏掉了，如果您将它烧录到盘上，那么您最终将得到一个刻录失败的光盘。

烧录盘

将映像写到盘中再简单不过了。首先，找到 CD-R/RW 的 SCSI 地址：

$ cdrecord -scanbus

Cdrecord 1.10 (i686-pc-linux-gnu) Copyright (C) 1995-2001 Jrg Schilling
Linux sg driver version: 3.1.24
Using libscg version 'schily-0.5'
scsibus0:
0,0,0 0) 'TOSHIBA ' 'DVD-ROM SD-M1202' '1020' Removable CD-ROM
0,1,0 1) 'LITE-ON ' 'LTR-24102B ' '5S54' Removable CD-ROM
0,2,0 2) *
0,3,0 3) *
0,4,0 4) *
0,5,0 5) *
0,6,0 6) *
0,7,0 7) *

每一项的前三个数字分别指 SCSI 总线、设备标识和 LUN（逻辑单元号，Logical Unit Number）。（第四个数字也是设备标识。） cdrecord 需要这三个数字。在上面的示例中，CD 刻录机是 0,1,0。SCSI 总线 0 上的设备都可以缩写为 1,0，即省去头一个 0。这是一个公共约定。如果有其它总线的话，则必须指定 — 没有快捷方式。

现在向盘中写内容：

$ cdrecord -v -eject speed=8 dev=0,1,0 test.iso

在上面的示例中：

    * -v 指详细方式
    * -eject 在完成写任务后弹出盘
    * -speed 指定写速度（8）
    * -dev 是从 cdrecord -scanbus 获得的设备号（0,1,0）
    * 最后一个是所烧录的映像的名称（test.iso）

对于创建用于公用分发的盘，这是一种简单且可用的方法，因为它创建了可以在任何 Windows 或 Linux 系统上读取的盘。 mkisofs 本身就非常适合于创建供下载的 .iso，而且 mkisofs 可以为许多平台创建文件系统。请参阅 mkisofs 联机帮助页以获取更多信息。

在一台运行速度极快且内存很大的机器上，您可以在刻录期间从容地处理非 CPU 密集型任务，但是在烧录盘期间最好别做别的事情。激光器不能先停下来，然后从停下来的地方重新开始，所以任何中断都是致命的。

cdrecord 将试图以最快速度运行刻录机，因此不必指定速度，但是，应该根据经验来判断如何做。指定较慢的速度对于纠正错误和缓冲区欠载运行很有用。采用“burn- proof”技术的新型驱动器（开发这项技术的初衷与它现在的名字正好相反；同样，谁取的这些名称呢？）不会有老式驱动器那样的缓冲区欠载运行烦恼。

复制盘

要直接将内容从源盘复制到可刻录盘，请使用下面的命令：

$ cdrecord -v dev=0,1,0 speed=4 -isosize /dev/scd0

这条命令直接将 CD-ROM 即 /dev/scd0 的内容“流”入 CD 刻录机 dev=0,1,0。不要在速度慢的旧机器上这么做。直接复制速度很快，但却更容易出错。更好的做法是：先将源盘的内容复制到硬盘驱动器，再从硬盘驱动器复制到 CD 刻录机：

$ mount /cdrom
$ dd if=/dev/scd0 of=/tmp/diskfile.iso
$ cdrecord dev=0,1,0 speed=8 fs=8m -v -eject -dummy /tmp/diskfile.iso

请注意两个新选项 fs=8m 和 -dummy 。 fs=8m 定义了环形缓冲区的大小：在一定程度上，越大越好。记住，中断是致命的；如果什么东西让数据传送慢下来了，那么 fs=8m 将创建一个足够大的缓冲区来让刻录机保持运行。如果 8 MB 还不够，那么您可能需要一台更好的 PC。另一方面，超过 8 MB 也不一定更好，因为操作系统重新装入 MMU（内存管理单元，Memory Management Unit）表时会浪费时间。缺省值是 4 MB。

-dummy 是一个了不起的选项，可以用它来先进行一次“排练”，然后在实际的盘上冒险。刻录机执行一切操作，但是不打开激光头，这使用户有机会在将内容提交到盘上之前捕获错误。

多段刻录

CD 由段构建而成，而段由磁道构成。只有一个段的盘上有一个导入点、一个 TOC（目录，table of content）、数据和一个导出点，导出点标记着这张盘的终点，并阻止在这张盘上进行进一步的刻录。 mkisofs 将单独段链接在一起。用 GUI 程序（如 X-CD-Roast 或 KonCD）创建多段刻录盘可能要更容易一些，但这里演示的是如何用命令行工具完成这一任务。

第一次在盘上刻录一个段时，请在 cdrecord 中使用 -multi 开关：

$ cdrecord -v -eject speed=8 dev=0,1,0 -multi test.iso

盘将会以某种方式被固定下来，使得盘可读，也可以添加更多数据。要向这张盘中添加更多段， mkisofs 需要知道起始扇区号和结束扇区号，可以象下面这样来找到这些号码：

$ cdrecord dev=0,1,0 -msinfo
0,27139

确保把要添加数据的盘放入了 CD 刻录机。然后，添加两个新开关 -C 和 -M ：

$ mkisofs -o test2.iso -Jr -V Session2 -C 0,27139 -M 0,1,0 /files/path/

或者更好的办法是，让命令 shell 完成这项工作：

$ mkisofs -o test2.iso -Jr -V Session2 -C `cdrecord dev=0,1,0 -msinfo` -M 0,1,0 /files/path/

多段刻录 CD 驱动器读取已写入的最后一个段。上面的命令从最后一个段获取 TOC，然后将它组合进新 TOC 中。在刻录盘上的最后一个段时，请省略 -multi 选项。

结束语

Linux 中的 CD 刻录功能强大且全面。CD 刻录机可以跨越网络共享，还可用于自动备份； mkisofs 和 cdrecord 也能用于 DVD。虽然有许多优秀的图形前端程序，但是完整的功能在命令行程序上。 