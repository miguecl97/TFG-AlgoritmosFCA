/**
* @file incrementalalgorithms.cpp
* @author mcantarero
*/

#include "IncrementalAlgorithms.hpp"
//#include "Lattice.cpp"

#include <iostream>
#include <vector>
#include <numeric> // std::iota
#include <cmath>



void AddNorris(int g, Context &c, Lattice &l){
    vector<int> aux = {g};
    vector<int> gPrime;

    c.objectPrime(aux,gPrime); // compute {g}'

    for(formalConcept f : l.getformalConcepts()){ // for each (A,B) in L

        if(IsSubset(gPrime,f.second)){
            insert_sorted(f.first,g); // A u g, inserts g in A if was not contained
        }else{
            vector<int> D;
            std::set_intersection(f.second.begin(),f.second.end(),gPrime.begin(),gPrime.end(),inserter(D,D.begin())); // D = B \cap {g}'
            vector<int> hvec = c.getObjectsVector() - f.first; // h = G - A
            bool empty = true; // we supose the set of elements is empty

            for(int h : hvec){
                vector<int> hprime;
                vector<int> haux ={h};
                c.objectPrime(haux,hprime);
                formalConcept f2 = make_pair(haux,hprime);

                if(l.find(f2) && IsSubset(hprime,D)){// there is an element that checks the conditions, {h} was in L && D \subseteq {h}'
                    empty = false;// set is not empty
                }

            }

            if(empty){
                l.add(make_pair(f.first+aux,D)); // add (A U g,D) to L
            }

        }
    }

    bool empty2 = true;

    for(int h : c.getObjectsVector()){
        vector<int> h2 = {h};
        vector<int> hprime2;
        c.objectPrime(h2,hprime2);

        if(l.find(make_pair(h2,hprime2)) && IsSubset(hprime2,gPrime)){//if there is an h that was inserted and {g}' \subseteq {h}'
            empty2=false;//set is not empty
        }

    }

    if(empty2){
        l.add(make_pair(aux,gPrime));// add ({g},{g}')
    }

}