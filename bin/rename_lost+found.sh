#!/bin/bash
"""
查找当前目录下包含指定关键字的文件

用法:
    ./rename_lost+found.sh [关键字] [目录路径]

示例:
    ./rename_lost+found.sh              # 查找包含 BUSI_NBR 的文件
    ./rename_lost+found.sh "keyword"    # 查找包含指定关键字的文件
    ./rename_lost+found.sh "keyword" /path
"""

keyword="${1:-BUSI_NBR}"
target_dir="${2:-.}"

if [ ! -d "$target_dir" ]; then
    echo "错误: '$target_dir' 不是有效的目录"
    exit 1
fi

count=0
while IFS= read -r -d '' file; do
    if grep -q "$keyword" "$file" 2>/dev/null; then
        echo "$file"
        ((count++))
    fi
done < <(find "$target_dir" -maxdepth 1 -type f -print0)

echo "---"
echo "共找到 $count 个包含 '$keyword' 的文件"
