/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#2
* Graph.h
* Header file for Graph ADT program
*********************************************************************************/ 

#include "List.h"
#define NIL 0
#define INF 100000

/*** Constructors-Destructors ***/
typedef struct nodeOfG{
	List ListArray[300];
	int parent[300],dis[300],color[300]; 
	int vertex;
	int edge;
	int source;
	
}GraphObj;
typedef GraphObj* Graph;
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
