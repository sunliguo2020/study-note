Wget -非交互的网路下载器
  基本语法：
     wget [optin] ... [URL] ...
 -b 
 --background 
   后台
 -e command
 --execute command
 
 -o logfile
 --output-file-logfile
   记录所有的信息到 logfile . 正常情况下消息重定向标准错误输出.
  -a logfile
  --append-output=logfile
       添加到logfile. 这个同 -o 相同, 只是添加到logfile 而不是覆盖旧的logfile.如果logfile不存在,一个新文件将会创建.
   -d 
   --debug
   -q
   --quiet
      关闭wget的输出.
   -v
   --verbose
      详细输出所有有用的输出.这是默认的.
    -nv
    --no-verbose

