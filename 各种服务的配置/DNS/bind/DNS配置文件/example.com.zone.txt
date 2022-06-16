$ttl 38400
example.com.	IN	SOA	dns.example.com. admin.example.com. (
			2005090503     
			10800    
			3600       
			604800   
			38400 )   
example.com.	     IN	NS	dns.example.com.
dns  		     IN	A	192.168.200.177
www.example.com.	     IN	A	192.168.16.9
mail1.example.com. IN	A	192.168.200.178
mail2.example.com. IN	A	192.168.200.179
mail3.example.com. IN	A	192.168.200.180
rhel4	         IN	CNAME	dns
bbs		         IN	CNAME	www
samba	         IN	CNAME	www
example.com.	     IN	MX	10 mail1.example.com.
example.com.	     IN	MX	11 mail2.example.com.
example.com.	     IN	MX	12 mail3.example.com.
