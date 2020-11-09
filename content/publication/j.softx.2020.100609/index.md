---
title: "pksensi: An R package to apply global sensitivity analysis in physiologically based kinetic modeling"
authors:
- admin
- Brad Reisfeld
- Weihsueh A. Chiu

date: "2020-07-1T00:00:00Z"
#doi: ""

# Publication type.
# Legend: 0 = Uncategorized; 1 = Conference paper; 2 = Journal article;
# 3 = Preprint / Working Paper; 4 = Report; 5 = Book; 6 = Book section;
# 7 = Thesis; 8 = Patent
publication_types: ["2"]

# Publication name and optional abbreviated publication name.
publication: In *SoftwareX*
publication_short: In *SoftwareX*

tags:
- sensitivity
- PBPK
- R

featured: false

links:
#- name: Custom Link
# url_pdf: '#'
url_source: 'https://doi.org/10.1016/j.softx.2020.100609'
links:
- icon: file
  icon_pack: fas
  name: BibTeX
  url: https://nanhung.netlify.com/bibtex/hsieh2020pksensi.html
url_code: 'https://github.com/ElsevierSoftwareX/SOFTX_2020_29'
url_dataset: ''
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

Sensitivity analysis (SA) is an essential tool for modelers to understand the influence of model parameters on model outputs. It is also increasingly used in developing and assessing physiologically based kinetic (PBK) models. For instance, several studies have applied global SA to reduce the computational burden in the Bayesian Markov chain Monte Carlo-based calibration process PBK models. Although several SA algorithms and software packages are available, no comprehensive software package exists that allows users to seamlessly solve differential equations in a PBK model, conduct and visualize SA results, and discriminate between the non-influential model parameters that can be fixed and those that need calibration. Therefore, we developed an R package, named **pksensi**, to make global SA more accessible in PBK modeling. This package can investigate both uncertainty and sensitivity in PBK models, including those with multivariate model outputs. It also includes functions to check the convergence of the global SA results. Overall, **pksensi** improves the user experience of performing global SA and can create robust and reproducible results for decision making in PBK model calibration.
