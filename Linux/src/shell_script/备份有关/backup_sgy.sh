#!/bin/bash

# 定义数据库连接参数
db_user="root"
db_password=""
db_name="sgy"

# 生成备份文件名
timestamp=$(date '+%Y%m%d')
backup_file="${db_name}-${timestamp}.sql.gz"

# 执行备份命令
mysqldump -u"${db_user}" -p"${db_password}" "${db_name}" | gzip -9 > "${backup_file}"

if [ $? -eq 0 ]; then
    echo "数据库 ${db_name} 备份成功，备份文件名为 ${backup_file}"
else
    echo "备份数据库 ${db_name} 失败"
fi
