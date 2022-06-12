  861  iptables -nL
  863  iptables -nL
  864  iptables
  865  iptables -F
  866  iptables
  867  iptables -nL
  871  iptables -t nat -A POSTROUTING  -o eno16777736 -j MASQUERADE
  872  iptables -nL
  873  iptables -A FORWARD -I eno16777736 -j ACCEPT
  874  iptables -A FORWARD -i eno16777736 -j ACCEPT
  885  iptables -F
  888  iptables -t nat -A POSTROUTING -s 192.168.10.1 -j MASQUERADE
  889  service iptables restart
  890  service iptables status
  891  iptables -nL
  892  iptables -nL -t nat
  893  iptables -t nat -A POSTROUTING -s 192.168.10.0/24 -j MASQUERADE
  895  iptables -F
  896  iptables -t nat -A POSTROUTING -s 192.168.10.0/24 -j MASQUERADE
  897  iptables -F
  898  iptables -t nat -A POSTROUTING -s 192.168.10.108 -j MASQUERADE
  899  iptables -nL
  900  iptables -nL -t nat
  901  iptables -F
  902  iptables -F -t nat
  904  iptables -A INPUT -i eno16777736 -j ACCEPT
  905  iptables -t nat -A POSTROUTING -o eno16777736 -s 192.168.10.108 -j MASQUERADE
  906  iptables -A INPUT -i eth0 -m state --state ESTABLISHED,RELATED -j ACCEPT
  954  iptables -nL
  955  iptables -nL -t nat
  956  history |grep iptables
 1015  history |grep iptables;
 1016  history |grep iptables >iptables.txt
