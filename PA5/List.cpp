//-----------------------------------------------------------------------------
// List.cpp
// CSE101 PA5
// Simon Carballo
// 1618309
// 01/10/21
//-----------------------------------------------------------------------------

#include<string>
#include<iostream>
#include<stdexcept>
#include<climits>
#include"List.h"

using namespace std;

//**************************************************************************
// Private Constructor -----------------------------------------------------
//**************************************************************************

// Node Constructor
List::Node::Node(ListElement x){
	data = x;
	next = nullptr; 
	prev = nullptr;
}


//**************************************************************************
// Class Constructors & Destructors ----------------------------------------
//**************************************************************************

// Creates new List in the empty state.
List::List(){
	frontDummy = new Node(INT_MIN); // Max Ints
	backDummy = new Node(INT_MAX);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L){
	// cout << "Constructor Called" << endl;
	// make this an empty List
	frontDummy = new Node(INT_MIN); // Max Ints
	backDummy = new Node(INT_MAX);
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;

	// Load elements of L into this
	Node* N = L.frontDummy->next;
	for(int x=0; x<L.num_elements; x++){
		this->insertBefore(N->data);
		N = N->next;
	}
}

// Destructor
List::~List(){
	clear();
	delete frontDummy;
	delete backDummy;
	// moveFront();
	// while(num_elements != 0){
	// 	eraseAfter();
	// }
}

//**************************************************************************
// Access functions --------------------------------------------------------
//**************************************************************************

// size()
// Returns the size of this List.
int List::length() const{
	return( num_elements );
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
	if(num_elements<=0){
		throw std::length_error("List: front(): empty List");
	}

	return(frontDummy->next->data);
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
	if(num_elements<=0){
		throw std::length_error("List: back(): empty List");
	}

	return(backDummy->prev->data);
}

// position()
// Returns the position of the cursor in this List. The value returned
// will be in the range 0 to size().
int List::position() const{
	return( pos_cursor );
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<size()
ListElement List::peekNext() const{
	if(pos_cursor>=num_elements){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	
	return(afterCursor->data);
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
	if(pos_cursor<=0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	
	return(beforeCursor->data);
}

//**************************************************************************
// Manipulation procedures -------------------------------------------------
//**************************************************************************

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
	moveFront();
	while( num_elements != 0 ){
		eraseAfter();
	}

	beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;

	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position size() in this List.
void List::moveBack(){
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;

	pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<size() 
ListElement List::moveNext(){
	if(pos_cursor>=num_elements){
		throw std::range_error("List: moveNext(): cursor at back");
	}

	beforeCursor = beforeCursor->next;
	afterCursor = afterCursor->next;
	pos_cursor++;

	return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
	if(pos_cursor<=0){
		throw std::range_error("List: movePrev(): cursor at front");
	}

	beforeCursor = beforeCursor->prev;
	afterCursor = afterCursor->prev;
	pos_cursor--;

	return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
	Node* tempNode = new Node(x);

	// cout << "InsertAfter: " << tempNode->data << endl;
	tempNode->next = afterCursor;
	tempNode->prev = beforeCursor;
	// cout << "TEST" << endl;

	afterCursor->prev = tempNode;
	beforeCursor->next = tempNode;

	afterCursor = tempNode;
	num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
	Node* tempNode = new Node(x);

	// cout << "InsertBefore: " << tempNode->data << endl;

	tempNode->next = afterCursor;
	tempNode->prev = beforeCursor;

	beforeCursor->next = tempNode;
	afterCursor->prev = tempNode;

	beforeCursor = tempNode;
	num_elements++;
	pos_cursor++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
	if(pos_cursor>=num_elements){
		throw std::range_error("List: setAfter(): cursor at back");
	}

	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
	if(pos_cursor<=0){
		throw std::range_error("List: setBefore(): cursor at front");
	}

	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<size()
void List::eraseAfter(){
	if(pos_cursor>=num_elements){
		throw std::range_error("List: eraseAfter(): cursor at back");
	}

	Node* tempNode = afterCursor;

	if( num_elements == 1 ){
		delete tempNode; 
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		pos_cursor = 0;
	} else {
		afterCursor = afterCursor->next;
		beforeCursor->next = afterCursor;
		afterCursor->prev = beforeCursor;
		delete tempNode;
	}
	num_elements--;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
	if(pos_cursor<=0){
		throw std::range_error("List: eraseBefore(): cursor at front");
	}

	Node* tempNode = beforeCursor;

	if( num_elements == 1 ){
		delete tempNode; 
		beforeCursor = frontDummy;
		afterCursor = backDummy;
		frontDummy->next = backDummy;
		backDummy->prev = frontDummy;
		pos_cursor = 0;
	} else {
		beforeCursor = beforeCursor->prev;
		afterCursor->prev = beforeCursor;
		beforeCursor->next = afterCursor; 
		delete tempNode;
		pos_cursor--;
	}
	num_elements--;
}


//**************************************************************************
// Other Functions ---------------------------------------------------------
//**************************************************************************

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of the element x.
// If x is found, places the cursor immediately after the found element (so 
// eraseBefore() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position size(),
// and returns -1. 
int List::findNext(int x){
	while( afterCursor->data != x ){
		if( pos_cursor == num_elements ){
			break;
		}else{
			moveNext();
		}
	}

	if( afterCursor->data == x ){
		this->moveNext();
		return( pos_cursor );
	}else{
		return -1;
	}
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of the element x.
// If x is found, places the cursor immediately before the found element (so 
// eraseAfter() would remove the found element), and returns the final 
// cursor position. If x is not found, places the cursor at position 0, and 
// returns -1. 
int List::findPrev(int x){
	while( beforeCursor->data != x ){
		if( pos_cursor == 0 ){
			break;
		}else{
			movePrev();
		}
	}

	if( beforeCursor->data == x ){
		this->movePrev(); 
		return( pos_cursor );
	}else{
		return -1;
	}
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique data
// values. The order of the remaining elements is obtained by retaining
// the frontmost occurrance of each element, and removing all other 
// occurances. The cursor is not moved with respect to the retained 
// elements, i.e. it lies between the same two retained elements that it 
// did before cleanup() was called.
void List::cleanup(){
	Node* N = frontDummy->next;
	int count = 0;

	for(int x = 0; x < num_elements; x++){
		Node* M = N->next;
		count = num_elements;
		// cout << "Instance: " << N->data << endl;
		for(int j = x+1; j < count; j++){
			// cout << "Comparing: " << M->data << endl;
			if(N->data == M->data){
				// cout << "Deleting Repeat" << endl;
				if(M == afterCursor){
					afterCursor = M->next;
				}else if(M == beforeCursor){
					beforeCursor = M->prev;
					pos_cursor--; // Cursor Position Error From here
				}
				// Cursor Corrector
				// cout << "Test:" << pos_cursor << " " << j << endl;
				if(pos_cursor>j-1){
					pos_cursor--;
				}
				// Relinkuing Dropped Node
				M->next->prev = M->prev;
				M->prev->next = M->next;
				num_elements--;
				delete M;
			}
			M = M->next;
		}
		N = N->next;
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed
// the elements of L. The returned List's cursor will be at its front
// (position 0).
List List::concat(const List& L) const{
	List T;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;

	for(int x=0; x<this->num_elements; x++){
		T.insertBefore(N->data);
		N = N->next;
	}

	for(int x=0; x<L.num_elements; x++){
		T.insertBefore(M->data);
		M = M->next;
	}

	T.moveFront();
	return T;
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
	Node* N = nullptr;
	string s = " ";

	s += "(";
	N = frontDummy->next;
	for(int x = 0; x < num_elements; x++){
		s += std::to_string(N->data);
		// cout << "Data Check:" << N->data << endl;
		if(x<num_elements-1){
			s += ", ";
		}
		N = N->next;
	}
	s += ")";

	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = ( this->num_elements == R.num_elements);
	N = this->frontDummy->next;
	M = R.frontDummy;
	M = M->next;

	while( eq && N != nullptr ){
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}

	return eq;
}


//**************************************************************************
// Overriden Operators -----------------------------------------------------
//**************************************************************************

// operator<<()
// Inserts string representation of L into stream.
ostream& operator<<( ostream& stream, const List& L ){
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged are unchanged.
bool operator==( const List& A, const List& B ){
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
	// cout << "Operator= Called" << endl;
	if( this != &L ){
		List temp = L;

		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}

