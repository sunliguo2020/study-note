```shell
git filter-branch --force --index-filter 'git rm --cached --ignore-unmatch pom.xml' --prune-empty --tag-name-filter cat -- --all

WARNING: git-filter-branch has a glut of gotchas generating mangled history
         rewrites.  Hit Ctrl-C before proceeding to abort, then use an
         alternative filtering tool such as 'git filter-repo'
         (https://github.com/newren/git-filter-repo/) instead.  See the
         filter-branch manual page for more details; to squelch this warning,
         set FILTER_BRANCH_SQUELCH_WARNING=1.
Proceeding with filter-branch...

fatal: bad revision 'rm'
```
在windows中将单引号改为双引号就可以了。

```shell
$ git filter-branch --force --index-filter "git rm -rf --cached --ignore-unmatch bin/106/15653613200.txt" --prune-empty --tag-name-filter cat -- --all
WARNING: git-filter-branch has a glut of gotchas generating mangled history
         rewrites.  Hit Ctrl-C before proceeding to abort, then use an
         alternative filtering tool such as 'git filter-repo'
         (https://github.com/newren/git-filter-repo/) instead.  See the
         filter-branch manual page for more details; to squelch this warning,
         set FILTER_BRANCH_SQUELCH_WARNING=1.
Proceeding with filter-branch...

Rewrite 66c31d78728c04b332ed5162f7ffc473629fe618 (1/48) (0 seconds passed, remaiRewrite 25d2d53084124d703eda80570e90beebdaebd3ba (2/48) (0 seconds passed, remaiRewrite 02ed653842ffbe4441829e0b1deee35906abf22c (3/48) (1 seconds passed, remaiRewrite 444920f8676c1299bdce307533fd5cc30e49c9d1 (3/48) (1 seconds passed, remaiRewrite 86aff3db77191a201b35cacb371e42b9fc7caa91 (3/48) (1 seconds passed, remaiRewrite 647ec23acf34a285a06ba2e1eef0e6489334a41b (13/48) (8 seconds passed, remaining 21 predicted)    rm 'bin/106/15653613200.txt'
Rewrite a771b46f3bd1f51d69500b137cdbf8ddb861ec06 (47/48) (34 seconds passed, remaining 0 predicted)
Ref 'refs/heads/dev' was rewritten
Ref 'refs/heads/master' was rewritten
Ref 'refs/remotes/origin/master' was rewritten
Ref 'refs/remotes/origin/dev' was rewritten
WARNING: Ref 'refs/remotes/origin/master' is unchanged

````
看来是需要加路径才可以来
