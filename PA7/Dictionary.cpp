//-----------------------------------------------------------------------------
// Dictionary.cpp
// CSE101 PA7
// Simon Carballo
// 1618309
// 03/1/22
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<stdexcept>
#include<climits>
#include"Dictionary.h"

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
      throw std::logic_error("Dictionary: getValue(): Does not contain k");
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
   num_pairs++;
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
   if(z->left==nil){
      Transplant(z, z->right);
      // if(z->parent==nil){
      //    root = z->right;
      // }else if(z==z->parent->left){
      //    z->parent->left = z->right;
      // }else{
      //    z->parent->right = z->right;
      // }
      // if(z->right!=nil){
      //    z->right->parent = z->parent;
      // }
   }else if(z->right==nil){
      Transplant(z, z->left);
      // if(z->parent==nil){
      //    root = z->left;
      // }else if(z==z->parent->left){
      //    z->parent->left = z->left;
      // }else{
      //    z->parent->right = z->left;
      // }
      // if(z->left!=nil){
      //    z->left->parent = z->parent;
      // }
   }else{
      Node* y = findMin(z->right);
      if(y->parent!=z){
         Transplant(y, y->right);
         y->right = z->right;
         y->right->parent = y;
      }
      Transplant(z, y);
      y->left = z->left;
      y->left->parent = y;
   }
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

