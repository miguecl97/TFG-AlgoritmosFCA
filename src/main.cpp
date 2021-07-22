#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <numeric> // std::iota

#include <vector>

#include <boost/algorithm/string.hpp>

#include "Context.hpp"
#include "Lattice.hpp"
#include "utilities.hpp"
#include "Algorithms.hpp"

using namespace std;

int main(int argc, char *argv[]){

  Context c;
  list<formalConcept> test;
  Lattice<formalConcept> l;
  

  list<formalConcept> list = l.getConcepts();
  if (argc > 1) {
    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    cout << c;
  }else{
    cout << "el primer argumento debe de ser un archivo .csv valido";
    return 0;
  }

  //for nextconcept
  vector<vector<int>> A;
  vector<vector<int>> B = {{}};
  vector<int> inum = {0};
  int r=0;
  vector<int> aux (c.getNObjects());
  vector<int> m (c.getNAttributes());
  std::iota(m.begin(), m.end(), 0);


  std::iota(aux.begin(), aux.end(), 0);

  A.push_back(aux);


  auto start = chrono::steady_clock::now();

/*
  for(int k =1; k< 10;k++){

    cout << "concepto numero : "<< k << endl;
    NextConcept(A,B,inum,r ,c,l);

    cout<< "r = "<< r << endl;
    cout << "inum = " << inum<< endl;

    for(int i = 0 ; i <=r; i++){
      cout<< "A[ "<< i<< "] "<< A[i];
    }

    cout << endl;

    for(int i = 0 ; i <=r; i++){
      cout<< "B[ "<< i<< "] "<< B[i];
    }

    cout << endl<< endl;

  }
*/

  LatticeLindig(c,l);

  auto end = chrono::steady_clock::now();


    cout << "Se ha calculado el retículo en " 
    << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		<< " ms" << endl;


  return 0;
}


