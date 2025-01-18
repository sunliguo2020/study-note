禁用视觉模式（Visual Mode）

在使用鼠标选择文本时，默认会进入视觉模式。

临时禁用     

​	vim命令模式>:set mouse-=a

永久禁用

​	在配置文件中.vimrc 添加 set mouse-=a

## 配置vi支持utf-8
```
set encoding=utf-8
set fileencodings=ucs-bom,utf-8,cp936,gb18030,gbk,gb2312,latin1
```
