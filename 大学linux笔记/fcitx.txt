Fedora Core 6中默认安装的SCIM输入法有一些问题，经常在使用中工作不正常。例如，有>时候在某些应用程序中输入中文时，候选词面板不显示，无法进行选词。 fcitx输入法在Fedora Core 6中表现地得更加稳定一些，因此这里介绍如何用fcitx来替换SCIM输入法。注意
这里使用英文界面，即en_US.UTF-8编码。首先下载fcitx ([url]http://www.fcitx.org/)[/url]可以下
载最新的tar包自己编译。编译的命令很简单：./configure make make install注意最后一
步需要使用root权限卸载SCIM输入法也不一定非得物理卸载SCIM，将之禁用就可以了。
首先在 /etc/X11/xinit/xinput.d/目录下建立一个新文件（fcitx.conf）：
XIM=fcitx
XIM_PROGRAM= /usr/local/bin/fcitx
XIM_ARGS="-d"
GTK_IM_MODULE=xim
QT_IM_MODULE=xim

然后在 /etc/alternatives/目录下，将符号链接xinputrc删除，重新建一个：
ln -s /etc/X11/xinit/xinput.d/fcitx.conf xinputrc
ln -s /etc/X11/xinit/xinput.d/fcitx.conf ~/.xinputrc
最后，在开始菜单>system>preferences>more preferences>input method里面选择fcitx作
为使用的输入法即可。配置fcitx输入法修改~/.fcitx/config文件中的相应偏好设置。最后
重新登录并启动xwindow就可以了。
