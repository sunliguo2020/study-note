#!/bin/bash
. functions
. liuyaninit
declare returnuserid=""
read formvalue
if test  -n "$formvalue";then
        IFS='&'
        declare $formvalue
        username=`echo "$username" | sed -e "s/+//g"`
        IFS=$'  \r\n'
fi
if test "$username" == "";then
	echo -n $'\n'
	echo "�û���Ϊ��"
	echo '<input type="button" value="��������" onClick="history.go(-1)">'
        exit 0
else
        checkuser $username $password
        userid=$returnuserid
        if test $userid -eq -1;then
		echo -n $'\n'
                echo "�û��������ڻ�������,����������!"
		echo '<input type="button" value="��������" onClick="history.go(-1)">'
                exit 1
        else
                cookieuserid=$userid
                echo "Set-Cookie: cookieuserid=$cookieuserid; path=/"
		echo -n $'\n'
		echo "�ɹ���¼"
		echo '<meta http-equiv="refresh" content="0;URL=authok.sh">'
		echo '<a href=authok.sh>�������û���Զ�ˢ�£��뵥������</a>'
                exit 0
        fi
fi
