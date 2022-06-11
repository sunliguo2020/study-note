LINUX中dd命令的使用

内容：
cd /bootls显示:boot.b               kernel.h     module-info-2.4.20-8  vmlinuzchain.b              lost+found   os2_d.b               vmlinuz-2.4.20-8config-2.4.20-8      message      System.mapgrub                 message.ja   System.map-2.4.20-8initrd-2.4.20-8.img  module-info  vmlinux-2.4.20-8
继续输入rdev vmlinuz /dev/hda8   //rdev 是设备管理命令
dd if=vmlinuz of=/dev/fdo   //制作LINUX引导盘
dd if=boot.b of=cc.dd    //制作镜像
mount -r /dev/hda5 /mnt/ht    //挂载fat32里的逻辑分区到 /mnt/ht文件夹里
md5sum boot.b cc.dd    //md5进行校验



Linux/UNIX命令dd简介
dd 是 Linux/UNIX 下的一个非常有用的命令，作用是用指定大小的块拷贝一个文件，并在拷贝的同时进行指定的转换。
dd - convert and copy a file
dd 的主要选项：指定数字的地方若以下列字符结尾乘以相应的数字:b=512, c=1, k=1024, w=2, xm=number m
if=file输入文件名，缺省为标准输入。
of=file输出文件名，缺省为标准输出。
ibs=bytes一次读入 bytes 个字节(即一个块大小为 bytes 个字节)。
obs=bytes一次写 bytes 个字节(即一个块大小为 bytes 个字节)。
bs=bytes同时设置读写块的大小为 bytes ，可代替 ibs 和 obs 。
cbs=bytes一次转换 bytes 个字节，即转换缓冲区大小。
skip=blocks从输入文件开头跳过 blocks 个块后再开始复制。
seek=blocks从输出文件开头跳过 blocks 个块后再开始复制。(通常只有当输出文件是磁盘或磁带时才有效)
count=blocks仅拷贝 blocks 个块，块大小等于 ibs 指定的字节数。
conv=conversion[,conversion...]用指定的参数转换文件。
转换参数:
ascii 转换 EBCDIC 为 ASCII。
ebcdic 转换 ASCII 为 EBCDIC。
ibm 转换 ASCII 为 alternate EBCDIC.
block 把每一行转换为长度为 cbs 的记录，不足部分用空格填充。
unblock使每一行的长度都为 cbs ，不足部分用空格填充。
lcase 把大写字符转换为小写字符。
ucase 把小写字符转换为大写字符。
swab 交换输入的每对字节。 Unlike theUnix dd, this works when an odd number ofbytes are read. If the input file containsan odd number of bytes, the last byte issimply copied (since there is nothing toswap it with).
noerror出错时不停止。
notrunc不截短输出文件。
sync 把每个输入块填充到ibs个字节，不足部分用空(NUL)字符补齐。
由于 dd 命令允许二进制方式读写，所以特别适合在原始物理设备上进行输入/输出。
例如可以用下面的命令为软盘建立镜像文件：
dd if=/dev/fd0 of=disk.img bs=1440k
有趣的是，这个镜像文件能被 HD-Copy ，Winimage 等工具软件读出。
再如把第一个硬盘的前512 个字节存为一个文件：dd if=/dev/hda of=disk.mbr bs=512 count=1 
