测试MySQL
MySQL里面有一个简单的数据库例子test ，而且它的内部数据库一直保持对权限和帐户的监视，因而 先运行mysql看看是否
可以工作。
首先启动MySQL：
# /etc/rc.d/init.d/mysql start
service mysqld start

如果一切正常，你将看到以下的信息出现： 
Starting mysqld daemon with databases from /var/lib/mysql
接着，用show databases命令可以将安装的数据库列出来：
mysql> show databases;
你就可以看到：

+----------+

| Database |

+----------+

| mysql |

| test |

+----------+

2 rows in set (0.00 sec)

更改管理员密码
在一切正常后，要做的第一件事情是更改管理员的密码。你可以运行mysqladmin 
格式： mysqladmin -u 用户名 -p 旧密码 password 新密码

set password for root=password("456");
update user set password=password('456');
清除密码 
   mysqladmin -uroot -p456 password""
# mysqladmin -u root password newpassword

此命令把root用户的口令变成newpassword。当然你可以把口令换成其它，因为这个很容易破解。

进入MySQL
你需要提供一个MySQL用户和此用户的口令。如果数据库运行在其它机器上，而不是你所在的这台机器上你需要指定主机名。
命令：
mysql -h <主机名> -u <用户名> -p <数据库名>
Enter password: ********
********代表你的口令；当mysql显示Enter password:提示时输入它。
例如，在此机器上，你可以敲入：
# mysql -u root -p mysql
Enter password：

操作MySQL 
　　在之前要指出的是：一条操作即是一条SQL语句，注意随后要跟上一个分号，以标志此条语句的结束。而且一条SQL 
语句不必全在一个单独行给出，可以写入多行，最后以分号结束此语句的输入。
1> 显示数据库列表     show databases;
2> 显示库中的数据表  
use mysql; #打开库
show tables;
3> 显示数据库的结构
 describe 表名;
 desc user;
4> 创建数据库
命令：CREATE DATABASE <数据库名> 例如，建立一个名为 test 的数据库
mysql> CREATE DATABASE test;
5>  删除数据库
命令： DROP DATABASE <数据库名>
例如，删除名为 test 的数据库
mysql> DROP DATABASE test 
drop databases if exits 
6> 连接数据库
命令： USE <数据库名>
例如，如果test数据库存在，尝试存取它：
mysql> USE test
屏幕提示：
Database changed
7> 建表
命令：CREATE TABLE <表名> ( <字段名1> <类型1> [,..<字段名n> <类型n>]);
例如，建立一个名为table_1的表，此表记录班上的人员及平均成绩，那么用字段 id 代表编号，为数字类型，且编号唯一，
不能为空, 缺省值为 0 ； 用字段 name 代表人名，为字符型，不为空；用字段 degree 代表成绩，为数字型，可为空。
编号id 为此表的关键字。建表如下：
mysql> CREATE TABLE table_1 (
> id INT(4) DEFAULT '0' NOT NULL,
> name CHAR(20) NOT NULL
> degree DOUBLE(16,2) ,
> PRIMARY KEY(id));
8> 删除表
命令：DROP TABLE <表名>
例如，删除表名为 table_1 的表
mysql> DROP TABLE table_1; 
9>插入数据
命令：INSERT INTO <表名> [( <字段名1>[,..<字段名n > ])]VALUES ( 值1 )[, ( 值n )]
例如，往表 test 中插入二条记录, 这二条记录表示：编号为1的名为joan 的成绩为96.45, 编号为2 的名为jeanny 的成绩为82.99.
mysql> INSERT INTO test VALUES(1,'joan',96.45),(2,'jeanny',82.99);
10> 查询表中的数据
命令： SELECT <字段1，字段2，...> FROM < 表名 > WHERE < 表达式 >
例如，查看表 test 中所有数据
mysql> SELECT * FROM test;
屏幕显示：
+----+-------------+----------+
| id | name | degree |
+----+-------------+----------+
| 1 | joan | 96.45 |
| 2 | jeanny | 82.99 |
+----+-------------+----------+　
11> 删除表中数据
命令： DELETE FROM < 表名 > WHERE < 表达式 >
例如，删除表 test 中编号为1 的记录
mysql> DELETE FROM test WHERE id=1; 
12> 修改数据库 
 在mysql的表中增加字段： 
 alter table dbname add column userid int(11) not null primary key auto_increment; 
 这样，就在表dbname中添加了一个字段userid，类型为int(11)。 

字段类型 
　　 1．INT[(M)] 　　 正常大小整数类型 
　　 2．DOUBLE[(M,D)] [ZEROFILL] 　　 正常大小(双精密)浮点数字类型 
　　 3．DATE 　　 日期类型。支持的范围是1000-01-01到9999-12-31。MySQL以YYYY-MM-DD格式来显示DATE值，但是允许你使用字符串或数字把值赋给DATE列 
　　 4．CHAR(M) 　　 定长字符串类型，当存储时，总是是用空格填满右边到指定的长度 
　　 5．BLOB TEXT  　　 BLOB或TEXT类型，最大长度为65535(2^16-1)个字符。 
　　 6．VARCHAR 变长字符串类型
  
mysql数据库的授权 添加用户
  添加用户
  1: 添加用户test_user 密码123  让他可以在任何主机上登录，并对所有数据库有查询插入修改删除的权限
  mysql>grant select,insert,update,delete on *.* to 'test_user'@'%' identified  by '123';
  2:添加一个用户test_user2
  mysql>grant select,insert,update,delete on test.* to 'test_user'@'localhost' identified
  3:创建一个本地的完全超级用户，admin 口令 123
    grant all privileges on *.* to admin@localhost identitied by '124' with     grant option; 

　 mysql>grant select,insert,delete,create,drop  on *.* (或test.*/user.*/..)  to 用户名@localhost  identified by 密码； 
　　 如：新建一个用户帐号以便可以访问数据库，需要进行如下操作： 
　　 mysql> grant usage 
　　 -> ON test.* 
　　 -> TO testuser@localhost; 
　　 Query OK, 0 rows affected (0.15 sec) 
　　 此后就创建了一个新用户叫：testuser，这个用户只能从localhost连接到数据库并可以连接到test 数据库。下一步，我们必须指定testuser这个用户可以执行哪些操作： 
　　 mysql> GRANT select, insert, delete,update 
　　 -> ON test.* 
　　 -> TO testuser@localhost; 
　　 Query OK, 0 rows affected (0.00 sec) 
　　 此操作使testuser能够在每一个test数据库中的表执行SELECT，INSERT和DELETE以及UPDATE查询操作。现在我们结束操作并退出MySQL客户程序： 
删除用户
  revoke all on *.* from 'test_user'@localhost;
  mysql>delete from user where User='test_uer';
  mysql>flush privileges;
删除匿名用户
  mysql>delete from user where host='localhost' and user='';
  mysql>flush privileges;//刷新内存授权表
优化
mysql>optimize table 表1,表2---

导入数据库表 
load data infile '/tmp/teacher' into tale teacher
或
  mysqlimport school /tmp/teacher.txt

导入：
mysql -uroot -p wordpress <20110403-blog.sql
将数据库school中的全部表备份到school.sql
  mysqldump --opt school>school.sql
 仅备份数据库school中的一部分表teacher和student
  mysqldump --opt shcool teacher student>school_teacher_student.sql
备份多个数据库
   mysqldump --databases school test>school_test.sql

   source school.sql
