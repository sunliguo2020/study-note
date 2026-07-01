#!/usr/bin/env python3
"""
将指定文件夹中的文件按照文件的修改时间分组，每个月份为一个文件夹。

用法:
    python groupByMonth.py [目录路径]

示例:
    python groupByMonth.py          # 整理当前目录
    python groupByMonth.py /path    # 整理指定目录
"""
import os
import sys
import time
import shutil


def organize_by_month(directory="."):
    """按月份整理文件"""
    if not os.path.isdir(directory):
        print(f"错误: '{directory}' 不是有效的目录")
        return

    os.chdir(directory)
    existing_dirs = set(os.listdir("."))

    for root, dirnames, filenames in os.walk("."):
        for filename in filenames:
            filepath = os.path.join(root, filename)
            try:
                mtime = os.path.getmtime(filepath)
                month_dir = time.strftime("%Y%m", time.gmtime(mtime))

                # 创建月份目录
                if month_dir not in existing_dirs:
                    os.makedirs(month_dir, exist_ok=True)
                    existing_dirs.add(month_dir)

                dest = os.path.join(".", month_dir, filename)
                if not os.path.isfile(dest):
                    print(f"移动: {filepath} -> {dest}")
                    shutil.move(filepath, dest)
                else:
                    print(f"跳过(已存在): {filename}")
            except Exception as e:
                print(f"处理文件 {filepath} 时出错: {e}")


if __name__ == "__main__":
    target = sys.argv[1] if len(sys.argv) > 1 else "."
    organize_by_month(target)
