//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(){
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    BigInteger C = newBigInteger();
    BigInteger D = newBigInteger();
    BigInteger E = newBigInteger();
    BigInteger F = newBigInteger();
    
    A = stringToBigInteger("+111122223333");
    B = stringToBigInteger("+222211110000");
    
    printBigInteger(stdout, A);
    printBigInteger(stdout, B);
    
    printBigInteger(stdout, sum(A, B));
    
    add(C, A, B);
    printBigInteger(stdout, C);
    
    printBigInteger(stdout, diff(A, B));
    
    subtract(D, A, B);
    printBigInteger(stdout, D);

    printBigInteger(stdout, diff(A, A));
    
    printBigInteger(stdout, prod(A, B));
    
    multiply(E, A, B);
    printBigInteger(stdout, E);
    
    F = copy(A);
    printBigInteger(stdout, F);
    
    printf("%d\n", equals(A, B));  // A==B return 0
    printf("\n");

    printf("%d\n", compare(A, B)); // A>B return 1 A<B return -1
    printf("\n");
    
    negate(A);
    printBigInteger(stdout, A);

    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    
    
    return EXIT_SUCCESS;
}

/* OUTPUT
111122223333

222211110000

333333333333

333333333333

-111088886667

-111088886667

0

24692592592493829630000

24692592592493829630000

111122223333

0

-1

-111122223333
 */
