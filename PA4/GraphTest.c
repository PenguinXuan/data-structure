//Zhuoxuan Wang
//CruzID: zwang437
//PA 4

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    Graph G1 = newGraph(7);

    addEdge(G1, 1, 4);
    addEdge(G1, 1, 5);
    addEdge(G1, 4, 5);
    addEdge(G1, 2, 3);
    addEdge(G1, 2, 6);
    addEdge(G1, 3, 7);
    addEdge(G1, 6, 7);

    printf("Undirected Graph:\n");
    printGraph(stdout, G1);

    BFS(G1, 2);
    List L1 = newList();
    getPath(L1, G1, 7);

    printf("The distance from %d to %d is %d\n", 2, 7, getDist(G1, 7));
    printf("A shortest %d-%d path is: ", 2, 7);
    printList(stdout, L1);
    printf("\n");

    printf("Size: %d\n", getSize(G1));
    printf("Order: %d\n", getOrder(G1));
    printf("Parent of 7 is: %d\n", getParent(G1, 7));
    printf("Source: %d\n", getSource(G1));
    printf("\n");

    Graph G2 = newGraph(7);

    addArc(G2, 1, 4);
    addArc(G2, 1, 5);
    addArc(G2, 4, 5);
    addArc(G2, 2, 3);
    addArc(G2, 2, 6);
    addArc(G2, 3, 7);
    addArc(G2, 6, 7);

    printf("Directed Graph:\n");
    printGraph(stdout, G2);

    BFS(G2, 2);
    List L2 = newList();
    getPath(L2, G2, 7);

    printf("The distance from %d to %d is %d\n", 2, 7, getDist(G2, 7));
    printf("A shortest %d-%d path is: ", 2, 7);
    printList(stdout, L2);
    printf("\n");

    printf("Size: %d\n", getSize(G2));
    printf("Order: %d\n", getOrder(G2));
    printf("Parent of 7 is: %d\n", getParent(G2, 7));
    printf("Source: %d\n", getSource(G2));

    freeList(&L1);
    freeList(&L2);
    freeGraph(&G1);
    freeGraph(&G2);

}
/*OUTPUT:
 Undirected Graph:
1: 4 5
2: 3 6
3: 2 7
4: 1 5
5: 1 4
6: 2 7
7: 3 6
The distance from 2 to 7 is 2
A shortest 2-7 path is: 2 3 7
Size: 7
Order: 7
Parent of 7 is: 3
Source: 2

Directed Graph:
1: 4 5
2: 3 6
3: 7
4: 5
5:
6: 7
7:
The distance from 2 to 7 is 2
A shortest 2-7 path is: 2 3 7
Size: 7
Order: 7
Parent of 7 is: 3
Source: 2
*/