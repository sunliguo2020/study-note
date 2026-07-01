#!/usr/bin/env python3
"""
列出当前目录下的所有文件并保存到文本文件

用法:
    python listFile2txt.py [目录路径] [输出文件名]

示例:
    python listFile2txt.py              # 列出当前目录，输出到 outfile
    python listFile2txt.py /path        # 列出指定目录
    python listFile2txt.py . filelist   # 指定输出文件名
"""
import os
import sys


def list_files(directory=".", output="outfile"):
    """列出目录中的文件并保存"""
    if not os.path.isdir(directory):
        print(f"错误: '{directory}' 不是有效的目录")
        return

    files = [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]

    with open(output, "w", encoding="utf-8") as f:
        for file in files:
            f.write(file + "\n")

    print(f"共 {len(files)} 个文件，已保存到 {output}")
    for i, file in enumerate(files, 1):
        print(f"{i:4d}. {file}")


if __name__ == "__main__":
    directory = sys.argv[1] if len(sys.argv) > 1 else "."
    output = sys.argv[2] if len(sys.argv) > 2 else "outfile"
    list_files(directory, output)
