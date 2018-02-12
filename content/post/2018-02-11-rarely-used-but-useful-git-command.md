---
title: Rarely used but useful Git command (SAVE and LOAD)
date: '2018-02-11'
slug: rarely-used-but-useful-git-command
---

I don't frequently use `git reset`. But sometime it is very useful. It just like the "SAVE and LOAD" method if you familiar with old video game :)

To revert to last version in current branch: 

```
git reset --hard HEAD
```

To revert to version before last version:

```
git reset --hard HEAD^
```

To revert to eariler version follow this step:

```
git reset 6c5989b 
git reset --soft HEAD@{1}
git commit -m "Revert to 6c5989b"
git reset --hard
git push
```
Here, `6c5986b` is the previous commit number.

![](http://files.explosm.net/comics/comicsavegamenew.png)