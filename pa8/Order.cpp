/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#8
* Order.cpp 
* First top-level client for Dictionary ADT program
*********************************************************************************/
#include<iostream>
#include <fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
  ifstream ifptr; 
  ofstream ofptr;
  int count = 1;
  string word;

  if( argc != 3 ){
    cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
    return(EXIT_FAILURE);
  }

  ifptr.open(argv[1]);
  if(!ifptr.is_open()){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
  }

  ofptr.open(argv[2]);
  if( !ofptr.is_open() ){
    cerr << "Unable to open file " << argv[2] << " for writing" << endl;
    return(EXIT_FAILURE);
  }

  Dictionary A;
  while(1){
      getline(ifptr, word);
      //cout << word << endl;
      if(word.empty()){
          break;
      }
      A.setValue(word, count);
      count++;
  }

  ofptr << A << endl;
  ofptr << A.pre_string();

  ifptr.close();
  ofptr.close();

  return(EXIT_SUCCESS);
}