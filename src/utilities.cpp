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