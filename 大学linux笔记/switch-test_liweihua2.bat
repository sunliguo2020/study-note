@color fc
@echo ��һ�����л�����Ҳ����ļ�����ʾ��������,�����ȴ�����
@echo off
::@����ʾ�������echo off����������������������ͽ��������ʾ��
pushd c:\
del lwh.txt

for /L %%i in (248,1,254) do ping 222.206.96.%%i  -n 1 -w 100 -l 16|find "a" >>lwh.txt

for /L %%i in (247,1,253) do ping 222.206.97.%%i  -n 1 -w 100 -l 16|find "a" >>lwh.txt

for /L %%i in (250,1,254) do ping 202.194.249.%%i  -n 1 -w 100 -l 16|find "a" >>lwh.txt

for /L %%i in (252,1,254) do ping 202.194.250.%%i  -n 1 -w 100 -l 16|find "a" >>lwh.txt

for /L %%i in (251,1,254) do ping 202.194.247.%%i  -n 2 -w 100 -l 16|find "a" >>lwh.txt

for /L %%i in (253,1,254) do ping 202.194.246.%%i  -n 1 -w 100 -l 16|find "a" >>lwh.txt

                             ping 202.194.240.62   -n 1 -w 100 -l 16|find "a" >>lwh.txt 

                             ping 202.194.254.254  -n 1 -w 100 -l 16|find "a" >>lwh.txt

                             ping 202.194.96.61    -n 1 -w 100 -l 16|find "a" >>lwh.txt
exit
