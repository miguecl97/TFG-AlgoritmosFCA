/**
 * @file algorithms.hpp
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

#ifndef __ALGORITHMS__
#define __ALGORITHMS__


 // <extension, intension>

void NextConcept(vector<vector<int>> &A,vector<vector<int>> &B,vector<int> &inum,int &r,Context &c, Lattice<formalConcept> &l);

list<formalConcept> Neighbors(vector<int> obj, vector<int> attr, Context &c);
void LatticeLindig(Context &c, Lattice<formalConcept> &l);


void InClose(int &r, int y,vector<vector<int>> &A ,vector<vector<int>> &B, Context &c, Lattice<formalConcept> &l);
bool isCannonical(int r, int y, vector<vector<int>> &A, vector<vector<int>> &B, Context &c);



void initializeTD(vector<vector<int>> &S, vector <int> &F,Context &c);
void preUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A, vector<int> &X);
void postUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A,vector<int> &B, vector<int> &X, Context &c);
vector<vector<int>> maxmodPartition(Context &c);
vector <int> nonDominatingMaxMod(Context &c, vector<vector<int>> part);
void InheritConcepts(vector<vector<int>> &T, vector<int> &D, vector<int> &A, vector<int> &B, vector<int> &marked, Context &c, Lattice<formalConcept> &l);
#endif
