不到迫不得已，不要轻易使用 `git filter-branch`，因为它重构了整个 Tree，所以每个开发人员都需要重新克隆仓库到本地，对于有很多开发者参与的大型项目来说，这么做会给很多人带来麻烦，与其事后对仓库内容进行修正，不如伊始就对每个 Commit 慎之又慎。



```
pip install git-filter-repo
```

#### 列出最大的文件

```
sunliguo@DESKTOP-F5FCNSM MINGW64 /f/github/study-note (master)
$ git rev-list --all|xargs -rL1 git ls-tree -r --long|sort -uk3|sort -rnk4|head -10
100644 blob 67e724a63c48be298034551b11d0850f77a720b1 11414341   大学linux笔记/dumpe2fs-ext3.txt
100644 blob 67e724a63c48be298034551b11d0850f77a720b1 11414341   linux系统配置/dumpe2fs-ext3.txt
100644 blob 67e724a63c48be298034551b11d0850f77a720b1 11414341   dumpe2fs-ext3.txt
100644 blob 67e724a63c48be298034551b11d0850f77a720b1 11414341   Linux/linux系统配置/dumpe2fs-ext3.txt
100644 blob 63382702f7d2d3e0e1228dfb4091b4ab720803f7 8509504    学习资料/unixps1.zip
100644 blob f8294e5032ebac88bb7a062ef5382b6b590cbfab 5413982    学习资料/unixps2.zip
100644 blob a538ff6938c73ba31ce3242c88f450e7a0e1531d 4789837    学习资料/unix_c.chm
100644 blob a1480e54f6e61efe3283604fa8e8e684584ad389 4521984    学习资料/FIL7.PDF
100644 blob 01df4aad044bed192dda7de11ec2c5da90830d83 3369501    学习资料/Addison Wesley - Advanced Programming in the UNIX Environment - 2nd Edition.chm
100644 blob d96a6fe01cfcf89b16392e7c7c19c71505a45ea6 2004480    大学linux笔记/Linux Screenshots Museum.doc

sunliguo@DESKTOP-F5FCNSM MINGW64 /f/github/study-note (master)
```



```

git filter-repo --invert-paths --path-match xxx --force
```

```
sunliguo@DESKTOP-F5FCNSM MINGW64 /f/github/study-note (master)
$ git filter-repo --invert-paths --path-match Linux/Linux编程/Linux编程技术详解.iso
Aborting: Refusing to destructively overwrite repo history since
this does not look like a fresh clone.
  (expected freshly packed repo)
Please operate on a fresh clone instead.  If you want to proceed
anyway, use --force.

sunliguo@DESKTOP-F5FCNSM MINGW64 /f/github/study-note (master)
$ git filter-repo --invert-paths --path-match Linux/Linux编程/Linux编程技术详解.iso  --force
Parsed 189 commitsHEAD is now at 42a08d5 git中如何删除大文件
Enumerating objects: 5422, done.
Counting objects: 100% (5422/5422), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3376/3376), done.
Writing objects: 100% (5422/5422), done.
Total 5422 (delta 1593), reused 5415 (delta 1590), pack-reused 0

New history written in 6.00 seconds; now repacking/cleaning...
Repacking your repo and cleaning out old 
```

### [Using git filter-repo](https://docs.github.com/zh/authentication/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository#using-git-filter-repo)

Warning

If you run `git filter-repo` after stashing changes, you won't be able to retrieve your changes with other stash commands. Before running `git filter-repo`, we recommend unstashing any changes you've made. To unstash the last set of changes you've stashed, run `git stash show -p | git apply -R`. For more information, see [Git Tools - Stashing and Cleaning](https://git-scm.com/book/en/v2/Git-Tools-Stashing-and-Cleaning).

To illustrate how `git filter-repo` works, we'll show you how to remove your file with sensitive data from the history of your repository and add it to `.gitignore` to ensure that it is not accidentally re-committed.

1. Install the latest release of the [git filter-repo](https://github.com/newren/git-filter-repo) tool. You can install `git-filter-repo` manually or by using a package manager. For example, to install the tool with HomeBrew, use the `brew install` command.

   ```shell
   brew install git-filter-repo
   ```

   For more information, see [*INSTALL.md*](https://github.com/newren/git-filter-repo/blob/main/INSTALL.md) in the `newren/git-filter-repo` repository.

2. If you don't already have a local copy of your repository with sensitive data in its history, [clone the repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository) to your local computer.

   ```shell
   $ git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY
   > Initialized empty Git repository in /Users/YOUR-FILE-PATH/YOUR-REPOSITORY/.git/
   > remote: Counting objects: 1301, done.
   > remote: Compressing objects: 100% (769/769), done.
   > remote: Total 1301 (delta 724), reused 910 (delta 522)
   > Receiving objects: 100% (1301/1301), 164.39 KiB, done.
   > Resolving deltas: 100% (724/724), done.
   ```

3. Navigate into the repository's working directory.

   ```shell
   cd YOUR-REPOSITORY
   ```

4. Run the following command, replacing `PATH-TO-YOUR-FILE-WITH-SENSITIVE-DATA` with the **path to the file you want to remove, not just its filename**. These arguments will:

   - Force Git to process, but not check out, the entire history of every branch and tag

   - Remove the specified file, as well as any empty commits generated as a result

   - Remove some configurations, such as the remote URL, stored in the *.git/config* file. You may want to back up this file in advance for restoration later.

   - **Overwrite your existing tags**

     ```shell
       $ git filter-repo --invert-paths --path PATH-TO-YOUR-FILE-WITH-SENSITIVE-DATA
       Parsed 197 commits
       New history written in 0.11 seconds; now repacking/cleaning...
       Repacking your repo and cleaning out old unneeded objects
       Enumerating objects: 210, done.
       Counting objects: 100% (210/210), done.
       Delta compression using up to 12 threads
       Compressing objects: 100% (127/127), done.
       Writing objects: 100% (210/210), done.
       Building bitmaps: 100% (48/48), done.
       Total 210 (delta 98), reused 144 (delta 75), pack-reused 0
       Completely finished after 0.64 seconds.
     ```

     由于本人不小心上传了大量csv文件，因此使用正则匹配将所有csv文件删除

     ```css
     git filter-repo --force --invert-paths --path-regex .+\.csv
     ```
     
     ### 删除单个目录
     
     要删除名为 `dir_to_remove` 的目录及其所有内容，你可以使用以下命令：
     
     git filter-repo --invert-paths --path dir_to_remove
     
     但是，这里有一个需要注意的地方：`git filter-repo` 的 `--path` 选项默认是包含指定路径的提交。因此，如果你直接使用 `--path dir_to_remove`，它会保留所有包含该目录的提交。为了删除这个目录，你需要结合使用 `--invert-paths` 选项，这会告诉 `git filter-repo` 保留所有**不**包含指定路径的提交。
     
     
     
     
     
     Important
     
     If the file with sensitive data used to exist at any other paths (because it was moved or renamed), you must run this command on those paths, as well.

5. Add your file with sensitive data to `.gitignore` to ensure that you don't accidentally commit it again.

   ```shell
   $ echo "YOUR-FILE-WITH-SENSITIVE-DATA" >> .gitignore
   $ git add .gitignore
   $ git commit -m "Add YOUR-FILE-WITH-SENSITIVE-DATA to .gitignore"
   > [main 051452f] Add YOUR-FILE-WITH-SENSITIVE-DATA to .gitignore
   >  1 files changed, 1 insertions(+), 0 deletions(-)
   ```

6. Double-check that you've removed everything you wanted to from your repository's history, and that all of your branches are checked out.

7. The `git filter-repo` tool will automatically remove your configured remotes. Use the `git remote set-url` command to restore your remotes, replacing `OWNER` and `REPO` with your repository details. For more information, see "[Managing remote repositories](https://docs.github.com/en/get-started/getting-started-with-git/managing-remote-repositories#adding-a-remote-repository)."

   ```shell
   git remote add origin https://github.com/OWNER/REPOSITORY.git
   ```

8. Once you're happy with the state of your repository, and you have set the appropriate remote, force-push your local changes to overwrite your repository on GitHub.com, as well as all the branches you've pushed up. A force push is required to remove sensitive data from your commit history.

   ```shell
   $ git push origin --force --all
   > Counting objects: 1074, done.
   > Delta compression using 2 threads.
   > Compressing objects: 100% (677/677), done.
   > Writing objects: 100% (1058/1058), 148.85 KiB, done.
   > Total 1058 (delta 590), reused 602 (delta 378)
   > To https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
   >  + 48dc599...051452f main -> main (forced update)
   ```

9. In order to remove the sensitive file from [your tagged releases](https://docs.github.com/en/repositories/releasing-projects-on-github/about-releases), you'll also need to force-push against your Git tags:

   ```shell
   $ git push origin --force --tags
   > Counting objects: 321, done.
   > Delta compression using up to 8 threads.
   > Compressing objects: 100% (166/166), done.
   > Writing objects: 100% (321/321), 331.74 KiB | 0 bytes/s, done.
   > Total 321 (delta 124), reused 269 (delta 108)
   > To https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
   >  + 48dc599...051452f main -> main (forced update)
   ```

