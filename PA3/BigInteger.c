//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

//-----------------------------------------------------------------------------
// BigInteger.c
// Implementation file for BigInteger ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"
#include "List.h"
#define POWER 9
#define BASE 1000000000
extern char * strtok(char * str, const char * delimiters);
extern char* strncpy(char * destination, const char * source, size_t num);
extern size_t strlen ( const char * str );

// structs --------------------------------------------------------------------

// private BigIntegerObj type
typedef struct BigIntegerObj{
    int sign;
    List longs;
}BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state.
BigInteger newBigInteger(){
    BigInteger N = malloc(sizeof(BigIntegerObj));
    N->sign = 0;
    return N;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    /*
    if(pN != NULL && *pN != NULL){
        freeList(*(pN)->longs);
    }*/
    free(*pN);
    *pN = NULL;
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero // state.
int sign(BigInteger N){
    if(N == NULL){
        printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
        exit(1);
    }
    return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B);

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
//int equals(BigInteger A, BigInteger B);

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N);

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N);

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    BigInteger N = newBigInteger();







/*

    char digits[10];







    int partition_length = length % POWER;
    if(s[1][0] <= '0' || s[1][0] >= '9')
    {
        if (s[1][0] == '-')
            N->sign = -1;
        else
            N->sign = 1;
    }
    else
    {
        strncpy(digits, s[1][1], partition_length);
        append(N->longs, digits);

    }
    while(s[1] != '\0')
    {
        strncpy(digits, s[1][1], partition_length + POWER);
        prepend(N->longs, digits);
    }*/
    return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N);

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B);

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B);

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
//itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B);

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B);

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B);

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B);

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N);


