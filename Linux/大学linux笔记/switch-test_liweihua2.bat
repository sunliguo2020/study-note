@color fc
@echo 第一次运行会出现找不到文件的提示，甭理它,继续等待即可
@echo off
::@则不显示该命令本身，echo off则此命令后的所有命令命令本身和结果都不显示。
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
