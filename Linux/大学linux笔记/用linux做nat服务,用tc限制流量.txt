最近有同事用bt和电驴疯狂下载，我们上网打cs受到极大影响，所以对nat上网做了流量控制,将一点经验介绍给网友，希望对cs fans 有所帮助.
我们上网环境如下：
    eth0 外网ip :a.b.c.d
    eth1 内网ip1:192.168.0.0/24  给老板和bt
    eth2 内网ip2:192.168.1.0/24  给我和csfans
用linux 做nat 命令如下:
echo 1 >; /proc/sys/net/ipv4/ip_forward
iptables -F
iptables -t nat -F    ----清除旧规则
iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -o eth0 -j SNAT --to a.b.c.d   ---为内网ip1 做nat
iptables -t nat -A POSTROUTING -s 192.168.1.0/24 -o eth0 -j SNAT -- to a.b.c.d   ---为内网ip2 做nat
------------为流量控制做基于fw过滤器的标记
iptables -I PREROUTING -t mangle -p tcp -s 192.168.0.0/24 -j MARK --set-mark 1
iptables -I PREROUTING -t mangle -p tcp -s 192.168.1.0/24 -j MARK --set-mark 2
------------为上传速率做流量控制
tc 要求内核2.4.18以上，所以不够的要升级
tc 只能控制网卡发送包的速率，所以上传速率的限制要在eth0上做
----删除旧有队列
tc qdisc del dev eth0 root
----加一个根队列,速率用网卡的速率10Mbit，也可用上传的速率
tc qdisc add dev eth0 root handle 100: cbq bandwidth 10Mbit avpkt 1000
----加一个根类
tc class add dev eth0 parent 100:0 classid 100:1 cbq bandwidth 10Mbit rate 10Mbit allot 1514 weight 1Mbit prio 8 maxburst 8 avpkt 1000 bounded
----加一个子类用于内网1速率限制为300Kbit
tc class add dev eth0 parent 100:1 classid 100:2 cbq bandwidth 10Mbit rate 300Kbit allot 1513 weight 30Kbit prio 5 maxburst 8 avpkt 1000 bounded
----加一个子类用于内网2速率限制为320Kbit
tc class add dev eth0 parent 100:1 classid 100:3 cbq bandwidth 10Mbit rate 320Kbit allot 1513 weight 32Kbit prio 6 maxburst 8 avpkt 1000 bounded
----设置队列规则
tc qdisc add dev eth0 parent 100:2 sfq quantum 1514b perturb 15
tc qdisc add dev eth0 parent 100:3 sfq quantum 1514b perturb 15
------将队列和fw过滤器映射起来 其中hand 1 的1是开始用iptables 做的标记，hand 2 的2也是开始用iptables 做的标记
tc filter add dev eth0 parent 100:0 protocol ip prio 1 handle 1 fw classid 100:2
tc filter add dev eth0 parent 100:0 protocol ip prio 2 handle 2 fw classid 100:3
-----------------------再做下载限制我只限制了老板和bt的下载速率，过滤器是用u32
tc qdisc del dev eth1 root
tc qdisc add dev eth1 root handle 200: cbq bandwidth 10Mbit avpkt 1000
tc class add dev eth1 parent 200:0 classid 200:1 cbq bandwidth 10Mbit rate 10Mbit allot 1514 weight 2Kbit prio 8 maxburst 8 avpkt 1000 bounded
tc class add dev eth1 parent 200:1 classid 200:2 cbq bandwidth 10Mbit rate 1000Kbit allot 1513 weight 1Mbit prio 5 maxburst 8 avpkt 1000 bounded
tc qdisc add dev eth1 parent 200:2 sfq quantum 1514b perturb 15
tc filter add dev eth1 parent 200:0 protocol ip prio 25 u32 match ip dst 192.168.0.0/24 flowid 200:2


----------------------
现在可以用tc -s qdisc ls dev eth0
            tc -s qdisc ls dev eth1
          tc -s class ls dev eth0
          tc -s class ls dev eth1 监视流量