要修改 Git 分支名，你可以使用 `git branch` 命令的 `-m` 或 `--move` 选项。以下是步骤和示例：

### 步骤：

1. 确保你当前不在要重命名的分支上。你可以通过 `git status` 来查看你当前所在的分支。
2. 切换到其他分支（如果你当前就在要重命名的分支上）。使用 `git checkout` 命令来切换分支。
3. 使用 `git branch -m` 命令来重命名分支。

### 示例：

假设你要将分支 `old-branch-name` 重命名为 `new-branch-name`，并且你当前不在 `old-branch-name` 分支上，你可以这样做：

```bash
bash复制代码

git branch -m old-branch-name new-branch-name
```

如果你当前就在 `old-branch-name` 分支上，你需要先切换到其他分支，然后再执行重命名操作：

```bash
# 切换到其他分支  
git checkout another-branch  
  
# 重命名分支  
git branch -m old-branch-name new-branch-name
```

### 注意事项：

- 如果你正在与他人合作，并且其他人已经拉取了旧的分支，他们需要在本地执行 `git fetch` 来获取最新的分支信息，然后可能需要执行 `git branch -m` 来更新他们本地的分支名（如果他们也需要这样做的话）。
- 如果你已经推送了旧的分支到远程仓库，并且想要更新远程仓库上的分支名，你需要使用 `git push` 命令并指定新的分支名：

```bash
git push origin :old-branch-name  # 删除远程的旧分支  
git push origin new-branch-name   # 推送新的分支到远程仓库
```

或者，如果你使用的是 Git 2.15 或更高版本，你可以使用 `-u` 或 `--set-upstream` 选项来一次性完成重命名和设置上游分支的操作：

```bash
git push -u origin new-branch-name
```

这会推送 `new-branch-name` 分支到远程仓库（如果它还不存在的话），并设置它为当前分支的上游分支。如果远程仓库上已存在同名的分支，Git 会尝试更新它。如果远程仓库上存在旧的分支名，你可能需要先手动删除它，或者使用上面提到的 `git push origin :old-branch-name` 命令来删除它。