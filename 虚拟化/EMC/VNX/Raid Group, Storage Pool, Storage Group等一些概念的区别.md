EMC产品自带的帮助文档通常都有非常详尽的介绍，下面简单说一下几个主要的存储概念：



RAID Group：简单来说，RAID Group就是将多个硬盘组合起来的一个集合，以实现更大容量、更快读写速度、更高冗余度等目的。常见的RAID Group类型有RAID 0、RAID 1、RAID 1/0、RAID 3、RAID 5、RAID 6。



#### LUN：

LUN是位于RAID Group之上的逻辑结构。LUN可以被添加进主机中，并被主机视作物理硬盘使用。如图所示，是一个由四块硬盘组成的RAID 5 Group，其上创建了三个LUN，LUN 1、 LUN 2、 LUN3：



#### Storage Group：

为了实现LUN Masking (LUN的安全屏蔽机制，

即1. 仅将LUN分配给特定的主机；

2. 阻止主机看到存储中所有的LUN)，需要有一个容器来”存放”LUN与主机的关系，
3. 这个容器就是Storage Group。

先创建一个Storage Group，再连接进主机(Connect Hosts)，然后将LUN添加进这个Storage Group，主机就可以看到添加进去的LUN。下图为CLARiiON Unisphere界面中Storage Group视图：



#### Storage Pool：

Pool的概念是为了实现存储虚拟化(Storage Virtualization)而诞生的。对CLARiiON来说，就是其引入的Virtual Provisioning (虚拟资源分配)功能。该功能可以让用户在Pool中创建Thin或者Thick LUN来分配存储资源。Thin和Thick LUN都能够以较简便地方式进行创建、扩容和压缩操作。Thin LUN允许分配比存储上实际物理占用空间更多的可用空间给主机(高存储效率)，而Think LUN在创建时会预留占用被分配的全部空间(高且可预测的性能)。



传统FLARE LUN、Thick LUN和Thin LUN的主要限制和区别如下：

功能	传统FLARE LUN	Thick LUN	Thin LUN
性能	最好	最好	非性能优先业务
硬盘数量限制	16	Pool硬盘数量限制 (整个存储硬盘数减去5块Vault盘)	Pool硬盘数量限制 (120或整个存储硬盘数减去5块Vault盘)
RAID类型	全部	5, 6, 1/0	5, 6, 1/0
Read Cache (读缓存)	√	√	√
Write Cache (写缓存)	√	√	√
Expand (LUN扩展)	通过MetaLUN的方式	√	√
Shrink (LUN压缩)	√	√	√
Spin Down (磁盘省电模式)	√	

Data Compression (数据压缩)	√	√	√
Auto-Tier (自动存储分层)	
√	√
Reserved LUN Pool (保留LUN Pool)	√	√	
Write Intent Log (MirrorView写日志)	√	

Clone Private LUN (克隆私有LUN)	√	

Snaps / Clones (快照/克隆镜像)	√	√	√
MirrorView (CLARiiON远程复制软件)	√	√	√
SAN Copy (CLARiiON远程复制软件)	√	√	√


使用Pool功能对CLARiiON的版本有要求，建议升级到FLARE 30版本以获得对Pool的完整支持。后续VNX系列就都支持了。



理解了上述概念，相信您在实际应用中，应该能知道如何为自己的主机添加LUN了。

