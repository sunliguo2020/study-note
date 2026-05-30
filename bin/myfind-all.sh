#!/bin/bash
"""
将文本文件按大小/行数分类到不同目录

用法:
    ./myfind-all.sh [目录路径] [-m mode]

模式:
    size  (默认) 按文件字节数分类: zero, 160, 408, 427, 428, 1000, 1215
    md5   按行数+MD5校验分类: line-2(特定内容), zero, 160, 408, 427

示例:
    ./myfind-all.sh                    # 处理当前目录，默认size模式
    ./myfind-all.sh /path/to/files     # 处理指定目录
    ./myfind-all.sh -m md5             # 使用md5校验模式
    ./myfind-all.sh /path -m md5       # 指定目录和模式
"""

# ============ 配置 ============
MD5_MATCH="4ac0f394c8607199747a4b4d8ed3da3b"
MD5_FAIL="1054a9137d0320af85d21550486a3d26"

# ============ 初始化计数器 ============
file_two=0
file_zero=0
file_160=0
file_408=0
file_427=0
file_428=0
file_1215=0
file_1000=0

# ============ 函数定义 ============
cleanup() {
    if [ -f "$sh_file" ]; then
        printf "Cleaning up..."
        rm -f "$sh_file" 2>/dev/null
        echo "done"
    fi
}

echo_result() {
    echo "========== 统计结果 =========="
    [ "$mode" = "md5" ] && echo "file_two=$file_two"
    echo "file_zero=$file_zero"
    echo "file_160=$file_160"
    echo "file_408=$file_408"
    echo "file_427=$file_427"
    [ "$mode" = "size" ] && echo "file_428=$file_428"
    [ "$mode" = "size" ] && echo "file_1215=$file_1215"
    [ "$mode" = "size" ] && echo "file_1000=$file_1000"
    echo "=============================="
}

trap "cleanup; echo_result; exit 2" 1 2 3 15

# ============ 创建分类目录 ============
create_dirs() {
    local dirs=("zero" "160" "408" "427")
    [ "$mode" = "size" ] && dirs+=("428" "1215" "1000")
    [ "$mode" = "md5" ] && dirs+=("line-2")

    for d in "${dirs[@]}"; do
        [ ! -d "$d" ] && mkdir "$d"
    done
}

# ============ 分类逻辑 ============
classify_size() {
    local file="$1"
    local wc_count
    wc_count=$(wc -c < "$file")

    if [ "$wc_count" -ge 1201 ]; then
        mv -v "$file" 1215/
        ((file_1215++))
    elif [ "$wc_count" -eq 0 ]; then
        mv -v "$file" zero/
        ((file_zero++))
    elif [ "$wc_count" -eq 160 ]; then
        mv -v "$file" 160/
        ((file_160++))
    elif [ "$wc_count" -eq 427 ]; then
        mv -v "$file" 427/
        ((file_427++))
    elif [ "$wc_count" -eq 428 ]; then
        mv -v "$file" 428/
        ((file_428++))
    elif [ "$wc_count" -eq 408 ] || [ "$wc_count" -eq 409 ]; then
        mv -v "$file" 408/
        ((file_408++))
    elif [ "$wc_count" -lt 1000 ]; then
        mv -v "$file" 1000/
        ((file_1000++))
    fi
}

classify_md5() {
    local file="$1"
    local line_count wc_count file_size

    line_count=$(wc -l < "$file")
    wc_count=$(wc -c < "$file")
    file_size=$(stat -c %s "$file")

    if [ "$line_count" -eq 2 ]; then
        local md5_result
        md5_result=$(md5sum "$file" | awk '{print $1}')
        if [ "$MD5_MATCH" = "$md5_result" ]; then
            echo "line-2 find one: $file"
            mv -v "$file" line-2/
            ((file_two++))
        elif [ "$wc_count" -eq 408 ] || [ "$wc_count" -eq 409 ]; then
            mv -v "$file" 408/
            ((file_408++))
        elif [ "$wc_count" -eq 427 ]; then
            mv -v "$file" 427/
            ((file_427++))
        fi
    elif [ "$file_size" -eq 0 ]; then
        mv -v "$file" zero/
        ((file_zero++))
    elif [ "$MD5_FAIL" = "$(md5sum "$file" | awk '{print $1}')" ] || [ "$file_size" -eq 160 ]; then
        mv -v "$file" 160/
        ((file_160++))
    fi
}

# ============ 主逻辑 ============
# 解析参数
mode="size"
search_dir=""

while [ $# -gt 0 ]; do
    case "$1" in
        -m)
            mode="$2"
            shift 2
            ;;
        *)
            search_dir="$1"
            shift
            ;;
    esac
done

if [ "$mode" != "size" ] && [ "$mode" != "md5" ]; then
    echo "错误: 模式必须是 'size' 或 'md5'"
    exit 1
fi

echo "模式: $mode"

# 创建临时文件列表
sh_file=$(mktemp)

if [ -z "$search_dir" ]; then
    find . -maxdepth 1 -name "*.txt" -type f | sort > "$sh_file"
else
    find "$search_dir" -name "*.txt" -type f | sort > "$sh_file"
fi

create_dirs

total=$(wc -l < "$sh_file")
echo "找到 $total 个文件"
[ "$total" -eq 0 ] && { cleanup; exit; }

count=$total

# 分批处理（每批5000个）
batch_size=5000
while [ "$total" -gt 0 ]; do
    while IFS= read -r file; do
        [ ! -f "$file" ] && continue
        echo "count=$count: $file"

        if [ "$mode" = "size" ]; then
            classify_size "$file"
        else
            classify_md5 "$file"
        fi

        ((count--))
    done < <(head -$batch_size "$sh_file")

    sed -i "1,${batch_size}d" "$sh_file"
    total=$(wc -l < "$sh_file")
done

cleanup
echo_result
