#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  9 18:25:04 2021

@author: miguelcant
"""

import matplotlib.pyplot as plt
import numpy as np

labels = ['NextClosure', 'Lindig', 'Inherit', 'InClose', 'Bordat', 'Godin','Norris']
time_sponges = [1328 , 3865, 9590, 309, 7933, 6651, 3058]
time_artificial = [2522, 35337, 29299, 7346, 15327, 18749, 9769]

x = np.arange(len(labels))  # the label locations
width = 0.35  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width/2, time_sponges, width, label='sponges.csv')
rects2 = ax.bar(x + width/2, time_artificial, width, label='artificial-dataset')

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Tiempo(ms)')
ax.set_xlabel('Algoritmo')
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

#ax.bar_label(rects1, padding=1)
#ax.bar_label(rects2, padding=3)

fig.tight_layout()

#plt.show()
plt.savefig("/home/miguelcant/Documentos/FCA_mcantarero/results/real-datasets/comparative-sponges.png")