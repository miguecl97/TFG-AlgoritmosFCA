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
   if (argc>1) {
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
  Lattice lnext;
  vector<int> inum = {0};
  vector<vector<int>> A ;
  A.push_back(objects);
  vector<vector<int>> B ;
  B.push_back({});
  int r = 0;
  int i = 0;
  NextConcept(A,B,inum,0,c,lnext);
  cout << "NextConcept(Ganter) : "<< lnext.getSize()<<endl;
  lnext.printTerminal();
  


  //--- ---

  //---BERRY'S ALGORITHM---
  //InheritConcepts(vector<vector<int>> T, vector<int> D, vector<int> &A, vector<int> &B, vector<int> marked, Context &c, Lattice &l)
  vector<int> atBerry;
  Lattice lberry;
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,lberry);
  cout << "Berry :"<< lberry.getSize()<<endl;
  //lberry.printTerminal();

  cout<< endl;

  //--- ---


  //-- INCLOSE ALGORITHM ---
  vector<vector<int>> A2 ;
  vector<vector<int>> B2 ;
  A2.push_back(objects);
  B2.push_back({});
  Lattice linclose;
  int r2=0;
  int y =0;
  cout << "In close: "<<linclose.getSize()<< endl;

  InClose(r,0,A2,B2,c,linclose);
  //linclose.printTerminal();
  
  //--- ---



  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  LatticeLindig(c,llindig);
  cout << "Lindig :"<<llindig.getSize()<< endl;
  //llindig.printTerminal();
  cout<< endl;
  //--- ---




  ofstream myfile; 
  myfile.open("lattice.g");
  //l.printGraphplaceInput(myfile,0);
  //l.printTerminal();
  //cout << "The lattice has been computed in :  "<< chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

  return 0;
}


