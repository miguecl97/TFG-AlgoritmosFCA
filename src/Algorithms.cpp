/**
* @file algorithms.cpp
* @author mcantarero
*/

#include"Algorithms.hpp"

#include <iostream>
#include <vector>
#include <numeric> // std::iota

void NextConcept(vector<vector<int>> &A,vector<vector<int>> &B,vector<int> &inum,int &r,Context &c, Lattice<formalConcept> &l){

    vector<int> m (c.getNAttributes());
    std::iota(m.begin(), m.end(), 0);

    bool found = false;

    
    for(int i = (int) c.getNAttributes() - 1; i >= 0; --i){

        found = false;

        if(count(B[r].begin(), B[r].end(),m[i])){
            found = true;
        }
        
        if(!found){
  
            //cout << "i = "<< i << endl;
            //cout << "inum [r] ="<< inum[r]<< endl;

            while(i < inum[r]){
                r = r-1;
            }
          
            if((int)inum.size() <= r+1){
                inum.resize(inum.size() + 1);
            }

            inum[r+1]=i;
            vector<int> auxprime;
            vector<int> mi = { m[i] };
            c.attributePrime(mi,auxprime );

            if((int)A.size() <= r+1){
                A.resize(A.size() + 1);
            }

            A[r+1].clear();
            
            set_intersection(A[r].begin(),A[r].end(),auxprime.begin(),auxprime.end(),inserter(A[r+1],A[r+1].begin()));
            
            for(int j = 0; j<i ; j++){
                if(!found){
                    vector<int> auxprime;
                    vector<int> mj = { m[j]};
                    c.attributePrime(mj,auxprime );

                    if(IsSubset(auxprime,A[r+1])){
                        found = true;
                    }
                }
            }
            
            if(!found){
                if((int)B.size() <= r+1){
                    B.resize(B.size() + 1);
                }    

                B[r+1].clear();
                std::set_union( B[r].begin(), B[r].end(),mi.begin(), mi.end(),back_inserter(B[r+1]) );

                for(int j = i+1;j<(int)c.getNAttributes();j++){
                    if(count(B[r+1].begin(), B[r+1].end(),j) == 0){
                        vector<int> auxprime;
                        vector<int> mj = { m[j] };
                        c.attributePrime(mj,auxprime );

                        if(IsSubset(auxprime,A[r+1])){
                            vector< int> copy (B[r+1].begin(), B[r+1].end());
                            B[r+1].clear();
                            std::set_union(copy.begin(), copy.end(),mj.begin(), mj.end(), back_inserter(B[r+1]) );
                        }
                    }
                }                
                r = r+1;          
                return ;
            }           
        }

    }
    if(B[r]==m){
        cout<< "fin del algoritmo";
    }
    
}



list<formalConcept> Neighbors(vector<int> obj, vector<int> attr, Context &c){


    vector<int> A (c.getNObjects());
    std::iota(A.begin(), A.end(), 0);

    list<formalConcept> neigh;
    vector<int> min;
    set_difference(A.begin(),A.end(), obj.begin(), obj.end(),std::inserter(min, min.end()));

    vector <int> minus(min);
    
    
    for( int x : minus){

        //cout << x;

        vector <int> m1;
        vector <int> aux = {x};

        vector <int> both;
        std::set_union(obj.begin(), obj.end(), aux.begin(), aux.end() ,back_inserter(both) );
        c.objectPrime(both, m1);


        vector <int> g1;
        c.attributePrime(m1,g1);

        vector<int> intersection;
        vector<int> difference;
        vector<int> difference2;

        //cout << "obj = "<< obj<< endl;
        //cout << "aux = "<< aux<< endl;

        set_difference(g1.begin(),g1.end(), obj.begin(), obj.end(),
        std::inserter(difference, difference.end()));
        //cout << "difference = "<< difference<< endl;

        //cout << "g1 = "<< g1<< endl;

        set_difference(difference.begin(),difference.end(), aux.begin(), aux.end(),
        std::inserter(difference2, difference2.end()));
        //cout << "difference2 = "<< difference2<< endl;

        //cout<< "min" << min<<endl;
        std::set_intersection(min.begin(),min.end(),difference2.begin(),difference2.end(),inserter(intersection,intersection.begin()));
        //cout << "intersection = "<< intersection<< endl;

       //cout << intersection;

       if(intersection.empty()){
            neigh.push_back(make_pair(g1,m1));

            cout << "añadiendo vecino"<< endl;
            cout << "("<< g1<< " , "<<m1<<")"<<endl;

       }else{
            vector <int> aux2;
            set_difference(min.begin(),min.end(), aux.begin(), aux.end(),std::inserter(aux2, aux2.end()));
            min = aux2;
            cout << "la interseccion no es vacía"<< intersection<<endl;
            cout << min<<endl;
       }
    
    }

    return neigh;

}


void LatticeLindig(Context &c, Lattice<formalConcept> &l){

    formalConcept f;
    vector <int> emptyobj;
    vector <int> emptyattr;

    cout << f.first;
    cout << f.second;
    c.objectDoublePrime(emptyobj,f.first);
    c.objectPrime(emptyattr,f.second);

    list <formalConcept> neigb = Neighbors(f.first,f.second,c);

    //list<formalConcept> lista = l.getConcepts();

    for(formalConcept x : neigb){
        //bool result = l.insertLookUp(x,f);
    }
    



}


