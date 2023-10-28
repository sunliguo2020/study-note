dd命令是linux下一个非常有用的磁盘命令。它可以将指定大小的块拷贝成一个文件，并在拷贝的同时执行指定的转换。由于dd命令允许
二进制读写，所以特别适合在原始物理设备上进行输入/输出操作。下面介绍几则dd命令的使用技巧。 
一、为软盘创建镜像文件
      使用如下命令创建软盘镜像。
      #dd if=/dev/fd0 of=disk.img bs=1440k
      使用dd命令制作出的软盘镜像文件能在HD-Copy或winimage下使用。

二、制作优盘启动盘
      首先打开linux的安装光盘，将images目录下的diskboot.img文件复制到/root目录下，然后将优盘挂载到/dev/sdb，然后执行如下命令即可：
      #dd if=/root/diskboot.img of=/dev/sdb bs=125682176
      优盘需要为引导型并且要分出引导分区。

三、使用windows引导linux
      提取引导文件
      #dd if=/dev/hda3 of=/bootsect.lnx bs=512 count=1
      编辑boot.ini文件
      将上面生成的bootsect.lnx文件复制到c:\下，并在boot.ini文件中增加一行：c:\bootsect.lnx="Linux"

四、备份还原硬盘主引导记录
      1、备份硬盘主引导记录
           #dd if=/dev/hda of=/disk.mbr bs=512 count=1
      2、还原硬盘主引导记录
           #dd if=/disk.mbr of=/dev/hda bs=512 count=1