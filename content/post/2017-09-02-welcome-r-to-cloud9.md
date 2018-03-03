+++
title = "Welcome R to Cloud9"
date = '2018-02-04'
slug = "welcome-r-to-cloud9"
tags = ["R", "c9"]
summary = " "
+++

I use R Studio to do the data analysis in my everyday work. 
But I wanna use the cloud-based system to remote and control my works more efficient.
Git is my first choice to control my files between my office desktop and my laptop. 
Unfortunately, sometimes, I forgot to commit my updated result when I leave my office.
And this is why I want to find this alternative method to use R in the cloud.

## 1. Install R

We can use this simple method to install R, but it can only install the old version `3.0.2`

```bash
sudo apt-get update 
sudo apt-get install r-base-core
```

So, I uninstall the old R 

```bash
sudo apt-get remove r-base-core
```

To install the latest R version, we need to know the current Ubuntu version first. Just use the following command,

```bash
lsb_release -a
```

And, I can find some information about current Ubuntu version "14.04" and the codename "trusty"

```bash
No LSB modules are available.
Distributor ID: Ubuntu
Description:    Ubuntu 14.04.5 LTS
Release:        14.04
Codename:       trusty
```

Add `deb` file in the "source.list" file by using "nano"

```bash
sudo nano /etc/apt/sources.list    
```

Then, add the following line and save the file.

```bash
deb http://cran.rstudio.com/bin/linux/ubuntu trusty/
```

Back to terminal, use the standard install process to install R

```
sudo apt-get update
```

```
sudo apt-get install r-base
```

then,

```
R
```

Boom!

![Imgur](https://i.imgur.com/WKh7TpL.png)


## 2. Test Example 

Let me do some tests. First, create the following R script and name it `hello.R`

```
png(file="hello.png",width=600,height=400,res=200)
plot.new()
mtext("Hello R!", line=-1)
dev.off()
```

- Enter to R console and type

```
source('hello.R')
```

Here is the output

![Imgur](https://i.imgur.com/ygu89QM.png)

Sometimes, I like to use the ggplot to create the fancy figure. So, I also do this test. Install "ggplot2" and create the R script call `hello-gg.R`

```
if(!require(ggplot2)) {install.packages("ggplot2"); require(ggplot2)}

p <- ggplot(NULL, aes(x = 1, y = 1)) + ylim(0.8, 1.2) +
     annotate("text", 1, 1, label = 'Hello R!',
              fontface = "bold", size = 14) +
     theme(axis.title = element_blank(), axis.ticks = element_blank(),
           axis.text = element_blank())

ggsave("hello-gg.png", width = 6, height = 4, dpi = 96)
```

Enter to R console and type

```bash
source('hello-gg.R')
```

Here is the output

![Imgur](https://i.imgur.com/VQf5uiS.png)

Now, I can use R to do statistical analysis and visualize result in Cloud 9!

## Reference
1. [https://stackoverflow.com/questions/16093331/how-to-install-r-version-3](https://stackoverflow.com/questions/16093331/how-to-install-r-version-3)
2. [https://cran.r-project.org/web/packages/showtext/vignettes/introduction.html](https://cran.r-project.org/web/packages/showtext/vignettes/introduction.html)
