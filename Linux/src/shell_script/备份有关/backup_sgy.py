import subprocess
import datetime

# 定义数据库连接参数
db_user = 'root'
db_password = ''
db_name = 'sgy'

# 生成备份文件名
timestamp = datetime.datetime.now().strftime('%Y%m%d')
backup_file = f'{db_name}-{timestamp}.sql.gz'

# 执行备份命令
try:
    subprocess.run(
        f"mysqldump -u {db_user} -p{db_password} {db_name} | gzip -9 > {backup_file}",
        shell=True,
        check=True
    )
    print(f"数据库 {db_name} 备份成功，备份文件名为 {backup_file}")
except subprocess.CalledProcessError as e:
    print(f"备份数据库 {db_name} 失败：{e}")
