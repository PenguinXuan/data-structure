//Zhuoxuan Wang
//CruzID: zwang437
//PA 2

//-----------------------------------------------------------------------------
// Matrix.c
// Implementation file for Matrix ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include"List.h"

#define MAXSIZE 100000
double vectorDot(List P, List Q);

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj{
    int column;
    double value;
}EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj{
    List rows[MAXSIZE];
    int NNZ;
    int size;
    
}MatrixObj;


// Constructors-Destructors ---------------------------------------------------

// newEntry()
// Returns reference to new Entry object. Initializes column and value fields.
// Private.
Entry newEntry(double entry_value, int c) {
    Entry E = malloc(sizeof(EntryObj));
    E->column = c;
    E->value = entry_value;
    return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
// Private.
void freeEntry(Entry* pE){
    if(pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    for (int i = 1; i <= n; i++)
    {
        M->rows[i] = newList();
    }
    
    M->size = n;
    M->NNZ = 0;
    return(M);
    
}


// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){   // not finished
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= size((*pM)); i++)
        {
            if (length((*pM)->rows[i]) > 0)
            {
                moveFront((*pM)->rows[i]);
                for (int j = 1; j <= length((*pM)->rows[i]); j++)
                {
                    if (index((*pM)->rows[i]) >= 0)
                    {
                        free((Entry)get((*pM)->rows[i]));
                        moveNext((*pM)->rows[i]);
                    }
                }
            }
            freeList(&(*pM)->rows[i]);
        }
        free(&(*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
    
}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M){
    if (M == NULL){
        printf("Matrix Error: calling size() on NULL Matrix reference\n");
        exit(1);
    }
    return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
        exit(1);
    }
    return(M->NNZ);
    
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.

int equals(Matrix A, Matrix B)
{
    int eq = 0;
    if (A == NULL || B == NULL)
    {
        printf("Matrix Error: calling equals() on NULL Matrix reference\n");
        exit(1);
    }
    eq = (size(A) == size(B));
    Entry E1 = NULL;
    Entry E2 = NULL;
    for (int i = 1; i <= size(A); i++)
    {
        if (length(A->rows[i]) > 0 && length(B->rows[i]) > 0)
        {
            moveFront(A->rows[i]);
            moveFront(B->rows[i]);
            for (int j = 1; j <= size(A); j++)
            {
                if (index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0)
                {
                    E1 = (Entry)get(A->rows[i]);
                    E2 = (Entry)get(B->rows[i]);
                    if (E1->column == E2->column && E1->value != E2->value)
                    {
                        eq = 0;
                    }
                    
                }
                else
                {
                    eq = 0;
                }
            }
        }
        else
        {
            break;
        }
    }
    return eq;
}


// Manipulation procedures -----------------------------------------------------

// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M) 
{
    if (M == NULL)
    {
        printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
        exit(1);
    }
    Entry temp = NULL;
    for (int i = 1; i <= size(M); i++)
    {
        if (length(M->rows[i]) > 0)
        {
            moveFront(M->rows[i]);
            for (int j = 1; j <= length(M->rows[i]); j++)
            {
                temp = (Entry)get(M->rows[i]);
                if (index(M->rows[i]) >= 0)
                {
                    Entry curr = temp;
                    moveNext(M->rows[i]);
                    freeEntry(&curr);
                    
                }
            }
            printf("\n");
        }
        else
        {
            if (length(M->rows[i+1]) <= 0)
            {
                break;
            }
        }
        
    }
    M->size = 0;
    M->NNZ = 0;
    
    
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(1);
    }
    if ((i >= 1 && i <= size(M)) || (j >= 1 && j <= size(M)))
    {
        if (length(M->rows[i]) == 0)
        {
            if (x != 0)
            {
                append(M->rows[i], newEntry(x, j));
                //printf("1*****%d,%d,  %.1f\n", i, j, x);
                M->NNZ++;
            }
        }
        else
        {
            moveFront(M->rows[i]);
            Entry curr = (Entry)get(M->rows[i]);
            if (j == curr->column)
            {
                if (x == 0)
                {
                    delete(M->rows[i]);
                    //printf("2*****%d,%d,  %.1f\n", i, j, x);
                    M->NNZ--;
                }
                else
                {
                    //printf("3*****%d,%d,  %.1f\n", i, j, x);
                    curr->value = x;
                }
            }
            else
            {
                if (x != 0)
                {
                    while (index(M->rows[i]) >= 0)
                    {
                        curr = (Entry)get(M->rows[i]);
                        //printf("#############%d, %.1f\n", curr->column, curr->value);
                        //printf("^^^^^^^^^^^^%d, %d\n", j, curr->column);
                        if (j > curr->column)
                        {
                            moveNext(M->rows[i]);
                            //printf("@@@@@@@@@@@@@@@@@%d\n", index(M->rows[i]));
                        }
                        else
                        {
                            break;
                        }
                    }
                    //printf("@@@@@@@@@@@@@@@@@%d\n", index(M->rows[i]));
                    if (index(M->rows[i]) < 0)
                    {
                        append(M->rows[i], newEntry(x, j));
                        //printf("4*****%d, %d,  %.1f\n", i, j, x);
                        M->NNZ++;
                    }
                    else
                    {
                        insertBefore(M->rows[i], newEntry(x, j));
                        //printf("5*****%d,%d,  %.1f\n", i, j, x);
                        M->NNZ++;
                    }
                    
                }
            }
            
        }
        
    }
    
}

// Matrix Arithmetic operations -------------------------------------------------

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    Entry E = NULL;
    for (int i = 1; i <= size(A); i++)
    {
        if (length(A->rows[i]) > 0)
        {
            moveFront(A->rows[i]);
            for (int j = 1; j <= length(A->rows[i]); j++)
            {
                if (index(A->rows[i]) >= 0)
                {
                     E = (Entry)get(A->rows[i]);
                     changeEntry(R, i, j, E->value);
                     moveNext(A->rows[i]);
                }
            }
        }
        else
        {
            if (length(A->rows[i+1]) <= 0)
            {
                break;
            }
        }
        
    }
    return R;
    
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    Entry curr = NULL;
    for (int i = 1; i <= size(A); i++)
    {
        if (length(A->rows[i]) > 0)
        {
            moveFront(A->rows[i]);
            //printf("###%d\n", length(A->rows[i]));
            for (int j = 1; j <= length(A->rows[i]); j++)
            {
                if (index(A->rows[i]) >= 0)
                {
                     curr = (Entry)get(A->rows[i]);
                     changeEntry(R, curr->column, i, curr->value);
                    //printf("######%d, %d, %.1f\n", curr->column, i, curr->value);
                     moveNext(A->rows[i]);
                }
            }
        }
        else
        {
            if (length(A->rows[i+1]) <= 0)
            {
                break;
            }
        }
        
    }
    //freeEntry(&curr);
    return R;
    
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
    if (A == NULL)
    {
        printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    Entry E = NULL;
    for (int i = 1; i <= size(A); i++)
    {
        if (length(A->rows[i]) > 0)
        {
            moveFront(A->rows[i]);
            for (int j = 1; j <= length(A->rows[i]); j++)
            {
                if (index(A->rows[i]) >= 0)
                {
                     E = (Entry)get(A->rows[i]);
                     changeEntry(R, i, E->column, x * E->value);
                     moveNext(A->rows[i]);
                }
            }
        }
        else
        {
            if (length(A->rows[i+1]) <= 0)
            {
                break;
            }
        }
        
    }
    return R;
}


// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
    if (A == NULL | B == NULL)
    {
        printf("List Error: calling sum() on NULL Matrix reference\n");
        exit(1);
    }
    if (size(A) != size(B))
    {
        printf("Matrix Error: calling sum() on different size Matrices\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    if (A == B)    // A*A has same reference
    {
        R = scalarMult(2.0, A);
        return R;
           
    }
    
    //Matrix temp = copy()
    Entry E1 = NULL;
    Entry E2 = NULL;
    for (int i = 1; i <= size(A); i++)
    {
       if (length(A->rows[i]) > 0 && length(B->rows[i]) > 0)
       {
           moveFront(A->rows[i]);
           moveFront(B->rows[i]);
           for (int j = 1; j <= size(A); j++)
           {
               if (index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0)
               {
                    E1 = (Entry)get(A->rows[i]);
                    E2 = (Entry)get(B->rows[i]);
                    if (E1->column == E2->column)
                    {
                        double s = E1->value + E2->value;
                        if (s != 0)
                        {
                            changeEntry(R, i, E1->column, s);
                        }
                        moveNext(A->rows[i]);
                        moveNext(B->rows[i]);
                    }
                   else if (E1->column < E2->column)
                   {
                       changeEntry(R, i, E1->column, E1->value);
                       moveNext(A->rows[i]);
                   }
                   else
                   {
                       changeEntry(R, i, E2->column, E2->value);
                       moveNext(B->rows[i]);
                   }
               }
               
               else
               {
                   if (index(A->rows[i]) >= 0 && index(B->rows[i]) <= 0)
                   {
                       while (index(A->rows[i]) >= 0)
                       {
                           E1 = (Entry)get(A->rows[i]);
                           changeEntry(R, i, E1->column, E1->value);
                           moveNext(A->rows[i]);
                       }
                       
                   }
                   if (index(B->rows[i]) >= 0 && index(A->rows[i]) <= 0)
                   {
                      while (index(B->rows[i]) >= 0)
                      {
                         E2 = (Entry)get(B->rows[i]);
                         changeEntry(R, i, E2->column, E2->value);
                         moveNext(B->rows[i]);
                      }
                       
                   }
               }
                
           }
       }
       else
       {
           if (length(A->rows[i]) <= 0 && length(B->rows[i]) <= 0)
           {
               break;
               
           }
           if (length(A->rows[i]) > 0 && length(B->rows[i]) <= 0)
           {
               moveFront(A->rows[i]);
               while (index(A->rows[i]) >= 0)
               {
                   E1 = (Entry)get(A->rows[i]);
                   changeEntry(R, i, E1->column, E1->value);
                   moveNext(A->rows[i]);
               }
               
           }
           if (length(B->rows[i]) > 0 && length(A->rows[i]) <= 0)
           {
              moveFront(B->rows[i]);
              while (index(B->rows[i]) >= 0)
              {
                 E2 = (Entry)get(B->rows[i]);
                 changeEntry(R, i, E2->column, E2->value);
                 moveNext(B->rows[i]);
              }
               
           }
       }
                   
    }
    //freeEntry(&E1);
    //freeEntry(&E2);
    return R;
}


// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
    if (A == NULL | B == NULL)
    {
        printf("List Error: calling diff() on NULL Matrix reference\n");
        exit(1);
    }
    if (size(A) != size(B))
    {
        printf("Matrix Error: calling diff() on different size Matrices\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    Entry E1 = NULL;
    Entry E2 = NULL;
    for (int i = 1; i <= size(A); i++)
    {
       if (length(A->rows[i]) > 0 && length(B->rows[i]) > 0)
       {
           moveFront(A->rows[i]);
           moveFront(B->rows[i]);
           for (int j = 1; j <= size(A); j++)
           {
               if (index(A->rows[i]) >= 0 && index(B->rows[i]) >= 0)
               {
                    E1 = (Entry)get(A->rows[i]);
                    E2 = (Entry)get(B->rows[i]);
                    //printf("#############%d, %.1f\n", E1->column, E1->value);
                    //printf("#############%d, %.1f\n", E2->column, E2->value);
                    if (E1->column == E2->column)
                    {
                        double s = E1->value - E2->value;
                        //printf("######%.1f\n", s);
                        if (s != 0)
                        {
                            changeEntry(R, i, E1->column, s);
                        }
                        //printf("1<<<<<<<<<<<\n");
                        moveNext(A->rows[i]);
                        moveNext(B->rows[i]);
                    }
                   else if (E1->column < E2->column)
                   {
                      // printf("2<<<<<<<<<<<\n");
                       changeEntry(R, i, E1->column, E1->value);
                       moveNext(A->rows[j]);
                       //printf("@@@@@@@@@@@@@@@@@%d\n", index(A->rows[i]));
                   }
                   else
                   {
                       //printf("3<<<<<<<<<<<\n");
                       changeEntry(R, i, E2->column, -1 * E2->value);
                       moveNext(B->rows[j]);
                      // printf("@@@@@@@@@@@@@@@@@%d\n", index(B->rows[i]));
                       
                   }
               }
               
               else
               {
                   if (index(A->rows[i]) >= 0 && index(B->rows[i]) <= 0)
                   {
                       while (index(A->rows[i]) >= 0)
                       {
                           E1 = (Entry)get(A->rows[i]);
                           changeEntry(R, i, E1->column, E1->value);
                           //printf("4<<<<<<<<<<<\n");
                           moveNext(A->rows[i]);
                       }
                       
                   }
                   if (index(B->rows[i]) >= 0 && index(A->rows[i]) <= 0)
                   {
                      while (index(B->rows[i]) >= 0)
                      {
                         E2 = (Entry)get(B->rows[i]);
                         changeEntry(R, i, E2->column, -1 * E2->value);
                         //printf("5<<<<<<<<<<<\n");
                         moveNext(B->rows[i]);
                      }
                       
                   }
               }
                
           }
       }
       else
       {
           if (length(A->rows[i]) <= 0 && length(B->rows[i]) <= 0)
           {
               break;
               
           }
           if (length(A->rows[i]) > 0 && length(B->rows[i]) <= 0)
           {
               moveFront(A->rows[i]);
               while (index(A->rows[i]) >= 0)
               {
                   E1 = (Entry)get(A->rows[i]);
                   changeEntry(R, i, E1->column, E1->value);
                   //printf("6<<<<<<<<<<<\n");
                   moveNext(A->rows[i]);
               }
               
           }
           if (length(B->rows[i]) > 0 && length(A->rows[i]) <= 0)
           {
              moveFront(B->rows[i]);
              while (index(B->rows[i]) >= 0)
              {
                 E2 = (Entry)get(B->rows[i]);
                 changeEntry(R, i, E2->column, -1 * E2->value);
                // printf("7<<<<<<<<<<<\n");
                 moveNext(B->rows[i]);
              }
               
           }
       }
                   
    }
    //freeEntry(&E1);
    //freeEntry(&E2);
    return R;
    
    
}



// product()
// Returns a reference to a new Matrix object representing AB.
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
    if (A == NULL | B == NULL)
    {
        printf("List Error: calling product() on NULL Matrix reference\n");
        exit(1);
    }
    if (size(A) != size(B))
    {
        printf("Matrix Error: calling product() on different size Matrices\n");
        exit(1);
    }
    int n = size(A);
    Matrix R = newMatrix(n);
    Matrix temp = transpose(B);
    for (int i = 1; i <= size(A); i++)
    {
        if (length(A->rows[i]) > 0)
        {
            moveFront(A->rows[i]);
            moveFront(temp->rows[i]);
            for (int j = 1; j <= size(temp); j++)
            {
                if (length(temp->rows[j]) > 0)
                {
                    double dotProduct = vectorDot(A->rows[i], temp->rows[j]);
                    if (dotProduct != 0.0)
                    {
                        changeEntry(R, i, j, dotProduct);
                    }
                }
                else
                {
                    if (length(temp->rows[j+1]) <= 0)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
           if (length(A->rows[i+1]) <= 0)
           {
               break;
           }
        }
    }
    return R;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M)
{
    if (M == NULL)
    {
        printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
        exit(1);
    }
    Entry curr = NULL;
    for (int i = 1; i <= size(M); i++)
    {
        if (length(M->rows[i]) > 0)
        {
            moveFront(M->rows[i]);
            printf("%d: ", i);
            for (int j = 1; j <= length(M->rows[i]); j++)
            {
                if (index(M->rows[i]) >= 0)
                {
                     curr = (Entry)get(M->rows[i]);
                     printf("(%d, %.1f)", curr->column, curr->value);
                     moveNext(M->rows[i]);
                }
            }
            printf("\n");
        }
        else
        {
            if (length(M->rows[i+1]) <= 0)
            {
                break;
            }
        }
        
    }
    printf("\n");
    
}

// vectorDot()
// computes the vector dot product of two matrix rows represented by Lists P and Q.
// Use this function together with function transpose() to help implement product().
double vectorDot(List P, List Q)
{
    double sum = 0.0;
    if (P != NULL && Q != NULL)
    {
        Entry E1 = NULL;
        Entry E2 = NULL;
        moveFront(P);
        moveFront(Q);
        
        while (index(P) >= 0 && index(Q) >= 0)
        {
            E1 = (Entry)get(P);
            E2 = (Entry)get(Q);
            if (E2->column > E1->column)
            {
                moveNext(P);
            }
            else if (E2->column == E1->column)
            {

                sum += E1->value * E2->value;
                moveNext(P);
                moveNext(Q);
            }
            else
            {
                moveNext(Q);
            }
    
        }
        if (index(P) >= 0 && index(Q) <= 0)
        {
            while (index(P) >= 0)
            {
                moveNext(P);
            }
        }
        if (index(Q) >= 0 && index(P) <= 0)
        {
           while (index(Q) >= 0)
           {
               moveNext(Q);
           }
        }
    }
    
    return sum;
     
}

