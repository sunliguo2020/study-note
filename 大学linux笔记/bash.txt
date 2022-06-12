bash 的命令行提示符结构由 shell 变量$PS1 所提供，命令行提示符除了以正常的字符组成，
还能有一些特殊的字符组成
          一个 ASCII 的 bell 字符(07)
     \a
          输出时间“星期 月 日”
     \d
          主机名简写
     \h
          主机名全称
     \H
          当前终端后台有多少进程
     \j
          当前终端设备名
     \l
          回车符号
     \r
          新建一行
     \n
          当前使用的 shell 名
     \s
          24 小时制式 HH:MM:SS
     \t
          12 小时制式 HH:MM:SS
     \T
          12 小时制式 HH:MM AM/PM
     \@
          24 小时制式 HH:MM
     \A
          当前用户名
     \u
          bash 的版本
     \v
          bash 的发行号
     \V
          当前工作目录，详细
     \w
          当前工作目录，简单
     \W
          命令的历史纪录号
     \!
          本次登入了 shell，共执行了多少条命令
     \#
          UID 为 0，提示符是#，否则就是$
     \$
          输入三位八进制码，转换成相应的字符
     \nnn
          转义为\
     \\
          转义为[
     \[
          转义为]
     \]






\a   alert(bell)
     
\b   回格

 \r    回车符号

  \n  新建一行

\t     横向制表符

\v     纵向制表符

\\     转义反斜杠

\'     转义单引号

\nnn     转义三位八进制所对应的字符

\xHH     转义二位十六进制所对应的字符









从历史列表里重用命令的方法
命令          说明                                   举例
            运行第 n 个命令
!N                                               !2
            运行最后一个命令
!!                                               !!
            运行从倒数的第 n 个命令
!-N                                              !-2
            运行最后一个以 str 开头的命令
!str                                             !c
            运行最后一个命令行含有 str 字符的命令
!?str?                                           !?cat?
            运行最后一个命令行含有 str1 字符的命令并且在其后加上 str2
!{str1}str2                                      !{cd}/tmp
            运行最后一个命令行含有 str1 字符的命令并且将所有的 str1 替换
^str1^str2^                                      ^less^more^
            成 str2
            引用最后一个命令的参数作为 cmd 的参数
cmd !$                                           ls /tmp
                                                 stat !$
按<ctrl+r>可以从历史纪录的最后向上搜索






bash 的模式匹配
字符                    举例                    含义
                                            匹配零或多个字符
*                     ls *.c
                                            匹配任意单个字符
?                     ls conf.?
                                            匹配列表中的任意一个字符
[list]                ls conf.[co]
                                            匹配范围内的任意一个字符
[lower-upper]         ls libdd.7958[1-9].sl
                                            用{}中的内容作为扩展名
str{str1,str2,str3….} ls ux*.{aa,bb}
                                            主目录
~                     ls -a ~
                                            root 用户的主目录
~username             ls -a ~root








命令或者赋值             举例                    含义
                                         标准输入重定向：将.login 文件作为 wc -l 的输入，计算并列出行数

<                  wc –l < .login
                                                                                  标准输出重定向：将执行 ps 的结果输出到
>                  ps –ef>/tmp/proc
                                         /tmp/proc 文件中
                                         标准输出追加：将执行 ps 的结果追加到
>>                 ps –ef>/tmp/proc
                                         /tmpproc 文件中
                                         标准输出重定向：忽略 noclobber 变量设置，
>!                 ps –ef>!/tmp/proc
                                         如果/tmp/proc 存在，覆盖/tmp/proc
                                         标准输出追加：忽略 noclobber 变量设置，将
>>!                ps –ef>>!/tmp/proc
                                         结果追加到/tmp/proc 的末尾
0- standard input
1- starndard ouput
2- standard error
                                         将 program 文件 cat 到标准输出， 并将标准错
                   cat program 2>errors
                                         误重定向到 errors 文件
                                         将 program 文件 cat 到标准输出， 并将标准错
                   cat program 2>>errors
                                         误追加到 errors 文件
                                         用 find 命令在系统中找到所有以.c 结尾的文
                   find / -name ‘*.c’ \
                                         件，  并且输出到的 cprograms 文件中，然后将
                   >cprograms 2>errors
                                         所有错误输入到 errors 文件中
                                         同上，但是把错误结果也一起输出到了
                   find / -name ‘*.c’ \
                                         cprograms 文件中
                   >cprograms 2>&1

