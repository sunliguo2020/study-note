1、10分钟git快速上手

*克隆远程项目到本地

```
git clone https://gitee.com/ubrong/demo.git
```

修改并提交到本地仓库

```
git add 文件

git commit 提交
```

推送到远程仓库

```
git remote [选项]
作用：设置或读取与远程仓库相关的内容
```

### 从版本库中恢复文件

- 已删除（或修改），未add
  - 检出命令：git checkout {文件路径}
- 已删除（或修改），已add，未commit
  - git checkout <commitId> 文件路径 表示从某个commit状态中恢复文件到工作区

- 已删除（或修改），已commit

### 分支

```
git init -b dev # 创建版本库同时创建分支
```

```
git branch <新分支名称> 仅用于创建分支，但不会切换到新分支
```

```
git branch -m <旧分支> <新分支>
```

删除分支

```
git branch -d <分支>
-d 用于删除已合并过的分支
-D 强制删除分支（不管是否合并过）
```

### 提交冲突与解决方法

提交冲突的原因：提交者的版本库<远程库

如何试下你本地同步：

```
git pull
```

### 提交修正

提交修正就是“修正”上一次的提交

```
git commit --amend
```

### 查看本地对应远程库的信息

```
git remote -v 
```

### 推送分支到远程库

```
git push {远程库remote 名称} {分支名称}
远程库的名称是你在remote时指定的名称，默认为origin。
要推送所有分支 则使用--all参数。
```

### 删除远程分支（方案一）

虽然在github后台删除远程分支比较简单，但是会导致本地库中的远程分支与实际分支不一致。

处理方案：

同步分支：git remote prune {origin 或你的远程库名称}

### 删除远程分支

```
git push {远程库remote名称} -d {远程分支名称}
```

