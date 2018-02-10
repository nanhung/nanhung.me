---
title: Sensitivity Analysis by Python SALib
date: '2017-08-29'
slug: sensitivity-analysis-by-python-salib
---


Sensitivity analysis is a mathematical method to understand how model output influenced by the uncertainty in the model parameters. 
This is a simple example to perform a sensitivity analysis by python module call "SALib". 
I use the Morris method as an example and visualize the test results. 
The testing environment is cloud9. 

repo: [SALib](https://github.com/SALib/SALib)

## 1. In terminal, update the package list and install python-pip

```
sudo apt-get update 
```

```
sudo apt-get install python-pip
```

## 2. Update the setuptools then install the SALib 

```
sudo pip install -U setuptools
```

```
sudo pip install SALib
```

## 3. Create the following python script and name it [morris.py](https://raw.githubusercontent.com/nanhung/c9.gsa/master/morris.py)

```python
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from SALib.analyze import morris
from SALib.sample.morris import sample
from SALib.test_functions import Ishigami, Sobol_G
from SALib.util import read_param_file
from SALib.plotting.morris import horizontal_bar_plot, covariance_plot, sample_histograms

# Read the parameter range file and generate samples
problem = read_param_file('Sobol_G.txt')

# Generate samples
param_values = sample(problem, N=1000, num_levels=4, grid_jump=2, optimal_trajectories=None)

# To use optimized trajectories (brute force method), give an integer value for optimal_trajectories

# Run the "model" -- this will happen offline for external models
Y = Sobol_G.evaluate(param_values)

# Perform the sensitivity analysis using the model output
# Specify which column of the output file to analyze (zero-indexed)
Si = morris.analyze(problem, param_values, Y, conf_level=0.95, 
                    print_to_console=True,
                    num_levels=4, grid_jump=2, num_resamples=100)

print 'Convergence index:', max(Si['mu_star_conf']/Si['mu_star'])

fig, (ax1, ax2) = plt.subplots(1, 2)
horizontal_bar_plot(ax1, Si,{}, sortby='mu_star', unit=r"tCO$_2$/year")
covariance_plot(ax2, Si, {}, unit=r"tCO$_2$/year")
fig.savefig('morris.png')

fig2 = plt.figure()
sample_histograms(fig2, param_values, problem, {'color':'y'})
fig2.savefig('morris2.png')
```

## 4. We also need the input file [Sobol_G.txt](https://raw.githubusercontent.com/nanhung/c9.gsa/master/Sobol_G.txt),
to defind the range of input parameters

```
x1 0.0 1.0
x2 0.0 1.0
x3 0.0 1.0
x4 0.0 1.0
x5 0.0 1.0
x6 0.0 1.0
x7 0.0 1.0
x8 0.0 1.0
```

## 5. Run the python script

```
python morris.py
```

After that, we can get the following result

```
Parameter                         Mu_Star         Mu    Mu_Star_Conf      Sigma
x1                                  2.659      0.015           0.048      2.784
x2                                  1.459      0.024           0.047      1.652
x3                                  0.598     -0.005           0.024      0.701
x4                                  0.345     -0.002           0.013      0.402
x5                                  0.034     -0.000           0.001      0.040
x6                                  0.035      0.000           0.002      0.041
x7                                  0.035     -0.001           0.001      0.041
x8                                  0.035      0.000           0.001      0.041
Convergence index: 0.0443469829843
```

Here are the visualize test results of  
**(1) Input paramter distributions, and**

![](https://i.imgur.com/Ho8vTE2.png)

**(2) Parameter sensitivty**  

![](https://i.imgur.com/E0wH2uG.png)

According to this result, we can easily determine which parameters are sensitive and have high effect on model output.