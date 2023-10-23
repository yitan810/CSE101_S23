/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#3
* GraphTest.c
* Test Client for Graph ADT program
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]){

    Graph G = newGraph(8);
    
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);

    printGraph(stdout, G);
    printf("\n");
    printf("vertices: %d\n", getOrder(G));
    printf("Edges: %d\n", getSize(G));
    printf("\n");

    printf("after transpose\n");
    printGraph(stdout, transpose(G));
    printf("\n");

    Graph newgraph = copyGraph(G);
    printGraph(stdout, newgraph);

    List L = newList();
    for(int i=1; i<=getOrder(G); i++){
        append(L, i);
    }

    DFS(G, L);
    printList(stdout, L);
    printf("\n");

    freeList(&L);
    freeGraph(&G);

    return 0;
}
