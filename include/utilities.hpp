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



ostream& operator<< (ostream& os,const vector<int>& v);

ostream& operator<<(ostream& out, const formalConcept& f);

bool IsSubset(std::vector<int> A, std::vector<int> B);

#endif
