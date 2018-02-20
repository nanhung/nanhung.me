---
title: Disqus on Hugo
date: '2018-02-10'
slug: disqus-on-hugo
tags: ["disqus", "hugo"]
---

I follow the blog post from Dr. Baumgartner to [install the Disqus on Hugo](https://portfolio.peter-baumgartner.net/2017/09/10/how-to-install-disqus-on-hugo/). But here is a detail I didn't notice. It seems that I should add following html script in `single.html` like [this](https://github.com/nanhung/nanhung.me/commit/767053ff6d37b868cad95d227c0cbaf5b3aebb13).

```html
  <div class="article-content">
  {{ partial "disqus.html" .}}
  </div>
```

![](http://geekshumor.com/wp-content/uploads/2013/11/Debugging.jpg)

**Update on 2018-02-19**:
I changed the theme to cactus. To add disqus to this theme, I remove the default setting 

```html
{{ template "_internal/disqus.html" . }}
```

and add following syntax in `single.html`

```html
{{ partial "disqus.html" . }}
```

