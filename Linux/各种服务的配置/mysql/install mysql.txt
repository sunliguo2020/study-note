第1步、yum安装mysql
[root@stonex ~]#  yum -y install mysql-server
安装结果：
Installed:
    mysql-server.x86_64 0:5.1.73-3.el6_5                                                                                                                                                         
Dependency Installed:
    mysql.x86_64 0:5.1.73-3.el6_5  perl-DBD-MySQL.x86_64 0:4.013-3.el6   perl-DBI.x86_64 0:1.609-4.el6

第2步、设置开机启动
[root@stonex ~]#  chkconfig mysqld on

第3步、启动MySql服务
[root@stonex ~]#  service mysqld start

第4步、设置MySQL的root用户设置密码
[root@stonex ~]#  mysql -u root
Welcome to the MySQL monitor.  Commands end with ; or \g.
...... 省略了一些行
mysql> select user,host,password from mysql.user;
查询用户的密码，都为空，用下面的命令设置root的密码为root
mysql> set password for root@localhost=password('root');
mysql> exit

第5步、用新密码登陆
[root@stonex ~]#  mysql -u root -p

第6步、基本命令
show databases; //查看系统已存在的数据库
use databasesname;   //选择需要使用的数据库
drop database databasename; //删除选定的数据库
exit    //退出数据库的连接
create database test01;    //建立名为test的数据库
show tables;        // 列出当前数据库下的表
其他基本的增删改查使用标准SQL即可

第7步、开放远程登录权限

GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'root' WITH GRANT OPTION;
FLUSH PRIVILEGES;






[root@aliyun ~]# service mysqld start
Initializing MySQL database:  WARNING: The host 'aliyun' could not be looked up                                                                                                                      with resolveip.
This probably means that your libc libraries are not 100 % compatible
with this binary MySQL version. The MySQL daemon, mysqld, should work
normally with the exception that host name resolving will not work.
This means that you should use IP addresses instead of hostnames
when specifying MySQL privileges !
Installing MySQL system tables...
OK
Filling help tables...
OK

To start mysqld at boot time you have to copy
support-files/mysql.server to the right place for your system

PLEASE REMEMBER TO SET A PASSWORD FOR THE MySQL root USER !
To do so, start the server, then issue the following commands:

/usr/bin/mysqladmin -u root password 'new-password'
/usr/bin/mysqladmin -u root -h aliyun password 'new-password'

Alternatively you can run:
/usr/bin/mysql_secure_installation

which will also give you the option of removing the test
databases and anonymous user created by default.  This is
strongly recommended for production servers.

See the manual for more instructions.

You can start the MySQL daemon with:
cd /usr ; /usr/bin/mysqld_safe &

You can test the MySQL daemon with mysql-test-run.pl
cd /usr/mysql-test ; perl mysql-test-run.pl

Please report any problems with the /usr/bin/mysqlbug script!

                                                           [  OK  ]
Starting mysqld:                                           [  OK  ]
