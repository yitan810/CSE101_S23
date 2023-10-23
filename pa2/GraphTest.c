/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#2
* GraphTest.c 
* Test Client for Graph ADT program
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph G = NULL;

   // Build graph G 
   FILE* out;
   out = fopen(argv[1], "w");
   G = newGraph(5);
  
   printf("create a graph\n\n");
   printf("vertex:%d edge:%d \n\n",getOrder(G),getSize(G));
   
   
   
   addEdge(G, 1, 2);
   addArc(G, 2, 3);
   printf("add three edge\n\n");
   printf("vertex:%d edge:%d \n\n",getOrder(G),getSize(G));
   
   printf("printf Graph to output_file\n\n");
   printGraph(out,G);
    
    printf("Execute function  MakeNull\n\n");
    makeNull(G);
    printf("vertex:%d edge:%d \n\n",getOrder(G),getSize(G));
    
    printf("add three edge again\n\n");
    addEdge(G, 1, 2);
    addArc(G, 2, 3);
    printf("vertex:%d edge:%d \n\n",getOrder(G),getSize(G));
    
    printf("Execute function  BFS\n\n");
    BFS(G,1);
    
    printf("The source of BFS is %d\n\n",getSource(G));
    printf("Parent: %d\n\n",getParent(G,3));
    printf("Calculate distance for 1-3: %d\n\n",getDist(G, 3));

    List L=newList();
    getPath(L, G,3);
    printf("printf path to output_file\n\n");
    printList(out, L);


	freeGraph(&G);
    return(0);
}
