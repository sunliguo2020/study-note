### 安装execjs
```
pip install pyexecjs
```

```python
import execjs  
  
# 创建一个 JavaScript 运行时  
runtime = execjs.get()  
  
# 要执行的 JavaScript 代码  
js_code = """  
function add(x, y) {  
    return x + y;  
}  
  
add(1, 2);  
"""  
  
# 执行 JavaScript 代码并获取结果  
result = runtime.eval(js_code)  
print(result)  # 输出: 3
```

使用外部javascript文件

```python
import execjs  
  
# 读取外部的 JavaScript 文件  
with open('my_script.js', 'r') as f:  
    js_code = f.read()  
  
# 编译并执行 JavaScript 代码  
ctx = execjs.compile(js_code)  
result = ctx.call('add', 1, 2)  # 假设 'add' 是你在 JavaScript 文件中定义的一个函数  
print(result)  # 输出: 3
```

