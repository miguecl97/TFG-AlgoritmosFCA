/**
 * @file Context.cpp
 * @author mcantarero
 * */
#include <math.h>
#include <iostream>
#include <iomanip>
#include <numeric> // std::iota
#include "Context.hpp"
#include "string.h"

Context::Context(){
    nObj = nProp = 0;
}

Context::Context(vector<vector<bool>> data, vector<string> obj, vector<string> attr){
    nObj = obj.size();
    nProp = attr.size();
    objects = obj;
    attributes= attr;
    table = data;     
}

Context::Context(vector<vector<bool>> data){
    table = data;
    nObj = data.size();
    nProp = data.at(0).size();

    for(int i=0;i<(int)nObj;i++){
        objects.push_back(to_string(i));
    }
    for(int i=0; i< (int)nProp;i++){
        attributes.push_back(to_string(i));
    }
 }

vector<int> Context::getObjectsVector(){
    vector<int> aux (getNObjects());
    std::iota(aux.begin(), aux.end(), 0);
    return aux;
}

vector<int> Context::getAttributesVector(){
    vector<int> aux (getNAttributes());
    std::iota(aux.begin(), aux.end(), 0);
    return aux;
}


bool Context::getIncidence(int i, int j){
    return table[i][j];
}

void Context::objectPrime(vector<int> &objset, vector<int> &objPrime){
    if(objset.empty()){
        objPrime.resize(attributes.size());
        for(size_t k=0 ;k < nProp ; k++){
            objPrime[k]=k;    //if empty fullfill the vector         
        }
    }else{
        objPrime.clear();
        bool temp = true;
        for(size_t k = 0 ; k < attributes.size() ; k++){
            temp = true;
            for(typename vector<int>::const_iterator j = objset.begin(); j< objset.end() ; j++){
                temp = table[*j][k] && temp;
            }    
                if(temp)
                    objPrime.push_back(k);
        }
    }
}


void Context::attributePrime(vector<int> &attrset, vector<int> &attributePrime){
    if(attrset.empty()){
        attributePrime.resize(objects.size());
        for(size_t k = 0 ; k< nObj ; k++){
            attributePrime[k]=k;
        }
    }else{
        attributePrime.clear();
        bool temp = true;
        for(size_t k = 0; k< nObj; k++){
            temp = true;
            for(typename vector<int>::const_iterator j = attrset.begin(); j< attrset.end(); j++){
                temp = table[k][*j] && temp;
            }
            if(temp)
                attributePrime.push_back(k);  
        }
    }
}

void Context::objectDoublePrime(vector<int> &objset, vector<int> &objDPrime){
    vector <int> aux;
    objectPrime(objset,aux);
    attributePrime(aux, objDPrime);
}


void Context::attributeDoublePrime(vector<int> &attrset, vector<int> &attributeDPrime){
    vector <int> aux;
    attributePrime(attrset,aux);
    objectPrime(aux, attributeDPrime);
}


ostream& operator<<(ostream& os, Context& c){

    TextTable t( '-', '|', '+' );
    t.add( "Objects / Attributes");
    for (size_t attrID = 0; attrID < c.getNAttributes(); attrID++){
        t.add(c.getAttributes().at(attrID));
    }
    t.endOfRow();

    for (size_t objID = 0; objID < c.getNObjects(); objID++){
        t.add(c.getObjects().at(objID));
        for(unsigned i=0; i < c.getNAttributes(); i++){
            if(c.getTable()[objID][i]==true)
                t.add("  x  ");
            else
                t.add( "     ");
        } 
        t.endOfRow();
    }
    t.setAlignment( 2, TextTable::Alignment::RIGHT );
    cout << t;
    
    return os;   
}
