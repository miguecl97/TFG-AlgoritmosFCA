/**
 * @file incrementalalgorithms.hpp
 * @author mcantarero
 */
#include <vector>
#include <fstream>
#include <iostream>

#include <boost/algorithm/string.hpp>

//#include "Context.hpp"
#include "Lattice.hpp"
#include "utilities.hpp"


using namespace std;

#ifndef __INCREMENTALALGORITHMS__
#define __INCREMENTALALGORITHMS__


 // <extension, intension>


void AddNorris(vector<int> aux,vector<int> &added, Context &c, Lattice &l);

void AddGodin(vector<int> g,formalConcept &inf, Context &c, Lattice &l);

#endif
