@pushd c:\
::将目录转到c盘下，@表示不显示命令本身，但显示命令结果的
@del lwh.txt
::删除以前生成过的结果文件
@color fc
::设置颜色
@for /L %%i in (248,1,254) do ping 222.206.96.%%i -n 1 -w 100 -l 16|find "a" >>lwh.txt
@for /L %%i in (247,1,253) do ping 222.206.97.%%i -n 1 -w 100 -l 16|find "a" >>lwh.txt
:: /L表示递增，所以起始值<结束值，前为起始值，中为步进，后为结束值，要用%%来扩展i，换成%i则命令不能执行。find后的a也可换成别的值，我随便加的而已
@echo 逸夫楼 is over.
::向用户显示一个结果。echo 与linux中的不同，win下如果加""则""也会显示出来，而linux却不
@pause
::暂停
@color f2
@for /L %%i in (250,1,254) do ping 202.194.249.%%i -n 1 -w 100 -l 16|find "a" >>lwh.txt
@echo 办公楼普通段finish.
@pause
@color fd
@for /L %%i in (252,1,254) do ping 202.194.250.%%i -n 1 -w 100 -l 16|find "a" >>lwh.txt
@echo 办公楼高级段end.
@pause
@color f6
@for /L %%i in (251,1,254) do ping 202.194.247.%%i -n 2 -w 100 -l 16|find "a" >>lwh.txt
@echo 二号楼conclude。经验显示：2号楼第一个answer包响应事件可能大于100ms，故发2次。
@pause 
@color f0
@for /L %%i in (253,1,254) do ping 202.194.246.%%i -n 1 -w 100 -l 16|find "a" >>lwh.txt
@echo 一号楼close,三号楼又开始再加上出口的山大地址~
ping 202.194.240.30  -n 1 -w 100 -l 16|find "a" >>lwh.txt
ping 202.194.252.254 -n 1 -w 100 -l 16|find "a" >>lwh.txt
ping 202.194.254.254 -n 1 -w 100 -l 16|find "a" >>lwh.txt
ping 202.194.96.61   -n 1 -w 100 -l 16|find "a" >>lwh.txt
@echo 新增的4号楼和老图的部分残余交换设备
@for /L %%i in (250,1,254) do ping 202.194.248.%%i -n 2 -w 100 -l 16|find "a" >>lwh.txt
ping 202.194.245.1 -n 1 -w 100 -l 16|find "a" >>lwh.txt
rem 这是个与汇聚相连的二层交换设备，intel 530T switch。
@echo 按任意键结束所有交换机的测试唠并退出窗口拉
@echo 去c:\lwh.txt看有无问题吧。
@pause
@exit
::结束,加与不加都可以的，默认没有命令就自动调用exit的。
