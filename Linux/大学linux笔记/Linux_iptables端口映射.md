8100
iptables -t nat -A PREROUTING -p tcp -m tcp --dport 8100 -j DNAT --to-destination 192.168.0.218:8100
iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -d 192.168.0.218 -p tcp -m tcp --dport 8100 -j SNAT --to-source 218.6.242.170
iptables -A INPUT -p tcp --dport 8100 -i eth0 -j ACCEPT
service iptables save 

5002
iptables -t nat -A PREROUTING -p tcp -m tcp --dport 5002 -j DNAT --to-destination 192.168.0.220:5900
iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -d 192.168.0.220 -p tcp -m tcp --dport 5900 -j SNAT --to-source 218.6.242.170
iptables -A INPUT -p tcp --dport 5002 -i eth0 -j ACCEPT
service iptables save 

iptables -1 nat -L

5900
iptables -t nat -A PREROUTING -p tcp -m tcp --dport 5900 -j DNAT --to-destination 192.168.0.220:5900
iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -d 192.168.0.220 -p tcp -m tcp --dport 5900 -j SNAT --to-source 218.89.191.178
iptables -A INPUT -p tcp --dport 5900 -i eth0 -j ACCEPT
service iptables save 

iptables -t nat -A PREROUTING -p tcp -d 218.89.191.178 --dport 5900 -j DNAT --to 192.168.0.220:5900
service iptables save 

×°¿¨
cd /usr/local/lib
rm -rf libpcap.so*
cd /usr/include
rm -rf pcap-bpf.h pcap.h pcap-named
cd gepei-libpcap  ./build
cd gepei-driver ./clear ./build


[root@localhost ~]# ifconfig
eth1      Link encap:Ethernet  HWaddr 00:0E:F5:00:0B:83  
          inet addr:218.6.242.170  Bcast:218.6.242.255  Mask:255.255.255.0
          inet6 addr: fe80::20e:f5ff:fe00:b83/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:2518 errors:0 dropped:0 overruns:0 frame:0
          TX packets:2163 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:797699 (779.0 KiB)  TX bytes:154900 (151.2 KiB)
          Base address:0xc400 Memory:ed040000-ed060000 

eth2      Link encap:Ethernet  HWaddr 00:0E:F5:00:0B:84  
          inet addr:192.168.0.1  Bcast:192.168.0.255  Mask:255.255.255.0
          inet6 addr: fe80::20e:f5ff:fe00:b84/64 Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
          RX packets:2443 errors:0 dropped:0 overruns:0 frame:0
          TX packets:2692 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:1000 
          RX bytes:189012 (184.5 KiB)  TX bytes:817171 (798.0 KiB)
          Base address:0xc800 Memory:ed080000-ed0a0000 

lo        Link encap:Local Loopback  
          inet addr:127.0.0.1  Mask:255.0.0.0
          inet6 addr: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:16436  Metric:1
          RX packets:8 errors:0 dropped:0 overruns:0 frame:0
          TX packets:8 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:0 
          RX bytes:560 (560.0 b)  TX bytes:560 (560.0 b)

[root@localhost ~]# iptables -t nat -A POSTROUTING -s 192.168.0.0/24 -o eth0 -j SNAT --to 218.89.191.178                                                         
[root@localhost ~]# service iptables save
