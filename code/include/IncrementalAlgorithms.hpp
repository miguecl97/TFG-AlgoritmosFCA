/**
 * @file incrementalalgorithms.hpp
 * @author mcantarero
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "Lattice.hpp"
#include "utilities.hpp"


using namespace std;

#ifndef __INCREMENTALALGORITHMS__
#define __INCREMENTALALGORITHMS__

/** 
* @brief Norris's algorithm for adding an object in the lattice.
* @param aux vector with the concept to add.
* @param added vector of addeds objects in the lattice.
* @param c context.
* @param l current and resulting lattice.
*/
void AddNorris(vector<int> aux,vector<int> &added, Context &c, Lattice &l);

/** 
* @brief Godin's algorithm for adding an object in the lattice.
* @param g concept to add.
* @param inf the min concept in the lattice.
* @param c context.
* @param l current and resulting lattice.
*/
void AddGodin(vector<int> g,formalConcept &inf, Context &c, Lattice &l);

/** 
* @brief function for getting the maximal conept of a concept in a lattice.
* @param intent intent of the concept wich its maximal concept is computed.
* @param generatorConcept formalConcept that generates the intent.
* @param l current lattice.
*/
formalConcept GetMaximalConcept(vector<int> intent, formalConcept generatorConcept, Lattice &l);

/** 
* @brief AddIntent's algorithm for adding an object in the lattice.
* @param intent vector ofthe object to add in the lattice.
* @param generatorConcept formalConcept that generates the intent.
* @param c context.
* @param l current and resulting lattice.
*/
formalConcept AddIntent(vector<int> intent, formalConcept generatorConcept, Context &c, Lattice&l);

#endif
