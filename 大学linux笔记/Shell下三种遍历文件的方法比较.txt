昨天一个同事遇到一个需求：

有一个日志文件A，当日志文件中的某行包含某个字符串BC时，将字符串EF变成EG，并输出到新文件。即：

Input，A:

asdfasdf

asdfasdBCasdfEFasd

 

output：

asdfasdf

asdfasdBCasdfEGasd

 

这个文件有500w+行。

最开始用如下脚本解决：

 

cat $1 | while read line
do
 echo $line | grep -q "BC"
if [ $? -eq 0 ] ; then
 echo $line | sed "s/EF/EG/g" >> $1.out
else
 echo $line >>$1.out
fi
done 

上述脚本在循环中使用了grep、sed等外部命令，由于外部命令要fork一个process，因此效率极为低下。初步估计，运行完要25个小时以上。因此将循环中的grep和sed替换掉，见如下：

cat $1 | while read line
do
    [[ "$line" == *"BC"* ]] && echo ${line/EF/EG} || echo ${line}
done

 
循环内部的代码简洁了很多，而且吧grep、sed等external command替换掉，在循环内部不会再有process 被fork出来。虽然执行效率提高很多，但也没有在我的耐心区间内得到结果，初步估算执行完需要半个小时以上。

问题应该不在循环内部，而是这种cat+while+read遍历文件内容的方式有问题。
 

换了awk的方式来做： 

#!/bin/awk -f

{
    if(match($0,"BC")){
        print gsub("EF","EG");
    }
    else{
        print $0;
    }
}

 这次效率有很大的提升，耗时18秒就出来了结果。按理说这已经比较满足需求了。
 

不过，我的同事又试了另外一种方法，用perl解决问题：

–这段代码是我一个同事写的。

 

#!/usr/bin/perl
open URLFILE, ">>aa";
my $cnt=0;

while (<>)
{

        if (/BC/)
        {
                s/EF/EG/g;
        }
        print URLFILE $_;
}

 

这段代码的执行效率很高，比awk效果还要好，13秒。

按理说，就读取文件的效率来说，perl虽然很快但应该不会比awk快。
 

只是这个Perl中所做的工作只是读取文件的一行，而awk在读取完一行后，还要按照分隔符将$0划分成一个个字段，分别存在$1,,,$n中，只是，我们这个需求并没有用到这个功能，用awk解决这个需求还是有点大材小用了。 

关于在shell下用什么方法来完成对文件的高效遍历，还有什么更好的方法吗？