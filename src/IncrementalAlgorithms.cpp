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



void AddNorris(vector<int> g,vector<int> &added, Context &c, Lattice &l){
    vector<int> gPrime;
    c.objectPrime(g,gPrime); // compute {g}'

    
    for(formalConcept f : l.getformalConcepts()){ // for each (A,B) in L
        if(IsSubset(gPrime,f.second)){
            l.replace(f,make_pair(f.first+g,f.second)); //hacemos efecto de los cambios en el retículo
            f.first = f.first + g; //A = A U {g}
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

                if(find(added.begin(), added.end(), h) != added.end() && IsSubset(hprime,D)){// there is an element that checks the conditions, {h} was added && D \subseteq {h}'
                    empty = false;// set is not empty
                }

            }
            if(empty){
                l.add(make_pair(f.first+g,D)); // add (A U g,D) to L
            }
        }
    }
    bool empty2 = true;
    for(int h : c.getObjectsVector()){ //h \in G
        vector<int> h2 = {h};
        vector<int> hprime2;
        c.objectPrime(h2,hprime2);

        if(find(added.begin(), added.end(), h) != added.end()  && IsSubset(hprime2,gPrime)){//if there is an h that was added and {g}' \subseteq {h}'
            empty2=false;//set is not empty
        }
    }
    if(empty2){
        l.add(make_pair(g,gPrime));// add ({g},{g}')
    }
    added.push_back(g.front()); // g has been added
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
                inf.second = inf.second+gPrime;
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
        vector<vector<formalConcept>> C(j+1);
        vector<vector<formalConcept>> CPrime(j+1);
        
        for(int i =0; i<= j; i++){

            for(formalConcept f : l.getformalConcepts()){
                if((int)f.second.size()==i){
                    C[i].push_back(f);// stova a dar core mirarlo bien
                }
                CPrime[i].clear();
            }
           
        }
        
        for(int i =0; i<= j; i++){

            for(formalConcept f : C[i]){
                if(IsSubset(gPrime,f.second)){
                    l.replace(f,make_pair(f.first+g,f.second)); //NOTE: por si falla
                    //f.first = f.first +g;
                    CPrime[i].push_back(make_pair(f.first + g,f.second)); //REVISAR

                    if(f.second==gPrime){
                        return;
                    }
                }else{
                    vector<int> intent;
                    std::set_intersection(f.second.begin(),f.second.end(),gPrime.begin(),gPrime.end(),inserter(intent,intent.begin())); // int = B \cap {g}'
                    
                    bool exists = false;

                    for(formalConcept fCPrime : CPrime[intent.size()]){
                        if(fCPrime.second==intent){
                            exists=true;
                            break;
                        }
                    }
                    if(!exists){
                        l.add(make_pair(f.first+g,intent));
                        CPrime[intent.size()].push_back(make_pair(f.first+g,intent));

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




formalConcept GetMaximalConcept(vector<int> intent, formalConcept generatorConcept, Lattice &l){
    bool parentIsMaximal=true;
    while (parentIsMaximal){
        parentIsMaximal=false;
        vector<formalConcept> parents=l.getConceptsAbove(generatorConcept);
        
        for(formalConcept parent : parents){
            if(IsSubset(parent.second,intent)){
                generatorConcept=parent;
                parentIsMaximal=true;
                break;
            }
        }
        
    }

    return generatorConcept;
}

formalConcept AddIntent(vector<int> intent, formalConcept generatorConcept, Context &c, Lattice&l){
    cout << "Llamada a addintent con"<<endl;
    cout << "Intent="<<intent<<endl;
    cout << "GeneratorConcept="<<generatorConcept<<endl;
    cout<<endl;
    
    generatorConcept = GetMaximalConcept(intent,generatorConcept,l);

    if(generatorConcept.second==intent){
        return generatorConcept;
    }
   
    vector<formalConcept> generatorParents = l.getConceptsAbove(generatorConcept);
    vector<formalConcept> newParents;
    vector<int> empty ={};
    newParents.push_back(make_pair(empty,empty));
/*
     cout << "Padres de "<<generatorConcept<<endl;
     for(formalConcept f : generatorParents){
         cout <<"->"<< f<< " + ";
     }
     cout << endl<<endl;*/

    for(formalConcept f : generatorParents){
        if(!IsSubset(intent,f.second)){
            vector<int> intersection;

            std::set_intersection(f.second.begin(),f.second.end(),intent.begin(),intent.end(),inserter(intersection,intersection.begin()));
            f=AddIntent(intersection,f,c,l);
            //l.replace(f,fnew);
            //f=fnew;
        }

        bool addParent=true;

        for(unsigned i=0; i<newParents.size();i++){
            if(IsSubset(newParents[i].second,f.second)){
                addParent=false;
                break;
            }else if(IsSubset(f.second,newParents[i].second)){
                //newParents.erase(f.second);
                newParents.erase(newParents.begin()+i);
                /*for(formalConcept f2: newParents){
                    cout<< f2;
                }
                cout << "deleting "<< newParents[i]<< "!!!!!!!";
                
                for(formalConcept f2: newParents){
                    cout<< f2;
                }
                cout <<endl;*/
            }
        }

        if(addParent){
            newParents.push_back(f);
        }
    }

    formalConcept newConcept = make_pair(generatorConcept.first,intent);
    l.add(newConcept);
    /*for(formalConcept p : newParents){

    }*/

    return newConcept;
}