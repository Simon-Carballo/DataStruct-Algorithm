//-----------------------------------------------------------------------------
// List.cpp
// CSE101 PA5
// Simon Carballo
// 1618309
// 01/10/21
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<iomanip>
#include<stdexcept>
#include<climits>
#include"List.h"

using namespace std;

void shuffle(List& D);

int main(int argc, char * argv[]){
   if(argc != 2){
      printf("Usage: %s <Size of Deck>\n", argv[0]);
      exit(1);
   }

   // cout << "Check Input" << argv[1] << endl;

   int size = atoi(argv[1]);
   // cout << "Check Size" << size << endl;
   
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;

   int count = 0;
   List L, T;
   for(int x=1; x<size+1; x++){
      count = 0;
      L.insertBefore(x);
      T = L;
      // cout << "List: " << L << endl;
      shuffle(T); // how to return
      // cout << T << endl;
      count++;
      // cout << "Match This: " << L << endl;
      while(!(L==T)){
         // cout << T << endl;
         shuffle(T);
         count++;
      }
      cout << " " << setw(16) << left << x;
      cout << setw(16) << left << count << endl;
   }

   return(EXIT_SUCCESS); 
}

void shuffle(List& D){
   List A, B, C;
   int half = D.length()/2;
   int longhalf = D.length()-half; // Half or Half+1
   D.moveFront();
   // List Splitter
   for(int x=0; x<half; x++){
      A.insertBefore(D.peekNext());
      D.moveNext();
   }
   for(int x=0; x<longhalf; x++){
      B.insertBefore(D.peekNext());
      D.moveNext();
   }
   // cout << "Testing for Split List:" << endl;
   // cout << A << endl;
   // cout << B << endl;
   A.moveFront();
   B.moveFront();
   for(int x=0; x<longhalf; x++){
      if(x<B.length()){
         C.insertBefore(B.peekNext());
         B.moveNext();
      }
      if(x<A.length()){
         C.insertBefore(A.peekNext());
         A.moveNext();
      }
   }
   // cout << "Testing Shuffled List" << endl;
   // cout << C << endl;
   D = C;
}

// Questions: 
// Line 40 - How to Return the list
// Line 69/70 - MoveFront Error