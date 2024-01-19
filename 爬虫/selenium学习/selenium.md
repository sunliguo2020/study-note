### 1、安装
```pip install selenium```
### 2、下载浏览器驱动
- google chrome 驱动地址
谷歌驱动的下载：
114及之前版本： http://chromedriver.storage.googleapis.com/index.html
117/118/119版本： https://googlechromelabs.github.io/chrome-for-testing/

### 框架代码：
```python
from selenium import webdriver
from selenium.webdriver.chrome.service import Service


service = Service('./chromedriver-win64/chromedriver.exe')
driver = webdriver.Chrome(service=service)

# 打开网页
# driver.get('https://passport.bilibili.com/login')
driver.get('http://www.sunliguo.com')

```
#### 元素定位
```
find_element_by_id()
find_element_by_name()
find_element_by_class_name()
find_element_by_tag_name()
find_element_by_link_text()
find_element_by_partial_link_text()
find_element_by_xpath()
find_element_by_css_selector()
```
在element变成elements就是找所有满足的条件，返回数组。

### 寻找
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