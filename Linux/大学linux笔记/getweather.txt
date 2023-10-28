ctcode=${1}

showversion()
{
    echo "Version 1.0 by Sipingal."
}
usage()
{
    echo "usage:getweather [citycode]    the default citycode is 296(深圳)"
    echo "                               -h --help  is for this screen."
    echo "The citycode:"
    cat << sipingal
125________北京
292________广州
252________上海
127________天津
212________重庆
115________沈阳
244________南京
211________武汉
166________成都
186________西安
82________石家庄
84________太原
189________郑州
103________长春
17________哈尔滨
69________呼和浩特
140________济南
248________合肥
287________厦门
255________杭州
276________福州
218________长沙
296________深圳
295________南宁
232________桂林
264________南昌
227________贵阳
1________香港
2________澳门
179________昆明
280________台北
150________拉萨
303________海口
57________兰州
56________西宁
78________银川
28________乌鲁木齐
sipingal
}

getcitycode()
{
    true=0 
    for num in 125 292 252 127 212 115 244 211 166 186 82 84 189 103 17 69 140 248 287 255 276 218 296 295 232 264 227 1 2 179 280 150 303 57 56 78 28
    do
    {
        if [ "${ctcode}" = "${num}" ]
	then
	    true=`echo ${true} + 1 |bc`
	else
	    continue
	fi
    }
    done

    if [ "${true}" = "1" ]
    then
    {
        citycode=${ctcode}
        getweather
        printweather
    }
    else
    {
        usage
    }
    fi
}

printweather()
{
    echo -e "天气\t\t$wheater"
    echo -e "温度\t\t$temp1"
    echo -e "风力\t\t$temp2"
    echo -e "紫外线\t\t$temp3"
    echo -e "空气\t\t$temp5"
}

getweather()
{

    #http://weather.qq.com/inc/ss${citycode}.htm
    wheater="`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $'| grep r_tembg5.gif | sed s'/.*"center">//'g |sed s'/<\/td>//'g`"
    temp1="`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $'  | perl -0 -ne 's/(tem1.gif.*)\n/$1/,print' | grep tem1.gif | sed s'/.*"center">//'g | sed s'/.*"center">//'g | sed s'/.*"center">//'g |sed s'/<\/td>//'g`"
    temp2=`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $'  | perl -0 -ne 's/(tem2.gif.*)\n/$1/,print' | grep tem2.gif | sed s'/.*"center">//'g | sed s'/.*"center">//'g | sed s'/.*"center">//'g |sed s'/<\/td>//'g`
    temp2="`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $' | perl -0 -ne 's/(tem2.gif.*)\n/$1/,print' | grep tem2.gif | sed s'/.*"center">//'g | sed s'/.*"center">//'g | sed s'/.*"center">//'g |sed s'/<\/td>//'g`"
    temp3="`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $'  | perl -0 -ne 's/(tem3.gif.*)\n/$1/,print' | grep tem3.gif | sed s'/.*"center">//'g | sed s'/.*"center">//'g | sed s'/.*"center">//'g |sed s'/<\/td>//'g`"
    temp5="`wget http://weather.qq.com/inc/ss${citycode}.htm -O /dev/stdout 2> /dev/null | tr '\t' ' ' |grep -v '^ $'  |grep -v '^  $' | grep -v '^   $'  | perl -0 -ne 's/(tem5.gif.*)\n/$1/,print' | grep tem5.gif | sed s'/.*"center">//'g | sed s'/.*"center">//'g | sed s'/.*"center">//'g |sed s'/<\/td>//'g`"
    #perl -0 -ne 's/(tem1.gif.*)\n/$1/,print'

}

# main

if [ "${ctcode}" = "" ]
then
{
    citycode=296
    getweather
    printweather
}
elif [ "${ctcode}" = "-H" ]
then
{
    usage
}
elif [ "${ctcode}" = "--help" ]
then
{
    usage
}
elif [ "${ctcode}" = "-V" ]
then
{
    showversion
}
elif [ "${ctcode}" = "--version" ]
then
{
    showversion
}
else
{   
    getcitycode
}
fi
