# AMATH536_FinalProject
This repository contains our code for our final project for AMATH 536, Mathematical Modeling of Cancer, at the University of Washington. 
We built the model from Lange et al, Nature Genetics, 2022, by adding copy number dependent selection for ecDNA. 

## About the files
The file 'copy_number_dependent_selection.ipynb' is a Jupyter Notebook that contains the code for our simulation, the code used to generate data, and all code for plotting.  

The file 'ecDNA_LangePaper.cpp' is the original code from Lange et al. It does not run in its current form due to deprecation of functions.  

The file 'ecDNA_LangeUpdated.cpp' is a fixed version of 'ecDNA_LangePaper.cpp' which updates the deprecated functions.   

The folder 'data' contained all simulation data generated from our Python simulation for this project. Data generated from the Lange et al code is in the main folder with .txt extensions..   

The folder 'figures' contains figures generated for this project.  

### Naming conventions
The data files are in the format ks_{num} _ alpha _ {num} _ k0_{num}.csv. If k0 is not listed, it is 100.

ks stands for k star, the threshold at which the fitness function becomes constant. The number immediately after ks in the file name is the k star at which the simulation was run. alpha is the slope of the line. k0 is the number of copies of ecDNA in the initiating cell. 
