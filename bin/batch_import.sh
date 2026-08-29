#!/bin/bash

# BASE_DIR 从命令行第一个参数传入
BASE_DIR="$1"
LOG_FILE="./batch_import.log"

# 参数校验
if [ -z "${BASE_DIR}" ]; then
    echo "用法: $0 <基础目录路径>"
    echo "示例: $0 /mnt/sdc1/sgy/guhua/0532/0532-2015"
    exit 1
fi

if [ ! -d "${BASE_DIR}" ]; then
    echo "错误：目录 ${BASE_DIR} 不存在!"
    exit 1
fi

> "${LOG_FILE}"

for subdir in "${BASE_DIR}"/*/; do
    dir_path="${subdir%/}"
    if [ -d "${dir_path}" ]; then
        echo "=====开始处理 ${dir_path} =====" | tee -a "${LOG_FILE}"
        python manage.py import_guhua --dir "${dir_path}" 2>&1 | tee -a "${LOG_FILE}"
    fi
done
