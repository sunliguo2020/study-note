#!/bin/bash
#备份mysql中所有的表
#一个数据库一个目录
#
MYUSER="root"
MYPASS="admin"
HOST="localhost"
BACKUPDIR="/mnt/TNAS_SUN"

DATE=$(date -I)
RETENTION=20

#MYSQLDATA="/var/lib/mysql"

[ ! -d $BACKUPDIR/$DATE ] && mkdir -p $BACKUPDIR/$DATE

# 查询所有的数据库名
DBS=`mysql -u$MYUSER -p$MYPASS -Bse "show databases"|grep -v "information_schema" |grep -v "test"`

for db_name in $DBS; do

  # 创建和数据库同名的目录
  mkdir -p $BACKUPDIR/$DATE/$db_name

  # 查询当前数据库中所有的数据表
  tables=$(mysql -u$MYUSER -p$MYPASS -Bse "use $db_name;show tables")

  for table_name in $tables; do
    echo $table_name
    mysqldump -u$MYUSER -p$MYPASS -h$HOST $db_name $table_name >$BACKUPDIR/$DATE/$db_name/$table_name.sql
  done

done
