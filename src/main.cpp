#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <numeric> // std::iota

#include <vector>

#include <boost/algorithm/string.hpp>

//#include "Context.hpp"
//#include "Lattice.hpp"
//#include "utilities.hpp"
#include "Algorithms.hpp"
//#include "Lattice.cpp"

using namespace std;

int main(int argc, char *argv[]){

  Context c;
  list<formalConcept> test;
  Lattice<formalConcept> l;
  
  if (argc>1 ) {
    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    cout << c;
  }else{
    cout << "Error: first argument must be a valid .csv file";
    return 0;
  }

  //for nextconcept
  vector<vector<int>> A ;
  vector<vector<int>> B ;
  vector<int> inum = {0};
  int r=0;
  vector<int> aux (c.getNObjects());
  vector<int> m (c.getNAttributes());
  std::iota(m.begin(), m.end(), 0);


  std::iota(aux.begin(), aux.end(), 0);

  A.push_back(aux);
  vector<vector<int>> T;
  vector<int> D;
  vector<int> marked;
  vector<int> a;
  InheritConcepts(T, D, a, aux, marked, c,l);

  int y =0;
  //InClose(r,0,A,B,c,l);


  ofstream myfile; 
  myfile.open("lattice.g");
  //LatticeLindig(c,l);
  //l.printGraphplaceInput(myfile,0);
  //l.printTerminal();
  //cout << "The lattice has been computed in :  "<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

  return 0;
}


