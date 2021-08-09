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
  Lattice l;

  //read infile .csv
   if (argc>1 ) {
    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    cout << c;
  }else{
    cout << "Error: first argument must be a valid .csv file";
    return 0;
  }


  /*** prepare data according to the context for algorithms ***/

  //general data:
  vector<int> objects (c.getNObjects());
  std::iota(objects.begin(), objects.end(), 0);

  vector<int> attributes (c.getNAttributes());
  std::iota(attributes.begin(), attributes.end(), 0);

  //--- NEXTCONCEPT ALGORITHM ---

  //--- ---

  //---BERRY'S ALGORITHM---
  //InheritConcepts(vector<vector<int>> T, vector<int> D, vector<int> &A, vector<int> &B, vector<int> marked, Context &c, Lattice &l)
  vector<int> atBerry;
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,l);

  //--- ---


  //-- INCLOSE ALGORITHM ---
  vector<vector<int>> A ;
  vector<vector<int>> B ;
  A.push_back(attributes);
  Lattice linclose;
  int r=0;
  //InClose(r,0,A,B,c,linclose);

  //--- ---



  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  LatticeLindig(c,llindig);
  //--- ---








  ofstream myfile; 
  myfile.open("lattice.g");
  //l.printGraphplaceInput(myfile,0);
  //l.printTerminal();
  //cout << "The lattice has been computed in :  "<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

  return 0;
}


