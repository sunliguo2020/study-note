import subprocess
from functools import partial
# 解决js文件中包含汉字报错的问题。
subprocess.Popen = partial(subprocess.Popen,encoding='utf-8')

import execjs 

f = open('.js',mode='r',encoding='utf-8')
js_code = f.read()
f.close()

js = execjs.compile(js_code)