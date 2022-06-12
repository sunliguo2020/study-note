#!/bin/bash
#外网查询手机号资料
#2015-02-06 添加区域ID参数，OrgID ，潍坊(0536)=106 济南(0531)=101
#2015-02-08 添加地域代码
#2016-07-22 添加自动删除已查询的号码
trap "Cleanup $1 &&exit 2" 1 2 3 15

Cleanup (){
	if [ -n "$count" ];then
		echo "count="$count
	#	echo "$1 = " $1
		tail -$count $1 > ./$1.temp
		mv $1.temp $1
	
	fi

}

[ -z $1 ] && echo "参数为包含手机号码的文本文件"  

. myinit.sh
#15653105283 15653102571 15653102579 15615310077 15605318160 
#denglu 15615310077 000000
denglu 15653613135 sg123456

OrgID=106
echo 地域:$OrgID

referer2="http://218.56.65.202:9081/PB_INTERFACE/pgCusd_login_test/LZ_CUSD_ORDER.prCusd.prCustReportInit_Cusd.do"
NU_URL="http://218.56.65.202:9081/bwflow/scripts/basic/hiddensubmit.jsp"

i=$1
	
line=`wc -l $1|cut -d ' ' -f 1`

count=$line

let li=line/5000
let li=li+1

file $1|grep text >/dev/null
#是否是包含手机号码的文件,还需要改进判断是否是电话号码
if [ $? ];then	

while [ ! $li -eq 0 ]
do

 for j in `head -5000 $1`
 do
 
POST_NU="bizAction=SA_C_ORDER_MAKE.bizCustFaultReport.bizGetPrdtInfo&BUSI_NBR="${j}"&custType=1&reportedOrgID=${OrgID}&prodClass=BANDVIP"
date '+%B-%d-%H:%M:%S' 

echo  count=$count
echo  -n $j

if [ ! -d $OrgID ];then
    mkdir $OrgID
fi

curl -A "$user_agent" -e $referer2 -d $POST_NU $NU_URL -b $COOKIE  >./$OrgID/$j.txt 2>/dev/null
echo "#size:" `ls -l $OrgID/$j.txt|awk '{print $5}'`
count=$(($count-1))
done 
	let li=li-1
	#删除前5000行，并修改文件。
	sed -i '1,5000d' $1
done
else
	echo "wen ben wenjian"
fi
