//-----------------------------------------------------------------------------
// Lex.c
// CSE101 PA1
// Simon Carballo 
// 1618309
// 01/11/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   FILE *in, *out;

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

   // Initialize Variables
   int line_count, index_count, x, temp;
   char line[MAX_LEN];
   //char* token;

   line_count = 0;

   // Preliminary Read to get total lines for array size
   while( fgets(line, MAX_LEN, in) != NULL){
      line_count++;
   }
   rewind(in);
   printf("Line_Count: %d\n", line_count);

   // Create new String Array
   char** arr = calloc(line_count, sizeof(char*));
   for (int i = 0; i<line_count; i++){
      arr[i] = calloc(MAX_LEN, sizeof(char));
   }
   // read each line of input file
   for(index_count = 0; index_count < line_count; index_count++) {
      fgets(line, MAX_LEN, in);
      strcpy(arr[index_count], line);
      // arr[index_count] = line;
      printf("Array[%d]: %s", index_count, arr[index_count]);
   }

   for(int v = 0; v<index_count; v++){
      printf("GG: %s", arr[v]);
   }
   // Create a new List
   List L = newList();
   append(L, 0);
   moveFront(L);

   // strCMP Test
   printf("Index_Count: %d\n", index_count);
   printf("Comparing %s and %s", arr[4], arr[1]);
   if(strcmp(arr[4], arr[1]) < 0){
      printf("strcmp Working\n");
   }else{
      printf("strcmp Not Working\n");
   }

   // Main sorting algorithm
   for(int i = 1; i < index_count ; i++){
      for(moveFront(L); index(L) != -1 ; moveNext(L)){
         if(strcmp(arr[i], arr[get(L)]) < 0){ // if s1 comes before s2
            insertBefore(L, i);
            printf("Before\n");
            break;
         } else if(index(L) == length(L)-1){
            append(L, i);
            printf("Append\n");
            break;
         } else if(strcmp(arr[i], arr[get(L)]) == 0){
            insertAfter(L, i);
            printf("Equals\n");
            break;
         }
      }
   }


   // for(int i = 1; i < index_count-1 ; i++ ){ // for each index run a loop to compare the strings in the array
   //    for(int j = 0; j!=length(L) ; j++ ){ // nested for loop to iterate through existing List index data
   //       if(strcmp(arr[i], arr[get(L)]) < 0){ // s1 comes before s2
   //          if(strcmp(arr[i], arr[i+1]) < 0){ // check next
   //             insertAfter(L, i);
   //          }else{
   //             continue;
   //          }
   //       } else if( strcmp(arr[i], arr[get(L)])>0){ // s1 comes after s2
   //          if(strcmp(arr[i], arr[i+1])<0){ // check next
   //             insertAfter(L, i);
   //          }else{
   //             continue;
   //          }
   //       } else {
   //          insertAfter(L, i);
   //       }
   //       moveNext(L);
   //    }
   //    moveFront(L);
   // }

   // printList(out, L);
   //Write to file loop
   for(moveFront(L); index(L) != -1; moveNext(L)){
      temp = get(L);
      fprintf(out, "%s", arr[temp]);
   }

   // close files 
   fclose(in);
   fclose(out);
   free(arr);
   freeList(&L);

   return(0);
}