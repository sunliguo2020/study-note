使用Linux备份Windows 


 
利用Linux下强大的备份工具tar程序来备份Windows，不但操作简单，备份、还原速度快，而且还能压缩。只要Linux分区空间足够大，想备份多大就备份多大。根据我个人的测试，tar可以将原文件压缩为原来的62%～64%，更为重要的是把备份保存在Linux分区上，无须担心病毒感染。 运用此法的前提是安装了Linux和Windows双操作系统，而且 
Linux分区下有足够的空间用来保存备份（Linux要平稳良好地运行必须有占其分区大小20%～30%的空闲空间。我使用Red Hat 7.3预留空间为4GB）。我建议最好是安装好Windows和Linux后，立刻备份Windows。使用Linux备份Windows具体操作如下。 创建Windows和备份目录 首先从Linux启动，然后进入Linux的虚拟终端Cxterm、konsole或rxvt，



在根目录下运行下面代码： #mkdir /mnt/windows 
创建Windows的挂接目录： 
#mkdir ./Backup 
注意，这两项操作皆在root目录下进行。然后创建备份文件目录，“./”表示当前目录。 


挂接Windows分区 运行下面代码挂接Windows分区： 

#mount -t vfat /dev/hda1 /mnt/windows 
其中，mount的-t参数是指定所要挂接文件系统的类型，vfat表示所要挂接的文件系统为Windows的FAT32，/dev/hda1是Windows所在的分区，可以根据系统的实际情况来确定。
 进入/mnt/windows目录 运行下面代码进入/mnt/windows目录：
 #cd /mnt/windows 用ls -lF命令查看该目录是否出现了Windows的文件和目录，如没有看到可以回到/root目录下重新挂接一下。
这一步主要是为了验证文件系统是否良好挂接。注意，要挂接的文件系统必须有/root权限。


 备份系统 运行下面代码备份系统：
 #cd /mnt/windows/
 #tar zcvf ./Backup/Windows.tar.gz ./* 这时虚拟终端上会出现详细的备份信息，备份结束就会在/backup目录下看到红色的windows.tar.gz备份文件。这时看一看是不是比原文件小了许多。 还原备份 重复前三步进入/mnt/windows目录删除原系统： #rm -rf ./* 这样就还原系统： # tar zxvf /root/Backup/Windows.tar.gz 注意，还原路径一定要正确。重启后即可进入Windows的备份。 经过多次试验，此法比较可靠，但有时也会丢失一些“小东西”，如“显示桌面”（或其它任务栏快捷方式）和“My Pictures”（WinMe）中的图片。事先可将Windows\Application Data\Microsoft\Internet Explorer\Quick Lanch下的快捷方式和My Documents\My Pictures下的图片备份到其它分区，待恢复后再考回来即可解决问题。   
