+++
# Date this page was created.
date = "2018-06-11"
  
# Project title.
title = "Sensitivity analysis of physiologically-based pharmacokinetic model"
  
# Project summary to display on homepage.
summary = "Reducing the dimensionality of Bayesian PBPK modeling algorithms by sensitivity analysis"

# Optional image to display on homepage (relative to `static/img/` folder).
# image_preview = "bubbles.jpg"
  
# Tags: can be used for filtering projects.
# Example: `tags = ["machine-learning", "deep-learning"]`
tags = ["sobol", "computer", "efficiency", "sensitivity", "uncertainty"]
  
# Optional external URL for project (replaces project detail page).
external_link = ""
  
# Does the project detail page use math formatting?
math = false
  
# Optional featured image (relative to `static/img/` folder).
# [header]
# image = "headers/bubbles-wide.jpg"
# caption = "My caption :smile:"
  
+++

Abstract:  
Traditionally, the usual solution to reduce parameter dimensionality in the physiologically-based pharmacokinetic (PBPK) model is through expert judgment. However, this approach may lead to lower efficiency and substantial bias in parameter estimates. The purpose of this study is to propose a global sensitivity analysis (GSA) algorithm to ascertain which parameters in a PBPK model are non-influential, and therefore can be assigned fixed values to improved speed and convergence in Bayesian parameter estimation with minimal bias. Overall, we propose that this GSA approach provides an objective, transparent, and reproducible approach to improve the performance and computational efficiency of PBPK models.