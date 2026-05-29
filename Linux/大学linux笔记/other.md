山东经济学院18-7信箱
  iamsunliguo@163.com
http://sunligo.ik8.com
444709033 
6034296
la9943355
069013

备份DBR(系统引导记录)：Ctrl+R查看硬盘扇区，柱面0、磁头1、扇区1为系统引导记录，选择“另存为”，输入文件名，回车完成备份。
※小知识※
   得到整GB分区：众所周知，1G等于1024M，但是当你分区时输入1024时，得到的却不是整1G分区，那么怎样才能得到整GB分区呢？运算方法如下:b=(a-1)×4+1024×a ;其中b为应该输入的数值，单位为M，a为希望得到的整数分区容量，单位为G，如想得到一个整2G分区，那么就应该输入(2-1)×4+1024×2=2052 .


df    磁盘使用状况

#cd /dev
#mkfs.ext3 -b 1024 /dev/ram3
# mount /dev/ram3 /mnt/m
# mkfs.ext3 -b 1024 -i 8196 /dev/ram4


metstat -a


soa 指示该区的权威
ns 列出该区的一个名字服务器
A 名字到地址的映射
PTR 地址到名字的映射
cname 别名


rpm qa

fdisk
说明：fdisk /dev/hda1

mkfs
说明：建立文件系统
mkfs -t ext3 /dev/hda2
mkfs -V-t msdos -c /dve/hda5

fsck
超级使用者
检查与修复linux 档案系统，可以同时检查一个或多个linux 档案系统
fsck －tmsdos －a /dev/hda5


试验一：将内存格式化后，挂载文件系统
 ls /dev/ram*
mount /dev/ram15 /mnt/ram15


ls
-l 长列表
－a 所有文件
－R

改变目录权限的命令
chown 
chgrp
chmod


useradd 
psswd


cp
mv
ln
mkdir -p
rm
more
du
df
where

find 
tar
/etc/httpd
http.conf
doucument


文件系统常见命令：
df －a 目录
df －k
df －T文件系统类型
df －i i结点
df －x 不显示文件系统的使用

du －sk /root
du -hm /etc

cal

dmsesg
touch 
uname -a

文件管理命令:
cp
mv
ln  -s 软链接 可以跨分区
ln 硬链接 不可以跨分区
mkdir -p 建立一连串目录
rm -rf
more
du -h
df -h
whereis ls

Find 命令详解:
find /tmp -atime 7 -print 7天打印目录
find /usr/src -name core -exec rm {} \ ;
find /home -name "*.jpg" -size 100k

tar 命令详解:

tar -cvfz test.tar.gz /
tar -xvfz

ps 进程管理:

-a 列出带有控制终端的全部进程,不仅仅是当前用户的进程
-r 只列出正在运行中的进程
-k 列出没有控制终端的进程

ps -aux |grep 
ls -l |wc -l
kill 

uname -a linux 版本信息
su -

用户重要配置文件
/home
/etc/passwd
/etc/shadow
/etc/group

grub修复
cd /mnt/sysimage
cd sbin
方法一:./grub-install /dev/hda
方法二:./grub
root (hd0,o)
setup(hd0)
kernel /vmlinuz-2.4.20-80
initrd /initrd-2.4.20-8.img
boot
复原root的密码:
e ,b
vi  /etc/pass


agp aperture size 128M 内存的一半
agp transfer mode 8x 
agp fast 



setup
service network restart
/etc/

发送消息：

wall < 文件名
gcc --version
ls /lib/libc-*


vi helloworld.c
#include<stdio.h>
int main(int argc,char**argv)
{
	printf("helloworld!\n");
	return 0;


}
gcc -o helloworld helloword.c 



计算机操作系统:
 计算机操作系统是方便用户,管理和控制计算机软硬件资源的系统软件(或程序集合)

操作系统目前有五大类型(批处理.分时.实时.网络和分布式)和五大功能(作业管理.文件管理.
存储管理.设备管理和进程管理)


文件系统:
文件系统=文件管理程序(文件和目录的集合)+它所管理的全部文件
是用户与外存的接口.
系统软件为用户提供统一方法(以数据记录的逻辑单位),访问存储在物理介质上的信息.


文件系统的特点:
使用方便,灵活,用户按名存取

itraf 网络监视软件;
/misc
是个空目录,供管理员放公共杂物.默认权限是全部用户都可以读取和执行文件,但是只有管理员能够写入文件.
ksnapshot 超级抓图工具

