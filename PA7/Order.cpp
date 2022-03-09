//-----------------------------------------------------------------------------
// Order.cpp
// CSE101 PA7
// Simon Carballo
// 1618309
// 03/2/22
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"
using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   ifstream in;
   ofstream out;
   string s1;

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
   Dictionary A;
   int x = 1;
   while(getline(in, s1, '\n')){
      A.setValue(s1, x);
      x++;
   }

   out << A << endl;
   out << A.pre_string() << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}