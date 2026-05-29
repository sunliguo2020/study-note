create table dept
(
 deptno int primary key,
 dname varchar(14),
 loc varchar(13)
);

create table emp
(
empno int primary key,
ename varchar(10),
job varchar(10),
mgr int,
hiredate datetime,
sal double,
comm double,
deptno int,
foreign key (deptno) references dept(deptno)
);

./ /mysql_script/mysqldate.sql

insert into dept values (10,'A','b');
insert into dept values (11,'A','b');
insert into dept values (12,'A','b');
insert into dept values (13,'A','b');
insert into dept values (14,'A','b');

commit;

分页显示

select  * from dept order by deptno limit 3,2;
limit 3,2    3条以后取两条。

自动递增；；；
create table article (
id int primary key auto_increment,
title varchar(255)
);
intsert into article values (null,'a');
insert into article (title) vlaues('c');

时间
 select now();
 select date_format(now(),'%y%m%d%h%i%s');
 select date_format(now(),'%Y-%m-%d %H:%i:%s');