# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
import execjs

with open('v2.js', mode='r', encoding='utf-8') as f:
    js_string = f.read()

JS = execjs.compile(js_string)

sign = JS.call("func2", "wupeiqi")
print(sign)  # wupeiqi666
