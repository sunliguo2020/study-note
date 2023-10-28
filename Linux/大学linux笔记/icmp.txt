[root@slg ~]# tcpdump host www.baidu.com -X -vv -n -c 1
tcpdump: listening on eth0, link-type EN10MB (Ethernet), capture size 96 bytes
15:51:42.204252 IP (tos 0x0, ttl  64, id 0, offset 0, flags [DF], proto: ICMP (1), length: 84) 192.168.0.30 > 202.108.22.5: ICMP echo request, id 44046, seq 1, length 64
        0x0000:  4500 0054 0000 4000 4001 9971 c0a8 001e  E..T..@.@..q....
        0x0010:  ca6c 1605 0800 0e93 ac0e 0001 0ef7 8445  .l.............E
        0x0020:  bc1d 0300 0809 0a0b 0c0d 0e0f 1011 1213  ................
        0x0030:  1415 1617 1819 1a1b 1c1d 1e1f 2021 2223  .............!"#
        0x0040:  2425 2627 2829 2a2b 2c2d 2e2f 3031 3233  $%&'()*+,-./0123
        0x0050:  3435                                     45
1 packets captured
14 packets received by filter
0 packets dropped by kernel

