//-----------------------------------------------------------------------------
// Graph.h
// CSE101 PA2
// Simon Carballo 
// 1618309
// 01/15/22
//-----------------------------------------------------------------------------


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

//*****************************************************************************
// Macros --------------------------------------------------------------
//*****************************************************************************

#define INF -2
#define NIL -1
#define WHITE 0
#define GRAY 1
#define BLACK 2


//*****************************************************************************
// Exported type --------------------------------------------------------------
//*****************************************************************************

typedef struct GraphObj* Graph;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// Graph newGraph()
// returns a Grapg pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n);

// freeGraph
// frees all dynamic memory associated with the Graph *pG, then sets the handle
// *pG to NULL
void freeGraph(Graph* pG);


//*****************************************************************************
// Access functions -----------------------------------------------------------
//*****************************************************************************


// getOrder()
// retun the corresponding field values
int getOrder(Graph G);

// getSize()
// Return the corresponding field values
int getSize(Graph G); 

// getSource() 
// returns the source vertex most recently used in dunction BFS(),
// or NULL if BFS() has not yet been created.
int getSource(Graph G);

// getParent()
// return the parent of vertex u in the Breadth-First tree created by BFS()
// NULL if BFS() not yet has not yet been called. 
int getParent(Graph G, int u);

// getDist()
// returns the distance from the most recent BFS source to vertex u
// INF if BFS() has not yet been called
int getDist(Graph G, int u);

// getPath()
// appends to the List L the verticies of a shortest path in G from source to u
// or appends to L the value NULL if no such path exists.
void getPath(List L, Graph G, int u);


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************


// makeNull()
// deletes all edges of G, restoring it to its original state
void makeNull(Graph G);

// addEdge()
// insets a new edge joining u to v
// u is added to the adjecency List of v, and v to the adjacency list of v
// Pre: range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v
// v is added to the adcency list of u
// Pre: Range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly
void BFS(Graph G, int s); 


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************


// printGraph()
// prints the adjecency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif