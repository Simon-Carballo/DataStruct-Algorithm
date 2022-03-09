//-----------------------------------------------------------------------------
// Graph.h
// CSE101 PA3
// Simon Carballo 
// 1618309
// 01/27/22
//-----------------------------------------------------------------------------


#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"

#define INF -2
#define NIL 0
#define UNDEF -2

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

// getParent()
// return the parent of vertex u in the Breadth-First tree created by BFS()
// NULL if BFS() not yet has not yet been called. 
int getParent(Graph G, int u);

// getDiscover()
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

// addEdge()
// insets a new edge joining u to v
// u is added to the adjecency List of v, and v to the adjacency list of v
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v);

// addArc()
// inserts a new directed edge from u to v
// v is added to the adcency list of u
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v);

// DFS()
// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S); 

//Visit()
int Visit(Graph G, List S, int u, int time);


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************

// transpose()
Graph transpose(Graph G);

// copyGraph()
Graph copyGraph(Graph G);

// printGraph()
// prints the adjecency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G);

#endif