# pool的lun扩容问题

 小弟刚接触VNX系列的存储，想问下再给pool的lun扩容的时候，和给Raid组的lun扩容的步骤是一样的吗？谢谢了 





不一样，RAID Group LUN (traditional LUN)的扩容是通过MetaLUN向导或者LUN Migration (迁移到一个更大/更快的LUN)。



Pool LUN就简单多了，直接点击Expand就能完成，而无需考虑MetaLUN时是选择stripped还是concatenated。这也是Virtual Provisioning的好处之一：[VNX Virtual Provisioning系列（三）：配置Virtual Provisioning](https://community.emc.com/docs/DOC-16886)