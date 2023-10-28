snmpwalk -v 1或2c(代表SNMP版本) -c SNMP密码 IP地址 OID(对象标示符)
 
–v：指定snmp的版本, 1或者2c，该参数必须有。
–c：指定连接设备SNMP读密码，该参数必须有。
IP：指定要walk的设备的IP地址，该参数必须有。
OID：代表要获取设备的指标oid，该参数不是必须的。

snmpwalk -v2c -c ruijie 172.22.41.20 ifPhysAddress

针对普通网络设备的端口，MIB的相关定义是Interface组，主要管理如下信息：
ifIndex 端口索引号
ifDescr 端口描述
ifType 端口类型
ifMtu 最大传输包字节数
ifSpeed 端口速度
ifPhysAddress 物理地址
ifOperStatus 操作状态
ifLastChange 上次状态更新时间
*ifInOctets 输入字节数
*ifInUcastPkts 输入非广播包数
*ifInNUcastPkts 输入广播包数
*ifInDiscards 输入包丢弃数
*ifInErrors 输入包错误数
*ifInUnknownProtos 输入未知协议包数
*ifOutOctets 输出字节数
*ifOutUcastPkts 输出非广播包数
*ifOutNUcastPkts 输出广播包数
*ifOutDiscards 输出包丢弃数
*ifOutErrors 输出包错误数
ifOutQLen 输出队长
其中，*号标识的是与网络流量有关的信息。