默认情况下，使用mysqldump备份出来的表记录都是在一条insert语句，这样对于导入来说效率要高些，但是遇到记录很多的大表，
可能会超过缓存区的大小，从而导致备份失败，可以使用参数实现一条记录一个insert语句，例如：
mysqldump -uroot -p --skip-opt  dbname > bak.sql

默认mysqldump会将多条插入语句导出成一条insert语句格式，如：
insert into t values(1),(2);
那有时我想生成多条insert语句，如：
insert into t  values(1);
insert into t values(2);
这时，在mysqldump时加上参数--skip-extended-insert即可。