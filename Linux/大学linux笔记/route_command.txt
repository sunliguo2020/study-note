route add default gw 192.168.1.1


route add [-net|-host] target [netmask Nm] [gw Gw] 

route add -net 127.0.0.0
route add -net 192.56.76.0 netmask 255.255.255.0 dev eth0
route add default gw mango-gw

