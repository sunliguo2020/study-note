#!/bin/bash
#usage: authok.sh?&sorttype=...&startno=...
#sorttype: "change","create"
. functions
. liuyaninit

allarticlescount=`ls $liuyansdir | wc -l`
echo "Set-Cookie: cookieuserid=$cookieuserid; path=/"
echo -n $'\n'
echo '<html>'
echo '<head>'
echo '<title>����--�б�</title>'
echo '<meta http-equiv="Content-type" content="text/html; charset=GB2312">'
echo '</head>'
echo '<body>'

#echo '<a href="../zhangcheng.htm" target=_blank>�³�����֯�淶</a>&nbsp;&nbsp;<a href="../xuanyan.html" target=_blank>��Ա����</a><br><br>';
if test "$cookieuserid" != "0";then
	echo -n "�û�����"
	getusername $cookieuserid $usersdir/list | transtohtml
	echo "&nbsp;<a href=addnewlvren.html target=_blank>�����»�Ա</a>"
	echo "&nbsp;<a href=modifyuserinfo.sh target=_blank>�޸��û���Ϣ</a>"
	echo "&nbsp;<a href=listlvrens.sh target=_blank>��ʾ��Ա�б�</a>";
	#echo "&nbsp;<a href="../xinwen/index.html" target=_blank>�����¼</a>";
	#echo "&nbsp;<a href="xinwen.html" target=_blank>��д���¼</a>";
	#echo "&nbsp;<a href="upload.sh" target=_blank>�ϴ���Ƭ</a>";
else
	echo "���ȵ�¼";
	exit 1;
fi
echo -n "<br><br>"
test "$sorttype" == "" && sorttype=change
if test "$sorttype" == "change";then
	newsorttype="create"
	newsortstring="[�������ⴴ��ʱ������]"
	sortstring="�������ı�ʱ������"
else
	newsorttype="change"
	newsortstring="[�������ı�ʱ������]"
	sortstring="�������ⴴ��ʱ������"
fi
echo "$topstring($sortstring)" 
echo "&nbsp;<a href=liuyanrequest.sh?liuyanprefix=$liuyansdir&liuyantype=newtitle target=_blank>[����������]</a>"
echo "&nbsp;<a href=authok.sh?sorttype=$sorttype&startno=$startno>[ˢ��]</a>"
echo "&nbsp;<a href=authok.sh?sorttype=$newsorttype&startno=$startno>$newsortstring</a>"
echo "<br>"
echo ""
test "$startno" == ""&&startno=1
test ! "$startno" -gt 1&&zhidingfiles="`ls $zhidingsdir`"
liuyanfiles="$zhidingfiles"
test "$startno" == ""&&startno=1
if test "$allarticlescount" -lt "$startno";then
	files1=""
else
	if test "$sorttype" == "change";then
		files1="`ls -t $liuyansdir | tail -n $((allarticlescount-startno+1)) | head -n $linesperpage`"
	else
		files1="`ls  $liuyansdir | sort -r | tail -n $((allarticlescount-startno+1)) | head -n $linesperpage`"
	fi
fi
for i in $files1;do
	if echo $zhidingfiles | grep $i >/dev/null;then
		continue
	else
		liuyanfiles="$liuyanfiles $i"
	fi	
done
echo "<TABLE width=\"100%\" cellSpacing=\"0\" cellPadding=\"0\"  align=\"center\"  border=1  style=\"table-layout:fixed;word-break:break-all;WORD-WRAP: break-word\">"
echo "<tr>"
echo "<td width=\"50%\" align=center>"
echo "�� ��"
echo "</td>"
echo "<td width=\"10%\" align=center>"
echo "�ظ�/���"
echo "</td>"
echo "<td width=\"20%\" align=center>"
echo "���ⴴ��"
echo "</td>"
echo "<td width=\"20%\" align=center>"
echo "���ظ�"
echo "</td>"
echo "</tr>"
echo "</table>"
for i in $liuyanfiles;do
	if test ! -d $liuyansdir/$i;then
		continue;
	fi
	if echo $zhidingfiles | grep $i >/dev/null;then
		guding=guding
	else
		guding=""
	fi
	echo
	showonetitle $liuyansdir $i $guding
done
echo "<TABLE width=\"100%\" cellSpacing=\"0\" cellPadding=\"0\"  align=\"center\"  border=1  style=\"table-layout:fixed;word-break:break-all;WORD-WRAP: break-word\">"
echo "<tr>"
echo "<td width=\"50%\" align=center>"
echo "�� ��"
echo "</td>"
echo "<td width=\"10%\" align=center>"
echo "�ظ�/���"
echo "</td>"
echo "<td width=\"20%\" align=center>"
echo "���ⴴ��"
echo "</td>"
echo "<td width=\"20%\" align=center>"
echo "���ظ�"
echo "</td>"
echo "</tr>"
echo "</table>"
if test "$startno" -gt 1;then
	echo "<a href=authok.sh?sorttype=$sorttype&startno=$((startno-linesperpage))>[prev]</a>&nbsp;"
fi
pages=$((allarticlescount/linesperpage))
for (( i=0 ; pages-i ; i=i+1 )); do
	if test $((i*linesperpage+1)) -eq $startno;then
		echo "$((i+1))&nbsp;"	
	else
		echo "<a href=authok.sh?sorttype=$sorttype&startno=$((i*linesperpage+1))>[$((i+1))]</a>&nbsp;"	
	fi
done
if test $((allarticlescount%linesperpage)) -gt 0;then
	if test $((i*linesperpage+1)) -eq $startno;then
		echo "$((i+1))&nbsp;"	
	else
		echo "<a href=authok.sh?sorttype=$sorttype&startno=$((i*linesperpage+1))>[$((i+1))]</a>&nbsp;"
	fi
fi
if test $((startno+linesperpage-1)) -lt $allarticlescount;then
	echo "<a href=authok.sh?sorttype=$sorttype&startno=$((startno+linesperpage))>[next]</a>"
fi 
echo "<br><font size=-1>ע���ظ��������Ѿ�ɾ����������</font>"

printhtmlend
