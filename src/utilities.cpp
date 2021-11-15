/**
* @file utilities.cpp
* @author mcantarero
*/

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "utilities.hpp"
#include <random>
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


vector< vector<int> > getAllSubsets(vector<int> set){
    vector< vector<int> > subset;
    vector<int> empty;
    subset.push_back( empty );

    for (int i = 0; i <(int) set.size(); i++)
    {
        vector< vector<int> > subsetTemp = subset;  //making a copy of given 2-d vector.

        for (int j = 0; j < (int)subsetTemp.size(); j++)
            subsetTemp[j].push_back( set[i] );   // adding set[i] element to each subset of subsetTemp. like adding {2}(in 2nd iteration  to {{},{1}} which gives {{2},{1,2}}.

        for (int j = 0; j < (int)subsetTemp.size(); j++)
            subset.push_back( subsetTemp[j] );  //now adding modified subsetTemp to original subset (before{{},{1}} , after{{},{1},{2},{1,2}}) 
    }
    //std::sort(subset.begin(),subset.end());
    return subset;
}

Context generate(int nObj, int nProp, int nGPrime, int filenumber){
    vector<vector<bool>> mat(nObj, vector<bool>(nProp, false));
    const int range_from  = 1;
    const int range_to    = nProp;
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(range_from, range_to);

    for(auto &row : mat){
        for(int i=0; i<nGPrime;i++){
            int random =distr(generator);
            while(row[random]==1){
                random = distr(generator);
            }
            row[random]=1;
        }
    }

    ofstream dataset;
    dataset.open ("/home/miguelcant/Documentos/FCA_mcantarero/datasets/M"+to_string(nProp)+"/g'"+to_string(nGPrime)+"/G"+to_string(nObj)+"dataset"+to_string(filenumber)+".csv");
    
    dataset<< " ,";
    for(int i=1;i<=nProp;i++){
        dataset<<i<<",";
    }
    dataset<<"\n";
    for(int i=1; i<= nObj;i++){
        dataset<<i<<",";
        for(int j=1;j<=nProp;j++){
            if(mat[i-1][j-1]){
                dataset<<"1,";
            }else{
                dataset<<"0,";
            }
        }
        dataset<<"\n";
    }
    dataset.close();
    return Context(mat);
}


void transformNodes(formalConcept f, vector<string> objects, vector<string> attributes){
    
    cout<< "{";
        if(f.first.size()!=0){
                for(vector<int>::const_iterator j = f.first.begin(); j<f.first.end() -1 ;j++){
                        cout<< objects[*j] << ", ";
                        
                }
        
                cout << objects[*(f.first.end() -1)];
        }
        cout<< "}, {";
        if(f.second.size()!=0){
                for(vector<int>::const_iterator j = f.second.begin(); j<f.second.end() -1 ;j++){
                        cout<< attributes[*j] << ", ";
                        
                }  
                cout << attributes[*(f.second.end() -1)];
        }
       cout << "}";

}



static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

void init(){
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
}

double getCurrentValue(){
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}

int parseLine(char* line){
    // This assumes that a digit will be found and the line ends in " Kb".
    int i = strlen(line);
    const char* p = line;
    while (*p <'0' || *p > '9') p++;
    line[i-3] = '\0';
    i = atoi(p);
    return i;
}

int getValue(){ //Note: this value is in KB!
    FILE* file = fopen("/proc/self/status", "r");
    int result = -1;
    char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmRSS:", 6) == 0){
            result = parseLine(line);
            break;
        }
    }
    fclose(file);
    return result;
}