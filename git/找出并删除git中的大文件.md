在git库中有时会存在很大的文件，比如二进制文件、记录账号密码的文件或者一些zip文件等。我们可能会忘记在gitignore中加上这些文件名，在commit和pull的时候就会很慢，甚至出错
下面分几步处理这些大文件

1. 显示10个最大的文件id列表

  ```
  git verify-pack -v .git/objects/pack/pack-*.idx | sort -k 3 -g | tail -10
  ```

  ```
  $ git verify-pack -v .git/objects/pack/pack-*.idx | sort -k 3 -g | tail -10
  ebdb8ed8dc5dc1853130464a046e4cb5f5250f50 blob   16995047 289806 50530080
  c8314b6a53d3be817056e1039ea1c09eb84e48fc blob   17550974 16408168 618857108
  8f6faaf850fc613ab9d5405dc0b9b844d83b434d blob   18190336 16840793 204351134
  db2d9cd01744c4a518fda8c05236bee3045d7b4b blob   18190336 5863977 198487105
  f91e726919baa8c8237e33907e65158be2aa14da blob   18346068 18125884 18795040
  bf0593318ae89b7651a1b83afaebebf123bf3813 blob   19361255 19328944 21033515
  a0ce986da047d0be539aa4ad33d4138b6a6cb725 blob   27562680 2361854 761724655
  fc5adb804cbe2e1f0c4f6b03917c88175e76748e blob   31251863 29165753 562994062
  fbf5c375a0bce40073286f937f191aee11b5bb11 blob   56499805 55955568 774680231
  64d06e529fcf16d1892d3ceb8a87d76665e9a5e3 blob   62486761 4637758 765016131
  ```

  

2. 根据文件id找出文件所在路径

  ```
  git rev-list --objects --all | grep 55d4e40c0927d5d489c0c92466a0d656f7068bcd
  ```

  ```
  $ git rev-list --objects --all | grep ebdb8ed8dc5dc1853130464a046e4cb5f5250f50
  ebdb8ed8dc5dc1853130464a046e4cb5f5250f50 Python's Books/data_wrangling/data/who/data.xls
  ```

  

3. 删除文件

  ```
  git log --pretty=oneline --branches -- your_file
  ```

  ```
  git log --pretty=oneline --branches -- node_modules.zip
  ```

  

4. 删除文件的历史记录

  ```
  git filter-branch --force --index-filter 'git rm -rf --cached --ignore-unmatch 你的大文件名' --prune-empty --tag-name-filter cat -- --all
  ```

  ```
  $ git filter-branch --force --index-filter 'git rm -rf --cached --ignore-unmatch ip_arp_202205.csv' --prune-empty --tag-name-filter cat -- --all
  WARNING: git-filter-branch has a glut of gotchas generating mangled history
           rewrites.  Hit Ctrl-C before proceeding to abort, then use an
           alternative filtering tool such as 'git filter-repo'
           (https://github.com/newren/git-filter-repo/) instead.  See the
           filter-branch manual page for more details; to squelch this warning,
           set FILTER_BRANCH_SQUELCH_WARNING=1.
  Proceeding with filter-branch...
  
  Cannot rewrite branches: You have unstaged changes.
  Additionally, your index contains uncommitted changes.
  
  ```

  

5. 清除缓存（真正删除）

  ```
  rm -rf .git/refs/original/
  git reflog expire --expire=now --all
  git gc --prune=now
  git gc --aggressive --prune=now
  git push origin master
  ```

  

6. 让远程仓库变小
git remote prune origin

