#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul  6 18:12:23 2021

@author: miguelcant
"""

import pandas as pd

names=['Clump Thickness','Uniformity of Cell Size','Uniformity of Cell Shape','Marginal Adhesion','Single Epithelial Cell Size','Bare Nuclei','Bland Chromatin','Normal Nucleoli','Mitoses','Class']
df2 = pd.read_csv('https://archive.ics.uci.edu/ml/machine-learning-databases/breast-cancer-wisconsin/breast-cancer-wisconsin.data', names = names)

df = pd.get_dummies(df2,columns=['Clump Thickness','Uniformity of Cell Size','Uniformity of Cell Shape','Marginal Adhesion','Single Epithelial Cell Size','Bare Nuclei','Bland Chromatin','Normal Nucleoli','Mitoses','Class'])

df = df.sample(n=500,replace=True)
df.to_csv("/home/miguelcant/Documentos/FCA_mcantarero/datasets/breastcancer.csv")

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
N, bins, patches = ax.hist(array, bins=99, color="#ffbb33",edgecolor='black') #initial color of all bins
plt.savefig("/home/miguelcant/Documentos/FCA_mcantarero/results/real-datasets/distribution-breast.png")