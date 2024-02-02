### 问题产生

给openmediavault系统重新用磁盘镜像的方式做了系统备份。但是无法引导系统。开机提示GRUB。

### 解决办法

用openmediavault的安装程序重新引导。进入grub程序

```shell
grub> ls  #查看现有磁盘及分区
grub> set root=(hd0,gpt2) #指定根目录
grub> /  #查看该目录下文件信息，如果该目录下有boot、etc等文件夹，那就是要找的分区
grub> set root=(hd0,gpt2)  #指定目标目录
grub> set prefix=(hd0,gpt2)/boot/grub
grub> insmod normal
grub> normal
```
输入完成后，安装界面会多出几个选项。选择debian后引导进入系统。

根据实际情况重新写入引导

```
sudo update-grub
sudo grub-install /dev/sda
```



