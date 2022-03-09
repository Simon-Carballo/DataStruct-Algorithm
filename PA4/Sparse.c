//-----------------------------------------------------------------------------
// Sparse.c
// CSE101 PA4
// Simon Carballo 
// 1618309
// 01/7/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Matrix.h"

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

   int size, a, b, i, j;
   double v;
   fscanf(in, "%d %d %d", &size, &a, &b);

   Matrix A = newMatrix(size);
   Matrix B = newMatrix(size);
   Matrix C, D, E, F, G, H, I, J;

   for(int x=0; x<a; x++){ // Scanning in Entries for Matrix A
      fscanf(in, "%d %d %lf", &i, &j, &v);
      changeEntry(A, i, j, v);
   }
   
   for(int x=0; x<b; x++){ // Scanning in Entries for Matrix B
      fscanf(in, "%d %d %lf", &i, &j, &v);
      changeEntry(B, i, j, v);
   }

   fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
   printMatrix(out, A);
   fprintf(out, "\n");

   fprintf(out , "B has %d non-zero entries:\n", NNZ(B));
   printMatrix(out, B);
   fprintf(out, "\n");

   C = scalarMult(1.5, A);
   fprintf(out, "(1.5)*A =\n");
   printMatrix(out, C);
   fprintf(out, "\n");

   D = sum(A, B);
   fprintf(out, "A+B =\n");
   printMatrix(out, D);
   fprintf(out, "\n");

   E = sum(A, A);
   fprintf(out, "A+A =\n");
   printMatrix(out, E);
   fprintf(out, "\n");

   F = diff(B, A);
   fprintf(out, "B-A =\n");
   printMatrix(out, F);
   fprintf(out, "\n");

   G = diff(A, A);
   fprintf(out, "A-A =\n");
   printMatrix(out, G);
   fprintf(out, "\n");

   H = transpose(A);
   fprintf(out, "Transpose(A) =\n");
   printMatrix(out, H);
   fprintf(out, "\n");

   printf("PRODUCT\n");
   I = product(A, B);
   fprintf(out, "A*B =\n");
   printMatrix(out, I);
   fprintf(out, "\n");

   J = product(B, B);
   fprintf(out, "B*B =\n");
   printMatrix(out, J);

   // Free mem
   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);

   // close files 
   fclose(in);
   fclose(out);

   return(0);
}