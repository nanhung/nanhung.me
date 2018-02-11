---
title: Disqus on Hugo
date: '2018-02-10'
slug: disqus-on-hugo
---

I follow the blog post from Dr. Baumgartner to [install the Disqus on Hugo](https://portfolio.peter-baumgartner.net/2017/09/10/how-to-install-disqus-on-hugo/). But here is a detail I didn't notice. It seems that I should add following html script in single.html.

```html
  <div class="article-content">
  {{ partial "disqus.html" .}}
  </div>
```

![Imgur](https://i.imgur.com/ysmjLPS.png)



