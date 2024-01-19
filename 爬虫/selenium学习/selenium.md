### 一、简介

Selenium可以“控制”浏览器，在浏览器页面上实现：点击、输入、滑动等操作。

Selenium VS 逆向

【优点】简单不需要逆向，只需要控制浏览器

【缺点】

### Selenium必备操作

- 定位
- 操作
- 执行JavaScript
- 源码读取和提取
- 携带Cookie
- 请求代理
- 特征检测
- 无头模式
- 标签截图

### 二、必备操作



### 1、安装

```python
pip install selenium
```



### 2、下载浏览器驱动
- google chrome 驱动地址
谷歌驱动的下载：
114及之前版本： http://chromedriver.storage.googleapis.com/index.html
117/118/119版本： https://googlechromelabs.github.io/chrome-for-testing/

### 快速上手-框架代码：
```python
from selenium import webdriver
from selenium.webdriver.chrome.service import Service


service = Service('./chromedriver-win64/chromedriver.exe')
driver = webdriver.Chrome(service=service)

# 打开网页
# driver.get('https://passport.bilibili.com/login')
driver.get('http://www.sunliguo.com')
time.sleep(10)

driver.close()
```


### 2.2 寻找标签
```python
import time
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By

service = Service("chromedriver-win64/chromedriver.exe")
driver = webdriver.Chrome(service=service)

driver.get('https://www.5xclass.cn/')

# 根据ID寻找
tag = driver.find_element(By.ID, "bs-example-navbar-collapse-1")
print(tag.text)
print(10 * "-")

# 根据类名寻找
tags = driver.find_elements(By.CLASS_NAME, "panel-heading")
for tag in tags:
    print(tag.text)
print(10 * "-")

# 根据标签名称寻找
tags = driver.find_elements(By.TAG_NAME, "li")
for tag in tags:
    print(tag.text)
print(10 * "-")

# 根据XPATH寻找
tag = driver.find_element(By.XPATH, "/html/body/div/div[2]/div/div[2]/div/div[2]/div[1]")
print(tag.text)
print(10 * "-")

# 根据XPATH寻找
tag = driver.find_element(By.XPATH, '//*[@id="bs-example-navbar-collapse-1"]/ul[1]/li[1]/a')
print(tag.text)
print(10 * "-")

# 根据XPATH寻找多个
tags = driver.find_elements(By.XPATH, '/html/body/div/div[2]/div/div[2]/div/div[2]/div[2]/div/div/div/div/div[2]/a')
for tag in tags:
    print(tag.text)
print(10 * "-")

# 根据父子关系嵌套寻找
parent = driver.find_element(By.XPATH, '/html/body/div/div[2]/div/div[2]/div/div[2]/div[2]/div/div/div/div')
tags = parent.find_elements(By.XPATH, "div[@class='course']/a")
for tag in tags:
    print(tag.text)

time.sleep(5)
driver.close()

```

#### 2.3 执行操作

常见的执行操作：点击、输入

tag.click()

tag.send_keys()

### 2.4 执行JavaScript

driver.execute_script("")

### 2.5 等待执行

如果页面加载比较慢，需要等待某个元素加载成功后，再执行某些操作。

#### 示例1 基于lambda表达式

```python
sms_btn = webDriverWait(driver,30,0.5).until(lambda dv:dv.find_element(BY.XPATH,''))
sms_btn.click()
```

#### 自定义函数

#### 全局配置

```
# 后续找元素时，没有找到时则等待10秒去寻找（一旦找到则继续）
driver.implicityly_wai(10)
```



### 2.6获取值

#### 示例一：文本和属性

```
<a id='x1' class='info mine' href='5xclass.cn'>武佩奇</a>
```

tag.text

tag.get_attribute('target')

tag.get_attribute('data-toggle')

#### 实例二：值

tag.value

tag.get_attribute('value')

tag.get_attribute('placeholder')