---
title: "Well-tempered MCMC simulations for population pharmacokinetic models"
authors:
- Frederic Y. Bois
- admin
- Wang Gao
- Weihsueh A. Chiu
- Brad Reisfeld

date: "2020-07-31T00:00:00Z"
#doi: ""

# Publication type.
# Legend: 0 = Uncategorized; 1 = Conference paper; 2 = Journal article;
# 3 = Preprint / Working Paper; 4 = Report; 5 = Book; 6 = Book section;
# 7 = Thesis; 8 = Patent
publication_types: ["2"]

# Publication name and optional abbreviated publication name.
publication: In *Journal of Pharmacokinetics and Pharmacodynamics*
publication_short: In *J Pharmacokinet Pharmacodyn*

tags:
- PBPK
- bayesian
- pharmacokinetics

featured: false

links:
#- name: Custom Link
# url_pdf: '#'
url_source: 'https://doi.org/10.1007/s10928-020-09705-0'
links:
- icon: file
  icon_pack: fas
  name: BibTeX
  url: https://nanhung.netlify.com/bibtex/bois2020well.html
url_code: 'https://www.gnu.org/software/mcsim/supplement_tempering.zip'
url_dataset: 'https://doi.org/10.5281/zenodo.3427946'
#url_slides: '#'
#url_video: '#'

# Featured image
# To use, add an image named `featured.jpg/png` to your page's folder. 
#image:
#  caption: 'Image credit: [**Unsplash**](https://unsplash.com/photos/pLCdAaMFLTE)'
#  focal_point: ""
#  preview_only: false

# Associated Projects (optional).
#   Associate this publication with one or more of your projects.
#   Simply enter your project's folder or file name without extension.
#   E.g. `internal-project` references `content/project/internal-project/index.md`.
#   Otherwise, set `projects: []`.
projects:
- FDA-PBPK

# Slides (optional).
#   Associate this publication with Markdown slides.
#   Simply enter your slide deck's filename without extension.
#   E.g. `slides: "example"` references `content/slides/example/index.md`.
#   Otherwise, set `slides: ""`.
# slides: example

#{{% alert note %}}
#Click the *Cite* button above to demo the feature to enable visitors to import publication metadata into their reference management software.
#{{% /alert %}}

#{{% alert note %}}
#Click the *Slides* button above to demo Academic's Markdown slides feature.
#{{% /alert %}}

#Supplementary notes can be added here, including [code and math](https://sourcethemes.com/academic/docs/writing-markdown-latex/).

---

A full Bayesian statistical treatment of complex pharmacokinetic or pharmacodynamic models, in particular in a population context, gives access to powerful inference, including on model structure. Markov Chain Monte Carlo (MCMC) samplers are typically used to estimate the joint posterior parameter distribution of interest. Among MCMC samplers, the simulated tempering algorithm (TMCMC) has a number of advantages: it can sample from sharp multi-modal posteriors; it provides insight into identifiability issues useful for model simplification; it can be used to compute accurate Bayes factors for model choice; the simulated Markov chains mix quickly and have assured convergence in certain conditions. The main challenge when implementing this approach is to find an adequate scale of auxiliary inverse temperatures (perks) and associated scaling constants. We solved that problem by adaptive stochastic optimization and describe our implementation of TMCMC sampling in the *GNU MCSim* software. Once a grid of perks is obtained, it is easy to perform posterior-tempered MCMC sampling or likelihood-tempered MCMC (thermodynamic integration, which bridges the joint prior and the posterior parameter distributions, with assured convergence of a single sampling chain). We compare TMCMC to other samplers and demonstrate its efficient sampling of multi-modal posteriors and calculation of Bayes factors in two stylized case-studies and two realistic population pharmacokinetic inference problems, one of them involving a large PBPK model.
