#!/bin/bash
function find_big_file(){
    # 文件排序，找出最后5个文件
    git verify-pack -v .git/objects/pack/pack-*.idx | sort -k 3 -g | tail -5| awk '{print $1}'
}

#find_big_file

# 将id查询为真实文件名
function id2name()
{
    git rev-list --objects --all | grep $1
}

function find_real_big_file_name(){
    #查找大文件的真实文件名
for item in `find_big_file`
do
    # echo $item
    id2name $item
done
}
function git_del_file(){
    # git 永久删除文件
    git filter-branch --force --index-filter "git rm -rf --cached --ignore-unmatch $1" --prune-empty --tag-name-filter cat -- --all
}

