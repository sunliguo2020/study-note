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

只有当修改my.ini中设置UTF8，才会全部修改成UTF8

-------------------------
mysql设置编码命令 

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