# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666

import subprocess

res = subprocess.check_output('node v1.js "root"', shell=True)
data_string = res.decode('utf-8')
print(data_string)
