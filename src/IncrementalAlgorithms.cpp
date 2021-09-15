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



void AddNorris(vector<int> aux,vector<int> &added, Context &c, Lattice &l){
    //vector<int> aux = {g};
    vector<int> gPrime;
    
    c.objectPrime(aux,gPrime); // compute {g}'

    for(formalConcept f : l.getformalConcepts()){ // for each (A,B) in L

        
        if(IsSubset(gPrime,f.second)){
            l.replace(f,make_pair(f.first+aux,f.second));
            //insert_sorted(f.first,g); // A u g, inserts g in A if was not contained
            f.first = f.first +aux;
            //l.replace(f,make_pair(f.first+aux,f.second));
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

                /*if(l.find(f2) && IsSubset(hprime,D)){// there is an element that checks the conditions, {h} was in L && D \subseteq {h}'
                    empty = false;// set is not empty
                }*/

                if(find(added.begin(), added.end(), h) != added.end() && IsSubset(hprime,D)){// there is an element that checks the conditions, {h} was added && D \subseteq {h}'
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
        //l.find(make_pair(h2,hprime2))
        if(find(added.begin(), added.end(), h) != added.end()  && IsSubset(hprime2,gPrime)){//if there is an h that was inserted and {g}' \subseteq {h}'
            empty2=false;//set is not empty
        }

    }

    if(empty2){
        l.add(make_pair(aux,gPrime));// add ({g},{g}')
    }

    added.push_back(aux.front());


}




void AddGodin(vector<int> g,formalConcept &inf, Context &c, Lattice &l){

    vector<int> gPrime;
    vector<int> emptyset={};
    c.objectPrime(g,gPrime);

    if(inf.first.empty() && inf.second.empty()){
        //l.replace(inf,make_pair(g,gPrime));
        inf.first=g;
        inf.second=gPrime;
        l.add(inf);
    }else{
        if(!IsSubset(inf.second,gPrime)){
            if(inf.first.empty()){
                inf.second= inf.second+gPrime;
            }else{
                
                l.add(make_pair(emptyset,inf.second+gPrime));
                //(empty,inf U{g'}) es un vecino superior de inf
                inf.first =emptyset;
                inf.second=inf.second + gPrime;
            }
        }

        int j =0;

        for(formalConcept f : l.getformalConcepts()){
            if((int)f.second.size()>j){
                j=f.second.size();
            }
        }
        vector<formalConcept> C(j+1);
        vector<formalConcept> CPrime(j+1);
        
        for(int i =0; i<= j; i++){

            for(formalConcept f : l.getformalConcepts()){
                if((int)f.second.size()==i){
                    C[i]=f;// stova a dar core mirarlo bien
                }
                CPrime[i]=make_pair(emptyset,emptyset);
            }
           
        }
        
        for(int i =0; i<= j; i++){

            for(formalConcept f : C){
                if(IsSubset(gPrime,f.second)){
                    f.first = f.first +g;
                    CPrime[i].first=CPrime[i].first+f.first;
                    CPrime[i].second=CPrime[i].second+f.second;

                    if(f.second==gPrime){
                        return;
                    }
                }else{
                    vector<int> intent;
                    std::set_intersection(f.second.begin(),f.second.end(),gPrime.begin(),gPrime.end(),inserter(intent,intent.begin())); // int = B \cap {g}'
                    //bool exists = false;

                    if(CPrime.size() < intent.size() || CPrime[intent.size()].second!=intent){
                        l.add(make_pair(f.first+g,intent));
                        CPrime[intent.size()].first=CPrime[intent.size()].first + f.first +g;
                        CPrime[intent.size()].second= CPrime[intent.size()].second + intent;

                        //upper neig update;
                        //update edges;

                        if(intent == gPrime){
                            return;
                        }
                    
                    }

                }
            }
           
        }

        
    }


}