#!/usr/bin/env python

from gongke import gongke
import os
import sys
#import time
import signal

def save2file(zhangHaoFile,zhanghao_readlines):
    
    zhanghao = open(zhangHaoFile,"r+")
    zhanghao.truncate()
    zhanghao.write(''.join(zhanghao_readlines))
    zhanghao.close()
    
def handler(signal_num,frame):
    print "\nYou Pressed Ctrl-c "
    #print "count = %d" %count
    #newfile = list(zhanghao)[-count:]
    
#     print "print zhanghao_del $"
#     for i in zhanghao_del:
#         print "zhanghao_del:",i,
#     print "print done"        
        
    #newfile = [val for val in zhanghao_readlines if val not in zhanghao_del]
    
    print "newfile len = ",len(zhanghao_readlines) 

    save2file(zhangHaoFile, zhanghao_readlines)
    
    sys.exit(signal_num)

signal.signal(signal.SIGINT,handler)

mygongke = gongke("15605311234","000000")

#haoma = "053602976180"
#mygongke.get_kuandai(haoma,"./")

savePath = "./kuandai"

if not os.path.isdir(savePath):
    os.mkdir(savePath)
if len(sys.argv) <= 1:
    print "usage:%s file" % sys.argv[0]
    exit(-1)

zhangHaoFile = sys.argv[1]

zhanghao = open(zhangHaoFile,"r+")
zhanghao_readlines = zhanghao.readlines()
zhanghao.close()
zhanghao_del = []
count = len(zhanghao_readlines)
#zhanghao.seek(0)

for i in zhanghao_readlines[:]:
    print len(zhanghao_del),"#count=", count,"#",i[:-1],
    
    getfile = mygongke.get_kuandai(i[:-1],savePath)
    print " size=",getfile['file_size'],"#",getfile['mod_time']
    
    zhanghao_readlines.remove(i)    
    zhanghao_del.append(i)
    #time.sleep(1)
    count -=1
if len(zhanghao_readlines) == 0:
    save2file(zhangHaoFile, zhanghao_readlines)
