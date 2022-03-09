//-----------------------------------------------------------------------------
// Arithmetic.cpp
// CSE101 PA6
// Simon Carballo
// 1618309
// 02/21/22
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;
   string s1, s2, white; 

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }

   // read each line of input file
   getline(in, s1);
   getline(in, white);
   getline(in, s2);

   BigInteger A, B, C, D, E, F;

   A = BigInteger(s1);
   B = BigInteger(s2);

   out << A << endl;
   out << endl;
   out << B << endl;
   out << endl;
   out << A+B << endl;
   out << endl;
   out << A-B << endl;
   out << endl;
   out << A-A << endl;
   out << endl;

   C = BigInteger("3"); 
   D = BigInteger("2");
   
   out << (C*A)-(D*B) << endl;
   out << endl;
   out << A*B << endl;
   out << endl;
   out << A*A << endl;
   out << endl;
   out << B*B << endl;
   out << endl;

   E = BigInteger("9");
   F = BigInteger("16");

   out << (E*(A*A*A*A))+(F*(B*B*B*B*B)) << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}