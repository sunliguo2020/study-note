# 阿里云主机更换操作系统（Debian）

### 创建新用户

如果只用useradd 用户名  默认不创建用户主目录

```
useradd -D sunliguo
```

### 改变运行级别（我只喜欢命令行）

```
systemctl get-default
systemctl set-default multi-user.target
```

### 安装nginx

```
apt-get install nginx
```

#### 添加虚拟主机

在/etc/nginx/conf.d新建文件virtual.conf

```
#
# A virtual host using mix of IP-, name-, and port-based configuration
#
#server {
#       listen 80;
#       server_name sunliguo.com;
#
#       return 301 http://blog.sunliguo.com$request_uri;
#
#}

server {
    listen       80;
    server_name  guotu.sunliguo.com;

    location / {
        include uwsgi_params;
        uwsgi_pass 127.0.0.1:8997;
#       uwsgi_param UWSGI_SCRIPT ITAM.wsgi;
#       uwsgi_param UWSGI_CHDIR /root/ITAM/;

    }
    location ^~ /static {

        alias /usr/share/nginx/static;

        }
}

server {
    listen       80;
    server_name  blog.sunliguo.com;
    root /usr/share/nginx/blog/;

    location / {
        try_files $uri $uri/ /index.php?$args;

        index  index.php index.html index.htm;
    }

    location ~ \.php$ {
        fastcgi_pass 127.0.0.1:9000; #指定FastCGI服务器如何传递请求
#       fastcgi_pass unix:/run/php-fpm/www.sock;
        fastcgi_index index.php;
        include fastcgi_params;
        fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
#       #fastcgi_param PATH_INFO $fastcgi_script_name;
        fastcgi_connect_timeout 300s;
        fastcgi_send_timeout 300s;
        fastcgi_read_timeout 300s;
        #fastcgi_buffer_size 128k;
        fastcgi_buffers 8 128k;
        }

}

```



### 安装数据库

```
apt install mariadb-server
```

修改密码：

```
FLUSH PRIVILEGES;
USE mysql;
ALTER USER 'root'@'localhost' IDENTIFIED BY '新密码';
```

创建数据库：

```
CREATE DATABASE mydatabase
  CHARACTER SET utf8mb4
  COLLATE utf8mb4_general_ci;
```

导入数据库

```
mysql -uroot -p blog <blog.sql
```


安装php

```
apt install php
```

```
apt-get install php-fpm
systemctl restart php8.2-fpm
```

**Configure Nginx to Use PHP-FPM:**

```
user = www-data
group = www-data
listen = /run/php/php8.2-fpm.sock
pm = dynamic
pm.max_children = 50
pm.start_servers = 5
pm.min_spare_servers = 2
pm.max_spare_servers = 10
```

```
server {
    listen 80;
    server_name test.example.com www.test.example.com;
    root /var/www/test.example.com;

    location / {
        index index.php index.html;
        try_files $uri $uri/ /index.php?$query_string;
    }

    location ~ \.php$ {
        include snippets/fastcgi-php.conf;
        fastcgi_pass unix:/run/php/php8.2-fpm.sock;
    }

    location ~ /\.ht {
        deny all;
    }
}
```

#### php扩展

```
apt install php-zip
apt install php-gd
```

