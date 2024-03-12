## Django中跨域解决方法

### 1、安装django-cors-headers

```
pip install django-cors-headers
```

### 2 、设置全局文件

```
INSTALLED_APPS = [
....
'corsheaders',
]

MIDDLEWARE = [
    'corsheaders.middleware.CorsMiddleware',
    'django.middleware.security.SecurityMiddleware',
    ...
    ]
    
 # 跨域
CORS_ALLOW_CREDENTIALS = True  # 允许跨域是携带Cookie，默认为False
CORS_ORIGIN_ALLOW_ALL = True    # 指定所有域名都可以访问后端接口，默认为Flase

```

