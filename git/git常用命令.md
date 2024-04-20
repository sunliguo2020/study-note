### 查看项目分支

```
git branch -a
```

### 创建分支

```
git checkout -b feature-A
```

```
git branch feature-A
git chekcout feature-A
```

分支上传

```
git push orgin feature-A
```

### 获取远程的分支

```bash
git checkout -b feature-D origin/feature-D
```

-b 参数的后面是本地仓库中新建分支的名称。为了便于理解，我们仍将器命名为feature-D,让它与远程仓库的对应分支保持同名。

如果你想要下载（检出）一个远程分支并在本地开始工作，你可以使用 `git checkout` 命令。这将在本地创建一个与远程分支对应的跟踪分支。

```bash
git checkout -b <local-branch-name> origin/<remote-branch-name>
```

这里<local-branch-name> `` 是你想要在本地创建的分支的名称，``<remote-branch-name> 是你想要下载的远程分支的名称。

例如，如果你想要下载名为 `feature-branch` 的远程分支，并在本地创建一个名为 `my-feature-branch` 的跟踪分支，你可以执行：

```bash
git checkout -b my-feature-branch origin/feature-branch
```

### 合并分支

分支合并有两种方式：

#### 本地分支间的合并
  比如，我在本地分支dev开发完一个功能后，先要把dev合并到本地的master分支，然后再推到远程仓库
  先从dev分支切换到master分支，使用checkout命令
  ```
  git checkout master
  ```
  这样就从当前分支（也就是dev分支）分支切换到了master分支
  现在我们已经位于master分支了，那么接下来我们就需要用merge命令来进行分支间的合并

```
git merge dev
```

  OK，键入这个命令后我们就成功地将本地的dev合并到了master分支上，之后再使用push命令将本地的master推送到远程仓库就可以啦。

```
git merge dev --no-ff
```

在合并的时加上--no-ff参数，可以在历史记录中明确记录下本次分支合并。

#### 远程分支合并到本地分支

远程分支合并到本地分支的前提是已经将dev分支的代码提交到远程仓库，那么此时远程仓库中的dev分支就是已经开发完成的代码。然后我们直接使用checkout命令从dev分支切换到master分支，接着使用pull命令将远程仓库的代码拉到本地的master即可
```
git pull origin dev
```

之后我们就可以使用push命令把本地的master分支合并到远程仓库啦

### 删除分支

- 删除本地分支

```
git branch -d <branchName>
```

- 删除远程分支

```
git push origin :f2
git push origin --delete [branch_name]
```



```
git branch -d -r <branchname> 
命令 git branch -r -d origin/f2 的作用是删除本地的远程跟踪分支 origin/f2，而不是删除远程仓库中的 f2 分支。
```

```
sunliguo@DESKTOP-A6J0GE8 MINGW64 /d/github/webcamSnapshot (master)
$ git branch -a
  feature
* master
  remotes/origin/f2
  remotes/origin/feature
  remotes/origin/master

sunliguo@DESKTOP-A6J0GE8 MINGW64 /d/github/webcamSnapshot (master)
$ git branch -r -d f2
error: remote-tracking branch 'f2' not found.

sunliguo@DESKTOP-A6J0GE8 MINGW64 /d/github/webcamSnapshot (master)
$ git branch -r -d origin/f2
Deleted remote-tracking branch origin/f2 (was 4615058).

```

没有删除远程分支，接着使用下面的命令：

```
sunliguo@DESKTOP-A6J0GE8 MINGW64 /d/github/webcamSnapshot (master)
$ git branch -a
  feature
* master
  remotes/origin/feature
  remotes/origin/master

sunliguo@DESKTOP-A6J0GE8 MINGW64 /d/github/webcamSnapshot (master)
$ git push origin --delete f2
To https://github.com/sunliguo2020/webcamSnapshot.git
 - [deleted]         f2

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

### 终端乱码

```
git config --global core.quotepath false
```

