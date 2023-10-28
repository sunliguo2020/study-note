引导linux的几种方法(2004-4-12)



引导linux方法，我所知的有如下几种：
方法1：引导软盘
(1)在linux下用mkbootdisk制作。
(2)如果硬盘引导信息丢失，无法进入Linux系统做引导软盘，对于RH，用RedHat linux光盘引导进入secure模式，当询问是否将硬盘中的linux系统设置为当前环境，选“是”，这时的系统进入到硬盘的linux环境，运行mkbootdisk，做一个启动盘。
(3)取相同版本的linux的启动软盘，修改syslinux.cfg文件中的“root=/dev/hdXX”为你的hdaX、hdbX、.... 也行！

方法2：dos方式：
在第一张光盘的里几个文件拷贝到硬盘的同一个目录里：
dosutils目录：loadlin.exe
isolinux目录：initrd.img、vmlinuz
然后在这个目录里建立一个批处理文件xxx.bat：
loadlin vmlinuz root=/dev/hdXX
loadlin vmlinuz initrd=initrd.img
（hdXX代表你的linux所在分区！具体是hda1、hda2、...要看你安装的分区了。）
启动到dos（不要加载其他驱动、设置），进入那个目录执行批处理文件，应该能进入了！

方法3：用WindowsNT loader(NT引导菜单)
如果你安装了windowsNT、2000、XP、...可以在linux下执行：
dd if=/dev/hdxx of=bootsect.lnx count=1 bs=512
将bootsect.lnx拷贝到C:\下。修改C:\boot.ini，增加一行内容，看上去是这样的：
[boot loader]
timeout=10
default=multi(0)disk(0)rdisk(0)partition(1)\WINNT
[operating systems]
multi(0)disk(0)rdisk(0)partition(1)\WINNT="Microsoft Windows 2000 Professional" /fastdetect
C:\bootsect.lnx="Red Hat 9"
启动NT（2000、XP...）可看见选择菜单！ 

方法4：用光盘引导
用光盘直接引导系统，在boot提示后输入：
vmlinuz root=/dev/hdXX
(hdXX是你要引导的Linux分区。)
