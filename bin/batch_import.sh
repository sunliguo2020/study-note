#!/bin/bash
BASE_DIR="/mnt/sdc1/sgy/guhua/0532/0532-2015"
LOG_FILE="./import_resident.log"

> "${LOG_FILE}"

for subdir in "${BASE_DIR}"/*/; do
    dir_path="${subdir%/}"
    if [ -d "${dir_path}" ]; then
        echo "=====开始处理 ${dir_path} =====" | tee -a "${LOG_FILE}"
        python manage.py import_guhua --dir "${dir_path}" 2>&1 | tee -a "${LOG_FILE}"
    fi
done
