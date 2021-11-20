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
  bool infile =false;
  int nG,nA,gprime,filenumber=0;
  ofstream results;
  ofstream csvfile;

  if(argc==5){

    nG=atoi(argv[1]);
    nA= atoi(argv[2]);
    gprime= atoi(argv[3]);
    filenumber = atoi(argv[4]);
    infile=true;
    c=generate(nG,nA,gprime,filenumber);
    csvfile.open ("/home/miguelcant/Documentos/FCA_mcantarero/results/M"+to_string(c.getNAttributes())+"/g'"+to_string(gprime) +"/tables/table"+to_string(c.getNObjects())+".csv",fstream::app);
    csvfile<<endl;
    csvfile<<gprime<<","<<nG<<",";
    results.open ("/home/miguelcant/Documentos/FCA_mcantarero/results/M"+to_string(c.getNAttributes())+"/g'"+to_string(gprime) +"/results/G"+to_string(c.getNObjects())+"-results"+to_string(filenumber)+".txt");

  }else if(argc==2){

    ifstream CSVfile(argv[1]);
    c = readCSV(CSVfile);

  }else{

    cout<< "ERROR: There are 2 ways of execute the algorithms program: \n";
    cout<< "-> Generating a artificial dataset by introducing number of objects, attributes and number of atributes per object in the command line:\n";
    cout<<"    ./bin/main 50 100 4 (will generate a context with |G|=50,|M|=100 and |g'|=4)"<<endl;
    cout<< "-> Using a existing dataset in a csv file: "<<endl;
    cout<< "   ./bin/main /datasets/test.csv"<<endl;
    return 0;

  }

  if(c.getNObjects()==0 ||c.getNAttributes()==0){
    cout<< "Error reading the csv file";
    return 0;
  }

  //auxiliar structures
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
  Lattice lganter;
  double ramganter=0;
  double cpuganter=0;
  int sizeganter=0;
  vector<int> Aganter={};
  int gganter =c.getNObjects()-1;
  auto startganter = chrono::steady_clock::now();
  NextGanter(Aganter,gganter,c,lganter);
  lganter.add(make_pair(attributesPrime,attributes));
  auto endganter = chrono::steady_clock::now();
  cpuganter=getCurrentValue();
  ramganter=getValue();
  sizeganter=lganter.getSize();
  cout << "->NextClosure(Ganter) has mined: "<< sizeganter<<" concepts ."<<endl;
  cout << "Time NextClosure " 
    << chrono::duration_cast<chrono::milliseconds>(endganter - startganter).count()
		<< " ms" << endl;
  //lganter.printTerminalConcepts(c.getObjects(),c.getAttributes());
  
  //--- ---
  



  //--- LINDIG'S ALGORITM ---
  Lattice llindig;
  double ramlindig=0;
  double cpulindig=0;
  int sizelindig=0;
  auto startlindig = chrono::steady_clock::now();
  LatticeLindig(c,llindig);
  auto endlindig = chrono::steady_clock::now();
  cpulindig=getCurrentValue();
  ramlindig=getValue();
  sizelindig=llindig.getSize();

  cout << "->Lindig has mined: "<<sizelindig<<" concepts ."<< endl;
  cout << "Time Lindig " 
    << chrono::duration_cast<chrono::milliseconds>(endlindig - startlindig).count()
		<< " ms" << endl;l=llindig;
  //llindig.printTerminal();
 //llindig.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---
  


  //---BERRY'S ALGORITHM---
  vector<int> atBerry={};
  Lattice lberry;
  double ramberry=0;
  double cpuberry=0;
  int sizeberry = 0;
  auto startberry = chrono::steady_clock::now();
  InheritConcepts({{}}, {}, atBerry, objects, {}, c,lberry);
  auto endberry = chrono::steady_clock::now();
  cpuberry=getCurrentValue();
  ramberry=getValue();
  sizeberry=l.getSize();
  cout << "->Berry has mined:" << sizeberry<<" concepts ."<<endl;
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
  double raminclose=0;
  double cpuinclose=0;
  int sizeinclose=0;
  auto startclose = chrono::steady_clock::now();
  linclose.add(make_pair(attributesPrime,attributes));
  InClose(r,y,A2,B2,c,linclose);
  auto endclose = chrono::steady_clock::now();
  cpuinclose=getCurrentValue();
  raminclose=getValue();
  sizeinclose=linclose.getSize();
  //linclose.printTerminalConcepts(c.getObjects(),c.getAttributes());
  cout << "->In close has mined: "<<sizeinclose<<" concepts ."<< endl;
  cout << "Time InClose " 
    << chrono::duration_cast<chrono::milliseconds>(endclose - startclose).count()
		<< " ms" << endl;
  //--- ---
  

  //---BORDAT'S ALGORITHM---
  Lattice lBordat;
  double rambordat=0;
  double cpubordat=0;
  int sizebordat=0;
  vector<int> objPrime;
  c.objectPrime(objects,objPrime);
  auto startbordat = chrono::steady_clock::now();
  LatticeBordat(objects,objPrime,objPrime,c,lBordat);
  lBordat.add(make_pair(empty,attributes));
  auto endbordat = chrono::steady_clock::now();
  cpubordat=getCurrentValue();
  rambordat=getValue();
  sizebordat= lBordat.getSize();
  cout << "->Bordat has mined:" << sizebordat<<" concepts ."<<endl;
  cout << "Time Bordat " 
    << chrono::duration_cast<chrono::milliseconds>(endbordat - startbordat).count()
		<< " ms" << endl;
  //lBordat.printTerminal();
  //--- ---
  

  /*ofstream myfile; 
  myfile.open("lattice.g");
  l.printGraphplaceInput(myfile,0);
  myfile.close();*/
  //l.printTerminal();

  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  //-----------------------------------------------------I N C R E M E N T A L S--------------------------------------------------------//
  //--------------------------------------------------------------- . ------------------------------------------------------------------//
  cout<< "Results of incremental algorithms: "<< endl;

  //-- NORRIS ALGORITHM ---
  Lattice lNorris;
  double ramnorris=0;
  double cpunorris=0;
  int sizenorris=0;
  vector<int> added ={};
  auto startnorris = chrono::steady_clock::now();
  for(int g : c.getObjectsVector()){
    AddNorris({g},added,c,lNorris);
    added.push_back(g);
  } 
  lNorris.add(make_pair(attributesPrime, attributes));
  auto endnorris = chrono::steady_clock::now();
  cpunorris=getCurrentValue();
  ramnorris=getValue();
  sizenorris=lNorris.getSize();
  cout << "->Norris has mined: "<< sizenorris<< " concepts ."<< endl;
  cout << "Time Norris " 
    << chrono::duration_cast<chrono::milliseconds>(endnorris - startnorris).count()
		<< " ms" << endl;
  //--- ---
  

  //---GODIN'S ALGORITHM---
  formalConcept inf(make_pair(empty,empty));
  Lattice lGodin;
  double ramgodin=0;
  double cpugodin=0;
  int sizegodin=0;
  auto startgodin = chrono::steady_clock::now();
  for(int g : objects){
    AddGodin({g},inf,c,lGodin);
  }
  auto endgodin = chrono::steady_clock::now();
  cpugodin=getCurrentValue();
  ramgodin=getValue();
  sizegodin=lGodin.getSize();
  cout << "->Godin has mined: " << sizegodin <<" concepts ."<<endl;
  cout << "Time Godin " 
    << chrono::duration_cast<chrono::milliseconds>(endgodin - startgodin).count()
		<< " ms" << endl;
  //lGodin.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---



  //---ADDINTENT ALGORITHM---
  formalConcept bottomconcept(make_pair(attributesPrime,attributes));
  Lattice lAddIntent;
  double ramaddintent=0;
  double cpuaddintent=0;
  int sizeintent=0;
  auto startintent = chrono::steady_clock::now();
  /*lAddIntent.add(bottomconcept);
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

  }*/
  auto endintent = chrono::steady_clock::now();
  cpuaddintent=getCurrentValue();
  ramaddintent=getValue();
  sizeintent =lAddIntent.getSize();
  cout << "->AddIntent has mined: " << sizeintent<<" concepts ."<<endl;
  cout << "Time Addintent " 
    << chrono::duration_cast<chrono::milliseconds>(endintent - startintent).count()
		<< " ms" << endl;
  //lAddIntent.printTerminalNodes();
  //lAddIntent.printTerminalConcepts(c.getObjects(),c.getAttributes());
  //--- ---
  

  if(infile){
  results << "NextClosure ("<<sizeganter<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endganter - startganter).count()
	  << " ms / "<<ramganter<<" kb / "<<cpuganter<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endganter - startganter).count()<< ",";
  results << "Lindig ("<<sizelindig<<") "  
    << chrono::duration_cast<chrono::milliseconds>(endlindig - startlindig).count()
	  << " ms / "<<ramlindig<<" kb / "<<cpulindig<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endlindig - startlindig).count()<< ",";
  results << "Inherit-Concepts ("<<sizeberry<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endberry - startberry).count()
	  << " ms / "<<ramberry<<" kb / "<<cpuberry<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endberry - startberry).count()<< ",";
  results << "InClose ("<<sizeinclose<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endclose - startclose).count()
	  << " ms / "<<raminclose<<" kb / "<<cpuinclose<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endclose - startclose).count()<< ",";
  results << "Bordat ("<<sizebordat<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endbordat - startbordat).count()
	 	<< " ms / "<<rambordat<<" kb / "<<cpubordat<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endbordat - startbordat).count()<< ",";
  results << "Godin ("<<sizegodin<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endgodin - startgodin).count()
		<< " ms / "<<ramgodin<<" kb / "<<cpugodin<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endgodin - startgodin).count()<< ",";
  results << "Norris ("<<sizenorris<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endnorris - startnorris).count()
		<< " ms / "<<ramnorris<<" kb / "<<cpunorris<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endnorris - startnorris).count()<< ",";
  results << "AddIntent ("<<sizeintent<<") " 
    << chrono::duration_cast<chrono::milliseconds>(endintent - startintent).count()
		<< " ms / "<<ramnorris<<" kb / "<<cpunorris<< " %" << endl;
  csvfile<<chrono::duration_cast<chrono::milliseconds>(endintent - startintent).count()<< ",";
  l.printIntoFile(results);
  results.close();
  csvfile.close();
  }else{
    l.printTerminalConcepts(c.getObjects(),c.getAttributes());
  }
  
  return 0;
}


