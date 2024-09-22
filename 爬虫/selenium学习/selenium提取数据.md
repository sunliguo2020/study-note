```python
li_list = web.find_elements_by_xpath('//*[@id="s_position_list"]/ul/li')

for li in li_list:
	h3 = li.find_element_by_xpath('./div[1]/div[1]/div[1]/a/h3')
	print(h3.text)
```

```javascript
var a = document.getElementsByClassName('um-login-header')[0];
a.parentNode.removeChild(a)

```

详情页新页面跳转  窗口切换

```python
web.switch_to.window(wed.window_handles[-1])
```

### iframe

### select
```pyton
from selenium.webdriver.support.select import Select
```