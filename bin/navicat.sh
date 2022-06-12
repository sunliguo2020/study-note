#!/bin/bash

#20150801 1:iconv -c 忽略无效字符
#	  2:去掉变量前后空格 echo $(echo " 12 34  ") 生成完文件再改变字符

id_file=./`date +%s`
find $1 -name "*txt" >$id_file


#trap "rm -f $id_file;echo rm -f ;exit" INT

echo find is done
echo \$id_file =$id_file

line=`wc -l $id_file|cut -d ' ' -f 1`
count=$line
echo $line
[[ $line -eq 0 ]] && rm -f $id_file && exit

let li=line/5000
let li=li+1 

while [ ! $li -eq 0 ]
do

for i in `head -5000 $id_file`
do
if [ -f $i ];then
	echo $count:$i
fi
file_mod_time=`stat -c %y $i|awk -F. '{print $1}'`

sed  "s/<\/root>/\<mod_time\>$file_mod_time<\/mod_time><\/root>/g" $i >>out.csv
count=$(($count-1))

done
let li=li-1
sed -i '1,5000d' $id_file
echo sed
done
