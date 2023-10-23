/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#8
* WordFrequency.cpp 
* Second top-level client for Dictionary ADT program
*********************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
   Dictionary D;

   size_t begin, end, len;
   ifstream inptr;
   ofstream outptr;
   string line;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; //delimiter

   if(argc != 3){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
   }

   inptr.open(argv[1]);
   if(!inptr.is_open()){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
   }

   outptr.open(argv[2]);
   if( !outptr.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for writng" << endl;
   }

   while( getline(inptr, line) ){
      len = line.length();

      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);
      transform(token.begin(), token.end(), token.begin(), ::tolower);
      
      while( token != ""){
         if (D.contains(token) == true) {
       		D.getValue(token)++;
         }
         else{
        	   D.setValue(token, 1);
         }

         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
         transform(token.begin(), token.end(), token.begin(), ::tolower);
      }
   }

   outptr << D << endl;

   inptr.close();
   outptr.close();

   return(EXIT_SUCCESS);
}
