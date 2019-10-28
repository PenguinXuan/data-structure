//Zhuoxuan Wang
//CruzID: zwang437
//PA 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"

#define MAX_LINE 160

int main(int argc, char* argv[])
{
    FILE *in, *out;
    char line[MAX_LINE];
    Matrix A, B;
    
    // check command line for correct number of arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    char *array[3];
    int i = 0;
    if (fgets(line, MAX_LINE, in) != NULL) // get the first line
    {
        char *token = strtok(line, "\n");
        token = strtok(line, " ");
        while (token != NULL)
        {
            array[i++] = token;
            token = strtok(NULL, " ");
        }
    }
    
    int n = atoi(array[0]); // size of matrices
    int m = atoi(array[1]); // # of NNZ of A
    int l = atoi(array[2]); // # of NNZ of B
    A = newMatrix(n);
    B = newMatrix(n);

    char *temp[3];
    int j = 1, k = 0;
    while (fgets(line, MAX_LINE, in) != NULL && j <= m)   // matrix A
    {
        printf("***%s\n", line);
        /*
        if (strlen(line) > 0)
        {
            printf("***%s\n", line);
            
            k = 0;
            char *token = strtok(line, "\n");
            token = strtok(line, " ");
            while (token != NULL)
            {
                temp[k++] = token;
                token = strtok(NULL, " ");
            }
            changeEntry(A, atoi(temp[0]), atoi(temp[1]), atof(temp[2]));
            printf("1<<<<<%d, %d,  %.1f\n", atoi(temp[0]), atoi(temp[1]), atof(temp[2]));
            j++;
        }
        else
        {
            fgets(line, MAX_LINE, in);
            
        }*/
    }
    
    printf("**************************\n");
    /*
    if (strcmp(line, "\n") != 0)
    {
        printf("***%s\n", line);
        k = 0;
        char *token = strtok(line, "\n");
        token = strtok(line, " ");
        while (token != NULL)
        {
            temp[k++] = token;
            token = strtok(NULL, " ");
        }
        changeEntry(B, atoi(temp[0]), atoi(temp[1]), atof(temp[2]));
        //printf("2<<<<<%d, %d,  %.1f\n", atoi(temp[0]), atoi(temp[1]), atof(temp[2]));
        
    }*/
    /*
    j = 0;
    while (fgets(line, MAX_LINE, in) != NULL)   // matrix B
    {
        if (strcmp(line, "\n") == 0)
        {
            continue;
        }
        printf("***%s\n", line);
        if (j <= l)
        {
            k = 0;
            char *token = strtok(line, "\n");
            token = strtok(line, " ");
            while (token != NULL)
            {
                temp[k++] = token;
                token = strtok(NULL, " ");
            }
            changeEntry(B, atoi(temp[0]), atoi(temp[1]), atof(temp[2]));
            printf("3<<<<<%d, %d,  %.1f\n", atoi(temp[0]), atoi(temp[1]),atof(temp[2]));
            j++;
        }
        else
        {
            break;
        }
    }*/
    
    //printf("A has %d non-zero entries:\n", NNZ(A));
    //printMatrix(stdout, A);
    //printf("B has %d non-zero entries:\n", NNZ(B));
    //printMatrix(stdout, B);
    /*
    printf("(1.5)*A = \n");
    printMatrix(stdout, scalarMult(1.5, A));
    printf("A+B = \n");
    printMatrix(stdout, sum(A, B));
    printf("A+A = \n");
    printMatrix(stdout, sum(A, A));
    printf("B-A = \n");
    printMatrix(stdout, diff(B, A));
    printf("A-A = \n");
    printMatrix(stdout, diff(A, A));
    printf("Transpose(A) = \n");
    printMatrix(stdout, transpose(A));
    printf("A*B = \n");
    printMatrix(stdout, product(A, B));
    printf("B*B = \n");
    printMatrix(stdout, product(B, B));
    */
    fclose(in);
    fclose(out);
    return 0;
       
    
    
}
