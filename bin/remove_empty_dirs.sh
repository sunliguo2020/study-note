#!/bin/bash

# 用法: ./remove_empty_dirs.sh <目标目录>
# 说明: 递归删除指定目录下所有空目录（包括删除子目录后变空的父目录）

# 错误处理:
#   -e : 遇到错误立即退出
#   -u : 使用未定义变量时退出
#   -o pipefail : 管道中任一命令失败则整个管道失败
set -euo pipefail

# 检查参数
if [ $# -ne 1 ]; then
    echo "用法: $0 <目标目录>"
    exit 1
fi

TARGET_DIR="$1"

# 检查目录是否存在
if [ ! -d "$TARGET_DIR" ]; then
    echo "错误: 目录不存在: $TARGET_DIR"
    exit 1
fi

echo "正在清理空目录: $TARGET_DIR"

# 核心逻辑:
# -depth  : 先处理子目录，再处理父目录（关键，保证删完子目录后父目录能变空）
# -type d : 只匹配目录
# -empty  : 只匹配空目录
# -print  : 打印被删除的目录
# -delete : 删除
find "$TARGET_DIR" -depth -type d -empty -print -delete

echo "清理完成。"