#!/bin/bash
#sed -n 's/.*>>\(.*\)<\/LATN>/\1/p'
#sed -n 's/.*>\(.*\)<\/LATN>/\1/p'
#sed -n 's/\(.*\)<\/INSTALL_ADDR>/\1/p' 5406399.txt |sed -n 's/.*<INSTALL_ADDR>\(.*\)/\1/p'
id_file=/tmp/`date +%s`

find $1 >$id_file

trap "rm -f $id_file;echo rm -f ;exit" INT

echo find is done

line=`wc -l $id_file|cut -d ' ' -f 1`
echo $line
[[ $line -eq 0 ]] && rm -f $id_file && exit

let li=line/5000
let li=li+1 

while [ ! $li -eq 0 ]
do

for i in `head -5000 $id_file`
do
if [ -f $i ];then
echo $i

LATN=`sed -n 's/.*>\(.*\)<\/LATN>/\1/p' $i`
#echo $LATN

BUSI_NBR=`sed -n 's/.*>\(.*\)<\/BUSI_NBR>/\1/p' $i`

USER_NAME=`sed -n 's/.*<USER_NAME>\(.*\)/\1/p' $i|sed -n 's/.*\(.*\)<\/USER_NAME>/\1/p'`

CUST_NAME=`sed -n 's/.*<CUST_NAME>\(.*\)/\1/p' $i|sed -n 's/.*\(.*\)<\/CUST_NAME>/\1/p'`

INSTALL_NAME=`sed -n 's/.*<INSTALL_ADDR>\(.*\)/\1/p' $i|sed -n 's/.*\(.*\)<\/INSTALL_ADDR>/\1/p'`

CERTIFICATES_NBR=`sed -n 's/.*>\(.*\)<\/CERTIFICATES_NBR>/\1/p' $i`

#echo $USER_NAME
#echo $i

if [ ! -n "$USER_NAME" ];then
	USER_NAME=NULL
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
echo  -ne "$(echo $BUSI_NBR)\t$(echo $USER_NAME)\t$(echo $CUST_NAME)\t$(echo $INSTALL_NAME)\t'$(echo $CERTIFICATES_NBR)" >>$2.txt

echo >>$2.txt

fi

done

let li=li-1

sed -i '1,5000d' $id_file
echo sed

done

rm -f $id_file
