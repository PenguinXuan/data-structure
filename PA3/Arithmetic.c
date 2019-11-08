//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

#define MAX_LEN 160

char* line_helper(FILE *in, char *line);
int main(int argc, char * argv[]){
    FILE *in, *out;
    char line[MAX_LEN];
    char *str = NULL;
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    BigInteger S, D, P;
    
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

    str = line_helper(in, line);
    if ((p=strchr(str, '\n')) != NULL)
        *p = '\0';
    A = stringToBigInteger(str);

    str = line_helper(in, line);
    if ((p=strchr(str, '\n')) != NULL)
        *p = '\0';
    B = stringToBigInteger(str);

    printBigInteger(stdout, A);
    printf("\n");
    printBigInteger(stdout, B);
    printf("\n");

    printf("*****%d\n", compare(A, B));
    /*
    S = sumAbs(A, B);
    printBigInteger(stdout, S);*/
    /*
    D = diffAbs(A, B);
    printBigInteger(stdout, D);
    */



    //printf("*****%d\n", compare(A, B));
    /*
    S = sum(A, B);
    printBigInteger(stdout, S);
    printf("\n");

    D = diff(A, B);
    printBigInteger(stdout, S);
    printf("\n");
    */
    //P = prod(A, B);

    /* close files */
    fclose(in);
    fclose(out);

    free(str);
    freeBigInteger(&A);
    freeBigInteger(&B);

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


