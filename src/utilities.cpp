/**
* @file utilities.cpp
* @author mcantarero
*/

#include "utilities.hpp"
Context readCSV(ifstream &f){
    string line;
    vector<string> values;
    vector<string> objects;
    vector<string> attributes;
    vector<vector<bool>> table;


    getline(f,line);
    boost::split(values, line, boost::is_any_of(DELIMITER));
    values.erase(values.begin());
    for (string value : values){
        attributes.push_back(value);
        
    }

    while(getline(f,line)){
        boost::split(values, line, boost::is_any_of(DELIMITER));
        objects.push_back(values.at(0));
        values.erase(values.begin());

        vector<bool> row;
        for (string value : values)
            row.push_back(value == CSVYES);

        table.push_back(row);

    }

    return Context(table,objects,attributes);

}



ostream& operator<< (ostream& os, const std::vector<int>& v) 
{
    os << "[";
    for (typename std::vector<int>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << "]";
    return os;
}


std::ostream& operator<<(ostream& out, const formalConcept& f){

        out<< "{";
        if(f.first.size()!=0){
                for(vector<int>::const_iterator j = f.first.begin(); j<f.first.end() -1 ;j++){
                        out<< *j << ", ";
                        
                }
        
                out << *(f.first.end() -1);
        }
        out<< "}, {";
        if(f.second.size()!=0){
                for(vector<int>::const_iterator j = f.second.begin(); j<f.second.end() -1 ;j++){
                        out<< *j << ", ";
                        
                }  
                out << *(f.second.end() -1);
        }
        out << "}";

        return out;
}

// B is subset of A
bool IsSubset(std::vector<int> A, std::vector<int> B)
{
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}


void insert_sorted( std::vector<int> & vec, int const& item ){
    if(find(vec.begin(),vec.end(),item) == vec.end())
        vec.insert(std::upper_bound( vec.begin(), vec.end(), item ),item );
}


vector<int> operator-(const vector<int>& vector1, const vector<int>& vector2){

    vector<int> aux;
    //std::sort(vector1.begin(), vector1.end());
    //std::sort(vector2.begin(), vector2.end());
    std::set_difference( vector1.begin(), vector1.end(), vector2.begin(), vector2.end(), std::back_inserter( aux )  );

    return aux;
}

vector<int> operator+(const vector<int>& vector1, const vector<int>& vector2){

    vector<int> aux;
    std::set_union(vector1.begin(), vector1.end(), vector2.begin(), vector2.end() ,back_inserter(aux) );
    sort(aux.begin(), aux.end() );
    aux.erase( unique( aux.begin(), aux.end() ), aux.end() );

    return aux;
}