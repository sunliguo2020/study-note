#########################################################################
# File Name: phone_group.sh
# Author: sunliguo
# mail: sunliguo2006@qq.com
# Created Time: Mon 15 Jan 2018 01:18:05 PM CST
#########################################################################
#!/bin/bash
phone_header=(130 131 132 145 155 156 175 176 185 186)

while getopts 'md:' opt
do
	case $opt in
		m)
			findopt=" -maxdepth 1";;
		d)
			directory=$OPTARG
			echo "group directoyr is :" $directory
			;;
		?)
			echo "Invalid option -$OPTARG"
			exit;;
	esac
done

if [  -n  "$directory" ] ;then
	workdirectory=$directory
	#echo "work directory is not null"
else
	workdirectory=$PWD
fi
echo "workdirectory :" $workdirectory

if [ ! -d $workdirectory ];then
	echo $workdirectory is not a directory
	exit 1
fi


for phone in ${phone_header[*]}
do
echo $phone
	find $workdirectory $findopt  -type f -name ${phone}\* | for i in `cat -`
		do
			MOD_TIME=`stat -c %y $i|awk '{print $1}'`
			if [ ! -d ${phone}-${MOD_TIME} ];then
				mkdir ${phone}-${MOD_TIME}
			fi
			echo '$i='$i
			mv -vn $i ${phone}-${MOD_TIME}/
		done
done
