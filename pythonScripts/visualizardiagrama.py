#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Nov  9 19:44:10 2021

@author: miguelcant
"""
from concepts import Context
import graphviz as gv
import pylab

c2 = Context.fromfile( '/home/miguelcant/Documentos/FCA_mcantarero/datasets/sponge.csv', frmat='csv')
c3 = Context.fromfile( '/home/miguelcant/Documentos/FCA_mcantarero/datasets/breastcancer.csv', frmat='csv')

#print(c2)
dot = c2.lattice.graphviz()
dot2 = c3.lattice.gaphviz()
filename = dot.render(filename='/home/miguelcant/Documentos/FCA_mcantarero/results/sponge.dot')
filename2 = dot2.render(filename='/home/miguelcant/Documentos/FCA_mcantarero/results/breast-cancer.dot')

#pylab.savefig('/home/miguelcant/Documentos/FCA_mcantarero/sponge.png')
#pylab.savefig('/home/miguelcant/Documentos/FCA_mcantarero/breast-cancer.png')

#print("hi")
