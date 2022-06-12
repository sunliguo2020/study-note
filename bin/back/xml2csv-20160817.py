#!/usr/bin/env python
# -*- coding: utf-8 -*-
'''
Created on 2016-7-14
处理xml保存到文件（csv格式）或者数据库
中文名的文件有问题
2016-7-28
    添加默认数据表
@author: sunliguo
'''
import xml.dom.minidom
import os
import time
import sys
import MySQLdb

class xml2csv:
    def __init__(self):
        self.phone_deal = {
                     'PROD_INST_ID':'',
                     'LATN':'',
                     'BUSI_NBR':"",
                     'USER_NAME':'',
                     'CUST_NAME':'',
                     'CUST_ID':'',
                     'INSTALL_ADDR':'',
                     'PROD':'',
                     'BRAND':'',
                     'COMBO':'',
                     'CITY_TYPE':'',   
                     'CUST_TYPE':'',   
                     'STRATE_GROUP':'',   
                     'VIP_LEVEL':'', 
                     'CUST_LEVEL':'',   
                     'USER_STATE':'',
                     'ORG_ID':'',     
                     'CERTIFICATES_NBR':'' 
                     }
    def parse(self,path):
        #print "path=",path
        if os.path.isfile(path):
			#文件最后修改时间 考虑linux上的时区问题
            #file_modtime = os.stat(path).st_mtime 
            file_modtime = time.strftime("%Y-%m-%d %H:%M:%S",time.gmtime(os.path.getmtime(path)+8*3600))
            #print "file_modtime= ",file_modtime,type(file_modtime)
            
            xmlfile = open(path)
            #replace 非法字符的处理 文件原先什么编码还没有判断
            replace_utf8=xmlfile.read().decode('gb2312',"replace").encode('UTF-8').replace('GB2312','UTF-8')
            xmlfile.close()
            #print replace_utf8
        else:
            print "path %s is not file" % path
            replace_utf8=""
            return False        
        #创建临时文件
		#open('./linshi.txt',"w").write(replace_utf8)
        with open('./linshi.txt',"w") as a:
            a.write(replace_utf8)
        #a.close()
        #如果不是xml的处理
        try:
            DOMTREE = xml.dom.minidom.parse('./linshi.txt')
            Data = DOMTREE.documentElement
        except:
            print  "%s xml parser error" % path
            return False
        #查找phone_deal 中的关键字
        for i in self.phone_deal.keys():
            #print "i is %s " % i
            #print self.phone_deal[i]
            try:
                #Data.getElementsByTagName(i) 
                self.phone_deal[i]=Data.getElementsByTagName(i)[0].childNodes[0].data
            except Exception,exp:
                self.phone_deal[i]='NULL'
                #print "Not find %s" % i
        #添加文件最后修改时间
        self.phone_deal["mod_time"]= str(file_modtime)
        #如果没有提取到BUSI_NBR字段，补充该文件的路径
        if self.phone_deal["BUSI_NBR"] =="NULL":
            self.phone_deal["BUSI_NBR"]=path
        #如果没啥问题，就返回phone_deal    
        return self.phone_deal
		
    def save2file(self,xml_result="",savefile="defaultSavefile.txt"):
        if not xml_result:
            return False
        #记录一行文件的列序
        fileStruct =("PROD_INST_ID",
                     "CUST_ID",
                     "LATN",
                     "BUSI_NBR",
                     "USER_NAME",
                     "CUST_NAME",
                     "INSTALL_ADDR",
                     "CERTIFICATES_NBR",
                     "mod_time")
		#保证首行有文件头
        if (os.path.isfile(savefile) and os.path.getsize(savefile) == 0) or not os.path.exists(savefile):
            with open(savefile,"w") as c:
                c.write(repr(fileStruct).replace("(",'').replace(")","").replace("'","")+'\n')
                #c.write(repr(fileStruct))
        str=[]
        for i in fileStruct:
            str.append(xml_result[i])
        str2=""
        for i in str:
            str2+='"'+i+'"'+","
        write_str=str2[:-1]
        with open(savefile,"a") as b:
            b.write(write_str.encode('utf-8')+'\n')
           
    def save2mysql(self,xml_result="",table="xml2sql"):
        cursor.execute("show tables")
        #返回值list_table =  ((u'0632',), (u'0633',), (u'0635-back',), (u'0635-pyxml-20160701',), (u'0635-quan',), (u'xml2sql',))
        #元祖的元祖
        list_table = cursor.fetchall()
        #print "list_table = ",list_table
        if table not in list_table[0]:
          try:
            print "creating tables %s =====" %table
            cursor.execute ( "CREATE TABLE `%s` ( \
`PROD_INST_ID` varchar(255) DEFAULT NULL,\
`CUST_ID` varchar(255) DEFAULT NULL,\
`LATN` varchar(255) DEFAULT NULL,\
`BUSI_NBR` varchar(255) DEFAULT NULL,\
`USER_NAME` varchar(255) DEFAULT NULL,\
`CUST_NAME` varchar(255) DEFAULT NULL,\
`INSTALL_ADDR` varchar(255) DEFAULT NULL,\
`CERTIFICATES_NBR` varchar(20) DEFAULT NULL,\
`mod_time` datetime DEFAULT NULL )\
ENGINE=MyISAM DEFAULT CHARSET=utf8;" % table)
          except Exception,e:
            print "create tables %s error" % table
            print "error %s" % e
            exit(-1)
        #exit(-1)
        if cursor in dir():
            print "error"
            return -1

        try :
            cursor.execute('insert into `%s` values("%s","%s","%s","%s","%s","%s","%s","%s","%s")' \
                              %(table,xml_result['PROD_INST_ID'],
                                xml_result["CUST_ID"],
                                xml_result["LATN"],
                                xml_result["BUSI_NBR"],
                                xml_result["USER_NAME"],
                                xml_result["CUST_NAME"],
                                xml_result["INSTALL_ADDR"],
                                xml_result["CERTIFICATES_NBR"],
                                xml_result["mod_time"]))
        except:
            print "cursor.execute error"
        
parser = xml2csv()

try :
    conn = MySQLdb.connect(host="192.168.10.102",
                            port=3306,
                            user="root",
                            passwd="",
                            db="guhua",
                            charset="utf8"
                            )
    cursor = conn.cursor()
except:
    print "connect mysql error"
    exit(-1)

# result=parser.parse("3419d95.txt")
# print type(result)
# print result
# if  result:
#     parser.save2file(result, "savefile")
#save to file
# if len(sys.argv) != 0:
#     count=1
#     for i in os.walk(sys.argv[1]):
#         for j in i[2]:
#             print "count=",count,":",i[0]+os.path.sep+j
#             result = parser.parse(i[0]+os.path.sep+j)
#             if  result:
#                 parser.save2file(result, "savefile2")
#             count+=1

#save to mysql
if len(sys.argv) != 0:

    count=1
    for root,dictorys,files in os.walk(sys.argv[1]):
        for j in files:
            #print "root = ",root
            #print "files = ",j
            print "count=",count,":",root+os.path.sep+j
            result = parser.parse(root+os.path.sep+j)
            if  result:
                #print type(result['USER_NAME'])
                parser.save2mysql(result,"0632")
                #cursor.execute("insert into xml2sql values(1,'2',3,4,5,6,7,8,9)")
                #print cursor.fetchall()
            count+=1