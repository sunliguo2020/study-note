#### 说明

根据需要扩展的 LUN 类型，无论是 LUN 还是 MelaLUN，请遵循下面正确的存储池 LUN 或 RAID 组 LUN 过程进行操作。



####  **Unisphere**

（VNX1 和 VNX2 阵列的过程相同）



**存储池 LUN**

- 存储池 LUN 可以通过 Unisphere 使用 2 个选项进行扩展：
  1.  “Storage”-->“LUNs”
  2. “Storage”-->“Storage Configuration”-->“Storage Pools”

但是，为了确保您知道其上创建 LUN 的存储对象，戴尔推荐使用选项 2，因此说明中假设使用的是选项 2。
 

1. 导航至“Storage Pools”

- “Storage”-->“Storage Configuration”-->“Storage Pools”

1. 选择 LUN 所在的存储池。
2. 在“Details”面板下的“LUN”选项卡中，右键单击要扩展的 LUN。
3. 选择“Expand”
4. 在选择所需的配置后，请单击“OK”

- 如果尝试扩展的 LUN 正在参与任何分层应用程序（快照、克隆、SAN 复制、MirrorView），则您必须先从分层应用程序中删除该 LUN，然后才能对其进行扩展。
- 如果尝试扩展的 LUN 已在迁移或扩展，则您必须等到操作完成后才能扩展该 LUN。
- 如果您不确定如何解决这些错误，我们推荐您联系戴尔支持人员以获得相关解释说明。

1. 屏幕刷新，并且该 LUN 在“User Capacity”下面显示新的大小

**RAID 组 LUN**

要扩展 RAID 组 LUN，您必须创建 MetaLUN。
MetaLUN 是将多个 LUN 组合在一起以增加 LUN 空间的容器。
MetaLUN 由基本 LUN（需要扩展的 LUN）以及一个或多个组件 LUN（为创建 MetaLUN 而要添加的 LUN，可增加 LUN 的大小）组成。
在创建 MetaLUN 之前，请参阅[在 VNX 或 CLARiiON 阵列上创建 MetaLUN 的最佳实践](https://www.dell.com/support/kbdoc/zh-cn/000029105/clariion-vnx-best-practices-for-creating-metaluns-on-vnx-or-clariion-arrays-customer-correctable)（英文版），以确保在创建 MetaLUN 时遵循戴尔最佳实践进行操作。

- RAID 组 LUN 可以通过 Unisphere 使用三个选项进行扩展：

1. “Storage”-->“LUNs”
2. “Storage”-->“Storage Configuration”-->“Storage Pools”-->“RAID Groups”选项卡
3. RAID 组 LUN 扩展向导（位于“Wizards”面板下，处于“Storage”选项卡下的任何区域中）

但是，为了确保您知道其上创建 LUN 的存储对象，戴尔推荐使用选项 2，因此说明中假设使用的是选项 2。
在尝试扩展 RAID 组 LUN 之前，请确保在所需位置创建具有要扩展的所需大小的 RAID 组 LUN。

1. 导航至“RAID Groups”

- “Storage”-->“Storage Configuration”-->“Storage Pools”-->“RAID Groups”选项卡。

1. 右键单击要扩展的所需 RAID 组 LUN。
2. 选择“Expand”。
3. 选择所需的 LUN 扩展类型

- **Striping：**随着所有其他主轴式硬盘共享数据，性能也随之提高。但是，由于您必须将数据重新条带化，因此无法立即获得额外的空间。
- **Concatenation：**立即获得额外的空间。但是，这不会提高性能。

1. 选择“Next”
2. 选择要添加到基本 LUN 的所需的组件 LUN。
3. 选择“Next”
4. 选择所需的 LUN 用户容量。

- **Current Capacity：**在组件 LUN 添加额外空间之前，相关 LUN 的容量。

- **Maximum Capacity：**总可用容量，其中包括通过添加组件 LUN 创建的额外空间。

- Other Capacity：

  这是手动分配的容量，而且不能是十进制值。

  - 无论在创建 MetaLUN 期间选择的用户容量如何，在创建 MetaLUN 后，都可以随时增加用户容量（最多增加到 MetaLUN 的最大大小）。

1. 选择“Next”
2. 选择所需的 LUN 设置。

- **MetaLUN Name：**新创建的 MetaLUN 所需的名称。默认情况下，选择基本 LUN 的名称。
- **Default Owner：**SP 分配的 MetaLUN 的所有权
- **Expansion Rate：**组件 LUN 扩展基本 LUN 的速率
- **Element Size：**元素大小的乘数。默认选项为 4，这会导致条带元素大小为 512 字节。
- **Enable Auto Assign：**在选中后，允许自动分配 MetaLUN 的 SP 所有权。

1. 选择“Next”
2. 验证所需的 MetaLUN 设置。
3. 选择“Finish”
4. 当您完成操作后，请选择“Finish”

- 完成 MetaLUN 后，MetaLUN 在“RAID Group”选项卡下将不可见。
- 您可在“LUNs”部分中看到 MetaLUN。
  - “Storage”-->“LUNs”

**NaviSecCLI**（VNX1 和 VNX2 阵列的过程相同）


**存储池 LUN**

Naviseccli“**lun -expand**”可让您扩展池 LUN。此命令对经典 LUN 不起作用。如果指定的新容量大于现有容量并且满足扩展要求，则 LUN 将会扩展。如果新容量小于现有容量，则屏幕会显示错误消息。

通过 NaviSecCLI 扩展池 LUN 所需的最小语法是：


lun -expand -l *lunNumber* -capacity

​            *或者*

lun -expand -name *lunName* -capacity
 

可与“**lun -expand**”命令配合使用的常见选项：

- **-l：**指定 LUN 编号。有效值是表示现有 LUN 的编号
- **-name：**指定 LUN 名称。该名称在池 LUN 中必须是唯一的。如果试图扩展含有空格字符的 LUN，则该 LUN 名称必须用引号括起来。
- **-capacity：**指定 LUN 的新容量。新容量必须大于现有容量，才能进行 LUN 扩展。
- **-sq mb|gb|tb|bc：**指定容量的大小限定符。有效值为 mb、gb、tb、bc。默认值为 GB。

还有其他选项可与“**lun -expand**”命令配合使用，您可在适用的 CLI 指南中找到它们。（下面提供了链接）

**RAID 组 LUN**

Naviseccli 命令“**metalun -expand**”可创建新的 MetaLUN 或扩展现有 MetaLUN 的容量。

通过 NaviSecCLI 扩展 RAID 组 LUN 所需的最小语法是：
 

metalun -expand - base *number|WWN* -lus *number|WWN*

 
可与“**lun -expand**”命令配合使用的常见选项： 

- **-base**：指定要扩展的 LUN 或 MetaLUN 的唯一编号或全球通用名称。
- **-lus**：指定要添加到 LUN 或 MetaLUN 的 LUN 的 LUN 编号或全球通用名称。
- **-cap tb|gb|mb|bc**：指定 MetaLUN 中可用空间的容量。容量必须小于 MetaLUN 组件的最大容量，并且大于或等于当前容量（添加 LUN 之前的 LUN 或 MetaLUN 的用户容量）。默认值是 MetaLUN 的最大容量（现有 LUN 和任何新 LUN 的总容量）。
- **-name**：指定 MetaLUN 的名称。如果您不指定名称，则它默认为主 LUN 的名称。
- **-sq**：指定 MetaLUN 组件容量的大小限定符。其中：tb 等于太字节、gb 等于吉字节、mb 等于兆字节、bc 等于块数。 
- **-type C|S**：将 MetaLUN 的扩展类型设置为“concatenate”或“stripe”。默认扩展类型为“stripe”。C 将扩展类型设置为“concatenate”。S 将扩展类型设置为“stripe”。 

还有其他选项可与“**metalun -expand**”命令配合使用，您可在适用的 CLI 指南中找到它们。

**VNX1 阵列：**[VNX Block 5.32 命令行界面参考（英文版）](https://support.emc.com/docu41553_VNX-Command-Line-Interface-Reference-for-Block.pdf?language=en_US)
**VNX2 阵列：**[VNX Block 5.33 命令行界面参考（英文版）](https://support.emc.com/docu47580_VNX-Command-Line-Interface-Reference-for-Block-5.33.pdf?language=en_US)



#### 其他信息

提醒：
扩展 LUN 也称为创建 MetaLUN。
没有 MetaLUN 按钮可供选择，菜单中也没有 MetaLUN 一词可供选择。