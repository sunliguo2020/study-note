#!/bin/bash
"""
将手机号文件按号段和日期分组到子目录

用法:
    ./phone_group.sh [-m] [-d <目录路径>]

选项:
    -m          仅处理当前目录（不递归）
    -d <路径>   指定要处理的目录

示例:
    ./phone_group.sh                    # 处理当前目录及子目录
    ./phone_group.sh -m                 # 仅处理当前目录
    ./phone_group.sh -d /path/to/files  # 处理指定目录
"""

phone_header=(130 131 132 133 134 135 136 137 138 139
              145 147 150 151 152 153 155 156 157 158 159
              166 175 176 177 178 180 181 182 183 184 185 186 187 188 189
              198 199)

findopt=""
directory=""

while getopts 'md:' opt; do
    case $opt in
        m) findopt="-maxdepth 1" ;;
        d) directory="$OPTARG" ;;
        ?)
            echo "用法: $0 [-m] [-d <目录路径>]"
            exit 1
            ;;
    esac
done

workdir="${directory:-$PWD}"

if [ ! -d "$workdir" ]; then
    echo "错误: '$workdir' 不是有效的目录"
    exit 1
fi

echo "工作目录: $workdir"

for phone in "${phone_header[@]}"; do
    echo "处理号段: $phone"
    while IFS= read -r -d '' file; do
        mod_time=$(stat -c %y "$file" | awk '{print $1}')
        target_dir="${workdir}/${phone}-${mod_time}"
        mkdir -p "$target_dir"
        echo "移动: $file -> $target_dir/"
        mv -vn "$file" "$target_dir/"
    done < <(find "$workdir" $findopt -type f -name "${phone}*" -print0)
done

echo "完成!"
