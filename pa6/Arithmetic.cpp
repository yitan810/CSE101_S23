/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#6
* BigInteger.cpp 
* main program for BigInteger program
*********************************************************************************/
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){

   ifstream ifptr; 
   ofstream ofptr;

   ifptr.open(argv[1]);
   ofptr.open(argv[2]);

   string string1 = "";
   string string2 = "";

   getline(ifptr, string1);
   BigInteger A = BigInteger(string1);
   getline(ifptr, string1);
   getline(ifptr, string2);
   BigInteger B = BigInteger(string2);
   
   BigInteger A1;
   BigInteger B1;
   BigInteger result;
   A1 = A; 
   B1 = B;

   ofptr << A << endl;
   ofptr << endl;
   ofptr << B << endl;
   ofptr << endl;
   result = A1 + B1;
   ofptr << result << endl;
   ofptr << endl;
   result = A1 - B1;
   ofptr << result << endl;
   ofptr << endl;
   result = A1 - A1;
   ofptr << result << endl;
   ofptr << endl;

   BigInteger S2 = BigInteger("2");
   BigInteger S3 = BigInteger("3");
   
   result = (S3 * A1) - (S2 * B1);
   ofptr << result << endl;
   ofptr << endl;
   A1 = A; 
   B1 = B;

   result = A1 * B1;
   ofptr << result << endl;
   ofptr << endl;

   A1 *= A1;
   ofptr << A1 << endl;
   ofptr << endl;
   A1 = A;

   B1 *= B1;
   ofptr << B1 << endl;
   ofptr << endl;
   B1 = B;

   BigInteger S9 = BigInteger("9");
   BigInteger S16 = BigInteger("16");

   A1 = A * A * A * A;
   B1 = B * B * B * B * B;

   result = (S9 * A1) + (S16 * B1);
   ofptr << result << endl;

   return EXIT_SUCCESS;
}
