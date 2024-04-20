### 删除远端分支后，某些还能显示

**本地缓存问题**：Git会在本地缓存一些远程分支信息，以加快命令的执行速度。即使远程分支已被删除，这些缓存信息可能仍然存在。

   在日常开发工作中，经常拉取远程分支，每次回拉取出新的远程分支信息，但如果远程有分支已经删除，git pull是不会在本地将这些分支删除的，因此本地可能存在很多远程已经不存在的分支信息（git branch -a 能够看到的分支列表），如果想要跟远程保持一致，就需要修剪本地分支，使用这个命令即可：

```bash
git remote prune origin
```

​                    

```
Administrator@DESKTOP-MI1461H MINGW64 /d/webcamSnapshot (master)
$ git branch -a
* master
  remotes/origin/HEAD -> origin/master
  remotes/origin/dev
  remotes/origin/f2
  remotes/origin/feature
  remotes/origin/feature-onvif
  remotes/origin/master

Administrator@DESKTOP-MI1461H MINGW64 /d/webcamSnapshot (master)
$ git remote prune origin
Pruning origin
URL: https://github.com/sunliguo2020/webcamSnapshot.git
 * [pruned] origin/dev
 * [pruned] origin/f2

Administrator@DESKTOP-MI1461H MINGW64 /d/webcamSnapshot (master)
$ git branch -a
* master
  remotes/origin/HEAD -> origin/master
  remotes/origin/feature
  remotes/origin/feature-onvif
  remotes/origin/master

Administrator@DESKTOP-MI1461H MINGW64 /d/webcamSnapshot (master)
$

```

### 切换远端分支

要切换到远端的新分支，你需要先确保该分支已经存在于远程仓库中，并且你的本地仓库已经与远程仓库同步。以下是一系列步骤，帮助你切换到远端的新分支：

1. **获取远程仓库的最新更新**：
首先，你需要使用 `git fetch` 命令来获取远程仓库的最新更新，包括新分支的信息。

```bash
git fetch origin
```

这里的 `origin` 是远程仓库的默认名称。如果你的远程仓库使用了不同的名称，请替换为相应的名称。

2. **查看远程分支**：
使用 `git branch -r` 命令来查看所有远程分支的列表。

```bash
git branch -r
```

这将列出所有远程分支，类似于 `origin/branch-name` 的格式。

3. **创建并切换到本地跟踪分支**：
现在，你可以使用 `git checkout` 命令配合 `-b` 选项来创建并切换到本地跟踪分支。这个本地分支将跟踪你在远程仓库中看到的新分支。

```bash
git checkout -b local-branch-name origin/remote-branch-name
```

在这里，`local-branch-name` 是你想要创建的本地分支的名称，`origin/remote-branch-name` 是你想要跟踪的远程分支的名称。

例如，如果远程分支名为 `feature/new-feature`，你可以这样操作：

```bash
git checkout -b feature-new-feature origin/feature/new-feature
```

这条命令会创建名为 `feature-new-feature` 的本地分支，并立即切换到这个分支。这个本地分支会自动设置为跟踪 `origin/feature/new-feature`。

4. **开始工作**：
现在你已经成功切换到了远端的新分支的本地跟踪分支，并可以开始在这个分支上工作了。

5. **保持同步**：
当你在这个分支上工作时，你可能想要定期与远程仓库同步，以确保你拥有最新的代码。你可以使用 `git pull` 命令来拉取远程分支的最新更改：

```bash
git pull origin remote-branch-name
```

请注意，如果你在团队中工作，其他人可能也在这个分支上工作，所以定期同步是一个好习惯。

确保你始终了解你所在的分支以及你正在与之交互的远程分支，以避免混淆或错误地将更改推送到错误的分支。

### 本地修改后不保留，直接拉取远程

这些错误信息表示你正在尝试合并远程分支`origin/feature-onvif`到你的本地分支，但是在执行合并操作之前，你遇到了几个问题。

首先，错误信息提到`lib/OnvifClient/CameraClient.py`这个文件有本地未提交的修改。这意味着你在这个文件上做了更改，但还没有将这些更改通过`git add`和`git commit`命令提交到本地仓库。合并操作会尝试将远程分支的更改应用到你的本地分支上，如果这些更改与你本地的修改冲突，Git 会提示你解决这些冲突。但在这个情况下，Git 甚至不能开始合并，因为它担心远程分支的更改会覆盖你本地的未提交修改。

为了解决这个问题，你可以采取以下几个步骤之一：

1. **提交你的更改**：如果你想要保留你在`CameraClient.py`文件中的修改，你应该先提交这些更改。这可以通过运行`git add lib/OnvifClient/CameraClient.py`（将文件添加到暂存区）和`git commit -m "描述你的更改"`（提交更改）来完成。

2. **暂存你的更改**：如果你暂时不想提交更改，但想要合并远程分支，你可以使用`git stash`命令来暂存你的本地修改。这样，你的更改会被保存起来，你可以在合并完成后再应用它们。

3. **放弃你的更改**：如果你不想保留你在`CameraClient.py`文件中的修改，你可以通过`git checkout -- lib/OnvifClient/CameraClient.py`来恢复文件的原始状态。

其次，错误信息还提到`mylogger/__init__.py`是一个未跟踪的文件，这意味着这个文件在Git的追踪之外，但它会被远程分支的更改覆盖。为了避免数据丢失，Git 阻止你合并，直到你处理了这个问题。

要解决这个问题，你可以选择：

- **移动或重命名文件**：如果你想要保留这个文件，但不想它被合并覆盖，你可以将其移动或重命名。
- **删除文件**：如果你不想要这个文件了，可以直接删除它。
- **添加并提交文件**：如果你认为这个文件应该被Git追踪，你可以使用`git add mylogger/__init__.py`和`git commit -m "添加__init__.py到mylogger目录"`来添加并提交它。

在解决了这些问题之后，你可以再次尝试合并远程分支。如果仍然有冲突，Git 会提示你解决它们。解决冲突后，你可以提交合并的结果。