//-----------------------------------------------------------------------------
// Matrix.c
// CSE101 PA4
// Simon Carballo 
// 1618309
// 02/2/22
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"
#include "Matrix.h"

//*****************************************************************************
// structs --------------------------------------------------------------------
//*****************************************************************************

// private MatrixObj type
typedef struct MatrixObj{
   List *rows;
   int size;
} MatrixObj;

// private EntryObj type
typedef struct EntryObj{
   int col;
   double val;
} EntryObj;


//*****************************************************************************
// Constructors-Destructors ---------------------------------------------------
//*****************************************************************************

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(Matrix));
    M->rows = calloc(n+1, sizeof(List));
    M->size = n;
    
    // New List for each row
    for(int x=0; x<n; x++){
        M->rows[x] = newList();
    }
    return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
    Matrix M = *pM;
    for(int x=0; x<M->size; x++){
        List L = M->rows[x];
        if(length(L) > 0){
            for(moveFront(L); index(L)>=0; moveNext(L)){
                Entry E = get(L);
                freeEntry(&E);
            }
        }
        freeList(&L);
    }
    free(*pM);
    M = NULL;
    pM = NULL;
}

// newEntry()
// Returns a reference to a new Entry Object for the Matrix
Entry newEntry(int col, double val){
    Entry E = malloc(sizeof(Entry));
    E->col = col;
    E->val = val;

    return E; 
}

// freeEntry()
// Frees heap memory associated with *pE
void freeEntry(Entry *pE){
    free(*pE);
    *pE = NULL;
}

//*****************************************************************************
// Access functions -----------------------------------------------------------
//*****************************************************************************

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    
    return( M->size );
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    // printf("StTEV\n");
    for(int x=0; x<size(M); x++){
        List L = M->rows[x];
        // printf("VALID %d\n", length(L));
        if(length(L)>0 && L!=NULL){
            for(moveFront(L); index(L)>=0; moveNext(L)){
                if(gVal(get(L)) != 0){
                    count++;
                }
            }
            // printf("%d\n", count);
        }
    }

    return count;
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    // Weak Equals Check
    if(size(A) != size(B)){
        return 0;
    }
    if(NNZ(A) != NNZ(B)){
        return 0;
    }
    if(A == B){
        return 1;
    }
    
    // Strong Equals Check
    for(int x=0; x<size(A); x++){
        List AL = A->rows[x];
        List BL = B->rows[x];
        if(length(AL) == length(BL)){
            if(length(AL)>0 && length(BL)>0){
                moveFront(AL);
                moveFront(BL);
                while(index(AL)>=0 && index(BL)>=0){
                    if(gCol(get(AL)) != gCol(get(BL))){
                        return 0;
                    }
                    if(gVal(get(AL)) != gVal(get(BL))){
                        return 0;
                    }
                    moveNext(AL);
                    moveNext(BL);
                }
            }
        }else{
            return 0;
        }

    }
    return 1;
}

// gVal()
// Returns the pointer value of "Value" in Entry
double gVal(Entry E){
    if(E == NULL){
        printf("Entry Error: calling gVal() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return E->val;
}

// gCol()
// Returns the pointer value of "Column" in Entry
int gCol(Entry E){
    if(E == NULL){
        printf("Entry Error: calling gCol() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    return E->col;
}


//*****************************************************************************
// Manipulation procedures ----------------------------------------------------
//*****************************************************************************

// //insert()
// //Adds Entry to the List of Matrix
// void insert(List L, Entry E){
//     if (length(L) == 0){
//         append(L, E);
//     }else{
//         for(moveFront(L); index(L)<=length(L); moveNext(L)){
//             if(gCol(get(L))==E->col){
//                 set(L, E); // Confused how to do this
//                 break;
//             }else if(gCol(get(L))>=E->col){
//                 insertBefore(L, E);
//                 break;
//             }else if(index(L)==length(L)-1){
//                 append(L, E);
//                 break;
//             }
//         }
//     }
// } 

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    for(int x=0; x<size(M); x++){
        M->rows[x] = newList(); // Reset all Lists in the Matrix
    }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if(M == NULL){
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(i<1 || i>size(M)){
        printf("Matrix Error: changeEntry() i is out of range\n");
        exit(EXIT_FAILURE);
    }
    if(j<1 || j>size(M)){
        printf("Matrix Error: changeEntry j is out of range\n");
        exit(EXIT_FAILURE);
    }

    Entry E = newEntry(j, x);
    List L = M->rows[i-1];

    if(length(L)==0){
        append(L, E);
    }else{
        for(moveFront(L); index(L)<=length(L); moveNext(L)){
            if(gCol(get(L))==E->col){
                set(L, E);// Or Set?
                break;
            }else if(gCol(get(L))>=E->col){
                insertBefore(L, E);
                break;
            }else if(index(L)==length(L)-1){
                append(L, E);
                break;
            }
        }
    }

}


//*****************************************************************************
// Arithmetic Operations ------------------------------------------------------
//*****************************************************************************

// addList()
// Returns In order sort of adding two lists
List addList(List L, List M){
    if(L==NULL || M==NULL){
        printf("Matrix Error: calling addList() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    // L: 1.1 2.2 4.4
    // M: 1.1 3.3 4.4 7.7 8.8 

    // S: 1.2 2.2 3.3 4.8 5.5 7.7 8.8 

    List S = newList();
    if(length(L)==0 && length(M)==0){
        return S;
    }else if(length(L)==0 && length(M)>0){
        moveFront(M);
        while(index(M)>=0){
            append(S, newEntry(gCol(get(M)), gVal(get(M))));
            moveNext(M);
        }
        return S;
    }else if(length(L)>0 && length(M)==0){
        moveFront(L);
        while(index(L)>=0){
            append(S, newEntry(gCol(get(L)), gVal(get(L))));
            moveNext(L);        
        }
        return S;
    }else{
        moveFront(L);
        moveFront(M);
        while(index(L)>=0 && index(M)>=0){
            // printf("Test\n");
            if(gCol(get(L)) == gCol(get(M))){
                append(S, newEntry(gCol(get(L)), gVal(get(L)) + gVal(get(M))));
                moveNext(L);
                moveNext(M);
            }else if(gCol(get(L)) < gCol(get(M))){
                append(S, newEntry(gCol(get(L)), gVal(get(L))));
                moveNext(L);
            }else if(gCol(get(L)) > gCol(get(M))){
                append(S, newEntry(gCol(get(M)), gVal(get(M))));
                moveNext(M);
            }
            // printf("Finish\n");
        }
        while(index(L)>=0){
            append(S, newEntry(gCol(get(L)), gVal(get(L))));
            moveNext(L);        
        }
        while(index(M)>=0){
            append(S, newEntry(gCol(get(M)), gVal(get(M))));
            moveNext(M);
        }
        return S;
    }
}

// subList()
// Returns In order sort of adding two lists
List subList(List L, List M){
    if(L==NULL || M==NULL){
        printf("Matrix Error: calling subList() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    List S = newList();
    // printf("lengths %d | %d\n", length(L), length(M));
    if(length(L)==0 && length(M)==0){
        return S;
    }else if(length(L)==0 && length(M)>0){
        moveFront(M);
        while(index(M)>=0){
            append(S, newEntry(gCol(get(M)), 0 - gVal(get(M))));
            moveNext(M);
        }
        return S;
    }else if(length(L)>0 && length(M)==0){
        moveFront(L);
        while(index(L)>=0){
            append(S, newEntry(gCol(get(L)), gVal(get(L))));
            moveNext(L);        
        }
        return S;
    }else{
        moveFront(L);
        moveFront(M);
        while(index(L)>=0 && index(M)>=0){
            // printf("Test\n");
            if(gCol(get(L)) == gCol(get(M))){
                // double temp = gVal(get(L)) - gVal(get(M));
                // printf("L Val = %.1f ", gVal(get(L)));
                // printf("M Val = %.1f ", gVal(get(M)));
                // printf("L-M=%.1f\n", temp);
                append(S, newEntry(gCol(get(L)), gVal(get(L)) - gVal(get(M))));
                moveNext(L);
                moveNext(M);
            }else if(gCol(get(L)) < gCol(get(M))){
                append(S, newEntry(gCol(get(L)), gVal(get(L))));
                moveNext(L);
            }else if(gCol(get(L)) > gCol(get(M))){
                append(S, newEntry(gCol(get(M)), 0 - gVal(get(M))));
                moveNext(M);
            }
            // printf("Finish\n");
        }
        while(index(L)>=0){
            append(S, newEntry(gCol(get(L)), gVal(get(L))));
            moveNext(L);        
        }
        while(index(M)>=0){
            append(S, newEntry(gCol(get(M)), 0 - gVal(get(M))));
            moveNext(M);
        }
        return S;
    }
}

// dot()
// Return the dot product of the two lists taken from the Matrix
double dot(List L, List M){
    if(L==NULL || M==NULL){
        printf("Entry Error: calling dot() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    double s = 0;
    moveFront(L);
    moveFront(M);
    while(index(L)>=0 && index(M)>=0){
        if(gCol(get(L)) == gCol(get(M))){
            s += (gVal(get(L)) * gVal(get(M)));
            moveNext(L);
            moveNext(M);
            // printf("sum:%.1lf", s);
        }else if(gCol(get(L)) < gCol(get(M))){
            moveNext(L);
        }else if(gCol(get(L)) > gCol(get(M))){
            moveNext(M);
        }
    }
    // printf("Tot: %.1lf\n");
    return s;
}

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if(A == NULL){
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix N = newMatrix(size(A));

    for(int i = 0; i<size(A); i++){
        List L = A->rows[i];
        if(length(L)>0){
            for(moveFront(L); index(L)>=0; moveNext(L)){
                changeEntry(N, i+1, gCol(get(L)), gVal(get(L)));
            }
        }
    }

    return N;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if(A == NULL){
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix T = newMatrix(size(A));

    for(int i = 0; i<size(A); i++){
        List L = A->rows[i];
        if(length(L)>0){
            for(moveFront(L); index(L)>=0; moveNext(L)){
                changeEntry(T, gCol(get(L)), i+1, gVal(get(L)));
            }
        }
    }

    return T;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if(A == NULL){
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));

    for(int i=0; i<size(M); i++){
        List L = A->rows[i];
        if(length(L)>0){
            for(moveFront(L); index(L)>=0; moveNext(L)){
                double temp = gVal(get(L)) * x;
                // printf("%.1lf\n", temp);
                changeEntry(M, i+1, gCol(get(L)), temp);
                // printf("changeEntry(M, %d, %d, %.1lf", i, gCol(get(L)), temp);                 
            }
            // printMatrix(stdout, M);
        }
    }
    return M;
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
        printf("Matrix Error: sum() size of Matrix A & B are not equivalent\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));
    // Add Scalar for A==B case
    if(A==B){
        M = scalarMult(2, A);
        return M;
    }
    for(int i=0; i<size(A); i++){
        if(M->rows[i] == NULL){
            break;
        }
        // printf("%d Row\n", i);
        M->rows[i] = addList(A->rows[i], B->rows[i]);
    }
    return M;
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Matrix Error: calling diff() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
        printf("Matrix Error: diff() size of Matrix A & B are not equivalent\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));
    if(A==B){
        return M;
    }
    
    for(int i=0; i<size(A); i++){
        // List LA = A->rows[i];
        // List LB = B->rows[i];
        // if(length(LA)>0 && length(LB)>0){
        //     M->rows[i] = subList(LA, LB);
        // }else if(length(LA)>0 && length(LB)==0){
        //     M->rows[i] = LA;
        // }else if(length(LA)==0 && length(LB)>0){
        //     M->rows[i] = LB;
        // }
        if(M->rows[i] == NULL){
            break;
        }
        M->rows[i] = subList(A->rows[i], B->rows[i]);
    }
    return M;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B){
    if(A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if(size(A) != size(B)){
        printf("Matrix Error: sum() size of Matrix A & B are not equivalent\n");
        exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));
    Matrix T = transpose(B);
    // printMatrix(stdout,A);
    // printMatrix(stdout,T);
    int i = 0;
    int j = 0;

    for(i=0; i<size(A); i++){ // Parse through Matrix A
        List LA = A->rows[i];
        if(length(LA)>0){
            for(j=0; j<size(T); j++){ // Parse through Matrix B transpose (T)
                List LT = T->rows[j];
                if(length(LT)>0){
                    double x = dot(LA, LT);
                    changeEntry(M, i+1, j+1, x);
                    // printf("Change Entry: M, %d, %d, %.1lf\n", i+1, j+1, x);
                }
            }
        }    
    }
    return M;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    if(M == NULL){
        printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }

    for(int x=0; x<size(M); x++){
        List L = M->rows[x];
        if(length(L)>0){
            printf("%d",length(L));
            fprintf(out, "%d:", x+1);
            for(moveFront(L); index(L)>=0; moveNext(L)){
                if(gVal(get(L))!=0){
                    fprintf(out, " (%d, %.1f)", gCol(get(L)), gVal(get(L)));
                }
            }
            fprintf(out,"\n");
        }
    }
}
