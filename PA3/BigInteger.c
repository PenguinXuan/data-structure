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
#include "math.h"


#define POWER 9
#define BASE 10
extern char * strtok(char * str, const char * delimiters);
extern char* strncpy(char * destination, const char * source, size_t num);
extern size_t strlen ( const char * str );

void add(BigInteger S, BigInteger A, BigInteger B);
void subtract(BigInteger D, BigInteger A, BigInteger B);
void multiply(BigInteger P, BigInteger A, BigInteger B);

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
    N->longs = newList();
    return N;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL.
void freeBigInteger(BigInteger* pN){
    if(pN != NULL && *pN != NULL){
        freeList(&(*pN)->longs);
    }
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
    int length = strlen(s);  //  elimited extra \n
    int start = 0;
    if (s[0] < '0' || s[0] > '9')
    {
        if (s[0] == '-') {
            N->sign = -1;
            start = 1;
        } else if (s[0] == '+') {
            N->sign = 1;
            start = 1;
        }
    } else {
        N->sign = 1;
    }

    for(int i = length - 1; i >= start; i -= POWER)
    {
        unsigned long number = 0;
        int number_begin = 0;
        if (i -  POWER < start){
            number_begin = start;
        } else {
            number_begin  = i - POWER + 1;
        }
        for (int j = number_begin; j <= i; j++) {
            number *= 10;
            number += (s[j] - '0');
        }
        append(N->longs, number);

    }
    return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N);

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
    long carry = 0;
    long base_to_power = (long)powl(BASE, POWER);

    moveFront(A->longs);
    moveFront(B->longs);

    while (index(A->longs) >= 0 || index(B->longs) >= 0 || carry > 0) {
        if (index(A->longs) >= 0) {
            carry += get(A->longs);
            moveNext(A->longs);
        }
        if (index(B->longs) >= 0) {
            carry += get(B->longs);
            moveNext(B->longs);
        }
        append(S->longs, carry % base_to_power);
        carry /= base_to_power;
    }

}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    if (A == NULL | B == NULL){
        printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger S = newBigInteger();
    if (A->sign == B->sign) {
        add(S, A, B);
    } else {
        subtract(S, A, B);
    }
    return S;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
//itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
    int borrow = 0;
    long diff = 0;
    long base_to_power = (long)powl(BASE, POWER);

    moveFront(A->longs);
    moveFront(B->longs);

    while (index(A->longs) >= 0 || index(B->longs) >= 0) {
        if (index(A->longs) >= 0) {
            diff += get(A->longs);
            moveNext(A->longs);
        }
        if (index(B->longs) >= 0) {
            diff -= get(B->longs);
            moveNext(B->longs);
        }
        if (diff < 0) {
            borrow = 1;
        }


        //append(S->longs, );
        //carry /= base_to_power;
    }




}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
    if (A == NULL | B == NULL){
        printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger D = newBigInteger();
    if(A->sign == B->sign) {
        add(D, A, B);
    } else {
        subtract(D, A, B);
    }
    return D;
}

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
void printBigInteger(FILE* out, BigInteger N)
{
    if(N == NULL){
        printf("List Error: calling printList() on NULL BigInteger reference\n");
        exit(1);
    }
    moveBack(N->longs);
    while(index(N->longs) >= 0){
        fprintf(out, "%ld", get(N->longs));
        movePrev(N->longs);
    }
}


