                      arp 包的分析
一下是从rfc826 中摘取的：

An Example:
-----------

Let there exist machines X and Y that are on the same 10Mbit Ethernet cable.  They have Ethernet address EA(X) and EA(Y) and DOD Internet addresses IPA(X) and IPA(Y) .  Let the Ethernet type of Internet be ET(IP).  Machine X has just been started, and sooner or later wants to send an Internet packet to machine Y on the same cable.  X knows that it wants to send to IPA(Y) and tells the hardware driver (here an Ethernet driver) IPA(Y).  The driver consults the Address Resolution module to convert <ET(IP), IPA(Y)> into a 48.bit Ethernet address, but because X was just started, it does not have this information.  It throws the Internet packet away and instead creates an ADDRESS RESOLUTION packet with
	(ar$hrd) = ares_hrd$Ethernet
	(ar$pro) = ET(IP)
	(ar$hln) = length(EA(X))
	(ar$pln) = length(IPA(X))
	(ar$op)  = ares_op$REQUEST
	(ar$sha) = EA(X)
	(ar$spa) = IPA(X)
	(ar$tha) = don't care
	(ar$tpa) = IPA(Y)
and broadcasts this packet to everybody on the cable.

Machine Y gets this packet, and determines that it understands the hardware type (Ethernet),
that it speaks the indicated protocol (Internet) and that the packet is for it 
((ar$tpa)=IPA(Y)).  It enters (probably replacing any existing entry) the information 
that <ET(IP), IPA(X)> maps to EA(X).  It then notices that it is a request, so it swaps fields,
putting EA(Y) in the new sender Ethernet address field (ar$sha), sets the opcode to reply, and
sends the packet directly (not broadcast) to EA(X).  At this point Y knows how to send to X,
but X still doesn't know how to send to Y.
    Machine X gets the reply packet from Y, forms the map from <ET(IP), IPA(Y)> to EA(Y), notices the packet is a reply and throws it away.  The next time X's Internet module tries to send a packet to Y on the Ethernet, the translation will succeed, and the packet will (hopefully) arrive.  If Y's Internet module then wants to talk to X, this will also succeed since Y has remembered the information from X's request for Address Resolution.
    大体的意思是说：X想和Y通信，但是X不知道Y的MAC地址。A就发了个arp广播。B收到后回复A。

    我们用到的以太网帧的结构:

+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+前同步码+分界符 +以太网帧头 +数据(46-1500 bytes) +校验值+扩展部分+
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
               +             +   
  +                             +
+++++++++++++++++++++++++++++++++
+目的MAC地址+源MAC地址+协议类型 +
+++++++++++++++++++++++++++++++++
  6 bytes     6 bytes     2 bytes

常见协议类型如下：
0800       IP
0806       ARP
0835       RARP
8137       Novell IPX
809b       Apple Talk

  arp包的结构:
+++++++++++++++++++++
+链路的地址类型     + 2 bytes 0x0001 代表以太网帧
+++++++++++++++++++++
+网络地址类型       + 2 bytes 0x0800 代表 ip address
+++++++++++++++++++++
+链路地址的长度(m)  + 1 bytes  m bytes
+++++++++++++++++++++ 
+网络层地址的长度(m)+ 1 bytes  n bytes
+++++++++++++++++++++
+操作码             + 2 bytes 0x0001 代表问询包 0x0002 代表应答包
+++++++++++++++++++++
+发送者的链路地址   + m bytes 
+++++++++++++++++++++
+发送者的网路层地址 + n bytes
+++++++++++++++++++++
+接收链路地址       + m bytes
+++++++++++++++++++++
+接收者网络层地址   + n bytes
+++++++++++++++++++++

 有了以上的基础知识，我们就实际抓个包看看长的什么样？
首先用arp -n　看一下有那些arp 缓存。可以用arp -d来删除某条记录。这里用192.168.0.2来实验。
　现用tcpdump -Xn host 192.168.0.2 待命。再在另一终端用ping -c 1 192.168.0.2
下面是截获的通信过程：

[root@slg ~]# tcpdump -Xn host 192.168.0.2
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), capture size 96 bytes
12:54:13.848422 arp who-has 192.168.0.2 tell 192.168.0.30
        0x0000:  0001 0800 0604 0001 0011 5b51 8685 c0a8  ..........[Q....
        0x0010:  001e 0000 0000 0000 c0a8 0002            ............
12:54:13.848514 arp reply 192.168.0.2 is-at 00:13:d4:55:a6:76
        0x0000:  0001 0800 0604 0002 0013 d455 a676 c0a8  ...........U.v..
        0x0010:  0002 0011 5b51 8685 c0a8 001e 0000 0000  ....[Q..........
        0x0020:  0000 0000 0000 0000 0000 0000 0000       ..............
问询包分析:         
  0001         arp包中的链路层地址类型为以太网地址
  0800         arp包中的网路层地址类型为IP地址
  06           以太网地址长度
  04           IP地址长度
  0001         问询包
  00115b518685 发送者的MAC地址
  c0a8 001e    发送者的IP地址
  000000000000 接收者的MAC地址
  c0a8 0002    接收者的IP地址
应答包:
  0001         arp包中的链路层地址类型为以太网地址
  0800         arp包中的网路层地址类型为IP地址
  06           以太网地址长度
  04           IP地址长度
  0002         应答包
  0013d455a676 发送者的MAC地址
  c0a8 0002    发送者的IP地址
  00115b518685 接收者的MAC地址
  c0a8 001e    接收者的IP地址
  通过具体的动手可以加深理解网络协议。


  参考资料：
     1. rfc 826 http://www.faqs.org/rfcs/rfc826.html
     2. Internet 应用协议实例剖析与服务器配置  林藤等编著 人民邮电出版社 1.4 ARP 基础与实例剖析 
