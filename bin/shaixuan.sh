#!/bin/bash
"""
筛选指定行数的文件并移动到对应目录

用法:
    ./shaixuan.sh <目录路径> [行数]

示例:
    ./shaixuan.sh /path/to/files    # 筛选25行的文件
    ./shaixuan.sh /path 10          # 筛选10行的文件
"""

if [ $# -eq 0 ]; then
    echo "用法: $0 <目录路径> [行数]"
    echo "示例: $0 /path/to/files 25"
    exit 1
fi

target_dir="$1"
line_count="${2:-25}"

if [ ! -d "$target_dir" ]; then
    echo "错误: '$target_dir' 不是有效的目录"
    exit 1
fi

target_subdir="line-${line_count}"
mkdir -p "${target_dir}/${target_subdir}"

count=0
while IFS= read -r -d '' file; do
    if [ -f "$file" ]; then
        lines=$(wc -l < "$file")
        if [ "$lines" -eq "$line_count" ]; then
            echo "移动: $file -> ${target_dir}/${target_subdir}/"
            mv "$file" "${target_dir}/${target_subdir}/"
            ((count++))
        fi
    fi
done < <(find "$target_dir" -maxdepth 1 -type f -print0)

echo "完成: 共移动 $count 个文件到 ${target_dir}/${target_subdir}/"
