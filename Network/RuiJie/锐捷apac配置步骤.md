# 基本思路
## 地址规划
vlan 规划

vlan 1000 设备管理vlan

vlan 1001 AP vlan

无线用户vlan ：210


## 1、地址分配
ap地址的获取，
用户地址的获取

ap自动获取到ip地址，在获取ip的时候，有个option 138 指明ac的ip地址。

然后ap和ac就可以通信了。
## 2、ap交换机管理

## 3、无线信号管理
在ac上无线信号，包括配置用户的vlan，ssid 密码等。


几个DHCP

*   ap 设备自动获取ip

    *   ap交换机端口设置的native vlan 即为ap设备的vlan
*   无线用户自动获取ip

    *   需要在ap上配置
    *


## 三层交换机景

1、场景需求

*   适用于三层交换机
*   无线用户和AP处于不同的vlan网段，DHCP由三层交换机下发。网关都在三层交换机上。

2、poe交换机配置

### 配置连接AP接口

```python
interface GigabitEthernet 0/1
 switchport mode trunk
 switchport trunk native vlan 1001  #  将ap所属的vlan配置为native vlan
 poe enable
!
```

ap交换机上联口配置

    interface GigabitEthernet 0/24
     switchport mode trunk
     switchport trunk allowed vlan only 2-4094
     ip dhcp snooping trust
     poe enable

## 三层交换机配置

*   配置DHCP服务器和地址池
*   配置三层交换机vlan

# ac配置
