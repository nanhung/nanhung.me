---
title: "Applying a global sensitivity analysis workflow to improve the computational efficiencies in physiologically-based pharmacokinetic modeling"
authors:
- admin
- Brad Reisfeld
- Frederic Y. Bois
- Weihsueh A. Chiu

date: "2018-06-08T00:00:00Z"
#doi: "10.3389/fphar.2018.00588"

# Publication type.
# Legend: 0 = Uncategorized; 1 = Conference paper; 2 = Journal article;
# 3 = Preprint / Working Paper; 4 = Report; 5 = Book; 6 = Book section;
# 7 = Thesis; 8 = Patent
publication_types: ["2"]

# Publication name and optional abbreviated publication name.
publication: In *Frontier in Pharmacology*
publication_short: In *Front. Pharmacol.*

tags:
- sensitivity
- PBPK
- bayesian
- pharmacokinetics
featured: false

links:
#- name: Custom Link
#  url: http://example.org
url_source: 'https://doi.org/10.3389/fphar.2018.00588'
links:
- icon: file
  icon_pack: fas
  name: BibTeX
  url: https://nanhung.netlify.com/bibtex/hsieh2018applying.html
#url_pdf: '#'
#url_code: '#'
#url_dataset: '#'
#url_project: '#'
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
slides: example

#{{% alert note %}}
#Click the *Cite* button above to demo the feature to enable visitors to import publication metadata into their reference management software.
#{{% /alert %}}

#{{% alert note %}}
#Click the *Slides* button above to demo Academic's Markdown slides feature.
#{{% /alert %}}

#Supplementary notes can be added here, including [code and math](https://sourcethemes.com/academic/docs/writing-markdown-latex/).

---

Traditionally, the solution to reduce parameter dimensionality in a physiologically-based pharmacokinetic (PBPK) model is through expert judgment. However, this approach may lead to bias in parameter estimates and model predictions if important parameters are fixed at uncertain or inappropriate values. The purpose of this study was to explore the application of global sensitivity analysis (GSA) to ascertain which parameters in the PBPK model are non-influential, and therefore can be assigned fixed values in Bayesian parameter estimation with minimal bias. We compared the elementary effect-based Morris method and three variance-based Sobol indices in their ability to distinguish “influential” parameters to be estimated and “non-influential” parameters to be fixed. We illustrated this approach using a published human PBPK model for acetaminophen (APAP) and its two primary metabolites APAP-glucuronide and APAP-sulfate. We first applied GSA to the original published model, comparing Bayesian model calibration results using all the 21 originally calibrated model parameters (OMP, determined by “expert judgment”-based approach) vs. the subset of original influential parameters (OIP, determined by GSA from the OMP). We then applied GSA to all the PBPK parameters, including those fixed in the published model, comparing the model calibration results using this full set of 58 model parameters (FMP) vs. the full set influential parameters (FIP, determined by GSA from FMP). We also examined the impact of different cut-off points to distinguish the influential and non-influential parameters. We found that Sobol indices calculated by eFAST provided the best combination of reliability (consistency with other variance-based methods) and efficiency (lowest computational cost to achieve convergence) in identifying influential parameters. We identified several originally calibrated parameters that were not influential, and could be fixed to improve computational efficiency without discernable changes in prediction accuracy or precision. We further found six previously fixed parameters that were actually influential to the model predictions. Adding these additional influential parameters improved the model performance beyond that of the original publication while maintaining similar computational efficiency. We conclude that GSA provides an objective, transparent, and reproducible approach to improve the performance and computational efficiency of PBPK models.
