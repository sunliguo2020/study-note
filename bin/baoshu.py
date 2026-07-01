#!/usr/bin/env python3
"""
统计当前目录下各个子目录中文件的个数

用法:
    python baoshu.py [目录路径]

示例:
    python baoshu.py          # 统计当前目录
    python baoshu.py /path    # 统计指定目录
"""
import os
import sys
import time


def count_files(directory):
    """统计指定目录下各子目录的文件数"""
    total = 0
    print(time.strftime("%Y-%m-%d %H:%M:%S", time.localtime()))

    for item in os.listdir(directory):
        item_path = os.path.join(directory, item)
        if os.path.isdir(item_path):
            count = 0
            for root, dirs, files in os.walk(item_path):
                count += len(files)
            print(f"{item}:\t{count}")
            total += count

    print(f"Total:\t{total}")
    return total


if __name__ == "__main__":
    target_dir = sys.argv[1] if len(sys.argv) > 1 else "."
    if not os.path.isdir(target_dir):
        print(f"错误: '{target_dir}' 不是有效的目录")
        sys.exit(1)
    count_files(target_dir)
