//Zhuoxuan Wang
//CruzID: zwang437
//PA 5

//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 1
#define GRAY 2
#define BLACK 3

void insertionSort(Graph G, int u, int v);
void Visit(Graph G, List S, int x, int *time);

// structs --------------------------------------------------------------------
// private GraphObj type
typedef struct GraphObj {
    List *adj;
    int *color;
    int *parent;
    int *discover;
    int *finish;
    int order;  // the number of vertices.
    int size;   // the number of edges.
    
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc(sizeof(List) * (n + 1));
    G->color = calloc(n + 1, sizeof(int));
    G->parent = calloc(n + 1, sizeof(int));
    G->discover = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));
    G->order = n;
    G->size = 0;
    
    for(int i = 1; i <= n; ++i) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
    }
    return G;
}
void freeGraph(Graph* pG) {
    if(pG != NULL && *pG != NULL) {
        for(int i = 1; i <= (*pG)->order; ++i) {
            freeList(&((*pG)->adj[i]));
        }
    }
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    free(*pG);
    *pG = NULL;
}

// Access functions -----------------------------------------------------------

// getOrder()
// Returns the order of G.
int getOrder(Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

// getSize()
// Returns the size of G.
int getSize(Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

// getParent()
// Return the parent of vertex u in the Breadth-First tree created by BFS(), NIL otherwise.
int getParent(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() on an invalid vertex\n");
        exit(1);
    }
    return G->parent[u];
    
}

// getDiscover()
// Return the discover time of vertex u
int getDiscover(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    return G->discover[u];

}

// getFinish()
// Return the finish time of vertex u
int getFinish(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(1);
    }
    return G->finish[u];
}

// Manipulation procedures ----------------------------------------------------

// addEdge()
// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v,
// and v to the adjacency List of u.
// Pre: u, v must lie in the range 1 to getOrder(G).
void addEdge(Graph G, int u, int v) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(1);
    }
    if ((u < 1 || u > getOrder(G)) && (v < 1 || v > getOrder(G))) {
        fprintf(stderr, "Graph Error: calling addEdge() on invalid vertices\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}

// addArc()
// inserts a new directed edge from u to v,
// i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// Pre: u, v must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }
    if ((u < 1 || u > getOrder(G)) && (v < 1 || v > getOrder(G))) {
        fprintf(stderr, "Graph Error: calling addArc() on invalid vertices\n");
        exit(1);
    }
    if (length(G->adj[u]) > 0) {
        insertionSort(G, u, v);
    } else {
        append(G->adj[u], v);
    }
    G->size++;
}

// DFS()
// Performs the depth first search algorithm on G.
// Pre: length(S) == n, where n = getOrder(G).
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Graph Error: calling DFS() on invalid source\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); ++i) {
        G->color[i] = WHITE;
        G->parent[i] = NIL;
    }
    int time = 0;
    List SCopy = copyList(S);
    clear(S);
    moveFront(SCopy);
    while (index(SCopy) >= 0) {
        int x = get(SCopy);
        if (G->color[x] == WHITE) {
            Visit(G, S, x, &time);
        }
        moveNext(SCopy);
    }
    freeList(&SCopy);

}
void Visit(Graph G, List S, int x, int *time) {
    G->discover[x] = ++(*time);   // discover u
    G->color[x] = GRAY;
    moveFront(G->adj[x]);
    while (index(G->adj[x]) >= 0) {
        int y = get(G->adj[x]);
        if (G->color[y] == WHITE) {
            G->parent[y] = x;
            Visit(G, S, y, time);
        }
        moveNext(G->adj[x]);
    }
    G->color[x] = BLACK;
    G->finish[x] = ++(*time);  // finish u
    prepend(S, x);
}


// Other operations -----------------------------------------------------------

// transpose()
// Returns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    int n = getOrder(G);
    Graph NEW = newGraph(n);
    for (int i = 1; i <= n; ++i) {
        moveFront(G->adj[i]);
        while (index(G->adj[i])>= 0) {
            int y = get(G->adj[i]);
            addArc(NEW, y, i);
            moveNext(G->adj[i]);
        }
    }
    return NEW;
}

// copyGraph()
// Returns a reference to a new graph which is a copy of G.
Graph copyGraph(Graph G) {
    int n = getOrder(G);
    Graph GCopy = newGraph(n);
    for (int i = 1; i <= n; ++i) {
        GCopy->adj[i] = copyList(G->adj[i]);
        GCopy->color[i] = G->color[i];
        GCopy->parent[i] = G->parent[i];
        GCopy->discover[i] = G->discover[i];
        GCopy->finish[i] = G->finish[i];
    }
    return GCopy;
}

// printGraph()
// prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(1);
    }
    for (int i = 1; i <= getOrder(G); ++i) {
        fprintf(out, "%d: ", i);
        printList(out, G->adj[i]);
        fprintf(out, "\n");
    }
}

void insertionSort(Graph G, int u, int v) {
    moveBack(G->adj[u]);
    while(index(G->adj[u]) >= 0 && v < get(G->adj[u])){
        movePrev(G->adj[u]);
    }
    if(index(G->adj[u]) >= 0){
        insertAfter(G->adj[u], v);
    }
    else{
        prepend(G->adj[u], v);
    }

}



