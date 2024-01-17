# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
import execjs

with open('v3.js', mode='r', encoding='utf-8') as f:
    js_string = f.read()

JS = execjs.compile(js_string)

username = JS.call("base64encode", "wupeiqi")
pwd = JS.call("base64encode", "123123")
password = JS.call("encryptPwd", pwd)

print(username)
print(password)
