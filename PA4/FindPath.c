//Zhuoxuan Wang
//CruzID: zwang437
//PA 4

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

    Graph G = newGraph(n);

    while (fgets(lines, MAX_LINE, in)) {
        char *x = strtok(lines, " ");
        char *y = strtok(NULL, " ");
        int u = atoi(x);
        int v = atoi(y);
        if (u == 0 && v == 0)
            break;
        addEdge(G, u, v);
    }

    printGraph(out, G);
    fprintf(out, "\n");

    while (fgets(lines, MAX_LINE, in)) {
        char *x = strtok(lines, " ");
        char *y = strtok(NULL, " ");
        int s = atoi(x);
        int d = atoi(y);
        if (s == 0 && d == 0)
            break;
        BFS(G, s);
        List L = newList();
        getPath(L, G, d);

        if (getDist(G, d) == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", s, d);
        }  else {
            fprintf(out, "The distance from %d to %d is %d\n", s, d, getDist(G, d));
        }
        if (front(L) == NIL) {
            fprintf(out, "No %d-%d path exists\n", s, d);
        }  else {
            fprintf(out, "A shortest %d-%d path is: ", s, d);
            printList(out, L);

        }
        fprintf(out, "\n");
        fprintf(out, "\n");
        freeList(&L);
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);

}