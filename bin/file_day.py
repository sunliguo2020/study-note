#!/usr/bin/env python3
"""
将当前目录下的文件按修改日期整理到子目录中

用法:
    python file_day.py [文件后缀]

示例:
    python file_day.py          # 整理所有 .txt 文件
    python file_day.py .md      # 整理所有 .md 文件
"""
import os
import sys
import time


def move_file(src, dst):
    """移动文件，自动创建目标目录"""
    if not os.path.isfile(src):
        print(f"'{src}' 不存在!")
        return False

    dst_dir = os.path.dirname(dst)
    if not os.path.exists(dst_dir):
        os.makedirs(dst_dir)

    if os.path.isfile(dst):
        print(f"目标文件已存在: {dst}")
        return False

    try:
        os.rename(src, dst)
        print(f"移动: {src} -> {dst}")
        return True
    except Exception as e:
        print(f"移动失败: {e}")
        return False


def organize_by_date(ext=".txt"):
    """按文件修改日期整理文件"""
    count = 0
    for file in os.listdir("."):
        file_path = os.path.join(".", file)
        if not os.path.isfile(file_path) or not file.endswith(ext):
            continue

        mtime = os.stat(file_path).st_mtime
        date_str = time.strftime("%Y-%m-%d", time.localtime(mtime))
        dst_path = os.path.join(".", date_str, file)

        if move_file(file_path, dst_path):
            count += 1

    print(f"共整理了 {count} 个文件")


if __name__ == "__main__":
    ext = sys.argv[1] if len(sys.argv) > 1 else ".txt"
    if not ext.startswith("."):
        ext = "." + ext
    organize_by_date(ext)
