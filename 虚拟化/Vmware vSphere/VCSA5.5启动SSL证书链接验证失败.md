### 原因

- 证书过期 VMCA根证书有效期1年
- 证书和主机名不匹配
- 时间不同步

### 解决方案

- 强制重建VMCA证书
- 

```
localhost:/usr/lib/vmware-vmdir/bin # ./vdcadmintool


==================
Please select:
0. exit
1. Test LDAP connectivity
2. Force start replication cycle
3. Reset account password
4. Set log level and mask
5. Set vmdir state
==================

3
  Account DN: administrator@vsphere.local
VmDirForceResetPassword failed (9100)


```

