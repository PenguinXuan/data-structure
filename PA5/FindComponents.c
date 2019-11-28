//Zhuoxuan Wang
//CruzID: zwang437
//PA 5

#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "Graph.h"


#define MAX_LINE 160
extern char *strtok(char *str, const char *delim);

int main(int argc, char* argv[]) {
    FILE *in, *out;
    int n;
    char lines[MAX_LINE];

    // check command line for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fgets(lines, MAX_LINE, in);
    sscanf(lines, "%d", &n); // get # of vertices
    List S = newList();
    for (int i = 1; i <= n; ++i) {
        append(S, i);
    }

    Graph G = newGraph(n);

    while (fgets(lines, MAX_LINE, in)) {
        char *x = strtok(lines, " ");
        char *y = strtok(NULL, " ");
        int u = atoi(x);
        int v = atoi(y);
        if (u == 0 && v == 0)
            break;
        addArc(G, u, v);
    }

    printGraph(out, G);
    fprintf(out, "\n");

    DFS(G, S);
    Graph T =  transpose(G);
    DFS(T, S);

    int numOfComponents = 0;
    moveFront(S);
    while(index(S) >= 0) {
        int x = get(S);
        if (getParent(T, x) == NIL) {
            ++numOfComponents;
        }
        moveNext(S);
    }
    fprintf(out, "G contains %d strongly connected components: ", numOfComponents);

    List *C = malloc(sizeof(List) * numOfComponents);
    for (int i = 0; i < numOfComponents; ++i) {
        C[i] = newList();
    }

    moveBack(S);
    for (int i = 0; i < numOfComponents; ++i) {
        while (index(S) >= 0 && get(S) != NIL) {
            int x = get(S);
            append(C[i], x);
            deleteBack(S);
        }
    }

    for (int i = 0; i < numOfComponents; ++i) {
        fprintf(out, "Component %d: ", i + 1)
        printList(out, C[i]);
        freeList(&((C[i]));
    }

    freeGraph(&G);
    freeGraph(&T);
    free(&C);
    fclose(in);
    fclose(out);

}

