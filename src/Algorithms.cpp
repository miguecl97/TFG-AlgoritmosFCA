/**
* @file algorithms.cpp
* @author mcantarero
*/

#include"Algorithms.hpp"
//#include "Lattice.cpp"

#include <iostream>
#include <vector>
#include <numeric> // std::iota
#include <cmath>

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

            //cout << "añadiendo vecino"<< endl;
            //cout << "("<< g1<< " , "<<m1<<")"<<endl;

       }else{
            vector <int> aux2;
            set_difference(min.begin(),min.end(), aux.begin(), aux.end(),std::inserter(aux2, aux2.end()));
            min = aux2;
            //cout << "la interseccion no es vacía"<< intersection<<endl;
            //cout << min<<endl;
       }
    
    }

    return neigh;

}


void LatticeLindig(Context &c, Lattice<formalConcept> &l){

    formalConcept f;
    vector <int> emptyobj;
    vector <int> emptyattr;

    c.objectDoublePrime(emptyobj,f.first);
    c.objectPrime(emptyattr,f.second);

    l.add(f);
    
    list <formalConcept> neigh;

    //list<formalConcept> lista = l.getConcepts();

    do{
        neigh = Neighbors(f.first,f.second,c);
        for(formalConcept x : neigh){
            l.insertLookUp(x,f);
        }
    }while(l.next(f,f));

}

void InClose(int &r, int y, vector<vector<int>> &A ,vector<vector<int>> &B, Context &c, Lattice<formalConcept> &l){
    int rnew = r+1;


    if((int)A.size() <= rnew+1){
        A.resize(rnew+1);
    }

    for(int j = y; j<(int)c.getNAttributes();j++){
        //int k = j+1;
        A[rnew].clear();
        for(int i : A[r]){
            if(c.getIncidence(i,j)){
                insert_sorted(A[rnew],i);
            }
        }

        if(A[rnew].size()>0){
            if(A[rnew].size()==A[r].size()){
                insert_sorted(B[r],j);
            }else{
                
                if(isCannonical(r,j-1,A,B,c)){
                    vector<int> aux = {j};
                    if((int)B.size() <= rnew+1){
                        B.resize(rnew + 1);
                    }

                    std::set_union(B[r].begin(), B[r].end(), aux.begin(), aux.end() , back_inserter(B[rnew]) );
                    sort(B[rnew].begin(), B[rnew].end() );
                    B[rnew].erase( unique( B[rnew].begin(), B[rnew].end() ), B[rnew].end() );

                    InClose(rnew,j+1,A,B,c,l);
                }
            }
        }
    }
    
    cout<< "Llamada r = "<< r<< endl;
    for(int i=0; i< (int) A.size() ; i++){
        cout << " A[ "<< i << "]"<< A[i];
    }
    cout << endl;
    for(int i=0; i< (int) B.size() ; i++){
        cout << " B[ "<< i << "]"<< B[i];
    }
    cout << endl;
    cout << endl;
}

bool isCannonical(int r, int y, vector<vector<int>> &A, vector<vector<int>> &B,Context &c){
    int h=0;
    int rnew=r+1;
    for(int k = B[r].size()-1; k>=0;--k ){
        for(int j = y; j>= B[r][k]+1; j--){
            for(h = 0; h<= (int)A[rnew].size()-1; h++){
                if(!c.getIncidence(A[rnew][k],j)){
                    break;
                }
            }
            if(h==(int)A[rnew].size()){
                return false;
            }
        }
        y = B[r][k]-1;
    }
    for(int j = y ; j>=0; j--){
        for(h=0; h <= (int) A[rnew].size()-1 ; h++){
            if(!c.getIncidence(A[rnew][h],j)){
                break;
            }
        }
        if(h==(int)A[rnew].size())
            return false;
    }
    return true;    
}
    
void initializeTD(vector<vector<int>> &S, vector <int> &F, Context &c){
    std::vector<std::vector<int> > T(c.getNAttributes(), std::vector<int>(c.getNAttributes()));

    vector<int> D(c.getNAttributes());
    vector<int> P(c.getNAttributes());
    std::iota(P.begin(), P.end(), 0);
    vector<int> O(c.getNObjects());

    std::iota(O.begin(), O.end(), 0);

    for(int x : P ){
        D[x] = c.getNAttributes();
        for(int y : P){
            for(int z : O){
                if(c.getIncidence(z,x) && !c.getIncidence(z,y)){
                    if(T[y][x] == 0){
                       D[x] = D[x]-1;
                    }
                    T[y][x] = T[y][x]+1;
                }
            }
        }
    }

    S=T;
    F=D;
}


void preUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A,vector<int> &B, vector<int> &X, Context &c){
    
    int x = X[0];
    vector<int> P(T.size());
    std::iota(P.begin(), P.end(), 0);

    vector<int> minus = (P-A)-X;

    for(int y : minus){
        if(T[x][y]==0){
            if(D[y]!=-1){
                //D[y] = max(D[y] - (int)X.size(),0);
                D[y]=D[y]-X.size();

            }
        }
    }

    vector<int> Rx;
    vector<int> aux ={x};
    c.attributePrime(aux,Rx);
    vector<int> minus2 = B - Rx;

    for(int j : minus2){
        vector<int> Rj;
        vector<int> aux2 ={j};
        c.objectPrime(aux2,Rj);

        vector<int> Z = ((P-A)-Rj)-X;
        vector<int> U = ((P-A)-Z)-X;

        for(int u : U){
            for(int z : Z){
                if(T[z][u]!=-1){
                    //T[z][u]=max(T[z][u]-1,0);
                    T[z][u]=T[z][u]-1;
                    if(T[z][u]==0){
                        D[u] = D[u]+1;
                    }
                }
            }
        }
     
    }

    /*
    for(int i = X.size()-1; i>=0; i--){
         
         for(int j = 0; j < (int)T.size(); j++){     
            T[j].erase(T[j].begin()+X[i]);
         }
         
         T.erase(T.begin()+X[i]);
         D.erase(D.begin()+X[i]);
    }
    */
    for(int i = X.size()-1; i>=0; i--){
         
         for(int j = 0; j < (int)T.size(); j++){     
            T[j][X[i]] = -1;
            T[X[i]][j] = -1;

         }
         
         D[X[i]]= -1;
    }


}

void postUpdate(vector<vector<int>> &T, vector <int> &D, vector<int> &A,vector<int> &B, vector<int> &X, Context &c){

    int x = X[0];
    vector<int> P(T.size());
    std::iota(P.begin(), P.end(), 0);

    vector<int> minus = (P-A)-X;

    for(int y : minus){
        if(T[x][y]==0){
            if(D[y]!=-1){
            //D[y] = max(D[y] + (int)X.size(),0);
            D[y]=D[y]+X.size();}
        }
    }

    vector<int> Rx;
    vector<int> aux ={x};
    c.attributePrime(aux,Rx);
    vector<int> minus2 = B - Rx;

    for(int j : minus2){
        vector<int> Rj;
        vector<int> aux2 ={j};
        c.objectPrime(aux2,Rj);

        vector<int> Z = ((P-A)-Rj)-X;
        vector<int> U = ((P-A)-Z)-X;

        for(int u : U){
            for(int z : Z){
                if(T[z][u]!=-1){
                    T[z][u]=T[z][u]+1;
                    if(T[z][u]==1){
                        D[u]=D[u]-1;
                        //D[u] = max(D[u]-1,0);
                    }
                }
            }
        }
     
    }
    /*
    for(int i = X.size()-1; i>=0; i--){
         
         for(int j = 0; j < (int)T.size(); j++){     
            T[j].erase(T[j].begin()+X[i]);
         }
         
         T.erase(T.begin()+X[i]);
         D.erase(D.begin()+X[i]);
    }
    */
    for(int i = X.size()-1; i>=0; i--){
         
         for(int j = 0; j < (int)T.size(); j++){     
            T[j][X[i]] = -1;
            T[X[i]][j] = -1;

         }
         
         D[X[i]]= -1;
    }
      
}

vector<vector<int>> maxmodPartition(Context &c,vector<int> &A,vector<int> &B){

    vector<int> P(c.getNAttributes());
    std::iota(P.begin(), P.end(), 0);
    vector<int> O(c.getNObjects());
    std::iota(O.begin(), O.end(), 0);
    vector<vector<int>> part;

    part.push_back(P-A);
    for(int y : B){
        //cout<< "iteration "<< y<< endl;
        vector<int> Ry;
        vector<int> aux ={y};
        c.objectPrime(aux,Ry);
        //cout << "RY="<< Ry<< endl;
        vector<vector<int>> partcopy = part;
        for(vector<int> k : partcopy){
            //cout << "k ="<<  k << endl;
            if(k.size()>1){
                vector<int> kprime;
                std::set_intersection(k.begin(),k.end(),Ry.begin(),Ry.end(),inserter(kprime,kprime.begin()));
                vector<int> kdoubleprime = k - Ry;
                //cout << "k' ="<< kprime<< endl;
                //cout << "k'' ="<< kdoubleprime<< endl;
                if(!kdoubleprime.empty() && !kprime.empty()){

                    for(int n=0; n<(int)part.size(); n++){
                        if(part[n]==k){
                            part[n]=kprime;
                            part.insert(part.begin()+n+1,kdoubleprime);
                        }
                    }/*
                    cout << "part = ";
                    for(vector<int> a : part){
                        cout << a<< " | ";
                    }
                    cout << endl;*/
                }
            }
        }
        //cout << "-------------------"<< endl<< endl;
    }

    return part;
}

vector<vector<int>> nonDominatingMaxMod(Context &c, vector<vector<int>> part){

    vector<vector<int>> ND;
    vector<vector<int>> relations;
    vector<int> m (c.getNAttributes());
    std::iota(m.begin(), m.end(), 0);

    for(int a : m){
        vector<int> aux ={a};
        vector<int> atprime ;

        c.attributePrime(aux,atprime);

        relations.push_back(atprime);
    }

    do{
        vector<int> X = part[0];
        part.erase(part.begin());


        ND.push_back(X);

        if(!part.empty()){
        vector<int> xprime;
        c.attributePrime(X,xprime);

        for(auto i = 0; i<(int)relations.size(); i++){
            if(relations.at(i) != xprime){
                //cout << " X' = "<< xprime << endl;
                //cout << "R["<< i << "] = "<< relations[i] << endl;
                if(IsSubset(xprime,relations[i])){
                    //cout<< "eliminando "<< relations[i] << endl;
                    vector<int> vi = {i};
                    part.erase(remove(part.begin(), part.end(), vi), part.end());
                }
            }
        }


        }
        //cout << "================"<< endl;

    }while(!part.empty());

    return ND;
}
int COUNTER = 0;
void InheritConcepts(vector<vector<int>> T, vector<int> D, vector<int> &A, vector<int> &B, vector<int> marked, Context &c, Lattice<formalConcept> &l){
    bool emptyrelation=false;

        COUNTER++;
        cout<< endl<< endl;
        cout << "Step "<< COUNTER << endl;
        cout <<"proccesing : "<< A << " x " << B <<   endl;
        cout << "marked : "<< marked<< endl;

    if(A.empty()){
        initializeTD(T,D,c);
        
    }

    if (B.empty()){
        cout << "emptyrelation "<< endl;
        emptyrelation=true;
        cout << "saliendo "<< endl;
        return;
    }

    if(!emptyrelation){
        cout << "not empty relation"<< endl;
        vector<vector<int>> part = maxmodPartition(c,A,B);
        //vector<vector<int>> ND = nonDominatingMaxMod(c,part);
        vector<vector<int>> ND;

        cout << "D= ";
        for(int d : D){
            cout << d<< " | ";
        }
        cout << endl;
        cout << "T ..."<< endl;

        for(vector<int> t: T){
            cout << t << endl;
        }
cout<< endl;
        //cout<< "diferencia : "<< dif<<endl;
        

        cout<< "maxmod partition :";
        for(vector<int> v: part){
            cout << v << " | ";
        }
        cout << endl;

        for(int m : marked){
            for(auto i=0; i<(int)part.size(); i++){
                if(count(part[i].begin(),part[i].end(),m)!=0 ){
                    part.erase(part.begin()+i);
                }
            }

        }


        cout<< "maxmod partition (after delete):";
        for(vector<int> v: part){
            cout << v << " | ";
        }
        cout << endl;

        for(vector<int> X : part){
            if(D[X.front()] == (int) X.size()){
                ND.insert(ND.begin(),X);
            }
        }

        cout<< "ND :";
        for(vector<int> v: ND){
            cout << v << " | ";
        }


        for(vector<int> n : ND){
            cout<< "ND = "<< n;
        }
        cout << endl;
        vector<vector<int>> NEW = ND;

        for(vector<int> X : NEW){
            cout << " ...(for) Step "<< COUNTER<< endl;
            vector<int> aprime;
            vector<int> sum = A+X;
            c.attributePrime(sum, aprime);

            vector<int> bprime;
            vector<int> intersection;

            vector<int> rx;
            c.attributePrime(X,rx);

            std::set_intersection(B.begin(),B.end(),rx.begin(),rx.end(),inserter(intersection,intersection.begin()));

            cout <<"generated : "<< sum << " x "<< intersection<<   endl;

            c.objectPrime(intersection, bprime);
            //cout << "A' = "<< sum<< " x "<< "B'="<< intersection << endl;

            preUpdate(T,D,A,B,X,c);
        /*
            for(vector<int> t :T){
                cout << t<< endl;
            }
            cout<< "despues del preupdate: "<< endl;
            for(int d : D){
                cout << d<< " | ";
            }*/

            cout << endl;

            InheritConcepts(T,D,sum,intersection,marked,c,l);

            postUpdate(T,D,A,B,X,c);

            vector<int> Y;
            vector<vector<int>> relations;
            vector<int> m (c.getNAttributes());
            std::iota(m.begin(), m.end(), 0);

            for(int a : m){
                vector<int> aux ={a};
                vector<int> atprime ;

                c.attributePrime(aux,atprime);

                relations.push_back(atprime);
            }

            vector<int> xprime=rx;

            for(auto i = 0; i<(int)relations.size(); i++){
                if(relations.at(i) != xprime){
                    //cout << " X' = "<< xprime << endl;
                    //cout << "R["<< i << "] = "<< relations[i] << endl;
                    if(IsSubset(xprime,relations[i])){
                        //cout<< "eliminando "<< relations[i] << endl;
                        //vector<int> vi = {i};
                        Y.push_back(i);
                    }
                }
            }


            marked = (marked + X);
        }

    }
}