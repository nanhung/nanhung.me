+++
title = "Save and Load"
date = '2018-02-01'
slug = "save-and-load"
tags = ["git"]
summary = "Rarely used but useful Git command"
+++

I don't frequently use `git reset`. But sometime it is very useful. It just like the "SAVE and LOAD" method if you familiar with old video game :)

To revert to last version in current branch: 

```bash
git reset --hard HEAD
```

For a single file :

```bash
git checkout -- <file name>
```

To revert to version before last version:

```bash
git reset --hard HEAD^
```

To revert to eariler version follow this step:

```bash
git reset 6c5989b 
git reset --soft HEAD@{1}
git commit -m "Revert to 6c5989b"
git reset --hard
git push
```
Here, `6c5986b` is the previous commit number.

![](https://files.explosm.net/comics/comicsavegamenew.png)