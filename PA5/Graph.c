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

void getPathHelper(List L, Graph G, int u);
void insertionSort(Graph G, int u, int v);

// structs --------------------------------------------------------------------
// private GraphObj type
typedef struct GraphObj {
    List *adj;
    int *color;
    int *parent;
    int *distance;
    int order;  // the number of vertices.
    int size;   // the number of edges.
    int source; // the label of the vertex that was most recently used as source for BFS.
    
} GraphObj;

// Constructors-Destructors ---------------------------------------------------
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adj = malloc(sizeof(List)*(n+1));
    G->color = calloc(n+1, sizeof(int));
    G->parent = calloc(n+1, sizeof(int));
    G->distance = calloc(n+1, sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    
    for(int i = 1; i <= n; ++i) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        G->distance[i] = INF;
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
    free((*pG)->distance);
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


int getDiscover(Graph G) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(1);
    }

}


int getFinish(Graph G, int u) {
    if(G == NULL) {
        fprintf(stderr, "Graph Error: calling getDist() on NULL Graph reference\n");
        exit(1);
    }
 
   
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

void DFS(Graph G, List S);


// Other operations -----------------------------------------------------------
Graph transpose(Graph G);
Graph copyGraph(Graph G);

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




