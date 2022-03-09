//-----------------------------------------------------------------------------
// FindPath.c
// CSE101 PA2
// Simon Carballo 
// 1618309
// 01/15/22
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

   while(fscanf(in, "%d %d", &u, &v)){
   	if( (u == 0) && (v == 0) ){
   		break;
   	}
   	addEdge(G, u, v);
   }

   // Graph Print
   printGraph(out, G);

   int x, y;
   List temp = newList();
   while(fscanf(in, "%d %d", &x, &y)){
      if( (x != 0) && (y != 0) ){ // Dummy Line Handele
         BFS(G, x);
         getPath(temp, G, y);
         if(getDist(G, y)==INF){     // If Dist is INF
            fprintf(out, "The distance from %d to %d is infinity\n", x, y);
            fprintf(out, "No %d-%d path exists\n\n", x, y);
         } else {
            fprintf(out, "The distance from %d to %d is %d\n", x, y, getDist(G, y));
            fprintf(out, "A shortest %d-%d path is: ", x, y);
            printList(out, temp);
            fprintf(out,"\n\n");
         }
         clear(temp);
      }else{
         break;
      }
   }

   // close & Free
   freeList(&temp);
   freeGraph(&G);
   fclose(in);
   fclose(out);

   return(0);
}