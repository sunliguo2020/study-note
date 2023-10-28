¿¿Linux¿¿¿¿¿¿
¿¿USB¿¿¿¿¿¿(¿¿)¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿32MB¿64MB¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿PC¿¿¿¿¿¿¿¿¿¿¿¿¿¿BIOS¿¿¿USB¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Windows
98¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Windows98¿¿¿¿¿¿¿¿¿¿¿¿¿linux¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿RedHat 8.0¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux¿¿¿¿
¿¿¿¿¿¿¿¿¿e3¿bvi¿Liuux¿¿¿
¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿USB¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux-2.4.20¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿SCSI¿¿¿usbcore¿usb-storage¿Loopback
device support¿RAM disk
support¿initrd¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿usb-storage¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿initrd.img¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
/sbin/init¿,¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿/sbin/init¿¿¿¿¿¿¿¿¿¿¿¿initrd.img¿¿¿¿¿¿¿¿¿¿¿initrd.img¿¿¿¿¿¿¿¿¿3¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿/sbin/init¿¿¿¿¿¿¿¿¿¿¿¿
1.¿¿initrd.img¿¿
 ¿¿# mkdir -p /mnt/initrd ¿¿
     # cd /tmp
 ¿¿# mkinitrd  /tmp/initrd.gz 2.4.20-usb ¿¿
2.¿¿initrd.img¿¿¿¿¿¿¿¿¿linuxrc ¿¿
  #gunzip initrd.gz ¿¿
  # mount -o loop /tmp/initrd /mnt/initrd ¿¿
 # cp /sbin/busybox /mnt/initrd/bin ¿
¿# cd /mnt/initrd/bin ¿¿
 # ln -s busybox sleep ¿¿
 # vi /mnt/initrd/linuxrc ¿
 ¿¿¿¿¿¿¿¿ ¿¿
   echo 'wait 3 seconds.....' 
¿¿/bin/sleep 3
¿¿3.¿¿¿¿initrd.img¿¿¿¿
¿¿¿¿¿¿¿initrd¿¿¿¿¿(¿4MB)¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
¿¿# mkdir -p /mnt/initrdusb ¿
 ¿ # cd /tmp ¿
 ¿# dd if =/dev/zero of=/tmp/initrdusb bs=1M count=1 ¿¿
    # mke2fs -m 0 initrdusb ¿¿
 # mount -o loop /tmp/initrdusb /mnt/initrdusb ¿¿
# cp -a /mnt/initrd/* /mnt/initrdusb ¿¿
 #umount /mnt/initrd ¿
¿# umount /mnt/initrdusb ¿
¿# cd /tmp ¿¿
# gzip -9  initrdusb ¿
¿# cp initrdusb.gz /boot/initrd-2.4.20-usb.img
¿¿4.¿¿¿¿¿¿¿¿¿¿¿¿¿
¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
¿¿¿¿¿¿¿¿¿
1.¿¿¿¿¿¿¿¿¿
¿¿¿¿Linux¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿ ¿¿
#modprobe usb-storage ¿¿
# fdisk -l /dev/sda ¿
¿Disk /dev/sda: 16 heads, 63
sectors, 126 cylinders ¿¿Units = cylinders of 1008 * 512 bytes ¿¿Device
Boot Start End Blocks Id System ¿
  ¿/dev/sda1 1 102 51376+ 6 FAT16
¿¿/dev/sda2 103 126 12096 83 Linux ¿
¿¿¿¿¿¿¿¿¿¿¿¿¿¿Windows98¿¿¿¿¿¿¿¿¿¿63¿¿¿¿¿¿¿¿fdisk¿x¿¿¿¿¿¿heads¿sectors¿cylinders¿¿¿¿¿2.¿¿¿¿¿ext2¿¿
¿¿# mke2fs -m 0 /dev/sda2 ¿¿
   # mkdir -p /mnt/sda2 ¿¿
  # mount /dev/sda2 /mnt/sda2 ¿
  ¿# cd /mnt/sda2
¿¿3.¿¿boot¿¿¿¿
 ¿¿¿¿¿¿¿¿initrd-2.4.20-usb.img¿¿¿¿¿boot¿¿¿¿¿¿¿¿¿¿¿¿lib/modules¿¿,¿¿¿
/boot/grub¿¿¿¿¿¿boot¿¿,¿¿boot/grub/menu.lst¿¿,¿¿¿¿:
¿¿timeout 10 ¿
  ¿color 0x17 0x70 ¿¿
     default 0 ¿¿
   title Windows 98
¿  ¿rootnoverify (hd0,0) ¿
    ¿makeactive ¿
    ¿chainloader +1 ¿¿
title GNU/Linux Redhat 8.0 (2.4.20-usb) 
   root (hd0,1) ¿¿kernel /boot/vmlinuz-2.4.20-usb ro
  root=/dev/sda2 ¿¿initrd /boot/initrd-2.4.20-usb.img
¿
  ¿¿¿grub,¿¿¿¿¿¿¿ ¿¿
   grub> root (hd1,1) ¿
  ¿grub> setup (hd1)
¿¿4.¿¿bin¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿insmod¿fsck¿mkdosfs¿¿¿¿¿¿¿¿¿¿¿¿¿ldd¿¿¿¿¿¿¿¿¿¿¿,¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿lib¿¿¿
¿¿¿¿¿¿¿¿¿¿¿,¿¿busybox¿¿¿¿¿¿¿¿¿Linux¿¿¿¿¿¿¿¿¿busybox¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux¿¿¿¿cat¿init¿ifconig¿route¿
¿ln  -s  busybox¿¿¿¿¿¿¿¿¿¿¿¿
¿¿¿¿¿¿¿¿¿¿¿¿busybox¿¿¿vi¿¿¿¿¿¿¿¿¿¿¿¿e3¿¿vi¿¿
¿¿¿¿¿¿¿¿bash¿¿¿¿¿¿¿¿¿/etc/termcap¿¿¿¿¿¿
¿¿/bin/bash ¿¿/etc/termcap ¿¿/usr/share/terminfo/l/linux
¿¿/usr/share/terminfo/k/klone+acs ¿¿/usr/share/terminfo/k/klone+color
¿¿/usr/share/terminfo/k/klone+sgr ¿¿
 5.¿¿dev¿¿ ¿
 ¿¿¿cp -a¿¿¿¿¿¿¿¿¿¿¿,¿¿console¿tty1¿tty2¿tty3sda¿sda1¿sda2¿hda¿hdb¿hda1¿¿¿¿¿¿¿¿6.¿¿etc/init.d/rcS
¿¿¿¿¿¿¿ ¿¿
  #!/bin/sh ¿¿
 PATH=/sbin:/bin ¿¿
 export PATH ¿¿
 mount -n -t proc none /proc ¿
¿umount /initrd ¿¿
mount -n -o remount,rw / ¿¿
mount -n -o remount,rw -t proc none /proc ¿
¿ifconfig lo 127.0.0.1

¿¿7.¿¿etc/fstab¿¿ ¿¿¿¿¿¿¿ ¿¿
    /dev/sda2 / ext2 defaults 1 1
¿¿none /proc proc defaults 0 0
¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Linux¿¿A(IP=192.168.100.5)¿¿¿¿
¿¿$ tar cf - win98 | nc -l -p 5555
¿¿¿¿¿¿¿¿¿¿B¿¿¿¿¿¿¿¿¿¿telnet¿¿¿¿¿A¿¿¿¿¿¿¿¿¿¿¿¿¿B¿¿¿¿¿¿¿¿¿¿
¿¿# mount -t vfat -o codepage=938,iocharset=cp936 /dev/hda5 /mnt/2dos ¿¿#
cd /mnt/2dos ¿¿# modprobe eepro00 ¿¿# ifconfig eth0 192.168.1.10 ¿¿#
route add default gw 192.168.1.1 ¿¿# ping 192.168.10.5 ¿¿# nc 192.168.10.5
5555 | tar xf - ¿¿¿¿¿¿¿¿format /s¿¿¿¿¿¿¿¿Windows
98¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿ ¿¿# mkdosfs -F 16 /dev/sda1
¿¿# xxd -c 16 /dev/sda1 | less ¿¿¿¿¿¿¿Boot
Record¿32¿35¿¿¿¿¿¿¿¿60 91 01
00¿¿4¿¿¿¿¿¿FAT¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Windows
98¿¿¿¿¿¿¿¿Linux¿bvi¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Boot
Record¿32¿35¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿Windows¿¿¿¿Linux¿¿¿¿
