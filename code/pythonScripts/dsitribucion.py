#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul  6 18:12:23 2021
This file creates an histogram of the attribute distribution from a csv file
@author: miguelcant
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('/home/miguelcant/Documentos/FCA_mcantarero/datasets/M100/g\'10/G500dataset1.csv', index_col=0)
suma=0
array=[]    

for i in range(0, df.shape[0]):
    attributes=df.iloc[i]
    suma=suma+attributes.sum()
    for idx, val in enumerate(attributes):
        if val==1:
            array.append(idx)
 

    
print("g'=")
print(suma/df.shape[0])

fig, ax = plt.subplots(figsize=[8,6])

# set plot title
ax.set_title("Distribución de los atributos")

# set x-axis name
ax.set_xlabel("Num. atributo")

# set y-axis name
ax.set_ylabel("|Relaciones|")
N, bins, patches = ax.hist(array, bins=99, color="#3336ff",edgecolor='black') #initial color of all bins
#plt.show()
plt.savefig("/home/miguelcant/Documentos/FCA_mcantarero/images/distribution-artificialg10G500.png")
    

