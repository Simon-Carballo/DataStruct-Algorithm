//-----------------------------------------------------------------------------
// Graph.c
// CSE101 Pa3
// Simon Carballo 
// 1618309
// 04/13/21
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//*****************************************************************************
// structs --------------------------------------------------------------------
//*****************************************************************************

#define WHITE 0
#define GRAY 1
#define BLACK 2


// private GraphObj type
typedef struct GraphObj{
   List* adj;
   int* color;
   int* finishTime;
   int* discoverTime;
   int* parent;
   int order;
   int size;
} GraphObj;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// Graph newGraph()
// returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n){
   int size = n+1;		// fix to account for 0 in List
   Graph G = malloc(sizeof(GraphObj));
   G->adj = calloc(size, sizeof(List));
   G->color = calloc(size, sizeof(int));
   G->finishTime = calloc(size, sizeof(int));
   G->discoverTime = calloc(size, sizeof(int));
   G->parent = calloc(size, sizeof(int));

   int i;
   for(i=1;i<=n;i++){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->finishTime[i] = UNDEF; 
      G->discoverTime[i] = INF;
   }

   G->order = n; 
   G->size = 0;

   return(G);
}

// freeGraph
// frees all dynamic memory associated with the Graph *pG, then sets the handle
// *pG to NULL
// Received assistance in fixing a pointer bug in this function
void freeGraph(Graph* pG){
   if(pG!=NULL && *pG!=NULL) { 
   	Graph G = *pG;

   	for( int i=1; i<=getOrder(G) ; i++){
   		freeList( &(G->adj[i]) );
   	}

      free(G->adj);
      free(G->color); 
      free(G->discoverTime);
      free(G->finishTime);
      free(G->parent);
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
   

   return( G->size );
}

// getParent()
// return the parent of vertex u in the Breadth-First tree created by BFS()
int getParent(Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getParent() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getParent() input index is out of range\n");
      exit(EXIT_FAILURE);
   }
   
   // if( !(1<=u) || !( u<=getOrder(G)) ){
   //    return NIL;
   // } else {
   //    return( G->parent[u] );
   // }
   return( G->parent[u] );
}

// getDicover()
int getDiscover(Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getDist() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getDist() input index is out of range\n");
      exit(EXIT_FAILURE); 
   }
   
   if( !(1<=u) || !( u<=getOrder(G)) ){
      return INF;
   } else {
      return( G->discoverTime[u] );
   }
}

// getFinish()
int getFinish(Graph G, int u){

   if( G==NULL ){
      printf("Graph Error: Calling getPath() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( !(1<=u) && !(u<=getOrder(G)) ){
      printf("Graph Error: getPath() input index is out of range\n");
      exit(EXIT_FAILURE);
   }

   if( !(1<=u) || !( u<=getOrder(G)) ){
      return UNDEF;
   } else {
      return( G->finishTime[u] );
   }
}


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

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

// DFS()
void DFS(Graph G, List S){

   if( G==NULL || S==NULL ){
      printf("Graph Error: Calling DFS() on NULL Graph reference\n");
      exit(EXIT_FAILURE);
   }
   if( length(S) != G->order ){
      printf("Graph Error: Calling DFS() on wrong content size\n");
      exit(EXIT_FAILURE);
   }

	for( int x = 1; x <= getOrder(G); x++){
		G->color[x] = WHITE;
		G->parent[x] = NIL; 
      G->discoverTime[x] = INF;
      G->finishTime[x] = UNDEF;
	}

   int time = 0;

   for(moveFront(S); index(S)>=0; moveNext(S)){
      if( G->color[get(S)] == WHITE ){
         time = Visit(G, S, get(S), time);
      }
   }

   // Remove old values 
   for( int i = 1 ; getOrder(G) >= i; i++ ){
      deleteBack(S);
   }
}


// Visit()
int Visit(Graph G, List S, int u, int time){
   // printf("Visitng @ time %d\n", time);
   time++;
   G->discoverTime[u] = time;
   G->color[u] = GRAY;

   if( length(G->adj[u]) > 0 ){
      for( moveFront(G->adj[u]) ; index(G->adj[u]) >= 0 ; moveNext(G->adj[u]) ){
         // printList(stdout, G->adj[u]);
         // printf("test\n");
         int y = get(G->adj[u]); // Error List Issue
         // printf("Pass %d\n", y);
         if( G->color[y] == WHITE ){
            G->parent[y] = u;
            time = Visit(G, S, y, time);
         }
      }
   }

   G->color[u] = BLACK;
   time++;
   G->finishTime[u] = time;
   prepend(S, u);
   return time;
}


//*****************************************************************************
// Other Functions ------------------------------------------------------------
//*****************************************************************************

// transpose()
Graph transpose(Graph G){
   int size = getOrder(G);
   Graph T = newGraph(size);

   for(int x = 1 ; x <= getOrder(G); x++){
      if(length(G->adj[x]) > 0){
         for(moveFront(G->adj[x]); index(G->adj[x]) != -1 ; moveNext(G->adj[x])){
            addArc(T, get(G->adj[x]), x); // Switch Direction of arc
         }
      }
   }

   return(T); 
}

// copyGraph()
Graph copyGraph(Graph G){
   int size = getOrder(G); 
   Graph N = newGraph(size);

   for( int x = 1 ; getOrder(G) >= x; x++ ){
      if(length(G->adj[x]) > 0){
         for( moveFront(G->adj[x]); index(G->adj[x]) != -1 ; moveNext(G->adj[x])){
            addArc(N, x, get(G->adj[x])); // Same Direction of Arc
         }  
      }
   }

   return(N);
}


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

