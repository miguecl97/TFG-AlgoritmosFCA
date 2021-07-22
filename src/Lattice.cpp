/**
 * @file Lattice.cpp
 * @author mcantarero
 */

#include "Lattice.hpp"



//Lattice's mathods.
//
/*
template<typename N>
Lattice<N>::Lattice(){
    count=0;
    last_position_index=0;
    was_inserted=false;
}*/

template<typename N>
list<N> Lattice<N>::getConcepts(){return concepts;}

template<typename N>
void Lattice<N>::add(N concept){
    concepts.push_back(Node(concept,count++));
    was_inserted=true;
}

template<typename N>
bool Lattice<N>::find(N& concp){
    typename std::list<Node>::iterator it;
    for(it= concepts.begin(); it!=concepts.end(); it++){
        if(it->c.first == concp.first && it->c.second == concp.second)
            return true;
    }

    return false;
}

template<typename N>
bool Lattice<N>::next(N& c, N& output){

    typename list<Node>::iterator it = find(concepts.begin(), concepts.end(), Node(c,0));

    if(it == concepts.end() || ++it == concepts.end())
        return false;
    
    output = it->c;
    last_position_index = it - concepts.begin();
    return true;

}

template <typename N>
bool Lattice<N>::insertLookUp(N& x, N& c){

    typename list<Node>::iterator x_pos = find(concepts.begin(),concepts.end(), Node(x,count));
    if(x_pos == concepts.end()){
        concepts.push_back(Node(x,count++));
        x_pos = concepts.end() -1;
    }

    typename list<Node>::iterator c_pos;
    if(was_inserted && ! (concepts[last_position_index].c.first == c.first)){
        c_pos = find(concepts.begin(),concepts.end(),Node(c,count));
        if(c_pos == concepts.end()){
            return false;
        }
    }

    c_pos = concepts.begin() + last_position_index;

    x_pos->lowerUpperNeighbors.first.push_back(c_pos->index);
    c_pos->lowerUpperNeighbors.second.push_back(x_pos->index);

    return true;

}


