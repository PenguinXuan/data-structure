//Zhuoxuan Wang
//CruzID: zwang437
//PA 1

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "List.h"

#define MAX_LINE 160

extern int strcmp(const char*, const char*);
extern char *strcpy(char *dest, const char *src);

int main(int argc, char* argv[]){
    FILE *in, *out;
    char lines[MAX_LINE];
    int count = 0;
    List myList = newList();
    
    // check command line for correct number of arguments
    if(argc != 3){
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    
    if(in == NULL){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if(out == NULL){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }
    
    while(fgets(lines, MAX_LINE, in) != NULL){
        count++;
    }
    rewind(in);
    
    char str[count - 1][MAX_LINE];
    
    for(int i = 0; i < count; i++){
        fgets(lines, MAX_LINE, in);
        strcpy(str[i], lines);
    }
    
    fclose(in);
    
    //Insertion Sort
    append(myList, 0);
    
    for(int i = 1; i < count; i++){
        moveBack(myList);
        int j = i - 1;
        while(j >= 0 && strcmp(str[i], str[get(myList)]) < 0){
            movePrev(myList);
            j--;
        }
        if(index(myList) >= 0){
            insertAfter(myList, i);
        }
        else{
            prepend(myList, i);
        }
    }
    moveFront(myList);
    
    while(index(myList) >= 0){
        fprintf(out, "%s", str[get(myList)]);
        moveNext(myList);
    }
    
    fclose(in);
    fclose(out);
    
    freeList(&myList);
    
    return 0;
   
    
}
