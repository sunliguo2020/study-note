# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
import base64

user = "wupeiqi"

res = base64.b64encode(user.encode('utf-8'))
print(res) # d3VwZWlxaQ==