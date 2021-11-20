/**
 * @file Lattice.h
 * @author mcantarero
 */

#include <utility>
#include <iostream>
#include <list>
#include <vector>

#include "utilities.hpp"
using namespace std;

#ifndef __LATTICE__
#define __LATTICE__

struct Node{
        int index; /** index of the node in the lattice. */
        formalConcept c; /** formalConcept of the node. */
        vector<int> ch; /**childs of the concept. */
        pair<vector<int>,vector<int>> lowerUpperNeighbors;/** upper and lower negihtbors of the concept. */ 

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
                int count; /** counter of the total number of concepts. */
                bool was_inserted; /** indicator of a previous insertion of a concept. */
                int last_position_index; /* last concept inserted. */
                vector<Node> concepts; /** vector with all the concepts of the laticce. */
                
        public:
                /**
                 * @brief Default constructor.
                 * @return the new Lattice.
                 */
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

                /**
                 * @brief getter of the size of the lattice.
                 * @return the number of nodes of the lattice.
                 */
                int getSize();

                /**
                 * @brief getter of the concepts of the lattice.
                 * @return a vector with all the formalConcepts of the lattice.
                 */
                vector<formalConcept> getformalConcepts();
                
                /**
                 * @brief getter of a node by an index.
                 * @param i index of the concept in the lattice.
                 * @return the Node.
                 */
                Node getConcept(int i);

                /**
                 * @brief Adds a new formal concept to the lattice.
                 * @param concept The formal concept to be added.
                 */
                void add(formalConcept concept);

                /**
                 * @brief replace an old  formal concept by a new in the lattice.
                 * @param f The formal concept to be replaced.
                 * @param newf new formalConcept to add.
                 */
                void replace(formalConcept f,formalConcept newf);

                /**
                 * @brief get the index of a formalConcept in the lattice.
                 * @param concept The formal concept to retrieve.
                 * @return index of the formalCOncept.
                 */
                int getIndex(formalConcept concp);

                /**
                 * @brief finds if a concept is in the lattice or not.
                 * @param concept The formal concept to find.
                 * @return true if it is , false if its not.
                 */
                bool find(formalConcept concp);

                /**
                 * @brief retrieve the parents of a concept in the lattice.
                 * @param c to find the parents.
                 * @return vector of all its parents.
                 */
                vector<formalConcept> getParents(formalConcept c);

                /**
                 * @brief retrieve the concepts above of a concept in the lattice.
                 * @param c to find the parents.
                 * @return vector of all its concepts above.
                 */
                vector<formalConcept> getConceptsAbove(formalConcept c);
                
                /**
                 * @brief retrieve the concept next to another concept.
                 * @param c to find the next.
                 * @param output concept next to c.
                 */
                bool next(formalConcept& c, formalConcept& output);
                
                /**
                 * @brief inserts a concept in the lattice by the lookup method.
                 * @param c concept to find for insert the other.
                 * @return true if insertion was fine, false if x was not in the lattice.
                 */
                bool insertLookUp(formalConcept& x, formalConcept& c);

                /**
                 * @brief output of a graph of the lattice by the terminal.
                 * @param out ofstream output.
                 * @param flag option of output.
                 */
                void printGraphplaceInput(ofstream& out, int flag=0);

                /**
                 * @brief prints the nodes of a lattice in the terminal.
                 */
                void printTerminalNodes();

                /**
                 * @brief prints the concepts of a lattice in the terminal.
                 * @param obj vector with the names of the objects.
                 * @param attr vector with the names of the attributes.
                 */          
                void printTerminalConcepts(vector<string> obj, vector<string> attr);

                /**
                 * @brief prints the nodes of a lattice in a file.
                 * @param out ofstream output.
                 */
                void printIntoFile(ofstream& out);

};




#endif
