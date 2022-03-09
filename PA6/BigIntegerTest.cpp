//-----------------------------------------------------------------------------
//  BigIntegerTest.cpp 
//  A test client for the BigInteger ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){

   string s1 = "9128734667000004389234563456345619187236478";
   // string s2 = "-330293847502398475";
   string s3 = "9876545439000000000000000200000000000006543654365346534";
   //string s4 = "9876545439000000000000000100000000000006543654365346534";
   //string s5 = "98765454390000000000000000000000000000065436543";
   //string s6 = "9876545439000000000000000000000000000006543";
   string s7 = "659179";
   string s8 = "882133";
   string s9 =  "-41085449";
   string s10 = "7402779357";

   //BigInteger N;
   BigInteger A = BigInteger(s9);
   BigInteger B = BigInteger(s10);

   cout << endl;

   cout << "Printing to String (Operator<<)" << endl;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "Printing Done" << endl;


   cout << "Arithmetic Test" << endl;
   cout << "Addition Test A+B: " << endl;
   BigInteger C = A+B;
   cout << "C= " << C << endl;
   cout << "Addition Test B+A: " << endl;
   BigInteger D = B+A;
   cout << "Subtraction Test A-A: " << endl;
   BigInteger E = A-A;
   cout << E << endl;
   cout << "Subtraction Test B-A: " << endl;
   BigInteger F = B-A;
   cout << F << endl;
   cout << "Multiplication Test A*B: " << endl;
   BigInteger G = A*B;
   cout << G << endl;
   cout << "Multiplication Test B*A: " << endl;
   BigInteger H = B*A;
   cout << H << endl;
   cout << "Multiplication Test C*E " << endl;
   BigInteger I = C*E;
   cout << I << endl;
   cout << "Subtraction Test A-B: " << endl;
   BigInteger Z = A-B;
   cout << Z << endl;
   cout << endl;

   cout << "(A==B) = " << ((A==B)?"True":"False") << endl;
   cout << "(A<B)  = " << ((A<B)? "True":"False") << endl;
   cout << "(A<=B) = " << ((A<=B)?"True":"False") << endl;
   cout << "(A>B)  = " << ((A>B)? "True":"False") << endl;
   cout << "(A>=B) = " << ((A>=B)?"True":"False") << endl << endl;

   cout << "C = " << C << endl;
   cout << "D = " << D << endl;
   cout << "(C==D) = " << ((C==D)?"True":"False") << endl;
   cout << "E = " << E << endl;
   cout << "F = " << F << endl;
   cout << "G = " << G << endl;
   cout << "H = " << H << endl;
   cout << "(G==H) = " << ((G==H)?"True":"False") << endl;
   cout << "I = " << I << endl << endl;

   cout << endl;

   A += B;
   B -= C;
   C *= D;
   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << endl;

   cout << A*B*C*D*F*G*H << endl << endl;

   cout << endl;

   // test exceptions
   try{
      BigInteger J = BigInteger("");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("+");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("12329837492387492837492$4982379487293847");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      BigInteger J = BigInteger("5298374902837409+82734098729287349827398");
   }catch( std::invalid_argument& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return EXIT_SUCCESS;
}

