　1. 显示环境变量HOME

　　$ echo $HOME

　　/home/redbooks

　　2. 设置一个新的环境变量hello

　　$ export HELLO="Hello!"

　　$ echo $HELLO

　　Hello!

　　3. 使用env命令显示所有的环境变量

　　$ env

　　HOSTNAME=redbooks.safe.org

　　PVM_RSH=/usr/bin/rsh

　　SHELL=/bin/bash

　　TERM=xterm

　　HISTSIZE=1000

　　...

　　4. 使用set命令显示所有本地定义的Shell变量

　　$ set

　　BASH=/bin/bash

　　BASH_VERSINFO=([0]="2"[1]="05b"[2]="0"[3]="1"[4]="release"[5]="i386-redhat-linux-gnu")

　　BASH_VERSION='2.05b.0(1)-release'

　　COLORS=/etc/DIR_COLORS.xterm

　　COLUMNS=80

　　DIRSTACK=()

　　DISPLAY=:0.0

　　...

　　5. 使用unset命令来清除环境变量

　　set可以设置某个环境变量的值。清除环境变量的值用unset命令。如果未指定值，则该变量值将被设为NULL。示例如下：

　　$ export TEST="Test..." #增加一个环境变量TEST

　　$ env|grep TEST #此命令有输入，证明环境变量TEST已经存在了

　　TEST=Test...

　　$ unset $TEST #删除环境变量TEST

　　$ env|grep TEST #此命令没有输出，证明环境变量TEST已经存在了

　　6. 使用readonly命令设置只读变量

　　如果使用了readonly命令的话，变量就不可以被修改或清除了。示例如下：

　　$ export TEST="Test..." #增加一个环境变量TEST

　　$ readonly TEST #将环境变量TEST设为只读

　　$ unset TEST #会发现此变量不能被删除

　　-bash: unset: TEST: cannot unset: readonly variable

　　$ TEST="New" #会发现此也变量不能被修改

　　-bash: TEST: readonly variable

　　环境变量的设置位于/etc/profile文件

　　如果需要增加新的环境变量可以添加下属行

　　export path=$path:/path1:/path2:/pahtN
