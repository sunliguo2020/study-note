**修改防抖动时间和下线检测时间**

​    修改防抖动时间： 

```
Ruijie(config)#wlansec  1                       ——》开启认证的wlansec下

Ruijie(config-wlansec)#webauh prevent-jitter 3600   ——》防抖动时间设置为60分钟，3600的单位是秒。

Ruijie(config)#ac-controller

Ruijie(config-ac)#prevent-jitter authed-only        ——》设置防抖动时间只针对认证用户有效。
```



​    修改下线检测时间： 

​    Ruijie(config)#wlansec  1                       ——》开启认证的wlansec下 

​    Ruijie(config-wlansec)#web-auth offline-detect interval 60 flow 0  ——》60的单位是分钟，0的单位0kb。意为：一旦检测到大于等于60分钟，该用户产生的流量是0kb，立马把用户踢下线。 

​    Ruijie(config)#ap-config all 

​    Ruijie(config)#sta-idle-timeout 3600              ——》3600的单位是秒，对应上面的60分钟。时间配置要配置成一致。 

 

​    下线检测时间   配置后达到的效果就是   用户认证成功后，若手机锁屏时间（这段时间内用户没有产生任何流量）大于等于60分钟，AC则认为用户已不在线，会在认证表项里把用户踢下线。若用户锁屏时间小于60分钟，用户重新打开手机连上WIFI，因此时用户还在设备的在线列表里，用户直接连上wifi就能上网。 

​    假设配置防抖动时间5分钟，配置下线检测时间10分钟，如果终端离开了网络，因为防抖动时间小于下线检测时间，防抖功能优先触发web认证将用户下线。 

