#!/bin/bash
#
#20150808:添加408文件
#
#20150818:一行文件如果结尾没有0x0a wc 则判断为空行
#20160524:添加427文件夹

Cleanup(){
	if [  -f $sh_file ];then
	    printf "Cleaning up..."
	    rm -f $sh_file 2>/dev/null
	    echo "done" 
	fi
    }
EchoResult(){
	echo "file_two=" $file_two
	echo "file_zero=" $file_zero
	echo "file_160=" $file_160
	echo "file_408=" $file_408
	echo "file_427=" $file_427
}
trap "Cleanup;EchoResult&&exit 2" 1 2 3 15

MD5="4ac0f394c8607199747a4b4d8ed3da3b"
Fail_md5="1054a9137d0320af85d21550486a3d26"

sh_file=/tmp/`date +%s`

if [ ! $1 ];then
    find  -maxdepth 1 -name "*txt" -type f |sort >$sh_file
else
	 find $1 -name *txt  |sort >$sh_file
fi

[ ! -d line-2 ] && mkdir line-2
[ ! -d zero ] && mkdir zero
[ ! -d 160 ] && mkdir 160
[ ! -d 408 ] && mkdir 408
[ ! -d 427 ] && mkdir 427

file_two=0
file_zero=0
file_160=0
file_408=0
file_427=0
#trap "rm -f $sh_file;echo rm -f;exit " INT

echo find is done

line=`wc -l $sh_file|cut -d ' ' -f 1`

echo $line

count=$line

[[ $line -eq 0 ]] && exit

let li=line/5000
let li=li+1

while [ ! $li -eq 0 ]
do
for i in `head -5000 $sh_file`
do
   {
       #如果不是文件，跳出继续
        [ ! -f $i ] && continue
	file_line=`wc -l $i|awk {'print $1'}`
	file_wc=`wc -c $i|awk {'print $1'}`
	file_size=`ls -l $i|awk {'print $5'}`
	echo  count=$count:${i}:line=$file_line#wc=$file_wc
	if  [ 2 -eq $file_line ];then
		result=`md5sum $i|awk {'print $1'}`
		if [ $MD5  = $result ];then
			echo line-2 find one: $i
                        mv -v  $i line-2
			file_two=$(($file_two+1))
                      #  echo "mv  $i line-2"
		elif [ $file_wc -eq 408 ] || [ $file_wc -eq 409 ];then
		    mv -v $i 408
		    file_408=$(($file_408+1))
		elif [ $file_wc -eq 427 ];then
		    mv -v $i 427
		    file_427=$(($file_427+1))
	        fi   
	elif  [ $file_size -eq 0 ];then
		   echo $i size=0 
		   mv -v $i zero
		   file_zero=$(($file_zero+1))
	elif [ $Fail_md5 = `md5sum $i|awk {'print $1'}` ] || [ $file_size -eq 160 ];then
	        mv -v $i 160
		file_160=$(($file_160+1))
	fi  
	 count=$(($count-1))
	}
done 

let li=li-1

sed -i '1,5000d' $sh_file
echo sed

done

#rm -f $sh_file
Cleanup
EchoResult
