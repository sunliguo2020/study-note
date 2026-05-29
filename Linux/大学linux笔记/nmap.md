-sT TCP connect()扫描
-sP ping scan
-sU UDP scan
-sR RPC scan
-PB
-PS -PT -PI
-b
nmap -sP 192.168.7.0/24 ping
nmap -sP -PT80 192.168.7.0/24
nmap -sT
nmap -sU
nmap -sS -O
nmap port scanning
  nmap -v -sT localhost
nmap Tcp SYN(half-open) scanning
  nmap -v -sS localhost
nmap TCP FIN scanning
  nmap -v -sF localhost
nmap TCP Xmas tree scanning
  namp -v -sX localhost
nmap TCP Null scanning
 nmap -v -sN localhost
nmap TCP RPC scanning
 nmap -v -O localhost
 nmap remote software version scanning

 You can also find out what software version opening the port.
# nmap -v -sV localhost
# nmap -v -sV 192.168.0.0/24
