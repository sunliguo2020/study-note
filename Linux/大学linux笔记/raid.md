raid 0 
  High speed
  Unsafe 
raid 1 
  Safe
  Low speed
raid 5 
   Safer than RAID 0
   Higher speed than RAID 1
raid 0 striping 
raid 0+1 

raidtools 应用软件

软件RAID 设备文件名：
/dev/mdN(N=0,1,2--)

软件RAID设备可以当做分区看待,需要格式化后挂载
#mkfs.ext3 /dev/md1
#mount /dev/md1 /opt
创建过程：

  1: 添加硬盘
    RAID 设备的成员是硬盘分区，需要先对硬盘分区，分区不能在同一个物理硬盘上
  2: 安装raidtools
  3:编写配置文件: /etc/raidtab
    可以从raidtools的示例文件复制
  4: 创建RAID设备
     mkraid /dev/md0

1: fdisk /dev/sdc
2: mdadm -C /dev/md0 -l 0 -n 2 /dev/sdc1 /dev/sdc2
   mdadm -C -v /dev/mdx -lY -nZ RAID成员
   mdadm --create --verbose /dev/mdx --level=Y --RAID-devices=Z RAID成员

 查看RAID的信息：
   mdadm -Ds /dev/md0
   mdadm -D /dev/md0
 -E or --examine 检测当前的块设备上是否有阵列的元数据信息
  mdadm -E /dev/sdc1

  mdadm /dev/md0 -f /dev/sdc1 //--fail
  表示把一个设备列为有问题的设备，以便用-r或--remove 参数移除。
  mdadm /dev/md0 -r RAID 成员  //移除
  mdadm /dev/md0 -a /dev/sdc5  // 添加
mdadm 参数 [RAID设备] [RAID成员]

  -A 或 --assemble 激活一个RAID
  -S 或 --stop 停止
  -s 或 --scan 扫描
  -D 或 --detail 察看RAID的详细信息
  --examine 察看RAID成员的详细信息
  mdadm -As
  mdadm -Ss
  mdadm -Ds
  mdadm --examine /dev/sdb
 RAID的启动方法：
  1：不通过读取mdadm.conf来启动RAID 
    mdadm -A RAID设备 RAID成员
    mdadm -A /dev/md0 /dev/sdb /dev/sdc
  2:利用配置好的/etc/mdadm.conf
    mdadm -A RAID设备
    mdadm -As

  mdadm -Ds>/etc/mdadm.conf
