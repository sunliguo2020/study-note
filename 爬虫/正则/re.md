### 适合使用re的条件

- 要找到的内容在页面源代码中，而且还在script标签中。

### 4个经常使用的方法：

- match()
- search()
- findall()
- finditer()

### 正则表达式

| .            | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| .            | 匹配除换行符意外的任意字符，当flags被设置为re.S时，可以匹配包含换行符以内的所有字符 |
| *            | 匹配前面0次或多次{0,}                                        |
| ?            | 可有可无                                                     |
| .*?          | 匹配除换行符以外的任意字符任意次 拒绝贪婪  惰性匹配          |
| .*           | 匹配除换行符以外的任意字符任意次 贪婪模式                    |
| +            | 匹配一次到多次 {1,}                                          |
| .+?          | 匹配除换行符以外的任意字符至少一次 拒绝贪婪                  |
| .+           | 匹配除换行符以外的任意字符至少一次 贪婪                      |
| []           | 里面是字符集合                                               |
| [0123456789] | 匹配任意一个数字字符                                         |
| [0-9]        |                                                              |
| \d           | 匹配任意一个数字字符，相当于[0-9]                            |
| \D           | 任意一个非数字字符，相当于[^0-9 ]                            |
| \w           | 匹配一位数字字母下划线  ，[a-zA-Z0-9_]                       |
| \W           | 匹配一位非数字字母下划线，[^a-zA-Z0-9_]                      |
|              |                                                              |

```
# search 匹配一次，字符串中包含就可以
print(re.search('[a-z]', "123456a"))
print(re.search('[a-z]{2}', "123456ab"))
```



```python
# match 必须第一位就匹配成功 否则失败 相当于search(^)
import re

print(re.search('\d', 'abc123'))
print(re.match('\d', 'abc123'))
```



```
import re

# findall 匹配所有 返回列表

print(re.findall('\d', '1234abc123'))

print(re.findall('\d', 'abc'))

print(re.findall('\d{2}', '123456abc789'))

myStr = '<div>我是HTML标签</div><div>div标签</div><div></div>'

# 匹配除div标签中的内容
print(re.findall('<div>.*?</div>', myStr))
print(re.findall('<div>.*</div>', myStr))

print(re.findall('<div>.+?</div>', myStr))
print(re.findall('<div>.+</div>', myStr))

# 存储括号中的值
print(re.findall('<div>(.*?)</div>', myStr))

```

