修改字段类型，数据会截断

mysql> alter table test modify column `busi_nbr` varchar(10);
Query OK, 106775 rows affected
Records: 106775  Duplicates: 0  Warnings: 106775


增加主键
mysql> alter table `test` add primary key(`prod_inst_id`);
1062 - Duplicate entry 'NULL' for key 'PRIMARY'


mysql> alter table `test` add primary key(`prod_inst_id`);
Query OK, 106775 rows affected
Records: 106775  Duplicates: 0  Warnings: 0


分组
select `busi_nbr`, count(*) as count from `test` group by `busi_nbr`;