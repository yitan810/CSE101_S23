/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#3
* Graph.h
* Header file for Graph ADT program
*********************************************************************************/ 

#include "List.h"
#define NIL -1
#define UNDEF -2

/*** Constructors-Destructors ***/
typedef struct nodeOfG{
	List ListArray[300];
	int parent[300],color[300],discover[300],finish[300]; 
	int vertex;
	int edge;
	int source;
	
}GraphObj;
typedef GraphObj* Graph;

// Constructors-Destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);
/*** Manipulation procedures ***/
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void DFS(Graph G, List S);
void Visit(Graph G, List S1, int x);
/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);