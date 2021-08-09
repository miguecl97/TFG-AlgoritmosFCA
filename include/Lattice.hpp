/**
 * @file Lattice.h
 * @author mcantarero
 */

#include <utility>
#include <iostream>
#include <list>
#include <vector>

#include "constants.hpp"
#include "utilities.hpp"
using namespace std;

#ifndef __LATTICE__
#define __LATTICE__

//typedef pair<vector<int>, vector<int>> formalConcept; // <extension, intension>

class Lattice{
        private:
                int count;
                bool was_inserted;
                int last_position_index;

                struct Node{

                        int index;
                        formalConcept c;
                        pair<vector<int>,vector<int>> lowerUpperNeighbors;

                        Node(){};

                        Node(const formalConcept& con,int i){
                                c=con;
                                index=i;
                        }

                        bool operator==(const Node& n) const{
                                return c.first == n.c.first; 
                        }
                };

                vector<Node> concepts; 
        public:
                Lattice(){
                        count=0;
                        last_position_index=0;
                        was_inserted=false;
                }
                /**
                 * @brief Retrieves the list of concepts of the lattice.
                 * @return The list of concepts of the lattice.
                 */
                
                vector<formalConcept> getConcepts();

                /**
                 * @brief Adds a new formal concept to the lattice.
                 * @param concept The formal concept to be added.
                 */
                
                void add(formalConcept concept);

                bool find(formalConcept& concp);

                bool next(formalConcept& c, formalConcept& output);
                
                bool insertLookUp(formalConcept& x, formalConcept& c);

                void printGraphplaceInput(ofstream& out, int flag=0);

                void printTerminal();


};




#endif
