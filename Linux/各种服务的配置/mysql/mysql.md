1：创建用户
　A>
	mysql> insert into mysql.user(Host,User,Password) values("localhost","test",password("1234"));
  B>
	命令:CREATE USER 'username'@'host' IDENTIFIED BY 'password'; 
	例子: CREATE USER 'dog'@'localhost' IDENTIFIED BY '123456'; 
			CREATE USER 'pig'@'192.168.1.101_' IDENDIFIED BY '123456'; 
			CREATE USER 'pig'@'%' IDENTIFIED BY '123456'; 
			CREATE USER 'pig'@'%' IDENTIFIED BY ''; 
			CREATE USER 'pig'@'%'; 
2:,授权: 

命令:		GRANT privileges ON databasename.tablename TO 'username'@'host' 
授权格式：	grant 权限 on 数据库.* to 用户名@登录主机 identified by "密码";

修改密码：
 　　mysql>update mysql.user set password=password('新密码') where User="test" and Host="localhost";

  　　mysql>flush privileges;
  
 
3修改密码：
命令:SET PASSWORD FOR 'username'@'host' = PASSWORD('newpassword');如果是当前登陆用户用SET PASSWORD = PASSWORD("newpassword"); 

例子: SET PASSWORD FOR 'pig'@'%' = PASSWORD("123456"); 

.删除用户 

4：删除用户：
命令: DROP USER 'username'@'host'; 


创建数据库：
CREATE DATABASE `test` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci; 
create database cacti default character set utf8 collate utf8_general_ci;


修改时区：

mysql> show variables like '%time_zone%'
    -> ;
+------------------+--------+
| Variable_name    | Value  |
+------------------+--------+
| system_time_zone | CST    |
| time_zone        | SYSTEM |
+------------------+--------+
2 rows in set (0.00 sec)

mysql> 