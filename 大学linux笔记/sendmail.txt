Build -c
Build install
mkdir /usr/share/sendmail
cp -a cf/ /usr/shar/sendmail
cp generic-linux.mc sendmail.mv
make install -cf
cp sendmail.mc /etc/mail
cd /etc/mail

touch access aliases

echo "chinalab.com">local-host-names

makemap hash access.db<access
mkdir /var/spool/mquene





sendmail.cf 是sendmail的配置文件。是由一个.mc的文件用m4 产生的。
sendmail.mv 
    	DAEMON_OPTIONS(`Port=smtp,Addr=127.0.0.1,Name=MTA`)dnl

m4 sendmail.mc>sendmail.cf
access 文件

domainname.com RELAY
localhost RELAY
192.168.1.0 RELAY 
access 决定了那些机器那个域可以使用邮件服务器转发邮件，接着：
makemap hash access.db<access


local-host-names ：包含接收邮件的主机名

echo "root:redhat">>/etc/mail/aliases
newaliases
