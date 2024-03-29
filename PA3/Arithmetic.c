//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

#define MAX_LEN 160

char* line_helper(FILE *in, char *line);
BigInteger power(BigInteger A, int c);
int main(int argc, char * argv[]){
    FILE *in, *out;
    char line[MAX_LEN];
    BigInteger A, B, C, D, E, F, G, H, I, J, K, L, M, N;
    // check command line for correct number of arguments
    if( argc != 3 ){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if( out==NULL ){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }

    char *p;
    char* str1 = line_helper(in, line);
    if ((p=strchr(str1, '\n')) != NULL)
        *p = '\0';
    A = stringToBigInteger(str1);

    char* str2 = line_helper(in, line);
    if ((p=strchr(str2, '\n')) != NULL)
        *p = '\0';
    B = stringToBigInteger(str2);

    printBigInteger(out, A);
    printBigInteger(out, B);

    C = sum(A, B);
    printBigInteger(out, C);

    D = diff(A, B);
    printBigInteger(out, D);

    E = diff( A, A);
    printBigInteger(out, E);

    BigInteger N3 = stringToBigInteger("3");
    BigInteger N2 = stringToBigInteger("2");

    F = prod(N3, A);
    G = prod(N2, B);
    H = diff(F, G);
    printBigInteger(out, H);

    I = prod(A, B);
    printBigInteger(out, I);

    J = prod(A, A);
    printBigInteger(out, J);

    K = prod(B, B);
    printBigInteger(out, K);


    BigInteger ATo4 = power(A, 4);
    BigInteger BTo5 = power(B, 5);
    BigInteger N9 = stringToBigInteger("9");
    BigInteger N16 = stringToBigInteger("16");

    L = prod(N9, ATo4);
    M = prod(N16, BTo5);

    N = sum(L, M);
    printBigInteger(out, N);

    /* close files */
    fclose(in);
    fclose(out);

    free(str1);
    free(str2);
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);
    freeBigInteger(&L);
    freeBigInteger(&M);
    freeBigInteger(&N);
    freeBigInteger(&N3);
    freeBigInteger(&N2);
    freeBigInteger(&ATo4);
    freeBigInteger(&BTo5);
    freeBigInteger(&N9);
    freeBigInteger(&N16);

    return 0;
}

char* line_helper(FILE *in, char *line){
    int len_digits =  0;
    char *str = NULL;

    fgets(line, MAX_LEN, in);
    len_digits = atoi(line);
    str = (char *) malloc(len_digits + 3);
    fgets(str, len_digits + 3, in);

    return str;

}

BigInteger power(BigInteger A, int c) {

    BigInteger temp = stringToBigInteger("1");
    for (int i = 0; i < c; i++) {
        BigInteger t = prod(A, temp);
        freeBigInteger(&temp);
        temp = t;
    }
    return temp;
    /*
    BigInteger temp = stringToBigInteger("1");
    while (c > 0) {
        if (c & 1) {
            BigInteger t1 = prod(A, temp);
            freeBigInteger(&temp);
            temp = t1;
        }
        c >>= 1;
        A = prod(A, A);
    }
    return temp;*/
}
