---
title: 'Sobol Sensitivity Analysis for pharmacokinetic Model'
subtitle: 'Convergence assessment of Sobol sensitivity analysis in pharmacokinetic modeling'
summary: Convergence assessment of Sobol sensitivity analysis in pharmacokinetic modeling.
authors:
- admin
tags:
- sobol
- mrgsolve
- convergence
- pharmacokinetics 
categories:
- sensitivity
date: "2019-02-08T00:00:00Z"
lastmod: "2019-02-08T00:00:00Z"
featured: false
draft: false

# Featured image
# To use, add an image named `featured.jpg/png` to your page's folder.
# Placement options: 1 = Full column width, 2 = Out-set, 3 = Screen-width
# Focal point options: Smart, Center, TopLeft, Top, TopRight, Left, Right, BottomLeft, Bottom, BottomRight
image:
  placement: 2
  caption: 'Image credit: [**Unsplash**](https://unsplash.com/photos/CpkOjOcXdUY)'
  focal_point: ""
  preview_only: false

# Projects (optional).
#   Associate this post with one or more of your projects.
#   Simply enter your project's folder or file name without extension.
#   E.g. `projects = ["internal-project"]` references `content/project/deep-learning/index.md`.
#   Otherwise, set `projects = []`.
projects: [sensitivity]

---

<div id="TOC">
<ul>
<li><a href="#reproducible-analysis"><span class="toc-section-number">1</span> Reproducible analysis</a></li>
<li><a href="#methods-and-defined-functions"><span class="toc-section-number">2</span> Methods and defined functions</a></li>
<li><a href="#results-1"><span class="toc-section-number">3</span> Results</a></li>
<li><a href="#take-away"><span class="toc-section-number">4</span> Take away</a></li>
</ul>
</div>

<p>I find a great <a href="https://github.com/mrgsolve/gallery/blob/master/application/sobol.md">example</a> about performing Sobol sensitivity analysis within pharmacokinetic modeling through <a href="https://mrgsolve.github.io/">mrgsolve</a> and <a href="https://dpastoor.github.io/PKPDmisc/">PKPDmisc</a>. I didn’t have any experience to use these packages in my study. But this is a good opportunity to understand how they work, since I have prior knowledge in sensitivity analysis. Last year, I was lucky to have a chance to participate in <a href="https://ec.europa.eu/jrc/en/event/training-course/samo-2018">the 10th summer school on Sensitivity Analysis of Model Output</a> (SAMO 2018). It was fantastic!<br />
Here I want to apply some techniques that I learned in this SAMO summer school, and it might be helpful to apply Sobol sensitivity analysis in pharmacokinetic modeling. Maybe in the future, I can integrate this approach in <a href="https://nanhung.rbind.io/pksensi/index.html">pksensi</a>.</p>
<div id="prerequisites---packages" class="section level2">
<h2><span class="header-section-number">0.1</span> Prerequisites - packages</h2>
<p>The list of R packages should be installed first to do the following testing. The related functions are also listed behind the package.</p>
<pre class="r"><code>library(tidyverse) 
library(mrgsolve) # mrgsim_ei
library(PKPDmisc) # auc_partial 
library(sensitivity) # sobol2007
library(randtoolbox) # sobol
library(reshape2) # melt
library(LSD) # heatscatter</code></pre>
<hr />
</div>
<div id="reproducible-analysis" class="section level1">
<h1><span class="header-section-number">1</span> Reproducible analysis</h1>
<p>This section is used to reproduce the result in previous post.</p>
<div id="the-sunitinib-pk-model" class="section level2">
<h2><span class="header-section-number">1.1</span> The sunitinib PK model</h2>
<pre class="r"><code>mod &lt;- mread(&quot;sunit&quot;, &quot;models&quot;) %&gt;% 
  update(end = 24, delta = 1) %&gt;% zero_re</code></pre>
<pre><code>## Building sunit ... done.</code></pre>
<pre class="r"><code>see(mod)</code></pre>
<pre><code>## 
## Model file:  sunit.cpp 
## $PARAM
## TVCL = 51.8
## TVVC = 2030
## TVKA = 0.195
## TVQ = 7.22
## TVVP = 583
## WTVC = 0.459
## SEXCL = -0.0876
## ASIANCL = -0.130
## GISTCL = -0.285
## SOLIDCL = -0.269
## MRCCCL = -0.258
## SEX = 0, ASIAN = 0, GIST = 0
## SOLID = 0, MRCC = 0, WT = 76.9
## 
## $MAIN
##   double CL  = TVCL * (1+SEXCL*SEX) * (1+ASIANCL*ASIAN) * 
##   (1+GISTCL*GIST) * (1+SOLIDCL*SOLID) * (1+MRCCCL*MRCC) * exp(ETA(1));
## 
## double V2 = TVVC*pow(WT/76.9, WTVC)*exp(ETA(2));
## double KA = TVKA*exp(ETA(3));
## double Q  = TVQ;
## double V3 = TVVP;
## 
## $OMEGA 0.14 0.18 0.64
## 
## $SIGMA 0.146
## 
## $PKMODEL cmt = &quot;GUT CENT, PERIPH&quot;, depot = TRUE
## 
## $POST
## capture CP = (1000*CENT/V2);</code></pre>
</div>
<div id="sunitinib-dosing" class="section level2">
<h2><span class="header-section-number">1.2</span> Sunitinib dosing</h2>
<pre class="r"><code>sunev &lt;- function(amt = 50,...) ev(amt = amt, ...)</code></pre>
</div>
<div id="a-bunch-of-helper-functions" class="section level2">
<h2><span class="header-section-number">1.3</span> A bunch of helper functions</h2>
<pre class="r"><code>gen_samples&lt;- function(n, l, which = names(l), factor = c(0.01,100)) {
  vars &lt;- select_vars(names(l), !!(enquo(which)))
  l &lt;- as.list(l)[vars]
  l &lt;- lapply(l, function(x) {
    x*factor  
  })
  n &lt;- length(l)*n*2
  df &lt;- as.data.frame(l)
  len &lt;- length(df)
  X &lt;- matrix(ncol=len, nrow=n)
  colnames(X) &lt;- names(df)
  Y &lt;- X
  for(i in seq(len)){
    r &lt;- runif(n, df[1,i], df[2,i])
    X[,i] &lt;- r
    r &lt;- runif(n, df[1,i], df[2,i])
    Y[,i] &lt;- r
  }
  return(list(x1 = as.data.frame(X), x2 = as.data.frame(Y)))
} </code></pre>
<pre class="r"><code>sim_chunk &lt;- function(mod, x) {
  mrgsim_ei(x = mod, ev = sunev(), 
            idata = x, obsonly = TRUE) %&gt;% 
    as_data_frame
}</code></pre>
<pre class="r"><code>batch_run &lt;- function(x) {
  out &lt;- sim_chunk(mod,x)
  out &lt;- group_by(out,ID) %&gt;% 
    summarise(AUC = auc_partial(time,CP))
  return(out$AUC)
}</code></pre>
</div>
<div id="sobol-sensitivity-analysis" class="section level2">
<h2><span class="header-section-number">1.4</span> Sobol sensitivity analysis</h2>
<p>The sampling method is based on this <a href="https://github.com/metrumresearchgroup/pbpk-qsp-mrgsolve/blob/master/docs/global_sensitivity_analysis.md">example</a>. Therefore I can adequately reproduce the same output.</p>
<pre class="r"><code>set.seed(88771)
samp &lt;- gen_samples(6000, param(mod), TVCL:TVVP)
head(samp$x1)</code></pre>
<pre><code>##       TVCL      TVVC      TVKA      TVQ      TVVP
## 1 2837.253 166875.30 11.013982 108.5520 34567.952
## 2 3490.800  14354.07 18.822180 547.8690 50545.862
## 3 2097.291 181348.34  9.694288 427.9187 24586.856
## 4 2341.387  26875.49 11.256036 698.8196  4460.470
## 5 5119.695  99479.77  2.140000 666.6529 45071.206
## 6 3456.046  19526.79  9.308946 240.5433  3260.133</code></pre>
<pre class="r"><code>x &lt;- sobol2007(batch_run, X1=samp$x1, X2=samp$x2, nboot=100)</code></pre>
<pre><code>## Warning: `as_data_frame()` is deprecated, use `as_tibble()` (but mind the new semantics).
## This warning is displayed once per session.</code></pre>
</div>
<div id="results" class="section level2">
<h2><span class="header-section-number">1.5</span> Results</h2>
<pre class="r"><code>plot(x)</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-10-1.png" width="672" /></p>
<p>The result shows that only TVCL and TVVC can significantly dominate the output result. Also, it’s difficult to determine the influence of TVKA, TVQ, and TVVP.</p>
<pre class="r"><code>x</code></pre>
<pre><code>## 
## Call:
## sobol2007(model = batch_run, X1 = samp$x1, X2 = samp$x2, nboot = 100)
## 
## Model runs: 420000 
## 
## First order indices:
##           original          bias   std. error     min. c.i.   max. c.i.
## TVCL  0.1601012111  2.214509e-03 0.0147719664  0.1316449251 0.189595425
## TVVC  0.3320740078  2.876393e-03 0.0251520442  0.2830470899 0.379087675
## TVKA  0.0010487694 -2.155859e-05 0.0006259874 -0.0003245785 0.002275195
## TVQ   0.0051811252 -2.478164e-04 0.0019619628  0.0013627356 0.009513428
## TVVP -0.0004045875 -1.257215e-04 0.0009964991 -0.0021085877 0.001548759
## 
## Total indices:
##        original          bias  std. error    min. c.i.  max. c.i.
## TVCL 0.62250758 -0.0034865050 0.017071677  0.592191898 0.66000962
## TVVC 0.81936724 -0.0004663454 0.017085775  0.782400067 0.85437849
## TVKA 0.01614792 -0.0005697163 0.005517145  0.004259271 0.02703173
## TVQ  0.04231475 -0.0017862104 0.047789088 -0.055005315 0.11255199
## TVVP 0.02456133  0.0004543576 0.009441657  0.003857844 0.04377317</code></pre>
</div>
</div>
<div id="methods-and-defined-functions" class="section level1">
<h1><span class="header-section-number">2</span> Methods and defined functions</h1>
<div id="log-uniform-quasi-monte-carlo-sampling" class="section level2">
<h2><span class="header-section-number">2.1</span> Log-uniform &amp; quasi-Monte Carlo sampling</h2>
<p>Based on the <code>gen_samples()</code> above, I further create two functions. The first one sample the parameters under the log-transformed parameter range. The main reason to develop this function is that the setting range of model parameters are extremely large in this example. The original example generated uniform samples from a 100 fold decrease to 100 fold increase based on the nominal parameter value. It might cause an unexpected sampling bias. Therefore, the new function aims to solve this problem.</p>
<p>Let’s call this function as <code>gen_samples_1()</code>.</p>
<pre class="r"><code>gen_samples_1 &lt;- function(n, l, which = names(l), factor = c(0.01,100)) {
  vars &lt;- select_vars(names(l), !!(enquo(which)))
  l &lt;- as.list(l)[vars]
  l &lt;- lapply(l, function(x) {x*factor})
  xx &lt;- log(factor, 10)[2] - log(factor, 10)[1]
  len &lt;- length(vars)
  X &lt;- matrix(runif(len * length(l)*n*2), ncol = len)
  Y &lt;- matrix(runif(len * length(l)*n*2), ncol = len)
  for(i in seq(len)){
    X[,i] &lt;- l[[i]][[1]] * 10^(X[,i] * xx)
    Y[,i] &lt;- l[[i]][[1]] * 10^(Y[,i] * xx)
    colnames(X) &lt;- colnames(Y) &lt;- vars 
  }
  return(list(x1 = as.data.frame(X), x2 = as.data.frame(Y)))
}</code></pre>
<p>Instead of the log-transformed parameter sampling, I further used <a href="https://en.wikipedia.org/wiki/Quasi-Monte_Carlo_method">quasi-Monte Carlo method</a> (QMC) in the second new function. Generally, this method can create a relative uniformly parameter condition than the random method. Let’s call this function as <code>gen_samples_2()</code>.</p>
<pre class="r"><code>gen_samples_2 &lt;- function(n, l, which = names(l), factor = c(0.01,100)) {
  vars &lt;- select_vars(names(l), !!(enquo(which)))
  l &lt;- as.list(l)[vars]
  l &lt;- lapply(l, function(x) {x*factor})
  xx &lt;- log(factor, 10)[2] - log(factor, 10)[1]
  len &lt;- length(vars)
  
  X &lt;- sobol(n = length(l)*n*2, dim = 5)
  Y &lt;- sobol(n = length(l)*n*2, dim = 5, seed = 2345, scrambling = 3)
  
  for(i in seq(len)){
    X[,i] &lt;- l[[i]][[1]] * 10^(X[,i] * xx)
    Y[,i] &lt;- l[[i]][[1]] * 10^(Y[,i] * xx)
    colnames(X) &lt;- colnames(Y) &lt;- vars 
  }
  return(list(x1 = as.data.frame(X), x2 = as.data.frame(Y)))
}</code></pre>
</div>
<div id="convergence-analysis" class="section level2">
<h2><span class="header-section-number">2.2</span> Convergence analysis</h2>
<p>This is one of the critical steps in sensitivity analysis. More details can be found in my published paper in <a href="https://www.frontiersin.org/articles/10.3389/fphar.2018.00588/full">Frontiers in Pharmacology</a>. Here I create a function called <code>sample_converge()</code>, which can generate the convergence index based on the values of the given sample number. The drawback of this function is time-consuming. Because it estimates the convergence index at each sample number and each defined sampling function.</p>
<pre class="r"><code>sample_converge &lt;- function(n, l, which = names(l)){
  vars &lt;- select_vars(names(l), !!(enquo(which)))
  m &lt;- matrix(NA, length(n), length(vars))
  colnames(m) &lt;- vars
  rownames(m) &lt;- n
  m2 &lt;- m1 &lt;- m
  for (i in seq(length(n))){
    samp &lt;- gen_samples(n[i], l, names(vars))
    samp1 &lt;- gen_samples_1(n[i], l, names(vars))
    samp2 &lt;- gen_samples_2(n[i], l, names(vars))
    x &lt;- sobol2007(batch_run, X1=samp$x1, X2=samp$x2, nboot=100)
    x1 &lt;- sobol2007(batch_run, X1=samp1$x1, X2=samp1$x2, nboot=100)
    x2 &lt;- sobol2007(batch_run, X1=samp2$x1, X2=samp2$x2, nboot=100)
    m[i,] &lt;- x$T[,&quot;max. c.i.&quot;] - x$T[,&quot;min. c.i.&quot;]
    m1[i,] &lt;- x1$T[,&quot;max. c.i.&quot;] - x1$T[,&quot;min. c.i.&quot;]
    m2[i,] &lt;- x2$T[,&quot;max. c.i.&quot;] - x2$T[,&quot;min. c.i.&quot;]
  } 
  X &lt;- list(MC = m, log_MC = m1, log_QMC = m2)
  m %&gt;% melt()
  
  return(X)
}</code></pre>
</div>
</div>
<div id="results-1" class="section level1">
<h1><span class="header-section-number">3</span> Results</h1>
<p>The first step in this section is using three defined functions to generate the testing parameter sets. The sampling number is 1000 for 5 parameters of TVCL, TVVC, TVKA, TVQ, and TVVP.</p>
<pre class="r"><code>set.seed(88771) 
samp &lt;- gen_samples(1000, param(mod), TVCL:TVVP)
set.seed(88771)
samp1 &lt;- gen_samples_1(1000, param(mod), TVCL:TVVP)
set.seed(88771)
samp2 &lt;- gen_samples_2(1000, param(mod), TVCL:TVVP)</code></pre>
<pre class="r"><code>head(samp$x1)</code></pre>
<pre><code>##       TVCL      TVVC      TVKA      TVQ      TVVP
## 1 2837.253  60942.57  7.963136 630.0039 22292.148
## 2 3490.800 149720.94 16.074012 622.5430 39757.169
## 3 2097.291  76185.77  9.419697 437.3082 45357.035
## 4 2341.387 201251.22  8.195339 541.6590  3983.256
## 5 5119.695 194035.06  9.592385 537.6485 48321.379
## 6 3456.046 137630.27 15.524459 414.2905 28568.707</code></pre>
<pre class="r"><code>head(samp1$x1)</code></pre>
<pre><code>##         TVCL        TVVC        TVKA          TVQ       TVVP
## 1   80.36703 33720.83858  0.03094521   0.11342304   250.5507
## 2  256.92007  1827.45564  1.73818471  24.59140377 11556.6357
## 3   21.55864  8151.36009  0.06179910   3.33735150   498.5483
## 4   33.27604  5318.35487 18.01243794   0.07733231   279.5965
## 5 4653.26263    23.78396 12.98278679 107.06337123   540.9213
## 6  241.52275 25146.74462  1.00422814   5.67155925  8914.3863</code></pre>
<pre class="r"><code>head(samp2$x1)</code></pre>
<pre><code>##        TVCL        TVVC        TVKA        TVQ        TVVP
## 1   51.8000  2030.00000 0.195000000  7.2200000   583.00000
## 2  518.0000   203.00000 1.950000000  0.7220000  5830.00000
## 3    5.1800 20300.00000 0.019500000 72.2000000    58.30000
## 4   16.3806   641.94237 0.616644144  0.2283164 18436.07876
## 5 1638.0598 64194.23650 0.006166441 22.8316447   184.36079
## 6  163.8060    64.19424 0.061664414  2.2831645    18.43608</code></pre>
<p>We can check the range of TVCL.</p>
<pre class="r"><code>i &lt;- &quot;TVCL&quot;</code></pre>
<pre class="r"><code>range(samp$x1[,i])</code></pre>
<pre><code>## [1]    1.395682 5179.881030</code></pre>
<pre class="r"><code>range(samp1$x1[,i])</code></pre>
<pre><code>## [1]    0.5188091 5178.9042539</code></pre>
<pre class="r"><code>range(samp2$x1[,i])</code></pre>
<pre><code>## [1]    0.5185827 5174.1793514</code></pre>
<p>The probability distributions of TVCL look like this.</p>
<pre class="r"><code>par(mfrow = c(3,2), mar = c(2,2,1,1))
samp$x1[,i] %&gt;% density() %&gt;% plot(main = &quot;MC&quot;)
samp1$x1[,i] %&gt;% density() %&gt;% plot(main = &quot;Log MC&quot;)
samp1$x1[,i] %&gt;% log(10) %&gt;% density() %&gt;% plot(main = &quot;Log MC&quot;)
samp2$x1[,i] %&gt;% log(10) %&gt;% density() %&gt;% plot(main = &quot;Log QMC&quot;)
samp$x1[,i] %&gt;% log(10) %&gt;% density() %&gt;% plot(main = &quot;MC&quot;)</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-19-1.png" width="672" /></p>
<p>Although the sampling ranges are nearly the same, we can easily understand how different sampling method that cause the difference of parameter sampling result.</p>
<pre class="r"><code>j &lt;- &quot;TVKA&quot;
par(mfrow = c(3,2), mar = c(2,2,4,1))
heatscatter(samp$x1[,i], samp$x1[,j], add.contour=T, 
            nlevels=3, xlab = i, ylab = j, main = &quot;MC&quot;)
heatscatter(samp1$x1[,i], samp1$x1[,j], add.contour=T,
            nlevels=3, xlab = i, ylab = j, main = &quot;Log MC&quot;)
heatscatter(log(samp1$x1[,i]), log(samp1$x1[,j]), add.contour=T,
            nlevels=3, xlab = i, ylab = j, main = &quot;Log MC&quot;)
heatscatter(log(samp2$x1[,i]), log(samp2$x1[,j]), add.contour=T,
            nlevels=3, xlab = i, ylab = j, main = &quot;Log QMC&quot;)
heatscatter(log(samp$x1[,i]), log(samp$x1[,j]), add.contour=T,
            nlevels=3, xlab = i, ylab = j, main = &quot;MC&quot;)</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-20-1.png" width="672" /></p>
<p>Here, we can find the devil in detail. The uniform sampling in the parameter range without log-transformed ignore the lowest value that might cause bias in sampling.</p>
<div id="sobol-sensitivity-analysis-1" class="section level2">
<h2><span class="header-section-number">3.1</span> Sobol sensitivity analysis</h2>
<p>Now, let’s run <code>Sobol2007()</code> with sampling parameter sets that were generated above</p>
<pre class="r"><code>x &lt;- sobol2007(batch_run, X1=samp$x1, X2=samp$x2, nboot=100)
x1 &lt;- sobol2007(batch_run, X1=samp1$x1, X2=samp1$x2, nboot=100)
x2 &lt;- sobol2007(batch_run, X1=samp2$x1, X2=samp2$x2, nboot=100)</code></pre>
<p>Print result</p>
<pre class="r"><code>x</code></pre>
<pre><code>## 
## Call:
## sobol2007(model = batch_run, X1 = samp$x1, X2 = samp$x2, nboot = 100)
## 
## Model runs: 70000 
## 
## First order indices:
##          original          bias  std. error     min. c.i.   max. c.i.
## TVCL 0.1578766813  5.012385e-03 0.029278635  0.0897186624 0.201866655
## TVVC 0.3447385309  8.374844e-03 0.052814673  0.2256359297 0.427604593
## TVKA 0.0024763449  2.373005e-05 0.001390263 -0.0003113366 0.005189519
## TVQ  0.0006193458  5.645544e-04 0.003724279 -0.0080400435 0.006242974
## TVVP 0.0014283420 -4.903354e-05 0.001889425 -0.0024604804 0.005245518
## 
## Total indices:
##          original          bias std. error   min. c.i.   max. c.i.
## TVCL  0.672686672 -0.0102220989 0.04633728  0.59281897 0.789283127
## TVVC  0.879711964 -0.0019054688 0.02182246  0.83962655 0.928699868
## TVKA -0.002296679  0.0008413025 0.00627142 -0.01699606 0.008496922
## TVQ   0.090611733 -0.0070882690 0.04120019  0.02882457 0.187441411
## TVVP -0.017351498  0.0017017751 0.03155429 -0.07603819 0.063987904</code></pre>
<pre class="r"><code>x1</code></pre>
<pre><code>## 
## Call:
## sobol2007(model = batch_run, X1 = samp1$x1, X2 = samp1$x2, nboot = 100)
## 
## Model runs: 70000 
## 
## First order indices:
##         original          bias  std. error    min. c.i.  max. c.i.
## TVCL 0.112745680  0.0026565784 0.022466040  0.063361769 0.15082631
## TVVC 0.182459668  0.0025801709 0.026674092  0.127316358 0.23893441
## TVKA 0.021922824  0.0004888711 0.005009015  0.010456681 0.03100943
## TVQ  0.023164323  0.0002864731 0.008486985  0.003380099 0.03716093
## TVVP 0.002536912 -0.0001392410 0.009145051 -0.017324642 0.02074989
## 
## Total indices:
##        original          bias std. error  min. c.i. max. c.i.
## TVCL 0.71060891 -0.0090987188 0.03552466 0.65125586 0.7909084
## TVVC 0.72747952  0.0027789293 0.03171177 0.66407305 0.7794759
## TVKA 0.32450192 -0.0051129215 0.04216267 0.23945646 0.4078702
## TVQ  0.24375109 -0.0073162011 0.03950212 0.17323399 0.3362771
## TVVP 0.08803744  0.0004144841 0.01928357 0.04367123 0.1287615</code></pre>
<pre class="r"><code>x2</code></pre>
<pre><code>## 
## Call:
## sobol2007(model = batch_run, X1 = samp2$x1, X2 = samp2$x2, nboot = 100)
## 
## Model runs: 70000 
## 
## First order indices:
##         original          bias  std. error    min. c.i.  max. c.i.
## TVCL 0.103053511  0.0028262338 0.016635276  0.065230617 0.13173635
## TVVC 0.107953643  0.0018690990 0.015629609  0.077203453 0.13310952
## TVKA 0.026633093  0.0017673356 0.005997603  0.012004116 0.03583295
## TVQ  0.022689512 -0.0004086214 0.008989424  0.005895948 0.03760702
## TVVP 0.002595473  0.0007961698 0.005699388 -0.008999633 0.01419777
## 
## Total indices:
##        original          bias std. error  min. c.i. max. c.i.
## TVCL 0.69397587 -0.0082166809 0.03517866 0.62262374 0.7715309
## TVVC 0.75993807 -0.0002017117 0.02741192 0.71040000 0.8298959
## TVKA 0.29168389  0.0003159408 0.04169429 0.22751231 0.3914107
## TVQ  0.22996502 -0.0017208325 0.03689100 0.15739127 0.3073664
## TVVP 0.09510386  0.0008423339 0.02086733 0.04653191 0.1337083</code></pre>
<p>Plot</p>
<pre class="r"><code>par(mfrow = c(2,2), mar = c(2,2,3,1))
plot(x, main = &quot;MC&quot;)
plot(x1, main = &quot;Log MC&quot;)
plot(x2, main = &quot;Log QMC&quot;)</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-23-1.png" width="672" /></p>
<p>Same as above, we can find that only TVCL and TVVC have an obvious influence on the model output in the previous sampling method. However, the proposed methods can easily rank the importance of parameters in this case.</p>
<p>The results of the parameter vs. model output look like this.</p>
<pre class="r"><code>par(mfrow = c(3,2), mar = c(2,2,4,1))
for (i in 1:5){
  heatscatter(log(x$X[,i]), log(x$y), xlab = &quot;&quot;, ylab = &quot;&quot;, main = names(x$X)[i])
}</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-24-1.png" width="672" /></p>
<p>This is the result of sampling in the log-transformed parameter range.</p>
<pre class="r"><code>par(mfrow = c(3,2), mar = c(2,2,4,1))
for (i in 1:5){
  heatscatter(log(x1$X[,i]), log(x1$y), xlab = &quot;&quot;, ylab = &quot;&quot;, main = names(x1$X)[i])
}</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-25-1.png" width="672" /></p>
<p>It’s an efficient way to see the relationship between parameter value and model output. The high impact parameter has relatively concentrated contour than other parameters.</p>
</div>
<div id="convergence-assessment" class="section level2">
<h2><span class="header-section-number">3.2</span> Convergence assessment</h2>
<p>The convergence index can simply calculate through the 95% CI of sensitivity index that is estimated from bootstrapping in the Sobol method. Here is the result of the convergence index under the sample number of 1000 from the above section.</p>
<pre class="r"><code>x$T[,&quot;max. c.i.&quot;] - x$T[,&quot;min. c.i.&quot;]</code></pre>
<pre><code>## [1] 0.19646416 0.08907332 0.02549298 0.15861684 0.14002610</code></pre>
<pre class="r"><code>x1$T[,&quot;max. c.i.&quot;] - x1$T[,&quot;min. c.i.&quot;]</code></pre>
<pre><code>## [1] 0.13965253 0.11540284 0.16841379 0.16304310 0.08509031</code></pre>
<pre class="r"><code>x2$T[,&quot;max. c.i.&quot;] - x2$T[,&quot;min. c.i.&quot;]</code></pre>
<pre><code>## [1] 0.14890720 0.11949593 0.16389841 0.14997513 0.08717637</code></pre>
<p>In this part, the values of the sample number were set at 500, 1000, 2000, 4000, and 8000. It will take a couple of minutes to run <code>sample_converge()</code></p>
<pre class="r"><code>sample &lt;- c(500, 1000, 2000, 4000, 8000)
set.seed(88771)
system.time(converge_list &lt;- sample_converge(sample, param(mod), TVCL:TVVP))</code></pre>
<pre><code>##    user  system elapsed 
## 400.042   5.766 402.707</code></pre>
<pre class="r"><code>df &lt;- do.call(rbind, list(converge_list[[1]] %&gt;% melt() %&gt;% cbind(type = &quot;MC&quot;),
                          converge_list[[2]] %&gt;% melt() %&gt;% cbind(type = &quot;log_MC&quot;),
                          converge_list[[3]] %&gt;% melt() %&gt;% cbind(type = &quot;log_QMC&quot;)))</code></pre>
<p>Finally, visualizing the result to see the convergence of each parameter. Both QMC and MC random sampling showed a similar result. Each parameter was close or below the threshold of 0.05. However, it’s hard to conclude that the QMC can provide the best way for Sobol sensitivity analysis in pharmacokinetic modeling.</p>
<pre class="r"><code>theme_set(theme_light())
df %&gt;% `colnames&lt;-`(c(&quot;sample.no&quot;, &quot;parameter&quot;, &quot;index&quot;, &quot;type&quot;)) %&gt;%
  ggplot(aes(sample.no, index, group = parameter)) + geom_line(aes(color = parameter)) + 
  facet_wrap(~type) + 
  expand_limits(y= c(0, 0.5)) + geom_hline(yintercept = 0.05, linetype=&quot;dashed&quot;, size = 0.2) +
  labs(y = &quot;Convergence index&quot;, x = &quot;Sample number&quot;) +
  theme(legend.position = &quot;top&quot;)</code></pre>
<p><img src="/post/2019-02-08-sobol-sensitivity-analysis-for-pk-model_files/figure-html/unnamed-chunk-29-1.png" width="672" /></p>
</div>
</div>
<div id="take-away" class="section level1">
<h1><span class="header-section-number">4</span> Take away</h1>
<ol style="list-style-type: decimal">
<li><p>Always plot the data. Because the devil might in the detail and your data might look likes a dinosaur.</p></li>
<li><p>Rethinking about the sampling. If the sampling range is too wide, try using the log-transformed method.</p></li>
<li><p>Try Quasi-Monte Carlo. The QMC method can generate distribution than random MC sampling uniformly. Unfortunately, QMC didn’t show the best result in convergence assessment in this case.</p></li>
</ol>
<pre class="r"><code>devtools::session_info()</code></pre>
<pre><code>## ─ Session info ──────────────────────────────────────────────────────────
##  setting  value                       
##  version  R version 3.5.2 (2018-12-20)
##  os       Ubuntu 18.04.1 LTS          
##  system   x86_64, linux-gnu           
##  ui       X11                         
##  language en_US                       
##  collate  en_US.UTF-8                 
##  ctype    en_US.UTF-8                 
##  tz       America/Chicago             
##  date     2019-02-10                  
## 
## ─ Packages ──────────────────────────────────────────────────────────────
##  package       * version     date       lib source        
##  assertthat      0.2.0       2017-04-11 [1] CRAN (R 3.5.2)
##  backports       1.1.3       2018-12-14 [1] CRAN (R 3.5.2)
##  bindr           0.1.1       2018-03-13 [1] CRAN (R 3.5.2)
##  bindrcpp      * 0.2.2       2018-03-29 [1] CRAN (R 3.5.2)
##  blogdown        0.10        2019-01-09 [1] CRAN (R 3.5.2)
##  bookdown        0.9         2018-12-21 [1] CRAN (R 3.5.2)
##  boot            1.3-20      2017-07-30 [4] CRAN (R 3.5.0)
##  broom           0.5.1       2018-12-05 [1] CRAN (R 3.5.2)
##  callr           3.1.1       2018-12-21 [1] CRAN (R 3.5.2)
##  cellranger      1.1.0       2016-07-27 [1] CRAN (R 3.5.2)
##  cli             1.0.1       2018-09-25 [1] CRAN (R 3.5.2)
##  colorspace      1.4-0       2019-01-13 [1] CRAN (R 3.5.2)
##  crayon          1.3.4       2017-09-16 [1] CRAN (R 3.5.2)
##  desc            1.2.0       2018-05-01 [1] CRAN (R 3.5.2)
##  devtools        2.0.1       2018-10-26 [1] CRAN (R 3.5.2)
##  digest          0.6.18      2018-10-10 [1] CRAN (R 3.5.2)
##  dplyr         * 0.7.8       2018-11-10 [1] CRAN (R 3.5.2)
##  evaluate        0.12        2018-10-09 [1] CRAN (R 3.5.2)
##  forcats       * 0.3.0       2018-02-19 [1] CRAN (R 3.5.2)
##  fs              1.2.6       2018-08-23 [1] CRAN (R 3.5.2)
##  generics        0.0.2       2018-11-29 [1] CRAN (R 3.5.2)
##  ggplot2       * 3.1.0       2018-10-25 [1] CRAN (R 3.5.2)
##  glue            1.3.0       2018-07-17 [1] CRAN (R 3.5.2)
##  gtable          0.2.0       2016-02-26 [1] CRAN (R 3.5.2)
##  haven           2.0.0       2018-11-22 [1] CRAN (R 3.5.2)
##  hms             0.4.2       2018-03-10 [1] CRAN (R 3.5.2)
##  htmltools       0.3.6       2017-04-28 [1] CRAN (R 3.5.2)
##  httr            1.4.0       2018-12-11 [1] CRAN (R 3.5.2)
##  jsonlite        1.6         2018-12-07 [1] CRAN (R 3.5.2)
##  knitr           1.21        2018-12-10 [1] CRAN (R 3.5.2)
##  labeling        0.3         2014-08-23 [1] CRAN (R 3.5.2)
##  lattice         0.20-38     2018-11-04 [4] CRAN (R 3.5.1)
##  lazyeval        0.2.1       2017-10-29 [1] CRAN (R 3.5.2)
##  LSD           * 4.0-0       2018-01-26 [1] CRAN (R 3.5.2)
##  lubridate       1.7.4       2018-04-11 [1] CRAN (R 3.5.2)
##  magrittr        1.5         2014-11-22 [1] CRAN (R 3.5.2)
##  memoise         1.1.0       2017-04-21 [1] CRAN (R 3.5.2)
##  modelr          0.1.2       2018-05-11 [1] CRAN (R 3.5.2)
##  mrgsolve      * 0.9.0       2019-01-23 [1] CRAN (R 3.5.2)
##  munsell         0.5.0       2018-06-12 [1] CRAN (R 3.5.2)
##  nlme            3.1-137     2018-04-07 [4] CRAN (R 3.5.0)
##  pillar          1.3.1       2018-12-15 [1] CRAN (R 3.5.2)
##  pkgbuild        1.0.2       2018-10-16 [1] CRAN (R 3.5.2)
##  pkgconfig       2.0.2       2018-08-16 [1] CRAN (R 3.5.2)
##  pkgload         1.0.2       2018-10-29 [1] CRAN (R 3.5.2)
##  PKPDmisc      * 2.1.1       2017-12-17 [1] CRAN (R 3.5.2)
##  plyr            1.8.4       2016-06-08 [1] CRAN (R 3.5.2)
##  prettyunits     1.0.2       2015-07-13 [1] CRAN (R 3.5.2)
##  processx        3.2.1       2018-12-05 [1] CRAN (R 3.5.2)
##  ps              1.3.0       2018-12-21 [1] CRAN (R 3.5.2)
##  purrr         * 0.3.0       2019-01-27 [1] CRAN (R 3.5.2)
##  R6              2.3.0       2018-10-04 [1] CRAN (R 3.5.2)
##  randtoolbox   * 1.17.1      2018-02-14 [1] CRAN (R 3.5.2)
##  Rcpp            1.0.0       2018-11-07 [1] CRAN (R 3.5.2)
##  RcppArmadillo   0.9.200.7.0 2019-01-17 [1] CRAN (R 3.5.2)
##  readr         * 1.3.1       2018-12-21 [1] CRAN (R 3.5.2)
##  readxl          1.2.0       2018-12-19 [1] CRAN (R 3.5.2)
##  remotes         2.0.2       2018-10-30 [1] CRAN (R 3.5.2)
##  reshape2      * 1.4.3       2017-12-11 [1] CRAN (R 3.5.2)
##  rlang           0.3.1       2019-01-08 [1] CRAN (R 3.5.2)
##  rmarkdown       1.11        2018-12-08 [1] CRAN (R 3.5.2)
##  rngWELL       * 0.10-5      2017-05-21 [1] CRAN (R 3.5.2)
##  rprojroot       1.3-2       2018-01-03 [1] CRAN (R 3.5.2)
##  rstudioapi      0.9.0       2019-01-09 [1] CRAN (R 3.5.2)
##  rvest           0.3.2       2016-06-17 [1] CRAN (R 3.5.2)
##  scales          1.0.0       2018-08-09 [1] CRAN (R 3.5.2)
##  sensitivity   * 1.15.2      2018-09-02 [1] CRAN (R 3.5.2)
##  sessioninfo     1.1.1       2018-11-05 [1] CRAN (R 3.5.2)
##  stringi         1.2.4       2018-07-20 [1] CRAN (R 3.5.2)
##  stringr       * 1.3.1       2018-05-10 [1] CRAN (R 3.5.2)
##  tibble        * 2.0.1       2019-01-12 [1] CRAN (R 3.5.2)
##  tidyr         * 0.8.2       2018-10-28 [1] CRAN (R 3.5.2)
##  tidyselect      0.2.5       2018-10-11 [1] CRAN (R 3.5.2)
##  tidyverse     * 1.2.1       2017-11-14 [1] CRAN (R 3.5.2)
##  usethis         1.4.0       2018-08-14 [1] CRAN (R 3.5.2)
##  withr           2.1.2       2018-03-15 [1] CRAN (R 3.5.2)
##  xfun            0.4         2018-10-23 [1] CRAN (R 3.5.2)
##  xml2            1.2.0       2018-01-24 [1] CRAN (R 3.5.2)
##  yaml            2.2.0       2018-07-25 [1] CRAN (R 3.5.2)
## 
## [1] /home/nanhung/R/x86_64-pc-linux-gnu-library/3.5
## [2] /usr/local/lib/R/site-library
## [3] /usr/lib/R/site-library
## [4] /usr/lib/R/library</code></pre>
</div>
