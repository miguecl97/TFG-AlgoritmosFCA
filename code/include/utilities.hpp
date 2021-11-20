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

/**
 * @brief Generates an artificial context with uniform distribution of attributes and stores it in a csv file.
 * @param nObj number of objects of the context.
 * @param nProp number of attributes of the context.
 * @param nGPrime number of attributes that each object will have.
 * @param filenumber final numbere extension of the csv file.
 * @return The formal context created.
 */
Context generate(int nObj, int nProp, int nGPrime,int filenumber);

/**
 * @brief Output operator.
 * @param os Output stream.
 * @param v the vector to be printed.
 * @return The output stream.
 * */
ostream& operator<< (ostream& os,const vector<int>& v);

/**
 * @brief Output operator.
 * @param os Output stream.
 * @param c The context to be printed.
 * @return The output stream.
 * */
ostream& operator<<(ostream& out, const formalConcept& f);

/**
 * @brief Checks is the vector B is a susbset or equal to vector A.
 * @param A vector Bc=A.
 * @param B vector Bc=A.
 * @return True if Bc=A false if its not.
 */
bool IsSubset(std::vector<int> A, std::vector<int> B);

/**
 * @brief Inserts an int into a vector and sort it.
 * @param vec vector that will recieve the int.
 * @param item int that will be inserted
 */
void insert_sorted( std::vector<int> & vec, int const& item );

/**
 * @brief - operator between two int vectors.
 * @param vector 1 minuend.
 * @param vector2 substrahend.
 * @return the diference between two vectors.
 */
vector<int> operator-(const vector<int>& vector1, const vector<int>& vector2);

/**
 * @brief + operator between two int vectors (union operator).
 * @param vector1 base vector.
 * @param vector2 vec to add.
 * @return a new vector which contains the elements of both vectors.
 */
vector<int> operator+(const vector<int>& vector1, const vector<int>& vector2);

/**
 * @brief computes the power set of a vector.
 * @param set vector which will be powered.
 * @return a vector of vector of the parts of the set.
 */
vector< vector<int> > getAllSubsets(vector<int> set);

/**
 * @brief transform the numeric nodes of a lattice with his meaning.
 * @param f formalCOncept that will be transformed.
 * @param objects string with the names of the objects.
 * @param attributes string with the names of the attributes.
 */
void transformNodes(formalConcept f, vector<string> objects, vector<string> attributes);

/*Below functions are auxiliar functions for taking measures of hardware resources, explanation avaible at:
https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
*/
void init();
double getCurrentValue(); 
int parseLine(char* line);
int getValue();
#endif
