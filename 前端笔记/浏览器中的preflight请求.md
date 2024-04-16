### PreFlight是什么？
一般来说preflight预检请求，指的就是OPTIONS请求。它会在浏览器认为即将要执行的请求可能会对服务器造成不可预知的影响时，由浏览器自动发出。
通过预检请求，浏览器能够知道当前的服务器是否允许执行即将要进行的请求，只有获得了允许，浏览器才会真正执行接下来的请求。 通常preflight请求不需要用户自己去管理和干预，它的发出的响应都是由浏览器和服务器自动管理的。

![image-20240416211248211](F:\github\study-note\前端笔记\浏览器中的preflight请求.assets\image-20240416211248211-17132731722431.png)

- 请求通常长这样子
```
Access-Control-Request-Headers: x-requested-with
Access-Control-Request-Method: POST
Origin: http://test.preflight.qq.com
```

- 响应通常长这样子

- ```
  Access-Control-Allow-Headers: Content-Type, Content-Length, Authorization, Accept, X-Requested-With
  Access-Control-Allow-Origin: http://test.preflight.qq.com
  Access-Control-Allow-Methods: POST, GET, OPTIONS, DELETE
  Access-Control-Max-Age: 86400
  ```

- 

### 什么时候会触发PreFlight请求

`preflight`预检请求属于`CORS`规范的一部分，目前所有的现代浏览器都实现了此规范，但是部分浏览器对规范内容有扩充。MDN上指出，一共有五项必须条件需要满足，否则浏览器在执行真实请求之前会发出预检请求，以免在获得允许之前对服务器产生不可预知的影响。 以下五项条件只要有`任意一项不满足`即会发送预检请求:

- 1: 请求方法限制

> 只能够使用`GET` `POST` `HEAD`

- 2: 请求头限制

> 只能包含以下九种请求头 `Accept` `Accept-Language` `Content-Language` `Content-Type` `DPR` `Downlink` `Save-Data` `Viewport-Width`  `Width`

- 3: Content-Type限制

> Content-Type只能包含以下三种类型 `text/plain` `multipart/form-data` `application/x-www-form-urlencoded`

- 4: XMLHttpRequestUpload对象限制

> `XMLHttpRequestUpload`对象没有注册任何事件监听器

- 5: ReadableStream对象限制

> 请求中不能使用`ReadableStream`对象

对于常规的开发来说，主要的限制在前三条。最常见的场景是设置了自定义请求头和`Content-Type`类型不在支持的范围以内。