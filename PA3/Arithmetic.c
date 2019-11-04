//Zhuoxuan Wang
//CruzID: zwang437
//PA 3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "BigInteger.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
    FILE *in, *out;
    int len_digits =  0;
    char line[MAX_LEN];
    char *str = NULL;
    BigInteger A = newBigInteger();
    BigInteger B = newBigInteger();
    
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
    fgets(line, MAX_LEN, in);
    len_digits = atoi(line);
    str = (char *) malloc(len_digits + 1);
    fgets(str, len_digits + 1, in);
    A = stringToBigInteger(str);

    fgets(line, MAX_LEN, in);
    len_digits = atoi(line);
    str = (char *) malloc(len_digits + 1);
    fgets(str, len_digits + 1, in);
    B = stringToBigInteger(str);

    /* close files */
    fclose(in);
    fclose(out);

    return 0;
}


