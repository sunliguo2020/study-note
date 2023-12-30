### 查看项目分支

```
git branch -a
```



### 删除本地分支

```
git branch -d <branchName>
```

以从http://git.xxx.com/test.git上拉去fast分支为例：

1、新建空文件夹
2、初始化git

```
git init
```

3、与远程仓库建立连接
命令：git remote add origin <远程git地址>
例如：

```
git remote add origin http://git.xxx.com/test.git
```



4、把远程分支拉去到本地
命令：git fetch origin <远程分支名称>
例如：git fetch origin fast
1
2
5、在本地建立分支localfast并切换到该分支，与远程分支建立连接
命令：git checkout -b <本地分支名称> origin/<远程分支>
例如：git checkout -b localfast origin/fast
1
2
6、拉取分支内容到本地分支
命令：git pull origin <远程分支名称>
例如：git pull origin fast
