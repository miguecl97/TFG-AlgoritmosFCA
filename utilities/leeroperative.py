#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul  6 18:12:23 2021

@author: miguelcant
"""

import pandas as pd
import matplotlib.pyplot as plt

names=['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30','31','32','33','34','35','36','37','38','39','40','41','42','43','44','45']
df2 = pd.read_csv('https://archive.ics.uci.edu/ml/machine-learning-databases/sponge/sponge.data', names = names)
del df2['9']
del df2['31']
del df2['32']
del df2['33']
del df2['34']
del df2['35']
del df2['36']
del df2['37']
del df2['38']
del df2['39']
del df2['40']
del df2['41']
del df2['42']
del df2['43']
del df2['44']
del df2['45']

df = pd.get_dummies(df2,columns=['1','2','3','4','5','6','7','8','10','11','12','13','14','15','16','17','18','19','20','21','22','23','24','25','26','27','28','29','30']) 
	   
df.to_csv("/home/miguelcant/Documentos/FCA_mcantarero/datasets/sponge.csv")

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
N, bins, patches = ax.hist(array, bins=100, color="#ffbb33",edgecolor='black') #initial color of all bins
plt.savefig("/home/miguelcant/Documentos/FCA_mcantarero/results/real-datasets/distribution-sponges.png")
    

