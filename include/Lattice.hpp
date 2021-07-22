/**
 * @file Lattice.h
 * @author mcantarero
 */

#include <utility>
#include <iostream>
#include <list>
#include <vector>

#include "constants.hpp"

using namespace std;

#ifndef __LATTICE__
#define __LATTICE__

//typedef pair<vector<int>, vector<int>> formalConcept; // <extension, intension>

//template named N
template<typename N>
//lattice class
class Lattice{
        private:
                int count;
                bool was_inserted;
                int last_position_index;
                //typedef pair<vector<int>, vector<int>> formalConcept; // <extension, intension>

                struct Node{

                        int index;
                        N c;
                        pair<vector<int>,vector<int>> upperLowerNeighbots;

                        Node(){};

                        Node(const N& con,int i){
                                c=con;
                                index=i;
                        }


                        bool operator==(const Node& n) const{
                                return c.first == n.c.first; 
                        }


                };

                list<Node> concepts; 

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
                list<N> getConcepts();

                /**
                 * @brief Adds a new formal concept to the lattice.
                 * @param concept The formal concept to be added.
                 */
                void add(N concept);

                bool find(N& concp);

                bool next(N& c, N& output);
                
                bool insertLookUp(N& x, N& c);


};

#endif
