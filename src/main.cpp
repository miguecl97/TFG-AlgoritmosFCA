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

  
}




int main(int argc, char *argv[]){


  /*** prepare data according to the context for algorithms ***/


  Context c;
  //read infile .csv
  if(argc>1){

    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    //cout << c;

  }else{
    cout << "Error: first argument must be a valid option";
    return 0;
  }


    //general data:
  vector<int> objects (c.getNObjects());
  std::iota(objects.begin(), objects.end(), 0);
  vector<int> objectsPrime;
  c.objectPrime(objects,objectsPrime);

  vector<int> attributes (c.getNAttributes());
  std::iota(attributes.begin(), attributes.end(), 0);
  vector<int> attributesPrime;
  c.attributePrime(attributes,attributesPrime);

  vector<int> empty={};


  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  //-------------------------------------------------------------B A T C H--------------------------------------------------------------//
  //--------------------------------------------------------------- . ------------------------------------------------------------------//

  cout<< "Results of batch algorithms: "<< endl;

  //--- NEXTCONCEPT ALGORITHM ---
  Lattice lnext;
  Lattice lganter;
  vector<int> inum = {0};
  vector<vector<int>> A ;
  A.push_back(objects);
  vector<vector<int>> B ;
  B.push_back(objectsPrime);
  int r2 =0;

  /*while(B[r2]!=c.getAttributesVector()){
    formalConcept f = make_pair(A[r2],B[r2]);
    if(!lnext.find(f)){
        lnext.add(f);
    }
    NextConcept(A,B,inum,r2,c,lnext);

  }*/
  //NextConcept(A,B,inum,r2,c,lnext);

  NextGanter({},c.getNObjects()-1,c,lganter);
  lganter.add(make_pair(attributesPrime,attributes));
  cout << "->NextConcept(Ganter) has mined: "<< lganter.getSize()<<" concepts ."<<endl;
  //lganter.printTerminalConcepts(c.getObjects(),c.getAttributes());
  
  //--- ---
  



  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  LatticeLindig(c,llindig);
  cout << "->Lindig has mined: "<<llindig.getSize()<<" concepts ."<< endl;
  //llindig.printTerminal();
  //--- ---
  


  //---BERRY'S ALGORITHM---
  vector<int> atBerry={};
  Lattice lberry;
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,lberry);
  cout << "->Berry has mined:" << lberry.getSize()<<" concepts ."<<endl;
  //lberry.printTerminal();
  //lberry.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---
  

  //-- INCLOSE ALGORITHM ---
  vector<vector<int>> A2 ;
  vector<vector<int>> B2 ;
  A2.push_back(objects);
  B2.push_back({});
  Lattice linclose;
  int r=0;
  int y =0;
  linclose.add(make_pair(attributesPrime,attributes));
  InClose(r,y,A2,B2,c,linclose);
  //linclose.printTerminalConcepts(c.getObjects(),c.getAttributes());
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
  //lGodin.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---



  //---ADDINTENT ALGORITHM---
  formalConcept bottomconcept(make_pair(attributesPrime,attributes));
  Lattice lAddIntent;
  lAddIntent.add(bottomconcept);
  for(int g : objects){
    vector<int> gaux={g};
    vector<int> gPrime;
    c.objectPrime(gaux,gPrime);
    cout<< g<<endl;
    formalConcept objectConcept = AddIntent(gPrime,bottomconcept,c,lAddIntent);
    vector<formalConcept> above = lAddIntent.getConceptsAbove(objectConcept);
    //lAddIntent.replace(objectConcept,make_pair(objectConcept.first+gaux,objectConcept.second));
    for(formalConcept f: above){
      lAddIntent.replace(f,make_pair(f.first+gaux,f.second));
    }

  }
  cout << "->AddIntent has mined: " << lAddIntent.getSize()<<" concepts ."<<endl;
  //lAddIntent.printTerminalNodes();
  //lAddIntent.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---
  
  /*
  cout<< "SALIDA GODIN";
  lGodin.printTerminal();
  
  */
  cout<<"SALIDA CORRECTA:";
  //llindig.printTerminal();
  return 0;
}


