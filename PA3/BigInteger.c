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


BigInteger sumAbs(BigInteger A, BigInteger B);
BigInteger diffAbs(BigInteger A, BigInteger B);
BigInteger prodOf(BigInteger A, unsigned long c);
void multiplyShift(BigInteger A, int shift);
int compareAbs(BigInteger A, BigInteger B);
void trimZero(BigInteger A);
void copyHelper(BigInteger A, BigInteger B);


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
int compare(BigInteger A, BigInteger B) {
    if ((A->sign > B->sign)) {    // 1 > -1
        return 1;
    } else if ((A->sign < B->sign)) { // 1 < -1
        return -1;
    } else {   // same sign
        if (A->sign < 0) {
            return -compareAbs(A, B);
        } else {
            return compareAbs(A, B);
        }

    }
}
int compareAbs(BigInteger A, BigInteger B) {
    trimZero(A);
    trimZero(B);
    if (length(A->longs) > length(B->longs)){ // len(A) > len(B)
        return 1;
    } else if (length(A->longs) < length(B->longs)){   // len(A) < len(B)
        return -1;
    } else {      // same sign && len(A) == len(B)
        moveBack(A->longs);
        moveBack(B->longs);
        while (index(A->longs) >= 0 && index(B->longs) >= 0) {
            if (get(A->longs) > get(B->longs)) {
                return 1;
            } else if (get(A->longs) < get(B->longs)) {
                return -1;
            } else {
                movePrev(A->longs);
                movePrev(B->longs);
            }
        }
    }
    return 0; // A  == B

}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL){
        printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
        exit(1);
    }
    if (compare(A, B) == 0) {
        return 1;
    }
    return 0;
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N) {
    if(N == NULL){
        printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
        exit(1);
    }
    while(length(N->longs) > 0){
        deleteFront(N->longs);
    }
    N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N) {
    if(N == NULL){
        printf("BigInteger Error: calling negate() on NULL BigInteger reference\n");
        exit(1);
    }
    N->sign = -N->sign;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s){
    BigInteger N = newBigInteger();
    int n = strlen(s);
    int start = 0;
    if (s[0] < '0' || s[0] > '9') {
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

    for (int i = n - 1; i >= start; i -= POWER)
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
    trimZero(N);
    return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N) {
    if(N == NULL){
        printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger M = newBigInteger();
    M->sign = N->sign;

    moveFront(N->longs);
    while (index(N->longs) >= 0) {
        append(M->longs, get(N->longs));
        moveNext(N->longs);
    }
    return M;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B) {
    BigInteger temp = sum(A, B);
    copyHelper(S, temp);
    freeBigInteger(&temp);
}


BigInteger sumAbs(BigInteger A, BigInteger B) {
    unsigned long carry = 0;
    long base_to_power = (long)powl(BASE, POWER);

    if (length(A->longs) == 0 || length(B->longs) == 0) {
        if (length(A->longs)== 0) {
            return copy(B);
        } else {
            return copy(A);
        }
    }

    BigInteger S = newBigInteger();
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
    return S;
}

BigInteger diffAbs(BigInteger A, BigInteger B) {
    int borrow = 0;
    unsigned long a, b;
    long base_to_power = (long)powl(BASE, POWER);
    BigInteger D = newBigInteger();

    moveFront(A->longs);
    moveFront(B->longs);
    while (index(A->longs) >= 0 || index(B->longs) >= 0 || borrow > 0) {
        if (index(A->longs) >= 0) {
            a = get(A->longs);
            moveNext(A->longs);
        }
        if (index(B->longs) >= 0) {
            b = get(B->longs);
            moveNext(B->longs);
        }
        if (a < b + borrow) {
            append(D->longs, a + base_to_power - b - borrow);
            borrow = 1;
        } else {
            append(D->longs, a - b - borrow);
            borrow = 0;
        }
        a = 0;
        b = 0;
    }
    trimZero(D);
    return D;

}



// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B){
    if (A == NULL || B == NULL){
        printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger S, localB = copy(B);
    if (A->sign == localB->sign) {
        S = sumAbs(A, localB);
        S->sign = A->sign;
    } else {
        switch (compareAbs(A, localB)) {
            case 1:
                S = diffAbs(A, localB);
                S->sign = A->sign;
                break;
            case -1:
                S = diffAbs(localB, A);
                S->sign = localB->sign;
                break;
            default:
                S = newBigInteger();
        }
    }
    freeBigInteger(&localB);
    return S;

}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
//itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B) {
   BigInteger temp = diff(A, B);
   copyHelper(D, temp);
   freeBigInteger(&temp);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL){
        printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger temp = copy(B);
    negate(temp);
    BigInteger res  = sum(A, temp);
    freeBigInteger(&temp);
    return res;
}

BigInteger prodOf(BigInteger A, unsigned long c) {
    unsigned long long res = 0;
    unsigned long carry = 0;
    long base_to_power = (long)powl(BASE, POWER);

    BigInteger p = newBigInteger();
    if (c == 0) {
        p->sign = 0;
        return p;
    } else if (c == 1) {
        freeBigInteger(&p);
        return copy(A);
    } else {
        moveFront(A->longs);
        while (index(A->longs) >= 0) {
            res = get(A->longs) * c + carry;
            append(p->longs, res % base_to_power);
            carry = res / base_to_power;
            moveNext(A->longs);
        }
        if (carry > 0) {
            append(p->longs, carry);
        }
    }

    return p;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B) {
    if (A->sign == 0 || B->sign == 0) {
        P->sign = 0;
        return;
    }
    BigInteger temp, localB = copy(B);
    BigInteger res = newBigInteger();
    int shift = 0;
    moveFront(localB->longs);
    while (index(localB->longs) >= 0) {
        temp = prodOf(A, get(localB->longs));
        multiplyShift(temp, shift);
        BigInteger res1 = sumAbs(res, temp);
        freeBigInteger(&res);
        freeBigInteger(&temp);
        res = res1;
        moveNext(localB->longs);
        shift++;

    }
    copyHelper(P, res);
    P->sign = A->sign * localB->sign;
    freeBigInteger(&res);
    freeBigInteger(&localB);

}

void multiplyShift(BigInteger A, int shift) {
    if (length(A->longs) == 0) {
        return;
    }
    while (shift-- > 0) {
        prepend(A->longs, 0);
    }
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B) {
    if (A == NULL || B == NULL){
        printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
        exit(1);
    }
    BigInteger P = newBigInteger();
    multiply(P, A, B);

    return P;
}

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
    if(N == NULL){
        printf("BigInteger Error: calling printList() on NULL BigInteger reference\n");
        exit(1);
    }
    if (N->sign == 0) {
        fprintf(out, "0\n\n");
        return;
    }
    moveBack(N->longs);
    if (N->sign < 0) {
        fprintf(out, "-");
    }
    while(index(N->longs) >= 0){
        if (index(N->longs) != (length(N->longs) - 1)) {
            fprintf(out, "%09ld", get(N->longs));
        } else {
            fprintf(out, "%ld", get(N->longs));
        }
        movePrev(N->longs);
    }
    fprintf(out, "\n\n");
}

void trimZero (BigInteger A) {
    while (length(A->longs) > 0) {
        moveBack(A->longs);
        if (get(A->longs) == 0) {
            delete(A->longs);
        } else {
            break;
        }
    }
    if (length(A->longs) == 0) {
        A->sign = 0;
    }
}

void copyHelper(BigInteger A, BigInteger B) {
    while (length(A->longs) > 0) {
        deleteFront(A->longs);
    }

    A->sign = B->sign;
    moveFront(B->longs);
    while (index(B->longs) >= 0) {
        append(A->longs, get(B->longs));
        moveNext(B->longs);
    }

}


