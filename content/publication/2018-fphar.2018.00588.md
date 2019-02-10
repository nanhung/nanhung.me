+++
title = "Applying a Global Sensitivity Analysis Workflow to Improve the Computational Efficiencies in Physiologically-Based Pharmacokinetic Modeling"
date = "2018-06-08"

# Authors. Comma separated list, e.g. `["Bob Smith", "David Jones"]`.
authors = ["**Hsieh NH**", "Reisfeld B", "Bois FY", "Chiu WA*"]

# Publication type.
# Legend:
# 0 = Uncategorized
# 1 = Conference proceedings
# 2 = Journal
# 3 = Work in progress
# 4 = Technical report
# 5 = Book
# 6 = Book chapter
publication_types = ["2"]

# Publication name and optional abbreviated version.
publication = "*Frontiers in Pharmacology*"
publication_short = "*Front. Pharmacol*"

# Abstract and optional shortened version.
abstract = "Traditionally, the solution to reduce parameter dimensionality in a physiologically-based pharmacokinetic (PBPK) model is through expert judgment. However, this approach may lead to bias in parameter estimates and model predictions if important parameters are fixed at uncertain or inappropriate values. The purpose of this study was to explore the application of global sensitivity analysis (GSA) to ascertain which parameters in the PBPK model are non-influential, and therefore can be assigned fixed values in Bayesian parameter estimation with minimal bias. We compared the elementary effect-based Morris method and three variance-based Sobol indices in their ability to distinguish influential parameters to be estimated and non-influential parameters to be fixed. We illustrated this approach using a published human PBPK model for acetaminophen (APAP) and its two primary metabolites APAP-glucuronide and APAP-sulfate. We first applied GSA to the original published model, comparing Bayesian model calibration results using all the 21 originally calibrated model parameters (OMP, determined by expert judgment-based approach) vs. the subset of original influential parameters (OIP, determined by GSA from the OMP). We then applied GSA to all the PBPK parameters, including those fixed in the published model, comparing the model calibration results using this full set of 58 model parameters (FMP) vs. the full set influential parameters (FIP, determined by GSA from FMP). We also examined the impact of different cut-off points to distinguish the influential and non-influential parameters. We found that Sobol indices calculated by eFAST provided the best combination of reliability (consistency with other variance-based methods) and efficiency (lowest computational cost to achieve convergence) in identifying influential parameters. We identified several originally calibrated parameters that were not influential, and could be fixed to improve computational efficiency without discernable changes in prediction accuracy or precision. We further found six previously fixed parameters that were actually influential to the model predictions. Adding these additional influential parameters improved the model performance beyond that of the original publication while maintaining similar computational efficiency. We conclude that GSA provides an objective, transparent, and reproducible approach to improve the performance and computational efficiency of PBPK models."

# Featured image thumbnail (optional)
image_preview = ""

# Is this a selected publication? (true/false)
selected = false

# Projects (optional).
#   Associate this publication with one or more of your projects.
#   Simply enter the filename (excluding '.md') of your project file in `content/project/`.
projects = ["GSA-PBPK"]

# Links (optional).
url_pdf = "https://www.frontiersin.org/articles/10.3389/fphar.2018.00588/pdf"
#url_preprint = "#"
#url_code = "#"
#url_dataset = "#"
#url_project = "#"
#url_slides = "#"
#url_video = "#"
#url_poster = "#"
url_source = "https://www.frontiersin.org/articles/10.3389/fphar.2018.00588/full"

# Custom links (optional).
#   Uncomment line below to enable. For multiple links, use the form `[{...}, {...}, {...}]`.
url_custom = [{name = "BibTeX", url = "https://nanhung.netlify.com/bibtex/hsieh2018applying.html"}]

# Does the content use math formatting?
math = true

# Does the content use source code highlighting?
highlight = false

# Featured image
# Place your image in the `static/img/` folder and reference its filename below, e.g. `image = "example.jpg"`.
[header]
#image = "headers/bubbles-wide.jpg"
#caption = "My caption :smile:"

+++