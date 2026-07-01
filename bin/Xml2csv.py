#!/usr/bin/env python3
"""
处理XML文件，提取数据保存到CSV文件或数据库

用法:
    python Xml2csv.py <目录路径>

功能:
    解析指定目录下的XML文件，提取手机号相关信息并保存到CSV或MySQL
"""
import xml.dom.minidom
import os
import sys
import time
import MySQLdb


class Xml2csv:
    """解析XML文件，提取phone_deal数据"""

    def __init__(self):
        self.phone_deal = {
            'PROD_INST_ID': '',
            'LATN': '',
            'BUSI_NBR': "",
            'USER_NAME': '',
            'CUST_NAME': '',
            'CUST_ID': '',
            'INSTALL_ADDR': '',
            'PROD': '',
            'BRAND': '',
            'COMBO': '',
            'CITY_TYPE': '',
            'CUST_TYPE': '',
            'STRATE_GROUP': '',
            'VIP_LEVEL': '',
            'CUST_LEVEL': '',
            'USER_STATE': '',
            'ORG_ID': '',
            'CERTIFICATES_NBR': ''
        }
        self.tempfile = f'./{int(time.time())}'

    def __del__(self):
        """清理临时文件"""
        if os.path.isfile(self.tempfile):
            os.remove(self.tempfile)

    def parse(self, path):
        """解析XML文件"""
        if not os.path.isfile(path):
            print(f"path {path} is not file")
            return False

        file_modtime = time.strftime(
            "%Y-%m-%d %H:%M:%S",
            time.gmtime(os.path.getmtime(path) + 8 * 3600)
        )

        with open(path, 'rb') as xmlfile:
            raw_data = xmlfile.read()

        # 尝试检测编码并转换
        try:
            content = raw_data.decode('gb2312', "replace").encode('UTF-8')
            content = content.replace(b'GB2312', b'UTF-8')
        except Exception:
            content = raw_data

        with open(self.tempfile, "wb") as a:
            a.write(content)

        try:
            DOMTREE = xml.dom.minidom.parse(self.tempfile)
            Data = DOMTREE.documentElement
        except Exception as e:
            print(f"{path} xml parser error: {e}")
            return False

        for key in self.phone_deal.keys():
            try:
                self.phone_deal[key] = Data.getElementsByTagName(key)[0].childNodes[0].data
            except Exception:
                self.phone_deal[key] = 'NULL'

        self.phone_deal["mod_time"] = str(file_modtime)

        if self.phone_deal["BUSI_NBR"] == "NULL":
            self.phone_deal["BUSI_NBR"] = path

        return self.phone_deal

    def save2file(self, xml_result="", savefile="defaultSavefile.txt"):
        """保存到CSV文件"""
        if not xml_result:
            return False

        fileStruct = (
            "PROD_INST_ID", "CUST_ID", "LATN", "BUSI_NBR",
            "USER_NAME", "CUST_NAME", "INSTALL_ADDR",
            "CERTIFICATES_NBR", "mod_time"
        )

        if not os.path.exists(savefile) or os.path.getsize(savefile) == 0:
            with open(savefile, "w", encoding='utf-8') as c:
                c.write(','.join(fileStruct) + '\n')

        row = ','.join(f'"{xml_result.get(k, "")}"' for k in fileStruct)
        with open(savefile, "a", encoding='utf-8') as b:
            b.write(row + '\n')

    def save2mysql(self, cur, xml_result="", table="xml2sql"):
        """保存到MySQL"""
        if not xml_result:
            return

        cur.execute("SHOW TABLES")
        tables = [row[0] for row in cur.fetchall()]

        if table not in tables:
            print(f"Creating table {table}...")
            cur.execute(f"""
                CREATE TABLE `{table}` (
                    `PROD_INST_ID` varchar(255) DEFAULT NULL,
                    `CUST_ID` varchar(255) DEFAULT NULL,
                    `LATN` varchar(255) DEFAULT NULL,
                    `BUSI_NBR` varchar(255) DEFAULT NULL,
                    `USER_NAME` varchar(255) DEFAULT NULL,
                    `CUST_NAME` varchar(255) DEFAULT NULL,
                    `INSTALL_ADDR` varchar(255) DEFAULT NULL,
                    `CERTIFICATES_NBR` varchar(255) DEFAULT NULL,
                    `mod_time` datetime DEFAULT NULL
                ) ENGINE=MyISAM DEFAULT CHARSET=utf8
            """)

        try:
            cur.execute(f"""
                INSERT INTO `{table}` VALUES (
                    "{xml_result['PROD_INST_ID']}",
                    "{xml_result['CUST_ID']}",
                    "{xml_result['LATN']}",
                    "{xml_result['BUSI_NBR']}",
                    "{xml_result['USER_NAME']}",
                    "{xml_result['CUST_NAME']}",
                    "{xml_result['INSTALL_ADDR']}",
                    "{xml_result['CERTIFICATES_NBR']}",
                    "{xml_result['mod_time']}"
                )
            """)
        except Exception as e:
            print(f"MySQL insert error: {e}")


class Conn2mysql:
    """MySQL数据库连接"""

    def __init__(self, host="192.168.10.102", db="phone", charset="utf8"):
        self.host = host
        self.db = db
        self.charset = charset

    def conn(self):
        """建立数据库连接"""
        try:
            conn = MySQLdb.connect(
                host=self.host,
                port=3306,
                user="root",
                passwd="",
                db=self.db,
                charset=self.charset
            )
            return conn.cursor()
        except Exception as e:
            print(f"MySQL连接失败: {e}")
            sys.exit(1)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("用法: python Xml2csv.py <目录路径>")
        sys.exit(1)

    parser = Xml2csv()
    conn2sql = Conn2mysql()
    cur = conn2sql.conn()

    count = 1
    for root, dirs, files in os.walk(sys.argv[1]):
        for j in files:
            filepath = os.path.join(root, j)
            print(f"count={count}: {filepath}")
            result = parser.parse(filepath)
            if result:
                parser.save2mysql(cur, result, "phone-2016-07")
            count += 1
