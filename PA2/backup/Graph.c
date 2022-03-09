//-----------------------------------------------------------------------------
// Graph.c
// CSE101 PA2
// Simon Carballo 
// 1618309
// 01/15/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//*****************************************************************************
// structs --------------------------------------------------------------------
//*****************************************************************************


// private GraphObj type
typedef struct GraphObj{
   List* adj;
   int* color;
   int* distance;
   int* parent;
   int order;
   int size;
   int source;
} GraphObj;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// Graph newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n){
   n++;		// fix to account for 0 in List
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc(n, sizeof(List));
   G->color = calloc(n, sizeof(int));
   G->distance = calloc(n, sizeof(int));
   G->parent = calloc(n, sizeof(int));

   int i;
   for(i=1; i<=n; i++){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }

   G->order = n-1; 
   G->size = 0; 
   G->source = NIL;

   return(G);
}

// freeGraph
// frees all dynamic memory associated with the Graph *pG, then sets the handle
// *pG to NULL
// Received assistance in fixing a pointer bug in this function
void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL) { 
   	Graph p = *pG;
   	for( int i=1; i<=getOrder(p) ; i++){
   		freeList( &(p->adj[i]) );
   	}
      free(p->adj);
      free(p->color); 
      free(p->distance);
      free(p->parent);
      free(*pG);
      *pG = NULL;
   }
}


//*****************************************************************************
// Access functions -----------------------------------------------------------
//*****************************************************************************

// getOrder()
// retun the number of vertices in the graph
int getOrder(Graph G){

   if( G==NULL ){
      printf("Graph Error: calling getOrder() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   return( G->order );
}

// getSize()
// Return the number of edges in the graph
int getSize(Graph G){

   if( G==NULL ){
      printf("Graph Error: Calling getSize() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   
   // if( (G->source) == NIL ){
   //    return NIL;
   // } else {
   //    return( G->size );
   // }

   return( G-> size );
}

// getSource() 
// returns the source vertex most recently used in dunction BFS(),
// or NULL if BFS() has not yet been created.
int getSource(Graph G){

   if( G==NULL ){
      printf("Graph Error: Calling getSource() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   return( G->source );
}


// getParent()
// return the parent of vertex u in the Breadth-First tree created by BFS()
// NULL if BFS() not yet has not yet been called. 
int getParent(Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getParent() input index is out of range\n");
      exit(EXIT_FAILURE);
   }
   
   if( G->source == NIL ){
      return NIL;
   } else {
      return( G->parent[u] );
   }
}

// getDist()
// returns the distance from the most recent BFS source to vertex u
// Returns NIL if BFS() has not yet been called
int getDist(Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getDist() input index is out of range\n");
      exit(EXIT_FAILURE); 
   }
   
   if( G->source == NIL ){
      return INF;
   } else {
      return( G->distance[u] );
   }
}

// getPath()
// appends to the List L the verticies of a shortest path in G from source to u
// or appends to L the value NULL if no such path exists.
void getPath(List L, Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getPath() input index is out of range\n");
      exit(EXIT_FAILURE);
   }
   if( getSource(G) == NIL ){
      printf("Graph Error: BFS() has not been run\n");
      exit(EXIT_FAILURE);
   }

   if (G->source == u){
      append(L, u);
   }else if(G->parent[u] == NIL){
      append(L, NIL);
   }else{
      getPath(L, G, G->parent[u]);
      append(L, u);
   }
}


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

// makeNull()
// deletes all edges of G, restoring it to its original state
void makeNull(Graph G){
   for(int i=1; getOrder(G)>= 0 ; i++){
      clear(G->adj[i]);
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }

   G->size = 0; 
   G->source = NIL; 
}

// addEdge()
// insets a new edge joining u to v
// u is added to the adjecency List of v, and v to the adjacency list of v
// Pre: range 1 to getOrder(G)
void addEdge(Graph G, int u, int v){

   if(!(1<=u) && !(u<=getOrder(G))){
      printf("Graph Error: Calling addEdge() input index is out of range\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=v) && !(v<=getOrder(G)) ){
   	printf("Graph Error: Calling getEdge() input index is out of range\n");
      exit(EXIT_FAILURE);
   }

   addArc(G, u, v);
   addArc(G, v, u);

   G->size--;
}

// addArc()
// inserts a new directed edge from u to v
// v is added to the adcency list of u
// Pre: Range 1 to getOrder(G)
void addArc(Graph G, int u, int v){

	if( G==NULL ){
		printf("Graph Error: Calling addArc() on NULL Graph Reference\n");
		exit(EXIT_FAILURE);
	}
   if(!(1<=u) && !(u<=getOrder(G))){
      printf("Graph Error: Calling addArc() input index is out of range\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=v) && !(v<=getOrder(G)) ){
      printf("Graph Error: Calling getArc() input index is out of range\n");
      exit(EXIT_FAILURE);
   }


   if( length(G->adj[u]) == 0 ){    // First Input Case
      append(G->adj[u], v);
      // printf("appending %d\n", v);
   } else {
      // printf("Else %d\n", v);
      for(moveFront(G->adj[u]); index(G->adj[u])<=length(G->adj[u]) ; moveNext(G->adj[u]) ){ // Parsing through for numerical order
         if(get(G->adj[u]) >= v){
            insertBefore(G->adj[u], v);
            break;
         }else if (index(G->adj[u]) == length(G->adj[u])-1) {
            append(G->adj[u], v);
            break;
         }
      }
   }

   G->size++;
}

// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent,
// and source fields of G accordingly  
// Based on psuedo code
void BFS(Graph G, int s){

   if( G==NULL ){
      printf("Graph Error: Calling BFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

	for( int x = 1; getOrder(G) >= x ; x++){
		G->color[x] = WHITE;
		G->distance[x] = INF;
		G->parent[x] = NIL; 
	}

   G->source = s;
	G->color[s] = GRAY;
	G->distance[s] = 0;
	G->parent[s] = NIL;

	List Queue = newList();
	append(Queue, s); 

	while( length(Queue)>=1 ){		// parse through Queue List
		int x = front(Queue);    // Dequeue 
		deleteFront(Queue);

      List adjList = G->adj[x];
      // printf("test\n");
		moveFront(adjList);

      for(int y = 0; y <= length(adjList)-1; y++){
         int t = get(adjList);
         if( G->color[t] == WHITE ){
            G->color[t] = GRAY;
            G->distance[t] = G->distance[x]+1;
            G->parent[t] = x;
            append(Queue, t);
         }
         moveNext(adjList);
      } 
		G->color[x] = BLACK;
	}
   freeList(&Queue);
}


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************

// printGraph()
// prints the adjecency list representation of G to the file pointed to by out
void printGraph(FILE* out, Graph G){

   if( G==NULL ){
      printf("Graph Error: Calling printGraph() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }

   for( int x=1; getOrder(G)>=x ; x++ ){
      fprintf(out, "%d: ", x);
      printList(out, G->adj[x]);
      fprintf(out,"\n");
   }
   fprintf(out, "\n");
}

