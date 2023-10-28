MYSQL创建数据库时候直接指定编码和排序规则
转载 2014年07月04日 10:13:03 3053
mysql 创建 数据库时指定编码很重要，很多开发者都使用了默认编码，但是我使用的经验来看，制定数据库的编码可以很大程度上避免倒入导出带来的乱码问题。

我们遵循的标准是，数据库，表，字段和页面或文本的编码要统一起来
很多mysql数据库工具（除了phpmyadmin，我偶尔用，功能强速度慢）都不支持创建时指定数据库编码，当然可以改my.ini来解决这个问题,但是需要重新启动mysql，不过用下面的语句会更有效

GBK: create database test2 DEFAULT CHARACTER SET gbk COLLATE gbk_chinese_ci;

UTF8: CREATE DATABASE `test2` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci

注意：如果不是通过my.ini配置文件设置的内容，只在当前状态下有效，当重启数据库服务后失效。所以如果想要不出现乱码只有修改my.ini文件，数据库编码可以在创建数据库时候指定UTF8，如下：
|character_set_client      | utf8                                  |
| character_set_connection | utf8                                  |
| character_set_database   | utf8                                  |
| character_set_filesystem | binary                                |
| character_set_results    | utf8                                  |
| character_set_server     | latin1                                |
| character_set_system     | utf8           

注意该配置| character_set_server     | latin1 无法设置成UTF8
交互时候仍然会出现乱码。

mysql> show variables like 'character_set%';
+--------------------------+----------------------------+
| Variable_name            | Value                      |
+--------------------------+----------------------------+
| character_set_client     | latin1                     |
| character_set_connection | latin1                     |
| character_set_database   | latin1                     |
| character_set_filesystem | binary                     |
| character_set_results    | latin1                     |
| character_set_server     | latin1                     |
| character_set_system     | utf8                       |
| character_sets_dir       | /usr/share/mysql/charsets/ |
+--------------------------+----------------------------+
8 rows in set (0.00 sec)

mysql>

character_set_server 默认的内部操作字符集
character_set_client 客户端来源数据使用的字符集
character_set_connection 连接层字符集
character_set_results 查询结果字符集
character_set_database 当前选中数据库的默认字符集
character_set_system 系统元数据（字段名等）字符集

以上这些参数如何起作用：

1.库、表、列字符集的由来
　　①建库时，若未明确指定字符集，则采用character_set_server指定的字符集。
　　②建表时，若未明确指定字符集，则采用当前库所采用的字符集。
　　③新增时，修改表字段时，若未明确指定字符集，则采用当前表所采用的字符集。

2.更新、查询涉及到得字符集变量
　　更新流程字符集转换过程：character_set_client-->character_set_connection-->表字符集。
　　查询流程字符集转换过程：表字符集-->character_set_result

3.character_set_database
　　当前默认数据库的字符集，比如执行use xxx后，当前数据库变为xxx，若xxx的字符集为utf8，那么此变量值就变为utf8(供系统设置，无需人工设置)。

3、MySQL客户端与字符集

1.对于输入来说：

　　客户端使用的字符集必须通过character_set_client、character_set_connection体现出来：

　　　　①在客户端对数据进行编码（Linux：utf8、windows：gbk）

　　　　②MySQL接到SQL语句后(比如insert)，发现有字符，询问客户端通过什么方式对字符编码：客户端通过character_set_client参数告知MySQL客户端的编码方式(所以此参数需要正确反映客户端对应的编码)

　　　　③当MySQL发现客户端的client所传输的字符集与自己的connection不一样时，会将client的字符集转换为connection的字符集

　　　　④MySQL将转换后的编码存储到MySQL表的列上，在存储的时候再判断编码是否与内部存储字符集（按照优先级判断字符集类型）上的编码一致，如果不一致需要再次转换

2.对于查询来说：

　　客户端使用的字符集必须通过character_set_results来体现，服务器询问客户端字符集，通过character_set_results将结果转换为与客户端相同的字符集传递给客户端。(character_set_results默认等于character_set_client)

4、MySQL字符编码转换原理：

　　问：若character_set_client为UTF8，而character_set_database为GBK，则会出现需要进行编码转换的情况，字符集转换的原理是什么？

　　答：假设gbk字符集的字符串“你好”，需要转为utf8字符集存储，实际就是对于“你好”字符串中的每个汉字去utf8编码表里面查询对应的二进制，然后存储。


只有当修改my.ini中设置UTF8，才会全部修改成UTF8

-------------------------
mysql设置编码命令 ，重启失效

SET character_set_client = utf8; 
SET character_set_connection = utf8; 
SET character_set_database = utf8; 
SET character_set_results = utf8;/*这里要注意很有用*/ 
SET character_set_server = utf8; 

SET collation_connection = utf8_bin; 
SET collation_database = utf8_bin; 
SET collation_server = utf8_bin; 

my.ini中配置默认编码 
default-character-set=utf8 

[root@aliyun ~]# vi /etc/my.cnf
[mysqld]
datadir=/var/lib/mysql
socket=/var/lib/mysql/mysql.sock
user=mysql
default-character-set=utf8
init_connect='SET NAMES utf8'
# Disabling symbolic-links is recommended to prevent assorted security risks
symbolic-links=0

[mysqld_safe]
log-error=/var/log/mysqld.log
pid-file=/var/run/mysqld/mysqld.pid