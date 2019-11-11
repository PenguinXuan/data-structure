//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

#ifndef BigInteger_h
#define BigInteger_h

#include <stdio.h>
#include <stdlib.h>

// Exported type -------------------------------------------------------------
typedef struct BigIntegerObj* BigInteger; // BigInteger reference type
// Constructors-Destructors ---------------------------------------------------
BigInteger newBigInteger(); // Returns a reference to a new BigInteger object in the zero state.
void freeBigInteger(BigInteger* pN); // Frees heap memory associated with *pN, sets *pN to NULL.

// Access functions -----------------------------------------------------------
int sign(BigInteger N); // Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
                        // state.
int compare(BigInteger A, BigInteger B); // Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int equals(BigInteger A, BigInteger B); // Return true (1) if A and B are equal, false (0) otherwise.

// Manipulation procedures ----------------------------------------------------
void makeZero(BigInteger N); // Re-sets N to the zero state.
void negate(BigInteger N);  // Reverses the sign of N: positive <--> negative. Does nothing if N is in the
                            // zero state.

// BigInteger Arithmetic operations -----------------------------------------------
BigInteger stringToBigInteger(char* s); // Returns a reference to a new BigInteger object representing the decimal integer
                                        // represented in base 10 by the string s.
                                        // Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
                                        // and an optional sign {+, -} prefix.
BigInteger copy(BigInteger N); // Returns a reference to a new BigInteger object in the same state as N.
BigInteger sum(BigInteger A, BigInteger B); // Returns a reference to a new BigInteger object representing A + B.
BigInteger diff(BigInteger A, BigInteger B); // Returns a reference to a new BigInteger object representing A - B.
BigInteger prod(BigInteger A, BigInteger B); // Returns a reference to a new BigInteger object representing A*B.

// Other operations -----------------------------------------------------------
void printBigInteger(FILE* out, BigInteger N);  // Prints a base 10 string representation of N to filestream out.

#endif /* BigInteger_h */
