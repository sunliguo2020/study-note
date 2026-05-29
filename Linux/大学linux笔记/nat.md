Why use nat ?
  1: do not have enough globally unique ip address to connect to the Internet
  2: To change over to a new ISP that requires the network to be renumbered
  3: To merge two intranets with duplicate address 
  4: To support basic load sharing using a single ip address
  
 Static Inside Source NAT Configuration Example
   ip nat inside source static 10.1.1.1 192.168.2.2
   
   interface Ethernet0
   ip address 10.1.1.10 255.255.255.0
   ip nat inside
   
   ineterface Serial0
   ip address 172.16.2.1 255.255.255.0
   ip nat outside
Static Inside Source PAT Configuration Example
   ip nat insdie source static 10.1.1.1 80 192.168.2.2 80
   ip nat insdie source static 10.1.1.2 25 192.168.2.2 25
   
   interface E0
   ip address 10.1.1.10 255.255.255.0
   ip nat inside
   
   inter S0
    ip address 17.16.2.1 255.255.255.0
    ip nat outside
   
  Static Outside Source NAT Configuration Example
    interface E0
      ip address 10.1.1.10 255.255.255.0
      ip nat inside
    
    interface S0
     ip 172.168.2.1 255.255.0
     ip nat outside
     
   Dynamic NAT Configuration
     ip nat pool dyn-nat 192.168.2.1 192.168.2.254 netmask 255.255.255.0
     ip nat inside source list 1 pool list 1
     
     access-list 1 10.1.1.0 0.0.0.255