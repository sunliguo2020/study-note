LVM 逻辑卷管理器

LVM1 ---> LVM2
 vgconvert -M2 vg0
初始化分区 pv (phisical volume)
pvcreate /dev/hda1 /dev/hda2 /dev/hda3
pv (Phisical Volume)
vgscan 读取物理分区 lvm数据库文件
创建卷组
vgcreate vg0 /dev/hda1 /dev/hda2
卷组VG (Volume Group)
逻辑卷 lv (logical volume)
 -n name -L 大小 
lvcreate -n data -L 10M vg0
lv改名 
  lvrename vg0 lv0 lvnew
扩大卷组vg  
 pvcreate /dev/hda3
 vgextend vg0 /dev/hda3
移除vg
  umount lv
  lvremove /dev/vg0/lv0
  vgremove vg0
移动
pvmove /dev/hda1 [/dev/hdb1]
扩展卷  lv
  lvextend  在扩展逻辑卷中的文件系统
  lvextend -L 8G /dev/vg0/lv0
  lvextend -L +5G /dev/vg0/lv0
  resize2fs /dev/vg0/lv0 
减小逻辑卷
  lvreduce 
  #umount
   umount /dev/vg0/lv0
   e2fsck -f /dev/vg0/lv0
   resize2fs /dev/vg0/lv0 30G
   lvreduce -L -7.26G vg0/lv0
   lvreduce -L -50M /dev/vg0/lv0
删除物理卷
  例：一个卷组包含两个80G的磁盘，希望将他们替换成160G的磁盘。不能删除LV中正在使用的PV。
  可以先用pvmove，释放在线的pv。
  pvmove 的唯一要求是，vg中连续空闲区段的数量必须等于要从pv中删除的区段数量.
  pvdisplay -m 
  释放之前禁止PV的分配
    pvchange -xn /dev/hda5
    pvmove /dev/hda5 /dev/hda6 将VG中pv hda5的内容搬移到hda6中
    pvmove /dev/hda5 lvm决定将hda5的内容被复制到哪里
    vgreduce vg0 /dev/hda5
