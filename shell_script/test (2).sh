#!/bin/bash
echo -n $'Content-type: text/html\n'
echo -n $'\n'
echo "<html> <head> <meta http-equiv=\"Content-Type\" content=\"text/html; charset=gb2312\"> </head> <body> ѡ���Կ�Ŀ: <form action=question.sh method=POST> <input type=hidden name=hiddensubject value=\"0\"> <input type=hidden name=hiddenno value=\"0\"> <input type=hidden name=hiddennextquestion value=\"0\"> <select name=\"truesubject\">"
{
while read lessonname lessonfullname;do
	echo "  <option>${lessonfullname}"
done
} <lessons
echo " </select><p> ��֤��:<input type=text name=rand><p> ����:<input type=text name=\"truename\" ><p> ѧ��:<input type=text name=\"trueno\"><p> �绰(����,��������ľ���):<input type=text name=\"truephone\"><p> <input type=submit value=\"ok\">(��ȷ��׼ȷ������ok) </form> </body> </html>"

