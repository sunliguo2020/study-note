### VMware vCenter Server Apliance忘记密码

##### 重置root密码

1、进入单用户模式

a、重启，grub进入编辑模式

b、添加启动参数 init=/bin/bash

c、b 启动

2、重置root密码

```
mount -o remount,rw /
passwd root
reboot
```

#### 常见问题

- GRUB密码，默认为vmware
- 密码策略 

#### 重置SSO密码

ssh 登录root

```bash
/usr/lib/vmware-vmdir/bin/vdcadmintool 
3

```

