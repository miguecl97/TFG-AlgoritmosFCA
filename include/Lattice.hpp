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

struct Node{

        int index;
        formalConcept c;
        //vector<int> ch;
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

class Lattice{
        private:
                int count;
                bool was_inserted;
                int last_position_index;

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
                vector<Node> getConcepts();

                int getSize();

                vector<formalConcept> getformalConcepts();
                
                Node getConcept(int i);
                /**
                 * @brief Adds a new formal concept to the lattice.
                 * @param concept The formal concept to be added.
                 */
                
                void add(formalConcept concept);

                void replace(formalConcept f,formalConcept newf);

                int getIndex(formalConcept concp);

                bool find(formalConcept concp);
                vector<formalConcept> getParents(formalConcept c);
                vector<formalConcept> getConceptsAbove(formalConcept c);
                
                bool next(formalConcept& c, formalConcept& output);
                
                bool insertLookUp(formalConcept& x, formalConcept& c);

                void printGraphplaceInput(ofstream& out, int flag=0);

                void printTerminalNodes();
                
                void printTerminalConcepts(vector<string> obj, vector<string> attr);

                void printIntoFile(ofstream& out);

};




#endif
