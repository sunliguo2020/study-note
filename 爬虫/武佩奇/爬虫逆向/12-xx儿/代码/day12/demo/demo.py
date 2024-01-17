# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
import subprocess

res = subprocess.check_output('node sdk.js "15cf502c3128593b1a3237e5c484d6c9"', shell=True)
data_string = res.decode('utf-8')
print(data_string)
