# Local vs. UTC
首先重要的问题是你使用utc还是local time.
UTC(Universal Time Coordinated)=GMT(Greenwich Mean Time)
Local time 是你手表上的时间

传统的POSIX计算机(Solaris,bsd,unix)使用UTC格式
linux可以处理UTC时间和蹩脚的Windows所使用的local time

到底是使用UTC还是local time可以这样来确定：
如果机器上同时安装有Linux和Windows，建议使用local time
如果机器上只安装有Linux，建议使用utc
确定后编辑/etc/sysconfig/clock, UTC=0 是local time; UTC=1 是UTC(GMT)

#查看当前时区
 more /etc/sysconfig/clock
# 确定timezone
运行tzselect,回答问题后会告诉你时区的名称，比如"Asia/Shanghai",把他记下来(后面我用$timezone代替)

# 设定timezone
 cp /usr/share/zoneinfo/$timezone /etc/localtime

# 重新启动或者运行时钟设置脚本使之发生作用

#将当前时间写入BIOS永久生效 
hwclock
