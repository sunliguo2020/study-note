数据定义语言
数据库
表
视图
索引
存储过程/函数

创建数据库
 create database [if not exits]  数据库名 

 create database if not exists test;

 drop database [if exists] 数据库名
 drop database
 .myd  数据文件 
 .myi  素引文件
 .frm  格式文件

table  表

create table 表名(
   列1 类型[选项]
   ------
   );
 use school;

 create table teacher
 (
   id int(4) auto_increment not null primary key,
   name char(10) not null,
   address varchar9(50) default '山东经济学院',
   year date
  );

drop table teacher;
修改表名称
alter table t1 rename t2;
修改表结构
 alter table t2 modify a tiny not null ,change b  char(20); 
增加列
  alter table t2 add d timestamp;
删除列
  alter table  t2 drop column c;

视图

  产品库视图
  create table t (qty int,price int);
  insert into values(2,30);
  create view v as select qty,price,qty*price as value from t;
  select * from v;
  alter view v as select qty,price


alter view v as select qty,price
drap view v;

索引
 存储过程/函数
 c/a/s B/A/S
  三层模式

  delimiter
    create procedure simpleproce (out paraml int)
    begin 
      select count(*) into paraml from t;
    end
    delimite;

    cal simpleproce(@a);

    select @a;
