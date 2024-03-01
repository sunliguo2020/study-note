# 浏览器的同源策略

<img src="F:\github\learning-vue\笔记\跨域-CORS方案.assets\image-20240227195528381.png" alt="image-20240227195528381" style="zoom: 150%;" />

CORS（Cross-Origin Resource Sharing）

CORS是一套机制，用于浏览器校验跨域请求 。

它的基本概念是：

只要服务器明确表示允许，则校验通过。

服务器明确拒绝或没有表示，则校验不通过。

# 开发者模式测试

```javascript
fetch('https://taobao.com')
```

CORS将请求分为两类：

简单请求

- 请求方法为：GET HEAD POST
- 头部字段满足CORS安全规范
- 请求头Content-Type为
  - text/plain
  - multipart/form-data
  - application/x-www-form-urlencoded

预检请求

