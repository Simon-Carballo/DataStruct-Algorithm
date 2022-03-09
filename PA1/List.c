//-----------------------------------------------------------------------------
// List.c
// CSE101 PA1
// Simon Carballo 
// 1618309
// 01/10/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

//*****************************************************************************
// structs --------------------------------------------------------------------
//*****************************************************************************

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor; 
   int length;
   int index;
} ListObj;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL; 
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( length(*pL) > 0 ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


//*****************************************************************************
// Access functions -----------------------------------------------------------
//*****************************************************************************

// length()
// Returns the number of elements in L
int length(List L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L){
   if( L==NULL ){
      printf("List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE); 
   }
   return(L->index);
}

// front()
// Returns front element of L
// Pre: length>0
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);     
   }
   if( L->length==0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->front->data);
}

// back()
// Returns back element of L
// Pre: length>0
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);     
   }
   if( L->length==0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
int get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);     
   }
   if( L->length==0){
      printf("List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->cursor==NULL){
      printf("List Error: calling get() on a NULL cursor reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->cursor->data);
}

// equals()
// Returns (1) iff Lists A and B are in same state, and returns false (0) otherwise 
// MAKE EDIT****: NEEDS TO BE A BOOLEAN
bool equals(List A, List B){
   
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);   
   }
   // if( A->length==0 || B->length==0 ){
   //    printf("List Error: calling equals() on empty List(s)\n");
   //    exit(EXIT_FAILURE);
   // }

   bool eq; 
   Node nodeA = A->front; 
   Node nodeB = B->front;

   // First check if length ==
   eq = ( A->length == B->length );
   if(!eq){
      return false;
   }

   // Loops to make sure each node is equal
   while( eq && nodeA!=NULL ){
      eq = (nodeA->data==nodeB->data);
      nodeA = nodeA->next; 
      nodeB = nodeB->next;
   }
   return eq;
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
   if( L==NULL ){
      printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

// clear()
// Resets L to its original empty state. 
void clear(List L){
   
   if( L==NULL ){
      printf("List Error: calling clear() on non-existant List(s)\n");
      exit(EXIT_FAILURE);
   }

   while( length(L) > 0){
      deleteFront(L);
   }


   L->cursor = L->front = L->back = NULL;
   L->index = -1;
   L->length = 0;
}

// set()
// Overwrites the cursor element's data with x. 
// Pre: length()>0, index()>=0
void set(List L, int x){
   
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      printf("List Error: calling get() on empty List\n");
      exit(EXIT_FAILURE);
   }
   if( L->index < 0 ){
      printf("List Error: calling get() on undefined index reference\n");
      exit(EXIT_FAILURE);
   }

   L->cursor->data = x;
}

// moveFront() 
// If L is non-empty, sets cursor under the front element, otherwise does nothing. 
void moveFront(List L){
   
   if( L==NULL ){
      printf("List Error: calling moveFront() on empty List(s)\n");
      exit(EXIT_FAILURE);
   }

   L->cursor = L->front;
   L->index = 0;
}

// moveBack() 
// If L is nonempty, sets cursor under the back element, otherwise does nothing. 
void moveBack(List L){
   
   if( L==NULL ){
      printf("List Error: calling moveBack() on empty List(s)\n");
      exit(EXIT_FAILURE);
   }
   
   L->cursor = L->back;
   L->index = L->length-1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front on L;
// If cursor is defined and at front, cursor becomes undefined; 
// If cursor is undefined do nothing
void movePrev(List L){
   
   if( L==NULL ){
      printf("List Error: calling moveNext() on empty List(s)\n");
      exit(EXIT_FAILURE);
   }

   if( L->cursor!=NULL ){
      if( L->cursor==L->front ){
         L->cursor = NULL;
         L->index = -1; 
      } else {
         L->cursor = L->cursor->prev;
         L->index--;
      }
   }
}

// moveNext()
// If cursor is defined and not at Back, move cursor one step toward the back on L;
// If cursor is defined and at back, cursor becomes undefined; 
// If cursor is undefined do nothing
void moveNext(List L){
   
   if( L==NULL ){
      printf("List Error: calling moveNext() on empty List(s)\n");
      exit(EXIT_FAILURE);
   }
   
   if( L->cursor!=NULL ){
      if( L->cursor==L->back ){
         L->cursor = NULL;
         L->index = -1;
      } else {
         L->cursor = L->cursor->next;
         L->index++; 
      }
   }
}

// prepend()
// adding in the front
void prepend(List L, int x) {
   if (L == NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node tempNode = newNode(x);
   if (L->length == 0) {
      L->front = tempNode;
      L->back = tempNode;
   } else {
      L->front->prev = tempNode;
      tempNode->next = L->front;
      L->front = tempNode;
      L->index++;
   }
   L->length++;
}

// append() 
// Insert new element into L. 
// If L is non-empty, insertion takes place after element. 
void append(List L, int x){
   
   if( L == NULL ){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node tempNode = newNode(x);

   if( L->length == 0 ){
      L->front = tempNode; 
      L->back = tempNode;
   }else{
      L->back->next = tempNode;
      tempNode->prev = L->back;
      L->back = tempNode;
   }
   L->length++;
}

// insertBefore() 
// Insert new element before cusor. 
// Pre: length()>0, index()>=0
void insertBefore(List L, int x){

   if( L == NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   if( L->cursor == NULL ){
      printf("List Error: calling insertBefore() on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0 ){
      printf("List Error: calling insertBefore() on empty List \n");
   }

   if( L->front == L->cursor ){
      prepend(L, x);
   } else {
      Node tempNode = newNode(x);

      tempNode->next = L->cursor;
      tempNode->prev = L->cursor->prev;
      L->cursor->prev->next = tempNode;
      L->cursor->prev = tempNode;

      L->length++;
      L->index++; 
   }
}

// insertAfter() 
// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int x){

   if( L == NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   } 
   if( L->cursor == NULL ){
      printf("List Error: calling insertAfter() on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if( L->length <= 0 ){
      printf("List Error: calling insertAfter() on empty List \n");
   }

   if( L->back == L->cursor ){
      append(L, x); 
   }else{
      Node tempNode = newNode(x);

      L->cursor->next->prev = tempNode;
      tempNode->next = L->cursor->next;
      tempNode->prev = L->cursor;
      L->cursor->next = tempNode;

      L->length++;
   }
}

// deleteFront()
// delete the front element. 
// Pre: length()>0
void deleteFront(List L){
   
   if( L == NULL ){
      printf("List Error: calling deleteFront() on non-existant List\n");
      exit(EXIT_FAILURE);
   }
   if( !(length(L)>0) ){
      printf("List Error: calling deleteFront() on empty List\n");
      exit(EXIT_FAILURE);
   }

   if( length(L) == 1 ){
      // Node front = L->front;
      Node temp = L->front;
      freeNode(&temp);
      L->cursor = NULL;
      L->front = L->back = NULL;
      L->index = -1;
   }else{
      Node tempNode = L->front;
      L->front = tempNode->next;
      L->front->prev = NULL;

      if( L->cursor != NULL ){
         L->index--;
      }
      freeNode(&tempNode);
   }
   L->length--;
}

// deleteBack()
// Delete the back element. 
// Pre: length()>0, index()>=0
void deleteBack(List L){

   if( L == NULL ){
      printf("List Error: calling deleteBack() on non-existant List\n");
      exit(EXIT_FAILURE);
   }
   if( !(length(L)>0) ){
      printf("List Error: calling deleteBack() on empty List\n");
      exit(EXIT_FAILURE);
   }

   if( L->length == 1 ){
      Node temp = L->back;
      freeNode(&temp);
      L->cursor = NULL;
      L->front = L->back = NULL;
      L->index = -1;
   }else{
      Node tempNode = L->back;
      L->back = tempNode->prev;
      L->back->next = NULL;

      if( L->index == L->length-1 ){
         L->index = -1;
      }
      freeNode(&tempNode);
   }
   L->length--;
}

// delete()
// Deletes the cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L){

   if( L == NULL ){
      printf("List Error: calling delete() on non-existant List\n");
      exit(EXIT_FAILURE);
   } 
   if( L->cursor == NULL ){
      printf("List Error: calling delete() on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if( L->length == 0 ){
      printf("List Error: calling delete() on empty List\n");
      exit(EXIT_FAILURE);
   } 

   // checking by index
   if (L->cursor == L->front) { // head
      deleteFront(L);
   } else if (L->cursor == L->back) { // tail
      deleteBack(L);
   } else { // in the middle
      // Node prev = L->cursor->prev;
      // Node next = L->cursor->next;
      // Node curr = L->cursor;

      // // unlinking
      // prev->next = next;
      // next->prev = prev;
      // freeNode(&curr);
      // freeNode(&prev); 
      // freeNode(&next);

      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;

      
      L->length--;
   }
   // make cursor indefined
   L->cursor = NULL;
   L->index = -1;
}


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************

// printList()
// Prints to the filed pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
   
   if( L==NULL ){
      printf("List Error: calling printList() NULL List reference\n");
      exit(EXIT_FAILURE);
   }

   Node tempNode = NULL;
   for(tempNode = L->front; tempNode!=NULL; tempNode = tempNode->next){
      fprintf(out, "%d " , tempNode->data);
   }
   freeNode(&tempNode);
}


// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new List is undefined, regardless of the states of the cursors in L. 
// The state of L is unchanged
List copyList(List L){
   
   // if( L==NULL ){
   //    printf("List Error: calling copyList() NULL List reference\n");
   //    exit(EXIT_FAILURE);
   // }

   List newL = newList(); 
   Node tempNode = NULL;
   
   if( length(L) > 0 ){
      for(tempNode = L->front; tempNode!=NULL; tempNode = tempNode->next){
      append(newL, tempNode->data);
      }
   }

   L->cursor = NULL;
   L->index = -1;
   
   freeNode(&tempNode);
   return(newL);
}

