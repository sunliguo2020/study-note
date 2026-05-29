一般模式：移动游标的方式
 1: 以word 为单位移动
    w   :向右移动一个word的开头
    3w ：向右移动3个word
    b  :光标向左移动一个word
    e  :下一个word的最后一个字符
 2:移动到指定的字符
   fx  :当前行上查找下一个字符x find
        3fx
   Fx  :左方向
   tx  :
   Tx  :
 3:以匹配一个括号为目的的移动
   %  :<>  () {} [] 
 4:移动到指定的行
   j : 下移一行
   k : 上移一行
   l : 右移一个字母
   h : 左移一个字母
   G : 最后一行
   nG：第n行
   :n 将光标移动到第n行
   命令模式下："." 代表当前行 “$"代表正文最后一行 ".+5"表示当前行往下的第5行
   gg：第一行
   n<Enter>:向下移动N行
   50% :将光标定位到文件的中间
   90% ：跳到接近文件尾的地方
   M :屏幕的中央(Middle)
   L :屏幕的最下行(Lowest)
   nL:屏幕的倒数第n行
   H : Home
   ctrl+f : 向前翻屏
   ctrl+b : 向后翻屏
   ctrl+d :向后翻半屏
   ctrl+u :向后翻半屏

0 : Number 0 移动到这一行的第一个字符
$ :本行行尾
2$ :下一行的行尾
^ <Home>:本行第一个非空字符
n<space> : Number n , 游标向右移动这一行的N个字符.
9k :上移9行
3a!<Esc> :添加3个！


一般模式：搜索与替换
/word  向后查找word
?word  向前查找word
:n1,n2s/word1/word2/g  n1,n2为数字,在n1与n2行之间寻找word1这个字符串，并将该字符串改为word2！  
:1,$s/word1/word2/g  第一行到最后一行
:1,$s/word1/word2/gc 确认conform
:s/ab/AB             当前行用AB替换ab
:%s/ab/AB            用AB替换ab(所有行,但是一行只替换一次)
rc :用c替换光标所指向的当前字符
nrc:用c替换光标所指向的前n个字符

一般模式：删除、复制与粘贴
nx : 连续向后删除n个字符
dd ：删除一行
ndd: 删除游标所在的向下n列
d1G ：删除游标所在到第一行的所有资料
dG ：删除游标所在到组后一行的所有资料
d0： 删除游标所在处到该行的第一个字符
d$ :  删除游标所在处到改行最后一个字符
dw :删除光标右侧的字 
ndw : 删除光标右侧的n个字
ndb :
nyy
y1G
yG
 y0
y$
J 将游标所在行与下一行和成一行
c 重复删除多个资料， 10cj 向下删除10行
u 撤销前一个动作
. 重复最后一条修改正文的命令
ctrl+r 重做上一个动作

:n1,n2 w [filename] 将n1到n2的内容存为filename
:345w  file 第345行写入file
:1,.w file  第一行到当前行写入file
:n1,n2d 删除n1到n2行的内容
:n1,n2con3 将n1到n2行的内容复制到n3行后
:n1,n2mon3 将n1到n2行的内容移动到n3行后
:d 删除光标所在的行
:3d 删除第3行
:.,$d 删除当前行直正文的末尾
:/str1/,/str2/d 删除从字符串str1到str2的所有行
:recover 恢复文件
区块选择：
v: 字符选择，会将经过的地方反白选择
V：行选择会将游标经过的行反白选择
Ctrl+v 区块选择，可以用长方形的方式选择资料
y 将反白的地方复制
d 将反白的地方删除
多文档编辑
:n 编辑下一个文档
:N 编辑上一个文档
:files 列出目前这个vim的开放的所有档案

多视窗操作
:sp filename 分屏(上下)打开多个文件
ctrl+w+j ctrl+w+k  在两个视窗之间移动 或ctrl+w(连续按两次) 在不同窗口切换
:vsp filename 分屏(左右打开)多个文件
vi -o file1 file2 水平分割
vi -O file1 file2 垂直分割
vim 环境设定
~/.vimiffo
:set autoindent  自动缩排
:set backup
:set ruler       右下角的一些状态说明
:set showmode    左下角
:syntax (off|on) 语法高亮
:set ignorecase  忽略正则表达式中大小写字母的区别 
:set ruler   
:set tabstop=n
:set mk 将选项保存在当前目录的.exrc文件中
/etc/vimrc
~/.vimrc


帮助
:help
:help {subject} 
例 :help x :help deleting :help index :help CTRL-A :help 'number'

插件:
 taglist 

应用技巧:
:1,20s/^/#/g 1到20行开始加入# 注释
:1,20s/^/\/\/g 加入 //
2: 
  定义快捷键 :map 快捷键 执行命令
3: 替换命令
  ab  替换符 原始信息
4: 直接将其他文件内容导入当前文件 
  :r file
  :r !date 插入当前时间
5: K 帮助信息
6:
 :.,$-1s/^$\ // 从当前行到倒数第二行删除开始的#和空格
