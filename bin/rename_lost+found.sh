#########################################################################
# File Name: rename_lost+found.sh
# Author: sunliguo
# mail: sunliguo2006@qq.com
# Created Time: Thu 25 Jan 2018 09:57:10 AM CST
#########################################################################
#!/bin/bash
for i in `find ./ -maxdepth 1 -type f |cat -`
do
	echo -n $i
	grep "BUSI_NBR" $i
done
