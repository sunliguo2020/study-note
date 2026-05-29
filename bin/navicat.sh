#!/bin/bash
"""
处理XML文件，添加修改时间并合并输出

用法:
    ./navicat.sh <目录路径>

示例:
    ./navicat.sh /path/to/xml/files
"""

if [ $# -eq 0 ]; then
    echo "用法: $0 <目录路径>"
    echo "示例: $0 /path/to/xml/files"
    exit 1
fi

target_dir="$1"

if [ ! -d "$target_dir" ]; then
    echo "错误: '$target_dir' 不是有效的目录"
    exit 1
fi

output_file="out.csv"
temp_file=$(mktemp)

# 查找所有txt文件
find "$target_dir" -name "*.txt" -type f > "$temp_file"

file_count=$(wc -l < "$temp_file")
echo "找到 $file_count 个文件"
echo "输出文件: $output_file"

count=$file_count
while IFS= read -r file; do
    if [ -f "$file" ]; then
        mod_time=$(stat -c %y "$file" | awk -F. '{print $1}')
        echo "处理 ($count): $file"
        sed "s/<\/root>/<mod_time>$mod_time<\/mod_time><\/root>/g" "$file" >> "$output_file"
    fi
    ((count--))
done < "$temp_file"

rm -f "$temp_file"
echo "完成! 输出文件: $output_file"
