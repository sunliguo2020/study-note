上面说过，可以通过命令行配置webalizer，也可以通过配置文件进行配置，在本文中我们将介绍使用命令行参数进行配置，需要了解配置文件使用方法的朋友可以参考README文件，里面有很详细的介绍。
可以执行webalizer –h得到所有命令行参数：
Usage: webalizer [options] [log file]
-h = 打印帮助信息
-v -V = 打印版本信息
-d = 打印附加调试信息
-F type = 日志格式类型. type= (clf | ftp | squid)
-i = 忽略历史文件
-p = 保留状态 (递增模式)
-q = 忽略消息信息
-Q = 忽略所有信息
-Y = 忽略国家图形
-G = 忽略小时统计图形
-H = 忽略小时统计信息
-L = 忽略彩色图例
-l num = 在图形中使用数字背景线
-m num = 访问超时 (seconds)
-T = 打印时间信息
-c file = 指定配置文件
-n name = 使用的主机名
-o dir = 结果输出目录
-t name = 指定报告题目上的主机名
-a name = 隐藏用户代理名称
-r name = 隐藏访问链接
-s name = 隐藏客户
-u name = 隐藏URL
-x name = 使用文件扩展名
-P name = 页面类型扩展名
-I name = index别名
-A num = 显示前几名客户类型
-C num = 显示前几名国家
-R num = 显示前几名链接
-S num = 显示前几名客户
-U num = 显示前几名URLs
-e num = 显示前几名访问页面
-E num = 显示前几名不存在的页面
-X = 隐藏个别用户
-D name = 使用dns缓存文件
-N num = DNS 进程数 (0=禁用dns)

假设，web服务器主机名为www.test.com，统计站点域名为www.test.com，访问日志为/var/log/httpd/access_log, 我们将webalizer分析结果输出到/var/www/html/log下面。则我们可以建立以下脚本/etc/rc.d/webalizer：

#!/bin/sh
run=/usr/sbin/webalizer
$run -F clf -p -n " " -t "www.test.com"
-o /var/www/html/log /var/log/httpd/access_log

说明：

-F clf 指明我们的web日志格式为标准的一般日志文件格式(Common Logfile Format)
-p 指定使用递增模式，这就是说每作一次分析后，webalizer会生产一个历史文件，这样下一次分析时就可以不分析已经处理过的部分。这样我们就可以在短时间内转换我们的日志文件，而不用担心访问量太大时日志文件无限增大了。
-n “ “ 指定服务器主机名为空，这样输出结果会美观一些。
-t “www.test.com” 指定输出结果标题.
/var/log/httpd/access_log:指定日志文件

然后在/etc/crontab中加入：
01 1 * * * root /etc/rc.d/webalizer
即每天凌晨1点执行该脚本。
然后运行/etc/rc.d/init.d/crond reload重载入crond服务。

测试：
执行以下命令:
# /etc/rc.d/webalizer
然后在浏览器中访问http://www.test.com/log/就可以看到webalizer的分析结果了。 
