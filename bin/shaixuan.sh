#!/bin/bash

for i in `find $1`
	do
if [ -f $i ] ;then
	
j=`wc -l $i|cut -d ' ' -f 1`
	echo $i
if [  $j -eq 25 ];then

	echo mv $i to line-25

	mv $i line-25
fi

fi
done 
