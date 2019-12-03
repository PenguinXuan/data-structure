//Zhuoxuan Wang
//CruzID: zwang437
//PA 5

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]) {
    Graph G = newGraph(7);
    
    addArc(G, 1, 4);
    addArc(G, 1, 5);
    addArc(G, 4, 5);
    addArc(G, 2, 3);
    addArc(G, 2, 6);
    addArc(G, 3, 7);
    addArc(G, 6, 7);

    fprintf(stdout, "Directed Graph:\n");
    printGraph(stdout, G);
    fprintf(stdout, "\n");
    
    List S = newList();
    for (int i = 1; i <= 7; ++i) {
        append(S, i);
    }
    
    DFS(G, S);
    
    fprintf(stdout, "Size: %d\n", getSize(G));
    fprintf(stdout, "Order: %d\n", getOrder(G));
    fprintf(stdout, "\n");
    
    for (int i =  1; i <= 7; ++i) {
       fprintf(stdout, "Parent of %d: %d\n", i, getParent(G, i));
       fprintf(stdout, "Discover time of %d: %d\n", i, getDiscover(G, i));
       fprintf(stdout, "Finish time of %d: %d\n",  i, getFinish(G, i));
       fprintf(stdout, "\n");
    }
    
    Graph T = transpose(G);
    fprintf(stdout, "Transpose of G:\n");
    printGraph(stdout, T);
    
    fprintf(stdout, "\n");
    
    
    Graph C = copyGraph(G);
    fprintf(stdout, "Copy of G:\n");
    printGraph(stdout, C);
    
    freeList(&S);
    freeGraph(&C);
    freeGraph(&T);
    freeGraph(&G);


}
/*OUTPUT:
 Directed Graph:
 1: 4 5
 2: 3 6
 3: 7
 4: 5
 5:
 6: 7
 7:

 Size: 7
 Order: 7

 Parent of 1: 0
 Discover time of 1: 1
 Finish time of 1: 6

 Parent of 2: 0
 Discover time of 2: 7
 Finish time of 2: 14

 Parent of 3: 2
 Discover time of 3: 8
 Finish time of 3: 11

 Parent of 4: 1
 Discover time of 4: 2
 Finish time of 4: 5

 Parent of 5: 4
 Discover time of 5: 3
 Finish time of 5: 4

 Parent of 6: 2
 Discover time of 6: 12
 Finish time of 6: 13

 Parent of 7: 3
 Discover time of 7: 9
 Finish time of 7: 10

 Transpose of G:
 1:
 2:
 3: 2
 4: 1
 5: 1 4
 6: 2
 7: 3 6

 Copy of G:
 1: 4 5
 2: 3 6
 3: 7
 4: 5
 5:
 6: 7
 7:

*/
