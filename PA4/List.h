//-----------------------------------------------------------------------------
// List.h
// CSE101 PA1
// Simon Carballo 
// 1618309
// 01/10/22
//-----------------------------------------------------------------------------


#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include<stdbool.h>

//*****************************************************************************
// Exported type --------------------------------------------------------------
//*****************************************************************************
typedef struct ListObj* List;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// newList()
// Creates and returms a new empty List. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);

//*****************************************************************************
// Access functions -----------------------------------------------------------
//*****************************************************************************

// length()
// Returns the number of elements in L
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// front() 
// Returns front element of L. Pre: length()>0
void *front(List L);

// back() 
// Returns back element of L. Pre: length()>0
void *back(List L);

// get() 
// Returns cursor element of L. Pre: length()>0, index()>=0
void *get(List L);


// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0).
int isEmpty(List L);


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element's data with x. 
void set(List L, void* x);

// moveFront()
// if L is non-empty, sets cursor under the front element, otherwise doese nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing. 
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L;
// If cursor is defined and at back, cursor becomes undefined; 
// If cursor is undefined do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L;
// If cursor is defined and at back, cursor becomes undefined;
// If cursor is undefined do nothing
void moveNext(List L);

// prepend()
// Insert new elemend into L. 
// If L is non-empty, insertion takes place before front elemnt. 
void prepend(List L, void* x); 

// append() 
// Insert new element into L. 
// If L is non-empty, insertion takes place after back element. 
void append(List L, void* x);

// insertBefore() 
// Insert new element before cursor. 
// Pre: lenght()>0, index()>=0
void insertBefore(List L, void* x);

// insertAfter()
// Insert new element after cursor. 
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x); 

// deleteFront()
// Delete the front element.
// Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
// Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. 
// Pre: length()>0, index()>=0 
void delete(List L); 


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************

// printList()
// Prints to the file pointed to by out, a string reprentation of L consisting
// of a space separated sequence of integers, with fron on left. 
void printList(FILE* out, List L);


#endif