#create a mout point:
 mkdir /tmp/ramdisk0
#create a filesystem:
 mke2fs /dev/ram0
#mount the ramdisk:
 mount /dev/ram0 /tmp/ramdisk0
