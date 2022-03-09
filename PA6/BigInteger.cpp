//-----------------------------------------------------------------------------
// BigInteger.cpp
// CSE101 PA6
// Simon Carballo
// 1618309
// 02/21/22
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<stdexcept>
#include<climits>
#include"List.h"
#include"BigInteger.h"

using namespace std;

long base = 1000000000;
int power = 9;

//**************************************************************************
// Private Constructor -----------------------------------------------------
//**************************************************************************

// Pow()
// Returns the power of the base
int Pow(int base, int power){
   int result = 1;
   for(int x=0; x<power; x++){
      result *= base;      
   }
   return result;
}


//**************************************************************************
// Helper Functions ---------------------------------------------------------
//**************************************************************************

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
   for(L.moveFront(); L.position()<L.length(); L.moveNext()){
      long temp = L.peekNext();
      temp *= -1;
      L.setAfter(temp);
   }
}

// sumList()
// Overwrites the state of S with A + sgn*B (considered as vectors).
// Used by both sum() and sub().
void sumList(List& S, List A, List B, int sgn){
   List T;
   A.moveBack();
   B.moveBack();
   // cout << A << endl;
   // cout << B << endl;
   while(A.position()>0 || B.position()>0){
      long N=0;
      long M=0;
      if(A.position()>0){
         N = A.peekPrev();
         // cout << N << endl;
         A.movePrev();
      }
      if(B.position()>0){
         M = B.peekPrev();
         B.movePrev();
      }
      // cout << "Test: " << N << " + " << M << endl;
      long R = N + (M*sgn);
      // cout << "Tot: " << R << endl;
      T.insertAfter(R);
   }
   // cout << T << endl;
   S = T;
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L){
   List T;
   long carry = 0;
   bool flag = false;

   // Negative Front Case
   if(L.front()<0){
      // cout << "Neg Case" << endl;
      flag = true;
      negateList(L);
   }

   for(L.moveBack(); L.position()>0; L.movePrev()){
      // cout << "Test" << endl;
      long dig = L.peekPrev();
      long norm = 0;
      dig += carry;
      // Nomalize
      if(dig<0){ // Negative Case
         long temp = 0;
         while((dig+temp)<0){
            temp += base;
         }
         norm = dig + temp;
         carry = -1*(temp/base);
      }else{
         carry = dig/base;
         norm = dig%base;
      }
      // Add to Normalized List
      // cout << "Norm" << norm << endl;
      // cout << "Carry" << carry << endl;
      T.insertAfter(norm);
   }
   // Extra Carry
   if(carry!=0){
      T.insertAfter(carry);
   }
   // cout << "Normalized List: " << T << endl;
   // Negative carry Case
   if(T.front()<0){
      // cout << "Neg Case" << endl;
      flag = true;
      negateList(T);
      normalizeList(T);
   }

   L = T;
   // Return Signum
   if(flag){
      return -1;
   }else{
      return 1;
   }
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p){
   L.moveBack();
   long z = 0;
   for(int x=p; x>0; x--){
      L.insertBefore(z);
   }
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m){
   for(L.moveFront(); L.position()<L.length(); L.moveNext()){
      long temp = L.peekNext();
      temp *= m;
      L.setAfter(temp);
   }   
}


//**************************************************************************
// Class Constructors & Destructors ----------------------------------------
//**************************************************************************
   
// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
   signum = 0;
   digits = List();
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
   // Empty String Check
   int strsize = s.size();
   if(strsize==0){
      throw std::invalid_argument("BigInteger: Constructor: empty string");
   } 
   // cout << "Size Before" << strsize << endl;

   string c = s;
   digits = List();

   // signum handler
   if(s[0]=='-'){
      signum = -1;
      c.erase(0,1);
   }else if(s[0]=='+'){
      signum = 1;
      c.erase(0,1);
   }else{
      signum = 1;
   }
   // cout << "String: " << c << endl;
   // Numeric String Check
   int csize = c.size();
   if(csize==0){
      throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
   } 
   for(int y=0; y<csize ; y++){
      if(isdigit(c[y]) == 0){
         throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
      }
   }
   
   int x = c.size();
   // cout << "Size After" << x << endl;
   int count = x/power;
   int leftover = x%power;
   while(x>0){
        long dig = 0;
        string temp;
        if(count > 0){
            temp = c.substr(x-power,power);
            count--;
            x -= power;
        }else{
            // cout << "Test" << endl;
            temp = c.substr(x-leftover,leftover);
            x -= leftover;
        }
        dig = stol(temp, nullptr, 10);
      //   cout << dig << endl;
        digits.insertAfter(dig);
   }
   // cout << "Printing List: " << digits << endl;
   // cout << "Signum: " << signum << endl;
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
   signum = N.signum;
   digits = List(N.digits);
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();

//**************************************************************************
// Access functions --------------------------------------------------------
//**************************************************************************

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
   return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
   // Signum Easy Case
   if(signum<N.signum){
      return -1;
   }
   if(signum>N.signum){
      return 1;
   }
   if(signum==0 && N.signum==0){
      return 0;
   }

   // Digits Length Test
   if(digits.length()!=N.digits.length()){
      // Negative Case
      if(signum==-1){
         if(digits.length()>N.digits.length()){
            return -1;
         }else{
            return 1;
         }
      }else if(signum==1){
         if(digits.length()<N.digits.length()){
            return -1;
         }else{
            return 1; 
         }
      }
   }

   // Digit Value Test
   List LA = List(digits);
   List LB = List(N.digits);
   LA.moveFront();
   LB.moveFront();
   while(LA.position()<LA.length()){
      long x = LA.peekNext();
      long y = LB.peekNext();
      if(signum==-1){
         if(x>y){
            return -1;
         }else if(x<y){
            return 1;
         }
      }else if(signum==1){
         if(x<y){
            return -1;
         }else if(x>y){
            return 1;
         }
      }
      LA.moveNext();
      LB.moveNext();
   }

   // If all Test Pass 
   return 0;
}


//**************************************************************************
// Manipulation procedures -------------------------------------------------
//**************************************************************************

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
   signum = 0;
   digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
   signum = signum * -1;
}


//**************************************************************************
// Arithmetic Operations ---------------------------------------------------
//**************************************************************************

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
   BigInteger T;
   // Easy Cases
   if(signum==0 && N.sign()==0){ // Both are empty Big Integer
      T.signum = 0;
      return T;
   }
   if(signum!=0 && N.sign()==0){ // If N is empty
      T.digits = digits;
      T.signum = signum;
      return T;
   }
   if(signum==0 && N.sign()!=0){ // If this is empty
      T.digits = N.digits;
      T.signum = N.signum;
      return T;
   }
   
   List L = digits;
   if(signum==-1){
      negateList(L);
   }

   sumList(T.digits, L, N.digits, N.signum);
   // cout << "Test List:" << T.digits << endl;
   T.signum = normalizeList(T.digits);

   return T;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
   BigInteger T;
   // Easy Cases
   if(signum==0 && N.sign()==0){ // Both are empty Big Integer
      T.signum = 0;
      return T;
   }
   if(signum!=0 && N.sign()==0){ // If N is empty
      T.digits = digits;
      T.signum = signum;
      return T;
   }
   if(signum==0 && N.sign()!=0){ // If this is empty
      T.digits = N.digits;
      T.signum = N.signum*-1;
      return T;
   }

   List L = digits;
   if(signum==-1){
      negateList(L);
   }

   int sign = N.signum * -1;
   // cout << "Sig Test: " << sign << endl;
   sumList(T.digits, L, N.digits, sign);
   // cout << "Test List: " << T.digits << endl;
   T.signum = normalizeList(T.digits);

   return T;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
   BigInteger T;
   // Easy Cases
   // cout << "Signum Test: " << signum << " " << N.signum << endl;
   if(signum==0 || N.sign()==0){ // Both are empty Big Integer
      T.signum = 0;
      return T;
   }

   BigInteger Temp;
   List L = N.digits;

   L.moveBack();
   for(int x=0; L.position()>0; x++){
      Temp.digits = digits;
      Temp.signum = 1;

      long mul = L.peekPrev();
      scalarMultList(Temp.digits, mul);
      shiftList(Temp.digits, x);

      // Add and Normalize
      T += Temp;
      L.movePrev();
   }

   if((signum==-1)^(N.sign()==-1)){
      T.signum = -1;
   }else{
      T.signum = 1;
   }

   // cout << "Actual Signum: " << T.signum << endl;
   return T;
}


//**************************************************************************
// Other Functions ---------------------------------------------------------
//**************************************************************************

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
   string s = "";
   // cout << digits << endl;
   bool flag = false;
   bool first = false; 

   if(signum==-1){
      s += "-";
   }

   // Printer Loop
   // Create a for loop to manually add zeros to fill the base amount 
   // EX: base 100 -> of 1 would be 01
	// cout << "Data Check:" << digits.peekNext() << endl;
	for(digits.moveFront(); digits.position()<digits.length(); digits.moveNext()){
      long val = digits.peekNext();
      long temp = val;
      // cout << "Test Val: " << val << endl; 
      int count = 0;
      if(val!=0){
         flag = true;
      }
      if(flag==false){
         continue;
      }
      // Negate
      if(val<0){
         val = val*-1;
      }
      // Digit Counter For 0
      while(temp>0){
         temp = temp/10;
         count++;
      }
      // Adding 0s
      int dif = power-count;
      // cout << "Dif: " << dif << endl;
      while(dif>0 && first){
         s += "0";
         dif--; 
      }
      // cout << "Exit" << endl;
      if(val!=0){
         first = true;
         s += std::to_string(val);
      }
	}

   // 0 case 
   if(!flag){
      s = "0";
   }

   return s;
}


//**************************************************************************
// Overriden Operators -----------------------------------------------------
//**************************************************************************

// operator<<()
// Inserts string representation of N into stream.
ostream& operator<<( ostream& stream, BigInteger N ){
   return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
   List M = A.digits;
   List N = B.digits;
   
   if(A.signum!=B.signum){
      return false;
   }else{
      return (M==N);
   }
}

// operator<()
// Returns true if and only if A is less than B.
// A < B
bool operator<( const BigInteger& A, const BigInteger& B ){
   List LA = A.digits;
   List LB = B.digits;

   // EasyTests
   if(A.signum<0 && B.signum>=0){ // If A is negative and B is 0 or positive
      return true;
   }
   if(A.signum==0 && B.signum>0){ // If A is 0 and B is Positive
      return true;
   }
   if(LA.length()!=LB.length()){ // If length are different
      return LA.length()<LB.length();
   }

   LB.moveFront();
   for(LA.moveFront(); LA.position()<LA.length(); LA.moveNext()){
      if(LA.peekNext()!=LB.peekNext()){
         if(A.signum==1 && B.signum==1){
            return LA.peekNext() < LB.peekNext(); 
         }else if(A.signum==-1 && B.signum==-1){
            return LA.peekNext() > LB.peekNext();
         }else{
            cout << "ERROR CASE Operator<" << endl;
         }
      }
   }
   return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
   return (B<A);
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
   return !(A>B);
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
   return !(A<B);
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
   BigInteger T;
   T = A.add(B);
   return T;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
   A = A.add(B);
   return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
   BigInteger T;
   T = A.sub(B);
   return T;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
   A = A.sub(B);
   return A; 
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
   BigInteger T;
   T = A.mult(B);
   return T;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
   A = A.mult(B);
   return A;
}
