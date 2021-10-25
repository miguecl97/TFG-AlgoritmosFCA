#include <fstream>
#include <iostream>
#include <chrono>
#include <sstream>
#include <string>
#include <numeric> // std::iota

#include <vector>

#include <boost/algorithm/string.hpp>

#include "Lattice.hpp"
#include "BatchAlgorithms.hpp"
#include "IncrementalAlgorithms.hpp"
#include "Lattice.cpp"

using namespace std;


int main(int argc, char *argv[]){


  /*** prepare data according to the context for algorithms ***/

  init();
  Context c;
  Lattice l;
  int gprime=10;
  //read infile .csv
  if(argc>1){

    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);
    //cout << c;

  }else{
    
    c=generate(100,100,gprime);
    cout << "Error: first argument must be a valid option";
  }
  //c=generate(250,250,75);

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
  cout<< "the dataset has "<< c.getNObjects() << " instances and "<<c.getNAttributes()<<" atributes. "<<endl;
  cout<< "Results of batch algorithms: "<< endl;

  //--- NEXTCONCEPT ALGORITHM ---
  Lattice lnext;
  Lattice lganter;
  vector<int> inum = {0};
  vector<vector<int>> A ;
  A.push_back(objects);
  vector<vector<int>> B ;
  B.push_back(objectsPrime);

  /*while(B[r2]!=c.getAttributesVector()){
    formalConcept f = make_pair(A[r2],B[r2]);
    if(!lnext.find(f)){
        lnext.add(f);
    }
    NextConcept(A,B,inum,r2,c,lnext);

  }*/
  //NextConcept(A,B,inum,r2,c,lnext);
/*
  auto startganter = chrono::steady_clock::now();
  NextGanter({},c.getNObjects()-1,c,lganter);
  lganter.add(make_pair(attributesPrime,attributes));
  auto endganter = chrono::steady_clock::now();
  cout<< "CPU USAGE NEXTCLOSURE:"<< getCurrentValue();<<endl
  cout << "->NextClosure(Ganter) has mined: "<< lganter.getSize()<<" concepts ."<<endl;
  cout << "Time NextClosure " 
    << chrono::duration_cast<chrono::milliseconds>(endganter - startganter).count()
		<< " ms" << endl;
  //lganter.printTerminalConcepts(c.getObjects(),c.getAttributes());
  
  //--- ---
  



  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  auto startlindig = chrono::steady_clock::now();
  LatticeLindig(c,llindig);
  auto endlindig = chrono::steady_clock::now();

  cout << "->Lindig has mined: "<<llindig.getSize()<<" concepts ."<< endl;
  cout << "Time Lindig " 
    << chrono::duration_cast<chrono::milliseconds>(endlindig - startlindig).count()
		<< " ms" << endl;l=lganter;
  //llindig.printTerminal();
  //--- ---
  


  //---BERRY'S ALGORITHM---
  vector<int> atBerry={};
  Lattice lberry;
  auto startberry = chrono::steady_clock::now();
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,lberry);
  auto endberry = chrono::steady_clock::now();
  cout << "->Berry has mined:" << l.getSize()<<" concepts ."<<endl;
  cout << "Time Berry " 
    << chrono::duration_cast<chrono::milliseconds>(endberry - startberry).count()
		<< " ms" << endl;
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
  auto startclose = chrono::steady_clock::now();
  linclose.add(make_pair(attributesPrime,attributes));
  InClose(r,y,A2,B2,c,linclose);
  auto endclose = chrono::steady_clock::now();
  //linclose.printTerminalConcepts(c.getObjects(),c.getAttributes());
  cout << "->In close has mined: "<<linclose.getSize()<<" concepts ."<< endl;
  cout << "Time InClose " 
    << chrono::duration_cast<chrono::milliseconds>(endclose - startclose).count()
		<< " ms" << endl;
  //--- ---

  //---BORDAT'S ALGORITHM---
  Lattice lBordat;
  vector<int> objPrime;
  c.objectPrime(objects,objPrime);
  auto startbordat = chrono::steady_clock::now();
  LatticeBordat(objects,objPrime,objPrime,c,lBordat);
  lBordat.add(make_pair(empty,attributes));
  auto endbordat = chrono::steady_clock::now();
  cout << "->Bordat has mined:" << lBordat.getSize()<<" concepts ."<<endl;
  cout << "Time Bordat " 
    << chrono::duration_cast<chrono::milliseconds>(endbordat - startbordat).count()
		<< " ms" << endl;
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
  auto startnorris = chrono::steady_clock::now();
  for(int g : c.getObjectsVector()){
    AddNorris({g},added,c,lNorris);
    added.push_back(g);
  } 
  lNorris.add(make_pair(attributesPrime, attributes));
  auto endnorris = chrono::steady_clock::now();
  cout << "->Norris has mined: "<< lNorris.getSize()<< " concepts ."<< endl;
  cout << "Time Norris " 
    << chrono::duration_cast<chrono::milliseconds>(endnorris - startnorris).count()
		<< " ms" << endl;
  //cout << "CONCEPTOS DE NORRIS:";
  //lNorris.printTerminal();
  //cout << endl <<endl<<"SALIDA CORRECTA(PUEDE VARIAR EL ORDEN):";
  //lberry.printTerminal();
  //--- ---
  

  //---GODIN'S ALGORITHM---
  formalConcept inf(make_pair(empty,empty));
  Lattice lGodin;
  auto startgodin = chrono::steady_clock::now();
  for(int g : objects){
    AddGodin({g},inf,c,lGodin);
  } 
  auto endgodin = chrono::steady_clock::now();
  cout << "->Godin has mined: " << lGodin.getSize()<<" concepts ."<<endl;
  cout << "Time Godin " 
    << chrono::duration_cast<chrono::milliseconds>(endgodin - startgodin).count()
		<< " ms" << endl;
  //lGodin.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---



  //---ADDINTENT ALGORITHM---
  formalConcept bottomconcept(make_pair(attributesPrime,attributes));
  Lattice lAddIntent;
  auto startintent = chrono::steady_clock::now();
  lAddIntent.add(bottomconcept);
  for(int g : objects){
    vector<int> gaux={g};
    vector<int> gPrime;
    c.objectPrime(gaux,gPrime);
    formalConcept objectConcept = AddIntent(gPrime,bottomconcept,c,lAddIntent);
    vector<formalConcept> above = lAddIntent.getConceptsAbove(objectConcept);
    //lAddIntent.replace(objectConcept,make_pair(objectConcept.first+gaux,objectConcept.second));
    for(formalConcept f: above){
      lAddIntent.replace(f,make_pair(f.first+gaux,f.second));
    }

  }
  auto endintent = chrono::steady_clock::now();
  cout << "->AddIntent has mined: " << lAddIntent.getSize()<<" concepts ."<<endl;
  cout << "Time Addintent " 
    << chrono::duration_cast<chrono::milliseconds>(endintent - startintent).count()
		<< " ms" << endl;
  //lAddIntent.printTerminalNodes();
  //lAddIntent.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---
  */
  /*
  cout<< "SALIDA GODIN";
  lGodin.printTerminal();
  
  */



  //-- INCLOSE ALGORITHM ---
  vector<vector<int>> A2 ;
  vector<vector<int>> B2 ;
  A2.push_back(objects);
  B2.push_back({});
  Lattice linclose;
  int r=0;
  int y =0;

  auto startclose = chrono::steady_clock::now();
  linclose.add(make_pair(attributesPrime,attributes));
  InClose(r,y,A2,B2,c,linclose);
  auto endclose = chrono::steady_clock::now();
  //linclose.printTerminalConcepts(c.getObjects(),c.getAttributes())

  cout << "->In close has mined: "<<linclose.getSize()<<" concepts ."<< endl;
  cout<< "CPU USAGE:"<< getCurrentValue()<<"%" <<endl;
  cout<< "RAM USED: "<< getValue()<<" Kb"<<endl;
  cout << "Time InClose " 
    << chrono::duration_cast<chrono::milliseconds>(endclose - startclose).count()
		<< " ms" << endl;
  //--- ---


  ofstream results;
  results.open ("/home/miguelcant/Documentos/FCA_mcantarero/results/"+to_string(c.getNAttributes())+"/"+to_string(gprime) +"results"+to_string(c.getNObjects())+".txt");
  linclose.printIntoFile(results);
  results.close();

  return 0;
}


