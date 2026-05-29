改变tty的分辨率
默认kernel给的tty分辨率是非常有限的（哈哈，什么有限，其实就是小，忒小了），而现在的显示器海大，hoho～，
所以对于工作在文本模式的朋友来说修改tty的分辨率是非常必要的，别白瞎了这个显示了嘿。
解决的方法就是给kernel传递VGA参数
1，lilo下设置方法
lilo:linux vga=318
将会启动1024x768x24bpp模式。附件是常用分辨率＋色彩所对应的编码
如果要默认就设置为1024x768x24bpp模式，可以修改/etc/lilo.conf，加入一下语句：
vga=0x318
然后保存退出，重启即可。

2，GRUB下设置方法
就是在grub的menu.lst启动列表的kernel最后添加vga参数，例如将tty分辨率设置为(1024x768x65536)
menu.lst位于/boot/grub/menu.lst

title Red Hat Linux (2.4.20-8)
        root (hd0,0)
	        kernel /vmlinuz-2.4.20-8 ro root=LABEL=/ vga=791
	        initrd /initrd-2.4.20-8.img
以下是常用参数列表
linux video=vga16 (640x480x16) <---默认的就是用的这个参数，支持最普通的硬件：）
linux vga=769 (640x480x256)
linux vga=771 (800x600x256)
linux vga=773 (1024x768x256)
linux vga=791 (1024x768x65536)
linux vga=775 (1280x1024x256)
