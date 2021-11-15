/**
 * @file batchalgorithms.hpp
 * @author mcantarero
 * 
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "Lattice.hpp"
#include "utilities.hpp"

using namespace std;

#ifndef __BATCHALGORITHMS__
#define __BATCHALGORITHMS__



/** 
* @brief NextClosure algorithm of Ganter
* @param A actual extension of a concept
* @param g next object to add the actual extension
* @param c context 
* @param l the resulting lattice
*/
void NextGanter(vector<int> &A,int &g, Context &c, Lattice &l);



/** 
* @brief LIndig's function for calculate the upper neighbors of a concept
* @param obj objects of the concept 
* @param attr attributes of the concpet
* @param c context 
*/
list<formalConcept> Neighbors(vector<int> obj, vector<int> attr, Context &c);
/** 
* @brief Lindig's algorithm for compute the lattice
* @param c context 
* @param l the resulting lattice
*/
void LatticeLindig(Context &c, Lattice &l);



/** 
* @brief InClose algorithm
* @param r number of the actual concept
* @param y number of the actual attribute iterating
* @param A vector of vector of extensions
* @param B vector of vector of intensions
* @param c context
* @param l the resulting lattice
*/
void InClose(int &r, int y,vector<vector<int>> &A ,vector<vector<int>> &B, Context &c, Lattice &l);
/** 
* @brief isCannonical procces of InClose algorithm for checking if the extension generated has been computed before
* @param r number of the actual concept
* @param y number of the actual attribute iterating
* @param A vector of vector of extensions
* @param B vector of vector of intensions
* @param c context
* @return true if it has been generated before or false if it has not been generated before
*/
bool isCannonical(int r, int y, vector<vector<int>> A, vector<vector<int>> B, Context &c);



/** 
* @brief proccess for initializing the tables T and D for the Berry's algorithm
* @param S table T
* @param F table D
* @param c context
*/
void initializeTD(vector<vector<int>> &S, vector <int> &F,Context &c);
/** 
* @brief preupdate tables T and D before calling again the algorithm
* @param T table T
* @param D table D
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @param X vector of marked extension 
* @param c context
*/
void preUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A, vector<int> &B, vector<int> &X, Context &c);
/** 
* @brief postupdate tables T and D before calling again the algorithm
* @param T table T
* @param D table D
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @param X vector of marked extension 
* @param c context
*/
void postUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A,vector<int> &B, vector<int> &X, Context &c);
/** 
* @brief computes the partition into maximum rectangles of the context
* @param c context
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @return vector of vectors with the partitions of the context
*/
vector<vector<int>> maxmodPartition(Context &c,vector<int> &A, vector<int> &B);
/** 
* @brief computes the non dominanting rectangles of a partition
* @param c context
* @param part vector of vectors with the partitions of the context
* @return vector of vectors with the non dominating partitions of the context
*/
vector<vector<int>> nonDominatingMaxMod(Context &c, vector<vector<int>> part);
/** 
* @brief preupdate tables T and D before calling again the algorithm
* @param T table T
* @param D table D
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @param marked vector of marked extension 
* @param c context
* @param l resulting lattice
*/
void InheritConcepts(vector<vector<int>> T, vector<int> D, vector<int> &A, vector<int> &B, vector<int> marked, Context &c, Lattice &l);



/** 
* @brief procces of Bordat for calculating the lowers neighbors of a concept
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @param c context
*/
vector<formalConcept> LowerNeighboursBordat(vector<int> A, vector<int> B,Context &c);
/** 
* @brief function for find the succesor of a concept in the lattice
* @param E formal concept to find
* @param F succesor of the formal concept
* @param l current lattice
*/
void FindBordat(formalConcept E, formalConcept &F,Lattice &l);
/** 
* @brief preupdate tables T and D before calling again the algorithm
* @param A vector of the extension of the current concept
* @param B vector of the intension of the current concept
* @param C vector of the objects candidates for add to the current extension
* @param c context
* @param l resulting lattice
*/
void LatticeBordat(vector<int> A, vector<int> B, vector<int> C,Context &c, Lattice &l);
    

#endif
