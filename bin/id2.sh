#!/bin/bash
"""
逐行读取文件内容并打印

用法:
    ./id2.sh <文件名>

示例:
    ./id2.sh 0536.list
    ./id2.sh data.txt
"""

if [ $# -eq 0 ]; then
    echo "用法: $0 <文件名>"
    echo "示例: $0 0536.list"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "错误: 文件 '$1' 不存在"
    exit 1
fi

while IFS= read -r line; do
    echo "$line"
done < "$1"
