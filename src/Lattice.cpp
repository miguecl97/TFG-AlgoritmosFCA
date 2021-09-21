

#include "Lattice.hpp"



vector<Node> Lattice::getConcepts(){
    return concepts;
}


int Lattice::getSize(){
    return concepts.size();
}

vector<formalConcept> Lattice::getformalConcepts(){
    vector<formalConcept> ret;
    typename std::vector<Node>::iterator it;
    for(it= concepts.begin(); it!=concepts.end(); it++){
        ret.push_back(it->c);
    }

    return ret;
}

Node Lattice::getConcept(int i){
    for(auto i =0; i<(int)concepts.size();i++){
        if(concepts[i].index==i){
            return concepts[i];
        }
    }

    return concepts[0];
}


void Lattice::replace(formalConcept f,formalConcept newf){
    typename std::vector<Node>::iterator it;
    for(it= concepts.end(); it!=concepts.begin(); it--){
        if(it->c.first == f.first && it->c.second == f.second){
            //cout << "reemplazando"<< f.first << ", "<<f.second<<endl<<"por "<< newf.first<< ", "<<newf.second<<endl;
            it->c.first=newf.first;
            it->c.second=newf.second;
            //cout << "nuevo concepto:"<< it->c.first << ", "<<it->c.second<<endl;
            return;
        }
    }

}


void Lattice::add(formalConcept concept){
    concepts.push_back(Node(concept,count++));
    was_inserted=true;
}



int Lattice::getIndex(formalConcept concp){
    typename std::vector<Node>::iterator it;
    for(it= concepts.begin(); it!=concepts.end(); it++){
        if(it->c.first == concp.first && it->c.second == concp.second)
            return it->index;
    }

    return -1;
}


bool Lattice::find(formalConcept concp){
    typename std::vector<Node>::iterator it;
    for(it= concepts.begin(); it!=concepts.end(); it++){
        if(it->c.first == concp.first && it->c.second == concp.second)
            return true;
    }

    return false;
}


bool Lattice::next(formalConcept& c, formalConcept& output){

    typename vector<Node>::iterator it = std::find(concepts.begin(), concepts.end(), Node(c,0));

    if(it == concepts.end() || ++it == concepts.end())
        return false;
    
    output = it->c;
    last_position_index = it - concepts.begin();
    return true;

}

bool Lattice::insertLookUp(formalConcept& x, formalConcept& c){

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

void Lattice::printGraphplaceInput(ofstream& out, int flag){
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

void Lattice::printTerminal(){
        cout << endl;
        cout << "List of concepts: "<< endl;
        for(typename vector<Node>::iterator i = concepts.begin(); i!= concepts.end(); i++){
                cout << "Concept: "<< i->index+1 << ": " << endl;
                cout << "( ";

                
                cout << i->c;


                cout << ") "<<endl;
        }

}       