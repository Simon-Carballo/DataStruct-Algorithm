//-----------------------------------------------------------------------------
// FindComponents.c
// CSE101 PA3
// Simon Carballo 
// 1618309
// 01/27/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char * argv[]){
   FILE *in, *out;

   // check command line for correct number of arguments
	if( argc != 3 ){
	   printf("Usage: %s <input file> <output file>\n", argv[0]);
	   exit(1);
   }	

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   if( in==NULL ){
	   printf("Unable to open file %s for reading\n", argv[1]);
	   exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
	   printf("Unable to open file %s for writing\n", argv[2]);
	   exit(1);
   }

   int var, u, v;
   fscanf(in, "%d", &var);

   Graph G = newGraph(var);
   List S = newList();
   Graph T = NULL;

   for( int i=1; i<=var; i++) append(S, i);

   while(fscanf(in, "%d %d", &u, &v)){
   	if( (u == 0) && (v == 0) ){
   		break;
   	}
   	addArc(G, u, v);
   }

   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out, G);

   // printf("Size of Graph: %d\n", getOrder(G));
   // printf("Size of List: %d\n", length(S));

   DFS(G, S); // DFS of Graph G
   T = transpose(G);
   DFS(T, S); // DFS of Graph GT

   int scc = 0; // Strongly Connected Components
   for( int x = 1; x <= getOrder(T) ; x++ ){ // Search for null in stack
      if( getParent(T, x) == NIL ){
         scc++;
      }
   }

   fprintf(out, "G contains %d strongly connected components:\n", scc);

   // Topological Sort
   int Row = 1;
   List *Res = calloc(scc+1, sizeof(List)); // Create list for each scc

   for( int i=1; scc>=i ; i++){
      Res[i] = newList(); 
   }

   if( scc>0 ){
      for( moveBack(S); index(S) != -1; movePrev(S) ){ //Start from back of stack to find null parent
         prepend(Res[Row], get(S));
         if( getParent(T, get(S)) == NIL ){ // Null Parent
            Row++;
         }
      }
   }

   // Print the SCC Components
   for( int x=1; scc>=x ; x++ ){
      fprintf(out, "Component %d: ", x);
      printList(out, Res[x]);
      fprintf(out,"\n");
   }

   // Free Lists
   for( int y=0; scc>=y; y++ ){
      freeList(&Res[y]);
   }


   // Free mem
   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}