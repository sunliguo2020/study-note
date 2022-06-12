#!/bin/bash

#20150801 1:iconv -c 忽略无效字符
#	  2:去掉变量前后空格 echo $(echo " 12 34  ") 生成完文件再改变字符

dflag=0
aflag=0
cflag=0
count=0

while getopts d:a:c: name
do
    case $name in
	d) dflag=1
	   dval=$OPTARG
	    ;;
	a) aflag=1
	    aval=$OPTARG
	    ;;
	c) cflag=1
	    cval=$OPTARG
	    ;;
	\?) echo "USAGE:`basename $0` [-d dictory] [-a name]"
    esac
done

if [ -z $aval ]||[ -z $dval ];then
    echo "USAGE:`basename $0` [-d dictory] [-a outfilename ] [-c 要处理的文件名的列表]"
    exit 2
fi 

if [ $cflag -eq 1 ];then
	id_file=$cval
else
	id_file=./$dval-`date +%s`
	find $dval -name "*txt" >$id_file
fi


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

PROD_INST_ID=`sed -n 's/.*>\(.*\)<\/PROD_INST_ID>/\1/p' $i`
LATN=`sed -n 's/.*>\(.*\)<\/LATN>/\1/p' $i`
BUSI_NBR=`sed -n 's/.*>\(.*\)<\/BUSI_NBR>/\1/p' $i`
USER_NAME=`iconv -f gb2312 -t utf8 -c $i|sed -n 's/.*>\(.*\)<\/USER_NAME>/\1/p'`
CUST_NAME=`iconv -f gb2312 -t utf8 -c $i|sed -n 's/.*>\(.*\)<\/CUST_NAME>/\1/p'`
CUST_ID=`sed -n 's/.*>\(.*\)<\/CUST_ID>/\1/p' $i`
INSTALL_NAME=`sed -n 's/.*>\(.*\)<\/INSTALL_NAME>/\1/p' $i`
CERTIFICATES_NBR=`sed -n 's/.*>\(.*\)<\/CERTIFICATES_NBR>/\1/p' $i`
file_mod_time=`stat -c %y $i|awk -F. '{print $1}'`

if [ ! -n "$USER_NAME" ];then
	USER_NAME=NULL
fi
if [ ! -n "$BUSI_NBR" ];then
	BUSI_NBR=`basename $i .txt`
fi
if [ ! -n "$CUST_NAME" ];then
	CUST_NAME=NULL
fi
if [ ! -n "$INSTALL_NAME" ];then
	INSTALL_NAME=NULL
fi
if [ ! -n "$CERTIFICATES_NBR" ];then
	CERTIFICATES_NBR=NULL
fi
if [ ! -n "$INSTALL_NAME" ];then
	INSTALL_NAME=NULL
fi
#echo $PROD_INST_ID
#echo aa
#echo $BUSI_NBR
#echo  -ne "$(echo $BUSI_NBR)\t$(echo $USER_NAME)\t$(echo $CUST_NAME)\t'$(echo $CERTIFICATES_NBR)"|iconv -f gb2312 -t utf8 -c  >>$1.phone.no
echo  -ne "\"$(echo $PROD_INST_ID)\",\"$(echo $LATN)\",\"$(echo $BUSI_NBR)\",\"$(echo $USER_NAME)\",\"$(echo $CUST_NAME)\",\"$(echo $CUST_ID)\",\"$(echo $CERTIFICATES_NBR)\",\"$file_mod_time\"\n" >>${aval}.phone.csv
fi
count=$(($count-1))
done
let li=li-1
sed -i '1,5000d' $id_file
echo sed
done

#rm -f $id_file
