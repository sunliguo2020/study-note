#!/usr/bin/env python3
"""
XML文件处理工具 - 将XML数据导入MySQL数据库

用法:
    python xml2sql.py <目录路径>

依赖:
    pip install MySQLdb
"""
import os
import sys
import time
import xml.dom.minidom
import MySQLdb


class XmlProcessor:
    """XML文件处理器"""

    def __init__(self):
        self.tempfile = f'/tmp/xml_{int(time.time())}'

    def __del__(self):
        if os.path.isfile(self.tempfile):
            os.remove(self.tempfile)

    def parse_and_save(self, filepath, cursor, table="xml_data"):
        """解析XML文件并保存到数据库"""
        if not os.path.isfile(filepath):
            print(f"跳过: {filepath} 不是文件")
            return False

        # 读取并转换编码
        with open(filepath, 'rb') as f:
            raw = f.read()

        try:
            content = raw.decode('gb2312', 'replace').encode('utf-8')
        except Exception:
            content = raw

        with open(self.tempfile, 'wb') as f:
            f.write(content)

        try:
            dom = xml.dom.minidom.parse(self.tempfile)
            root = dom.documentElement
        except Exception as e:
            print(f"XML解析失败 {filepath}: {e}")
            return False

        # 提取数据
        data = {}
        fields = [
            'PROD_INST_ID', 'LATN', 'BUSI_NBR', 'USER_NAME',
            'CUST_NAME', 'CUST_ID', 'INSTALL_ADDR', 'CERTIFICATES_NBR'
        ]

        for field in fields:
            try:
                data[field] = root.getElementsByTagName(field)[0].childNodes[0].data
            except Exception:
                data[field] = ''

        data['mod_time'] = time.strftime(
            "%Y-%m-%d %H:%M:%S",
            time.gmtime(os.path.getmtime(filepath) + 8 * 3600)
        )

        # 创建表（如果不存在）
        cursor.execute("SHOW TABLES LIKE %s", (table,))
        if not cursor.fetchone():
            print(f"创建表: {table}")
            cursor.execute(f"""
                CREATE TABLE `{table}` (
                    `PROD_INST_ID` varchar(255) DEFAULT NULL,
                    `LATN` varchar(255) DEFAULT NULL,
                    `BUSI_NBR` varchar(255) DEFAULT NULL,
                    `USER_NAME` varchar(255) DEFAULT NULL,
                    `CUST_NAME` varchar(255) DEFAULT NULL,
                    `CUST_ID` varchar(255) DEFAULT NULL,
                    `INSTALL_ADDR` varchar(255) DEFAULT NULL,
                    `CERTIFICATES_NBR` varchar(255) DEFAULT NULL,
                    `mod_time` datetime DEFAULT NULL
                ) ENGINE=MyISAM DEFAULT CHARSET=utf8
            """)

        # 插入数据
        placeholders = ', '.join(['%s'] * (len(fields) + 1))
        columns = ', '.join(fields + ['mod_time'])
        values = tuple(data[f] for f in fields + ['mod_time'])

        try:
            cursor.execute(f"INSERT INTO `{table}` ({columns}) VALUES ({placeholders})", values)
            print(f"已导入: {filepath}")
            return True
        except Exception as e:
            print(f"导入失败 {filepath}: {e}")
            return False


def main():
    if len(sys.argv) < 2:
        print("用法: python xml2sql.py <目录路径>")
        sys.exit(1)

    target_dir = sys.argv[1]
    if not os.path.isdir(target_dir):
        print(f"错误: '{target_dir}' 不是有效的目录")
        sys.exit(1)

    # 连接数据库
    try:
        conn = MySQLdb.connect(
            host="192.168.10.102",
            port=3306,
            user="root",
            passwd="",
            db="phone",
            charset="utf8"
        )
        cursor = conn.cursor()
    except Exception as e:
        print(f"数据库连接失败: {e}")
        sys.exit(1)

    processor = XmlProcessor()
    count = 0

    for root, dirs, files in os.walk(target_dir):
        for filename in files:
            filepath = os.path.join(root, filename)
            if processor.parse_and_save(filepath, cursor, "xml_data"):
                count += 1

    conn.commit()
    cursor.close()
    conn.close()
    print(f"\n完成! 共导入 {count} 个文件")


if __name__ == "__main__":
    main()
