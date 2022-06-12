#########################################################################
# File Name: /mnt/sdb3/bin/groupByDay.sh
# Author: sunliguo
# mail: sunliguo2006@qq.com
# Created Time: Mon 15 Jan 2018 01:18:05 PM CST
#########################################################################
#!/bin/bash

#for i in `find $PWD -maxdepth 1 -type f`
find $PWD -maxdepth 1 -type f | for i in `cat -`
do
	MOD_TIME=`stat -c %y $i|awk '{print $1}'`
	if [ ! -d $MOD_TIME ];then
		mkdir $MOD_TIME
	fi
	mv -v $i $MOD_TIME/
done
