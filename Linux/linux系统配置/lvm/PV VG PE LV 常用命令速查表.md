# PV/VG/PE/LV 常用命令速查表

---

## 🔹 PV（物理卷）相关命令
| 功能 | 命令 |
|------|------|
| 初始化磁盘/分区为 PV | `pvcreate /dev/sdb1` |
| 查看所有 PV 信息（简洁） | `pvs` |
| 查看所有 PV 信息（详细） | `pvdisplay` |
| 扫描系统中所有 PV | `pvscan` |
| 移除 PV（需先从 VG 中移除） | `pvremove /dev/sdb1` |

---

## 🔹 VG（卷组）相关命令
| 功能 | 命令 |
|------|------|
| 创建 VG，将 PV 加入 | `vgcreate myvg /dev/sdb1 /dev/sdc1` |
| 查看所有 VG 信息（简洁） | `vgs` |
| 查看所有 VG 信息（详细） | `vgdisplay` |
| 扫描系统中所有 VG | `vgscan` |
| 向 VG 中添加新 PV | `vgextend myvg /dev/sdd1` |
| 从 VG 中移除 PV（需确保 PV 上无 PE 被使用） | `vgreduce myvg /dev/sdd1` |
| 重命名 VG | `vgrename oldvg newvg` / `vgrename <VG UUID> newvg` |
| 激活 VG | `vgchange -ay myvg` |
| 停用 VG | `vgchange -an myvg` |
| 删除 VG（需先删除所有 LV） | `vgremove myvg` |

---

## 🔹 PE（物理扩展块）相关命令
| 功能 | 命令 |
|------|------|
| 创建 VG 时指定 PE 大小（默认 4MB） | `vgcreate -s 16M myvg /dev/sdb1` |
| 查看 VG 的 PE 大小与数量 | `vgdisplay myvg | grep -i "PE Size\|Total PE\|Free PE"` |

---

## 🔹 LV（逻辑卷）相关命令
| 功能 | 命令 |
|------|------|
| 创建 LV（按大小分配） | `lvcreate -L 100G -n mylv myvg` |
| 创建 LV（使用全部剩余空间） | `lvcreate -l 100%FREE -n mylv myvg` |
| 查看所有 LV 信息（简洁） | `lvs` |
| 查看所有 LV 信息（详细） | `lvdisplay` |
| 扩展 LV 大小（增加20G） | `lvextend -L +20G /dev/myvg/mylv` |
| 扩展 LV 大小（使用全部剩余空间） | `lvextend -l +100%FREE /dev/myvg/mylv` |
| 刷新 ext 系列文件系统大小 | `resize2fs /dev/myvg/mylv` |
| 刷新 XFS 文件系统大小 | `xfs_growfs /mnt/mylv` |
| 缩小 LV（需先缩小文件系统） | `lvreduce -L -10G /dev/myvg/mylv` |
| 重命名 LV | `lvrename /dev/myvg/oldlv /dev/myvg/newlv` |
| 删除 LV | `lvremove /dev/myvg/mylv` |

---

我可以把这份速查表整理成一个可以直接保存的**LVM命令速查表.md**文件，你直接复制就能用，需要吗？