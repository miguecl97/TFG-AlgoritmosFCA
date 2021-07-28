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

//template named N
template<typename N>
class Lattice{
        private:
                int count;
                bool was_inserted;
                int last_position_index;

                struct Node{

                        int index;
                        N c;
                        pair<vector<int>,vector<int>> lowerUpperNeighbors;

                        Node(){};

                        Node(const N& con,int i){
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
                
                vector<N> getConcepts();

                /**
                 * @brief Adds a new formal concept to the lattice.
                 * @param concept The formal concept to be added.
                 */
                
                void add(N concept);

                bool find(N& concp);

                bool next(N& c, N& output);
                
                bool insertLookUp(N& x, N& c);

                void printGraphplaceInput(ofstream& out, int flag=0);

                void printTerminal();

};



template<typename N>
vector<N> Lattice<N>::getConcepts(){return concepts;}

template<typename N>
void Lattice<N>::add(N concept){
    concepts.push_back(Node(concept,count++));
    was_inserted=true;
}

template<typename N>
bool Lattice<N>::find(N& concp){
    typename std::vector<Node>::iterator it;
    for(it= concepts.begin(); it!=concepts.end(); it++){
        if(it->c.first == concp.first && it->c.second == concp.second)
            return true;
    }

    return false;
}

template<typename N>
bool Lattice<N>::next(N& c, N& output){

    typename vector<Node>::iterator it = std::find(concepts.begin(), concepts.end(), Node(c,0));

    if(it == concepts.end() || ++it == concepts.end())
        return false;
    
    output = it->c;
    last_position_index = it - concepts.begin();
    return true;

}

template<typename N>
bool Lattice<N>::insertLookUp(N& x, N& c){

    typename vector<Node>::iterator x_pos = std::find(concepts.begin(),concepts.end(), Node(x,count));
    if(x_pos == concepts.end()){
        concepts.push_back(Node(x,count++));
        x_pos = concepts.end() - 1;
    }

    typename vector<Node>::iterator c_pos;
    if(was_inserted && ! (concepts[last_position_index].c.first == c.first)){
        c_pos = std::find(concepts.begin(),concepts.end(),Node(c,count));
        if(c_pos == concepts.end()){
            return false;
        }
    }

    c_pos = concepts.begin() + last_position_index;

    x_pos->lowerUpperNeighbors.first.push_back(c_pos->index);
    c_pos->lowerUpperNeighbors.second.push_back(x_pos->index);

    return true;

}

template<typename N>
void Lattice<N>::printGraphplaceInput(ofstream& out, int flag){
        ofstream tempout("explain.graph");

        for(typename vector<Node>::iterator i = concepts.begin(); i!= concepts.end(); i++){
                tempout << "Node "<< i->index << ": " << i->c << endl;
                out << "( ";

                if(flag ==0){
                        out << i->c;
                }else if(flag ==1){
                        out<< i->index;
                }

                out << ") "<< i->index<< " node "<<endl;

                for(typename vector<int>::iterator j = i->lowerUpperNeighbors.second.begin();
                    j< i->lowerUpperNeighbors.second.end();j++){
                            out<< *j << " "<< i->index << " edge" << endl;
                    }
        }
}

template<typename N>
void Lattice<N>::printTerminal(){
        cout << endl;
        cout << "List of concepts: "<< endl;
        for(typename vector<Node>::iterator i = concepts.begin(); i!= concepts.end(); i++){
                cout << "Concept: "<< i->index+1 << ": " << endl;
                cout << "( ";

                
                cout << i->c;


                cout << ") "<<endl;
        }

}       

#endif
