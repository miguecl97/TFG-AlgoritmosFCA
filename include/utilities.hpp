/**
 * @file utilities.h
 * @author mcantarero
 */
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include <boost/algorithm/string.hpp>

#include "Context.hpp"
//#include "Lattice.hpp"

using namespace std;

#ifndef __UTILITIES__
#define __UTILITIES__

const string DELIMITER = ",";
const string CSVYES = "1";

typedef pair<vector<int>, vector<int>> formalConcept;


/**
 * @brief Reads a CSV file and return the corresponding formal context.
 * @param f File that contains the CSV information.
 * @return The formal context read from the file.
 */
Context readCSV(ifstream &f);

Context generate(int nObj, int nProp, int d,int filenumber);

ostream& operator<< (ostream& os,const vector<int>& v);

ostream& operator<<(ostream& out, const formalConcept& f);

bool IsSubset(std::vector<int> A, std::vector<int> B);

void insert_sorted( std::vector<int> & vec, int const& item );


vector<int> operator-(const vector<int>& vector1, const vector<int>& vector2);
vector<int> operator+(const vector<int>& vector1, const vector<int>& vector2);

vector< vector<int> > getAllSubsets(vector<int> set);

void transformNodes(formalConcept f, vector<string> objects, vector<string> attributes);
void init();
double getCurrentValue(); 
int parseLine(char* line);
int getValue();
#endif
