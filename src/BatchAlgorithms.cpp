/**
* @file algorithms.cpp
* @author mcantarero
*/

#include "BatchAlgorithms.hpp"
//#include "Lattice.cpp"

#include <iostream>
#include <vector>
#include <numeric> // std::iota
#include <cmath>

void NextConcept(vector<vector<int>> A,vector<vector<int>> B,vector<int> &inum,int r,Context &c, Lattice &l){
    vector<int> m(c.getNAttributes());
    std::iota(m.begin(), m.end(), 0);
    bool found = false;
    
    //add the new concept generated
    formalConcept f = make_pair(A[r],B[r]);
    if(!l.find(f)){
        l.add(f);
    }

    //check if we reach the final of algorithm
    if(B[r]==m){    
        return;
    }

    //start the algoritm
    for(int i = (int) c.getNAttributes(); i > 0; i--){
        found = false;
                        
        if(count(B[r].begin(), B[r].end(),m[i-1])!=0){
            found = true;
        }

        if(!found){
            while(i < inum[r]){
                r = r-1;
            }

            if((int)inum.size() <= r+1){
                inum.resize(r + 2);
            }
            
            inum[r+1]=i;
            vector<int> auxprime;
            vector<int> mi = { m[i-1] };
            c.attributePrime(mi,auxprime );

            if((int)A.size() <= r+1){
                A.resize(r + 2);
            }

            A[r+1].clear();
            set_intersection(A[r].begin(),A[r].end(),auxprime.begin(),auxprime.end(),inserter(A[r+1],A[r+1].begin()));
            
            for(int j = 1; j<i ; j++){
                if(!found){
                    vector<int> auxjprime;
                    vector<int> mj = { m[j-1]};
                    c.attributePrime(mj,auxjprime );

                    if(IsSubset(auxjprime,A[r+1])){
                        //could be a bit more efficient with a break; but for a clearly code
                        found = true;
                    }
                }
            }
            
            if(!found){
                if((int)B.size() <= r+1){
                    B.resize(r+2);
                }  

                B[r+1] = B[r] + mi;

                for(int j = i+1;j<=(int)c.getNAttributes();j++){
                    if(count(B[r+1].begin(), B[r+1].end(),j-1) == 0){
                        vector<int> auxj2prime;
                        vector<int> mj = { m[j-1] };
                        c.attributePrime(mj,auxj2prime );

                        if(IsSubset(auxj2prime,A[r+1])){
                            insert_sorted(B[r+1],m[j-1]);
                        }
                    }
                }   

                r = r+1;    
                /* for printing whats happening
                cout << "calling again nextconcept: "<< endl;
                cout<< "i ="<< i <<endl;
                cout<< "r= "<< r << " / / inum="<< inum<<endl;
                for(int w =0; w< (int)A.size() ; w++){
                    cout << " A["<< w<< "]="<< A[w];
                }
                cout << endl;
                for(int e = 0; e<(int)B.size() ; e++){
                cout << " B["<< e<< "]="<< B[e];
                }
                cout << endl<< endl;
                */

                //call again with the result list
                NextConcept(A,B,inum,r,c,l);            
            }  
        }
    }
}



list<formalConcept> Neighbors(vector<int> obj, vector<int> attr, Context &c){
    vector<int> A (c.getNObjects());
    std::iota(A.begin(), A.end(), 0);
    list<formalConcept> neigh;

    vector<int> min = A-obj;
    vector <int> minus(min);
    
    for( int x : minus){
        vector <int> m1;
        vector <int> aux = {x};
        vector <int> both;

        //O U {x}
        std::set_union(obj.begin(), obj.end(), aux.begin(), aux.end() ,back_inserter(both) );

        c.objectPrime(both, m1); 
        vector <int> g1;
        c.attributePrime(m1,g1);

        vector<int> intersection;
        vector<int> difference =  g1 - obj;
        vector<int> difference2= difference - aux;

        std::set_intersection(min.begin(),min.end(),difference2.begin(),difference2.end(),inserter(intersection,intersection.begin()));

       if(intersection.empty()){
            neigh.push_back(make_pair(g1,m1));
       }else{
            vector <int> aux2;
            set_difference(min.begin(),min.end(), aux.begin(), aux.end(),std::inserter(aux2, aux2.end()));
            min = aux2;
       }
    }
    return neigh;
}


void LatticeLindig(Context &c, Lattice &l){
    formalConcept f;
    vector <int> emptyobj;
    vector <int> emptyattr;
    //{ }''
    c.objectDoublePrime(emptyobj,f.first);
    //{ }'
    c.objectPrime(emptyattr,f.second);

    l.add(f);
    list <formalConcept> neigh;

    do{
        neigh = Neighbors(f.first,f.second,c);
        for(formalConcept x : neigh){
            l.insertLookUp(x,f);
        }
    }while(l.next(f,f));

}

void InClose(int &r, int y, vector<vector<int>> &A ,vector<vector<int>> &B, Context &c, Lattice &l){
    int rnew = r+1;
    if(r==0){
        vector<int> empty= {};
        vector<int> attributes (c.getNAttributes());
        std::iota(attributes.begin(), attributes.end(), 0);
        l.add(make_pair(empty,attributes));
    }

    if((int)A.size() <= rnew){
        A.resize(rnew+1);
    }

    for(int j = y; j<(int)c.getNAttributes();j++){
        //int k = j+1;
        A[rnew]={};
        
        for(int i : A[r]){
            if(c.getIncidence(i,j) == true){
                insert_sorted(A[rnew],i);
            }
        }

        if(A[rnew].size()>0){

            if(A[rnew].size()==A[r].size()){
                insert_sorted(B[r],j);
            }else{
                if(isCannonical(r,j-1,A,B,c)){
                    vector<int> aux = {j};
                    if((int)B.size() <= rnew){
                        B.resize(rnew + 1);
                    }
                    B[rnew]= B[r]+aux;                    

                    InClose(rnew,j+1,A,B,c,l);
                }
            }
            
        }

    }
    /*
        cout << "Lista de salida: r="<< r<<", y ="<< y << endl;
                    for(int i=0 ; i < (int) A.size(); i++){
                        cout<< "A["<< i<< "]="<< A[i]<<", ";
                    }
                    cout<< endl;
                    for(int i=0 ; i < (int) B.size(); i++){
                        cout<< "B["<< i<< "]="<< B[i]<<", ";
                    }
                    cout << endl<< endl;

    
    for(int i=0 ; i < (int) min(A.size(),B.size()); i++){
        formalConcept f = make_pair(A[i],B[i]);
        if(!l.find(f)){
            l.add(f);
        }
    }*/

    formalConcept f = make_pair(A[r],B[r]);
    if(!l.find(f)){
        //cout << "anadiendo concepto"<< endl;
        l.add(f);
    }

}

bool isCannonical(int r, int y, vector<vector<int>> A, vector<vector<int>> B,Context &c){
    int h=0;
    int rnew=r+1;
    for(int k = B[r].size()-1; k>=0;k-- ){
        for(int j = y; j>= B[r][k]+1; j--){
            for(h = 0; h<= (int)A[rnew].size()-1; h++){
                if(!c.getIncidence(A[rnew][h],j)){
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
                    T[z][u]=T[z][u]-1;
                    if(T[z][u]==0){
                        D[u] = D[u]+1;
                    }
                }
            }
        }
    }

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
                    }
                }
            }
        }
     
    }

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
        vector<int> Ry;
        vector<int> aux ={y};
        c.objectPrime(aux,Ry);
        vector<vector<int>> partcopy = part;
        for(vector<int> k : partcopy){
            if(k.size()>1){
                vector<int> kprime;
                std::set_intersection(k.begin(),k.end(),Ry.begin(),Ry.end(),inserter(kprime,kprime.begin()));
                vector<int> kdoubleprime = k - Ry;

                if(!kdoubleprime.empty() && !kprime.empty()){
                    for(int n=0; n<(int)part.size(); n++){
                        if(part[n]==k){
                            part[n]=kprime;
                            part.insert(part.begin()+n+1,kdoubleprime);
                        }
                    }
                }
            }
        }
    }

    return part;
}



void InheritConcepts(vector<vector<int>> T, vector<int> D, vector<int> &A, vector<int> &B, vector<int> marked, Context &c, Lattice &l){
    bool emptyrelation=false;

    if(A.empty()){
        initializeTD(T,D,c);
    }

    if (B.empty()){
        emptyrelation=true;
    }
    

    if(!emptyrelation){
        vector<vector<int>> part = maxmodPartition(c,A,B);
        vector<vector<int>> ND;

        //compute Non Dominating MaxMod
        for(int m : marked){
            for(auto i=0; i<(int)part.size(); i++){
                if(count(part[i].begin(),part[i].end(),m)!=0 ){
                    part.erase(part.begin()+i);
                }
            }
        }

        for(vector<int> X : part){
            if(D[X.front()] == (int) X.size()){
                ND.insert(ND.begin(),X);
            }
        }

        vector<vector<int>> NEW = ND;

        for(vector<int> X : NEW){
            vector<int> aprime;
            vector<int> sum = A+X;
            c.attributePrime(sum, aprime);
            vector<int> bprime;
            vector<int> intersection;
            vector<int> rx;
            c.attributePrime(X,rx);

            std::set_intersection(B.begin(),B.end(),rx.begin(),rx.end(),inserter(intersection,intersection.begin()));

            c.objectPrime(intersection, bprime);

            preUpdate(T,D,A,B,X,c);
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
            
            for(auto i = 0; i<(int)relations.size(); i++){
                if(relations.at(i) != rx){
                    if(IsSubset(rx,relations[i])){
                        Y.push_back(i);
                    }
                }
            }
            marked = (marked + X +Y);

        }

    }

    if(!B.empty() || A.size() == c.getNAttributes()){
        l.add(make_pair(B,A));
    }

}