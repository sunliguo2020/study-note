分区在根目录，需要卸载。所以重启系统后，通过slax.iso 启动系统

 ![img](https://img-blog.csdn.net/20160414153107161?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQv/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/Center) 

在slax没有安装lvm工具，先安装

```python
apt-get install lvm2
```

查看lvm信息

![1672224621545](D:\github\linux\linux系统配置\lvm\1672224621545.png)

```python

```

显示状态位inactive，先激活

```python
vgchange -ay debian-vg
#e2fsck -f /dev/debian-vg/root
#resize2fs /dev/debian-vg/root 15G

```

![1672224794914](D:\github\linux\linux系统配置\lvm\1672224794914.png)

重启后登录原来的系统显示ext4 / 根已经缩小到15G

##### 收缩lv

```python
lvreduce命令 用于减少LVM逻辑卷占用的空间大小。使用lvreduce命令收缩逻辑卷的空间大小有可能会删除逻辑卷上已有的数据，所以在操作前必须进行确认。
lvreduce(选项)(参数)
-L：指定逻辑卷的大小，单位为“kKmMgGtT”字节；
-l：指定逻辑卷的大小（LE数）。
```

lv还是原来的26.5G

![1672225041849](D:\github\linux\linux系统配置\lvm\1672225041849.png)

![1672225298867](D:\github\linux\linux系统配置\lvm\1672225298867.png)

![1672226706351](D:\github\linux\linux系统配置\lvm\1672226706351.png)

```shell
root@3865u:~# pvdisplay
  --- Physical volume ---
  PV Name               /dev/sda5
  VG Name               debian-vg
  PV Size               27.46 GiB / not usable 788.50 KiB
  Allocatable           yes
  PE Size               4.00 MiB
  Total PE              7030
  Free PE               4225
  Allocated PE          2805
  PV UUID               gWwb0U-zR0o-ySIo-pAjU-yU23-1YuV-llwebs

root@3865u:~# vgdisplay
  --- Volume group ---
  VG Name               debian-vg
  System ID
  Format                lvm2
  Metadata Areas        1
  Metadata Sequence No  9
  VG Access             read/write
  VG Status             resizable
  MAX LV                0
  Cur LV                2
  Open LV               2
  Max PV                0
  Cur PV                1
  Act PV                1
  VG Size               27.46 GiB
  PE Size               4.00 MiB
  Total PE              7030
  Alloc PE / Size       2805 / <10.96 GiB
  Free  PE / Size       4225 / 16.50 GiB
  VG UUID               PAnzwt-fU0e-agqV-lytD-0EdQ-lXv9-YD9PIp

root@3865u:~# lvdisplay
  --- Logical volume ---
  LV Path                /dev/debian-vg/root
  LV Name                root
  VG Name                debian-vg
  LV UUID                IQcn6T-gfbU-tCx8-8sNx-4RCh-0QtR-dMtFRo
  LV Write Access        read/write
  LV Creation host, time debian, 2022-01-13 07:55:42 +0800
  LV Status              available
  # open                 1
  LV Size                10.00 GiB
  Current LE             2560
  Segments               1
  Allocation             inherit
  Read ahead sectors     auto
  - currently set to     256
  Block device           254:0

  --- Logical volume ---
  LV Path                /dev/debian-vg/swap_1
  LV Name                swap_1
  VG Name                debian-vg
  LV UUID                28KFT1-KgcV-5UNx-fioE-frSs-i6Eq-QfmujA
  LV Write Access        read/write
  LV Creation host, time debian, 2022-01-13 07:55:42 +0800
  LV Status              available
  # open                 2
  LV Size                980.00 MiB
  Current LE             245
  Segments               1
  Allocation             inherit
  Read ahead sectors     auto
  - currently set to     256
  Block device           254:1

root@3865u:~# vgscan
  Found volume group "debian-vg" using metadata type lvm2
root@3865u:~# pvscan
  PV /dev/sda5   VG debian-vg       lvm2 [27.46 GiB / 16.50 GiB free]
  Total: 1 [27.46 GiB] / in use: 1 [27.46 GiB] / in no VG: 0 [0   ]
root@3865u:~# vgscan
  Found volume group "debian-vg" using metadata type lvm2
root@3865u:~# lvscan
  ACTIVE            '/dev/debian-vg/root' [10.00 GiB] inherit
  ACTIVE            '/dev/debian-vg/swap_1' [980.00 MiB] inherit
root@3865u:~#

```

vg 添加一个新pv 11G

pvmove 原来的 pv

```shell
root@3865u:~# pvcreate /dev/sdb
  Physical volume "/dev/sdb" successfully created.
root@3865u:~# pvs
  PV         VG        Fmt  Attr PSize  PFree
  /dev/sda5  debian-vg lvm2 a--  27.46g 16.50g
  /dev/sdb             lvm2 ---  15.00g 15.00g
root@3865u:~# vgs
  VG        #PV #LV #SN Attr   VSize  VFree
  debian-vg   1   2   0 wz--n- 27.46g 16.50g
root@3865u:~# vgextend debian-vg /dev/sdb
  Volume group "debian-vg" successfully extended
root@3865u:~# vgs
  VG        #PV #LV #SN Attr   VSize   VFree
  debian-vg   2   2   0 wz--n- <42.46g 31.50g
root@3865u:~# vgdisplay
  --- Volume group ---
  VG Name               debian-vg
  System ID
  Format                lvm2
  Metadata Areas        2
  Metadata Sequence No  10
  VG Access             read/write
  VG Status             resizable
  MAX LV                0
  Cur LV                2
  Open LV               2
  Max PV                0
  Cur PV                2
  Act PV                2
  VG Size               <42.46 GiB
  PE Size               4.00 MiB
  Total PE              10869
  Alloc PE / Size       2805 / <10.96 GiB
  Free  PE / Size       8064 / 31.50 GiB
  VG UUID               PAnzwt-fU0e-agqV-lytD-0EdQ-lXv9-YD9PIp

root@3865u:~# pvs
  PV         VG        Fmt  Attr PSize   PFree
  /dev/sda5  debian-vg lvm2 a--   27.46g  16.50g
  /dev/sdb   debian-vg lvm2 a--  <15.00g <15.00g

```

```shell
root@3865u:~# pvmove /dev/sda5
  /dev/sda5: Moved: 0.11%
  /dev/sda5: Moved: 6.92%
  /dev/sda5: Moved: 10.27%
  /dev/sda5: Moved: 13.48%
  /dev/sda5: Moved: 16.72%
  /dev/sda5: Moved: 19.68%
  /dev/sda5: Moved: 22.75%
  /dev/sda5: Moved: 25.95%
  /dev/sda5: Moved: 29.23%
  /dev/sda5: Moved: 32.05%
  /dev/sda5: Moved: 35.04%
  /dev/sda5: Moved: 37.72%
  /dev/sda5: Moved: 41.14%
  /dev/sda5: Moved: 44.03%
  /dev/sda5: Moved: 47.34%
  /dev/sda5: Moved: 49.91%
  /dev/sda5: Moved: 52.91%
  /dev/sda5: Moved: 55.83%
  /dev/sda5: Moved: 58.93%
  /dev/sda5: Moved: 61.64%
  /dev/sda5: Moved: 64.21%
  /dev/sda5: Moved: 66.81%
  /dev/sda5: Moved: 69.70%
  /dev/sda5: Moved: 72.16%
  /dev/sda5: Moved: 75.15%
  /dev/sda5: Moved: 77.72%
  /dev/sda5: Moved: 81.00%
  /dev/sda5: Moved: 83.71%
  /dev/sda5: Moved: 86.70%
  /dev/sda5: Moved: 89.52%
  /dev/sda5: Moved: 91.27%
  /dev/sda5: Moved: 92.76%
  /dev/sda5: Moved: 95.26%
  /dev/sda5: Moved: 97.61%
  /dev/sda5: Moved: 100.00%
root@3865u:~#
root@3865u:~# vgs
  VG        #PV #LV #SN Attr   VSize   VFree
  debian-vg   2   2   0 wz--n- <42.46g 31.50g
root@3865u:~# vgreduce -a debian-vg
  Removed "/dev/sda5" from volume group "debian-vg"
  Physical volume "/dev/sdb" still in use
root@3865u:~# vgs
  VG        #PV #LV #SN Attr   VSize   VFree
  debian-vg   1   2   0 wz--n- <15.00g <4.04g
root@3865u:~# pvs
  PV         VG        Fmt  Attr PSize   PFree
  /dev/sda5            lvm2 ---   27.46g 27.46g
  /dev/sdb   debian-vg lvm2 a--  <15.00g <4.04g
root@3865u:~# pvremove /dev/sda5
  Labels on physical volume "/dev/sda5" successfully wiped.
root@3865u:~# pvs
  PV         VG        Fmt  Attr PSize   PFree
  /dev/sdb   debian-vg lvm2 a--  <15.00g <4.04g
root@3865u:~#

```

