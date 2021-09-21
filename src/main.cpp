#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <numeric> // std::iota

#include <vector>

#include <boost/algorithm/string.hpp>

//#include "Context.hpp"
#include "Lattice.hpp"
//#include "utilities.hpp"
#include "BatchAlgorithms.hpp"
#include "IncrementalAlgorithms.hpp"
#include "Lattice.cpp"

using namespace std;

void callAlgorithms(Context &c, vector<int> opt){
  //general data:
  vector<int> objects (c.getNObjects());
  std::iota(objects.begin(), objects.end(), 0);

  vector<int> attributes (c.getNAttributes());
  std::iota(attributes.begin(), attributes.end(), 0);

  vector<int> empty={};


  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  //-------------------------------------------------------------B A T C H--------------------------------------------------------------//
  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  if(opt.empty()){
    opt={1,2,3,4,5,6,7};
  }
  cout<< "Results of batch algorithms: "<< endl;

  if(std::count(opt.begin(),opt.end(),1)){
  //--- NEXTCONCEPT ALGORITHM ---
  Lattice lnext;
  vector<int> inum = {0};
  vector<vector<int>> A ;
  A.push_back(objects);
  vector<vector<int>> B ;
  B.push_back({});

  NextConcept(A,B,inum,0,c,lnext);

  cout << "->NextConcept(Ganter) has mined: "<< lnext.getSize()<<" concepts ."<<endl;
  //lnext.printTerminal();
  
  //--- ---
  }




  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  LatticeLindig(c,llindig);
  cout << "->Lindig has mined: "<<llindig.getSize()<<" concepts ."<< endl;
  //llindig.printTerminal();
  //--- ---




  //---BERRY'S ALGORITHM---
  vector<int> atBerry;
  Lattice lberry;
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,lberry);
  cout << "->Berry has mined:" << lberry.getSize()<<" concepts ."<<endl;
  //lberry.printTerminal();
  //--- ---


  //-- INCLOSE ALGORITHM ---
  vector<vector<int>> A2 ;
  vector<vector<int>> B2 ;
  A2.push_back(objects);
  B2.push_back({});
  Lattice linclose;
  int r=0;
  int y =0;
  InClose(r,y,A2,B2,c,linclose);
  //linclose.printTerminal();
  cout << "->In close has mined: "<<linclose.getSize()<<" concepts ."<< endl;
  
  //--- ---


  //---BORDAT'S ALGORITHM---
  Lattice lBordat;
  vector<int> objPrime;
  c.objectPrime(objects,objPrime);
  LatticeBordat(objects,objPrime,objPrime,c,lBordat);
  lBordat.add(make_pair(empty,attributes));
  cout << "->Bordat has mined:" << lBordat.getSize()<<" concepts ."<<endl;
  //lBordat.printTerminal();
  //--- ---

  ofstream myfile; 
  myfile.open("lattice.g");
  //l.printGraphplaceInput(myfile,0);
  //l.printTerminal();

  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  //-----------------------------------------------------I N C R E M E N T A L S--------------------------------------------------------//
  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  cout<< "Results of incremental algorithms: "<< endl;

  //-- NORRIS ALGORITHM ---
  Lattice lNorris;
  vector<int> added ={};
  for(int g : objects){
    AddNorris({g},added,c,lNorris);
  } 
  lNorris.add(make_pair(empty, attributes));
  cout << "->Norris has mined: "<< lNorris.getSize()<< " concepts ."<< endl;
  //cout << "CONCEPTOS DE NORRIS:";
  //lNorris.printTerminal();
  //cout << endl <<endl<<"SALIDA CORRECTA(PUEDE VARIAR EL ORDEN):";
  //lberry.printTerminal();
  //--- ---


  //---GODIN'S ALGORITHM---
  formalConcept inf(make_pair(empty,empty));
  Lattice lGodin;
  for(int g : objects){
    AddGodin({g},inf,c,lGodin);
  } 
  cout << "->Godin has mined: " << lGodin.getSize()<<" concepts ."<<endl;
  //lGodin.printTerminal();
  //--- ---
}




int main(int argc, char *argv[]){


  /*** prepare data according to the context for algorithms ***/


  Context c;
  //read infile .csv
  vector<int> options;

  if(argc==1){
    options={};
    if(argc>1){
      for(auto i=0;i< argc;i++){
        options.push_back(i);
      }
    }

    cout << "MONUMENTOS GRANADA:"<<endl;
    ifstream CSVfile1("./blackBoxTests/monumentosGranada.csv");
    c = readCSV(CSVfile1);
    callAlgorithms(c,options);
    cout << endl<< "...------------------------------------.-------------------------------------------------------..."<< endl;

    cout << "TRIANGULOS: "<<endl;
    ifstream CSVfile2("./blackBoxTests/simpletest.csv");
    c = readCSV(CSVfile2);
    callAlgorithms(c,options);
    cout << endl<< "...------------------------------------.-------------------------------------------------------..."<< endl;

    cout<< "BERRY'S EXAMPLE: "<<endl;
    ifstream CSVfile3("./blackBoxTests/testBerry.csv");
    c = readCSV(CSVfile3);
    callAlgorithms(c,options);
    cout << endl<< "...------------------------------------.-------------------------------------------------------..."<< endl;

    cout<<"GANTER'S EXAMPLE: "<<endl;
    ifstream CSVfile4("./blackBoxTests/testGanter.csv");
    c = readCSV(CSVfile4);
    callAlgorithms(c,options);
    cout << endl<< "...------------------------------------.-------------------------------------------------------..."<< endl;


  }else if(argc==2 && !std::isdigit(*argv[1])){
    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    cout << c;
    callAlgorithms(c,options);
  }else{
    cout << "Error: first argument must be a valid option";
    return 0;
  }

  return 0;
}


