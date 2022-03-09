//-----------------------------------------------------------------------------
// Dictionary.cpp
// CSE101 PA8
// Simon Carballo
// 1618309
// 03/8/22
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<stdexcept>
#include<climits>
#include"Dictionary.h"

#define BLK 0
#define RED 1

using namespace std;

//**************************************************************************
// Private Constructor -----------------------------------------------------
//**************************************************************************

// Node Constructor
Dictionary::Node::Node(keyType k, valType v){
	key = k;
   val = v;
	parent = nullptr; 
	left = nullptr;
   right = nullptr;
   color = BLK;
}


//**************************************************************************
// Class Constructors & Destructors ----------------------------------------
//**************************************************************************

// Creates new Dictionary in the empty state.
Dictionary::Dictionary(){
   Node* NullNode = new Node("", -1);
   nil = NullNode; 
   root = NullNode;
   current = NullNode;
   num_pairs = 0;
   root->parent = nil;
   // cout << "Hello" << endl;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
   Node* NullNode = new Node("", -1);
   nil = NullNode; 
   root = NullNode;
   current = NullNode;
   num_pairs = 0;
   root->parent = nil;
   // cout << "Copy Contructor" << endl;

	// Load elements of D into this
   // cout << D.root << endl;
   preOrderCopy(D.root, D.nil);
   // cout << "Test" << endl;
}

// Destructor
Dictionary::~Dictionary(){
   postOrderDelete(root);
}


//**************************************************************************
// Helper functions --------------------------------------------------------
//**************************************************************************

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
   // If there is a seg fault, switch nil to a value instead liek -1
   Node* x = R;
   if(x!=nil){
      inOrderString(s, x->left);
      s += x->key;
      s += " : ";
      s += std::to_string(x->val);
      s += "\n";
      inOrderString(s, x->right);
   }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
   Node* x = R;
   if(x!=nil){
      s += x->key;
      s += "\n";
      preOrderString(s, x->left);
      preOrderString(s, x->right);
   }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
   // cout << "PreOrder" << endl;
   // Node* x = R;
   if(R!=N){
      setValue(R->key, R->val);
      // cout << R->key << " : " << R->val << endl;
      preOrderCopy(R->left, N);
      preOrderCopy(R->right, N);
   }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
   Node* x = R;
   if(x!=nil){
      postOrderDelete(x->left);
      postOrderDelete(x->right);
      remove(x->key);
   }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node *Dictionary::search(Node* R, keyType k) const{
   Node* x = R;
   if(x==nil || k==x->key){
      return x;
   }else if(k < x->key){
      return search(x->left, k);
   }else{ // k > x.key
      return search(x->right, k);
   }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMin(Node* R){
   if(R==nil){
      throw std::logic_error("Dictionary: findMin(): Dictionary is empty");
   }
   Node* x = R;
   while(x->left!=nil){
      x = x->left;      
   }
   return x;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node *Dictionary::findMax(Node* R){
   if(R==nil){
      throw std::logic_error("Dictionary: findMax(): Dictionary is empty");
   }
   Node* x = R;
   while(x->right!=nil){
      x = x->right;      
   }
   return x;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node *Dictionary::findNext(Node* N){
   if(N->right!=nil){
      return findMin(N->right);
   }
   Node* y = N->parent;
   while(y!=nil && N==y->right){
      N = y;
      y = y->parent;
   } 
   return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node *Dictionary::findPrev(Node* N){
   if(N->left!=nil){
      return findMax(N->left);
   }
   Node* y = N->parent;
   while(y!=nil && N==y->left){
      N = y;
      y = y->parent;
   }
   return y;
}

// Transplant()
// Private Helper function to transplant parents
void Dictionary::Transplant(Node* u, Node* v) {
   if(u->parent == nil){
      root = v;
   }else if(u == u->parent->left){
      u->parent->left = v;
   }else{
      u->parent->right = v;
   }
   if(v!=nil){
      v->parent = u->parent;
   }
}

//**************************************************************************
// RBT Helper Functions ----------------------------------------------------
//**************************************************************************
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
   Node* y = N->right;
   N->right = y->left;
   if(y->left!=nil){
      y->left->parent = N;
   }
   y->parent = N->parent;
   if(N->parent==nil){
      root = y;
   }else if(N==N->parent->left){
      N->parent->left = y;
   }else{
      N->parent->right = y;
   }
   y->left = N;
   N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
   Node* y = N->left;
   N->left = y->right;
   if(y->right!=nil){
      y->right->parent = N;
   }
   y->parent = N->parent;
   if(N->parent==nil){
      root = y;
   }else if(N==N->parent->right){
      N->parent->right = y;
   }else{
      N->parent->left = y;
   }
   y->right = N;
   N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
   Node* y;
   // cout << "Test" << endl;
   // cout << "Insert Colors" << N->color << endl;
   while(N->parent->color==RED){
      if(N->parent==N->parent->parent->left){
         y = N->parent->parent->right;
         if(y->color==RED){
            // cout << "InsertFix: Case 1" << endl;
            N->parent->color = BLK;
            y->color = BLK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
         }else{
            if(N==N->parent->right){
               // cout << "InsertFix: Case 2" << endl;
               N = N->parent;
               LeftRotate(N);
            }
            // cout << "InsertFix: Case 3" << endl;
            N->parent->color = BLK;
            N->parent->parent->color = RED;
            RightRotate(N->parent->parent);
         }
      }else{
         y = N->parent->parent->left;
         if(y->color==RED){
            // cout << "InsertFix: Case 4" << endl;
            N->parent->color = BLK;
            y->color = BLK;
            N->parent->parent->color = RED;
            N = N->parent->parent;
         }else{
            if(N==N->parent->left){
               // cout << "InsertFix: Case 5" << endl;
               N = N->parent;
               RightRotate(N);
            }
            // cout << "InsertFix: Case 6" << endl;
            N->parent->color = BLK;
            N->parent->parent->color = RED;
            LeftRotate(N->parent->parent);
         }
      }
      // cout << "Insert Colors: " << N->color << endl;
   }
   root->color = BLK;
   // cout << "RB_Insert Done" << endl;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
   if(u->parent==nil){
      root = v;
   }else if(u==u->parent->left){
      u->parent->left = v;
   }else{
      u->parent->right = v;
   }
   v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
   Node* w;
   // cout << "Delete_Fixup Issue" << endl;
   while((N != root) && (N->color == BLK)){
      if(N == N->parent->left){
         w = N->parent->right;
         if(w->color == RED){
            w->color = BLK;                        // case 1
            N->parent->color = RED;                   // case 1
            LeftRotate(N->parent);                // case 1
            w = N->parent->right;                     // case 1
         }
         if((w->left->color == BLK) && (w->right->color == BLK)){
            w->color = RED;                          // case 2
            N = N->parent;                           // case 2
         }else{
            if(w->right->color == BLK){
               w->left->color = BLK;                // case 3
               w->color = RED;                       // case 3
               RightRotate(w);                   // case 3
               w = N->parent->right;                  // case 3
            }
            w->color = N->parent->color;               // case 4
            N->parent->color = BLK;                // case 4
            w->right->color = BLK;                  // case 4
            LeftRotate(N->parent);                // case 4
            N = root;                             // case 4
         }
      }else{ 
         w = N->parent->left;
         if(w->color == RED){
            w->color = BLK;                        // case 5
            N->parent->color = RED;                   // case 5
            RightRotate(N->parent);               // case 5
            w = N->parent->left;                      // case 5
         }
         if((w->right->color == BLK) && (w->left->color == BLK)){
            w->color = RED;                          // case 6
            N = N->parent;                           // case 6
         }else{ 
            if(w->left->color == BLK){
               w->right->color = BLK;               // case 7
               w->color = RED;                       // case 7
               LeftRotate(w);                    // case 7
               w = N->parent->left;                   // case 7
            }
            w->color = N->parent->color;               // case 8
            N->parent->color = BLK;                 // case 8
            w->left->color = BLK;                   // case 8
            RightRotate(N->parent);               // case 8
            N = root;                             // case 8
         }
      }
   }
   N->color = BLK;

   // while((N!=root)&&(N->color==BLK)){
   //    if(N==N->parent->left){
   //       w = N->parent->right;
   //       // cout << "Delete Color: " << w->color << endl;
   //       if(w->color==RED){
   //          cout << "Fixup Case 1" << endl;
   //          w->color = BLK;
   //          N->parent->color = RED;
   //          LeftRotate(N->parent);
   //          w = N->parent->right;
   //       }
   //       if((w->left->color==BLK)&&(w->right->color==BLK)){
   //          cout << "Fixup Case 2" << endl;
   //          w->color = RED;
   //          N = N->parent;
   //       }else{
   //          if(w->right->color==BLK){
   //             cout << "Fixup Case 3" << endl;
   //             w->left->color = BLK;
   //             w->color = RED;
   //             RightRotate(w);
   //             w = N->parent->right;
   //          }
   //          cout << "Fixup Case 4" << endl;
   //          w->color = N->parent->color;
   //          N->parent->color = BLK;
   //          w->right->color = BLK;
   //          LeftRotate(N->parent);
   //          N = root;
   //       }
   //    }else{
   //       w = N->parent->left;
   //       // cout << "Delete color: " << w->color << endl;
   //       if(w->color==RED){
   //          cout << "Fixup Case 5" << endl;
   //          w->color = BLK;
   //          N->parent->color = RED;
   //          RightRotate(N->parent);
   //          cout << "Test:" << w->right->color << " " << w->left->color << endl;
   //          w = N->parent->left;
   //          cout << "Test:" << w->right->color << " " << w->left->color << endl;
   //          cout << "Poo" << endl;
   //       }
   //       cout << "Test:" << w->right->color << " " << w->left->color << endl;
   //       if((w->right->color==BLK)&&(w->left->color==BLK)){
   //          cout << "Fixup Case 6" << endl;
   //          w->color = RED;
   //          N = N->parent;
   //       }else{
   //          if(w->left->color==BLK){
   //             cout << "Fixup Case 7" << endl;
   //             w->right->color = BLK;
   //             w->color = RED;
   //             LeftRotate(w);
   //             w = N->parent->left;
   //          }
   //          cout << "Fixup Case 8" << endl;
   //          w->color = N->parent->color;
   //          N->parent->color = BLK;
   //          RightRotate(N->parent);
   //          N = root;
   //       }
   //    }
   // }
   // N->color = BLK;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
   Node* x;
   Node* y = N;
   int origin_color = y->color;
   // cout << "Delete Issue" << endl;
   if(N->left==nil){
      // cout << "Delete Case 1" << endl;
      x = N->right;
      RB_Transplant(N, N->right);
   }else if(N->right==nil){
      x = N->left;
      RB_Transplant(N, N->left);
   }else{
      y = findMin(N->right);
      origin_color = y->color;
      x = y->right;
      if(y->parent==N){
         x->parent = y;
      }else{
         RB_Transplant(y, y->right);
         y->right = N->right;
         y->right->parent = y;
      }
      RB_Transplant(N, y);
      y->left = N->left;
      y->left->parent = y;
      y->color = N->color;
   }
   if(origin_color==BLK){
      RB_DeleteFixUp(x);
   }
}


//**************************************************************************
// Access functions --------------------------------------------------------
//**************************************************************************

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
   return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
   Node* x = search(root, k);
   if(x!=nil){
      return true;
   }else{
      return false;
   }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
   if(!contains(k)){
      throw std::logic_error("Dictionary: getValue(): key 'Blah ");
   }

   Node* x = search(root, k);
   return x->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
   if(current==nil){
      return false;
   }else{
      return true;
   }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
   if(hasCurrent()){
      return current->key;
   }else{
      throw std::logic_error("Dictionary: currentKey(): current is not set");
   }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
   if(hasCurrent()){
      return current->val;
   }else{
      throw std::logic_error("Dictionary: currentVal(): current is not set");
   }
}


//**************************************************************************
// Manipulation procedures -------------------------------------------------
//**************************************************************************

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
   postOrderDelete(root);
   root = nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
   Node* y = nil;
   Node* x = root;
   Node* z = new Node(k, v);

   // cout << "setVal first: " << x->val << endl;
   while(x!=nil){ // Tree Traverse
      y = x;
      if(z->key<x->key){
         x = x->left;
      }else if(z->key>x->key){
         x = x->right;
      }else{ // Overwrite
         x->val = v;
         return;
      }
   }
   z->parent = y;
   if(y==nil){
      root = z;
   }else if(z->key<y->key){
      y->left = z;
   }else{
      y->right = z;
   }
   z->left = nil;
   z->right = nil;
   z->color = RED;
   num_pairs++;
   RB_InsertFixUp(z);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
   if(!contains(k)){
      throw std::logic_error("Dictionary: remove(): key does not exist");
   }

   Node* z = search(root, k);
   RB_Delete(z);
   if(z==current){
      current = nil;
   }
   delete z;
   num_pairs--;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
   if(size()>0){
      current = findMin(root);
   }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
   if(size()>0){
      current = findMax(root);
   }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: next(): current does not exist");
   }

   if(current==findMax(root)){
      current = nil;
   }else{
      current = findNext(current);
   }
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
   if(!hasCurrent()){
      throw std::logic_error("Dictionary: next(): current does not exist");
   }

   if(current==findMin(root)){
      current = nil;
   }else{
      current = findPrev(current);
   }
}


//**************************************************************************
// Other Functions ---------------------------------------------------------
//**************************************************************************

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
	string s = "";
   // cout << "To String Root: " << root->key << endl; 
   inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
   string s = "";
   preOrderString(s, root);
   return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool Dictionary::equals(const Dictionary& D) const{
   // Size Check
   if(size()!=D.size()){
      return false;
   }
   // Tree Parsing
   string s1,s2,s3,s4;
   inOrderString(s1, root);
   // cout << s1 << endl;
   // cout << D.root->key << endl;
   D.inOrderString(s2, D.root);
   // cout << s2 << endl;
   // cout << "Equals Test" << endl;
   if(s1!=s2){
      return false;
   }
   preOrderString(s3, root);
   // cout << s3 << endl;
   D.preOrderString(s4, D.root);
   // cout << s4 << endl;
   // cout << "Equals Test" << endl;
   if(s3!=s4){
      return false;
   }

   return true;
}


//**************************************************************************
// Overriden Operators -----------------------------------------------------
//**************************************************************************

// operator<<()
// Inserts string representation of L into stream.
// issue: Const
ostream& operator<<( ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
Dictionary& Dictionary::operator=( const Dictionary& D ){
	// cout << "Operator= Called" << endl;
   if( this != &D ){
		Dictionary temp = D;

		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
   return *this;
}

