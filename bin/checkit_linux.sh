#!/bin/bash
#2015-02-06 添加区域ID参数，OrgID ，潍坊(0536)=106 济南(0531)=101
#2015-02-08 添加地域代码

#< value="99999">省公司</>
#< value="101">济南</>
#< value="102">青岛</>
#< value="103">淄博</>
#< value="104">德州</>
#< value="105">烟台</>
#< value="106">潍坊</>
#< value="107">济宁</>
#< value="108">泰安</>
#< value="109">临沂</>
#< value="110">菏泽</>
#< value="111">滨州</>
#< value="112">东营</>
#< value="113">威海</>
#< value="114">枣庄</>
#< value="115">日照</>
#< value="116">莱芜</>
#< value="117">聊城</>

 [ -z $1 ] && echo "参数为包含电话号码的文本文件"  
echo a
. myinit.sh
#15653105283 15653102571 15653102579 15615310077 15605318160 
denglu 15615310077 000000

#潍坊的电话
OrgID=105
echo 地域:$OrgID
referer2="http://61.156.3.60:9081/PB_INTERFACE/pgCusd_login_test/LZ_CUSD_ORDER.prCusd.prCustReportInit_Cusd.do"
NU_URL="http://61.156.3.60:9081/bwflow/scripts/basic/hiddensubmit.jsp"


i=$1
	
#j=`expr $1 + $2`
line=`wc -l $1|cut -d ' ' -f 1`

let li=line/5000
let li=li+1

file $1|grep text >/dev/null
#是否是包含电话号码的文件,还需要改进判断是否是电话号码
if [ $? ];then	

while [ ! $li -eq 0 ]
do

 for j in `head -5000 $1`

 do
POST_NU="bizAction=SA_C_ORDER_MAKE.bizCustFaultReport.bizGetPrdtInfo&BUSI_NBR="${j}"&custType=1&reportedOrgID=${OrgID}&prodClass=PSTN"

date '+%B-%d-%H:%M:%S' 

echo  -n $j
#echo $POST_NU

if [ ! -d $OrgID ];then
    mkdir $OrgID
fi

curl -A "$user_agent" -e $referer2 -d $POST_NU $NU_URL -b $COOKIE  >./$OrgID/$j.txt 2>/dev/null
echo "#size:" `ls -l $OrgID/$j.txt|awk '{print $5}'`
done 
	let li=li-1
	#删除前5000行，并修改文件。
	sed -i '1,5000d' $1
done

else
	echo "wen ben wenjian"
fi
