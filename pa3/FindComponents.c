/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#3
* FindComponents.c
* Main program for Graph ADT program using DFS
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

int main(int argc, char* argv[]){
    FILE *fptr;
    int n;

    fptr = fopen(argv[1],"r");
    fscanf(fptr, "%d", &n);
    Graph G = newGraph(n);

    while(1){
        int u, v;
        fscanf(fptr, "%d %d",&u,&v);
        if(u==0 && v==0){
			break;
		}
		addArc(G,u,v);
    }
    fclose(fptr);

    List L = newList();
    for(int i=1;i<=getOrder(G);i++){
        append(L, i);
    }

    DFS(G, L);
    Graph GT = transpose(G);
    DFS(GT, L);
    
    int count = 0;
    List NIL_List = newList();
    for(moveBack(L); index(L)>=0; movePrev(L)){
        if(GT->parent[get(L)] == NIL){
            append(NIL_List, get(L));
            count++;
        }
    }

    FILE* out;
	out = fopen(argv[2], "w");
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    fprintf(out, "G contains %d strongly connected components:\n", count);

    moveFront(L);
    moveFront(NIL_List);
    for(int i=1; i<=count; i++){
        fprintf(out, "Component %d:", i);
        int anc = get(NIL_List);
        for(moveFront(L);index(L)>=0;moveNext(L)){
            if(get(L)==anc){
                fprintf(out, " %d", get(L));
                if(index(L)==length(L)-1){
                    fprintf(out, "\n");
                }
                else{
                    moveNext(L);
                    while(GT->parent[get(L)] != NIL){
                        fprintf(out, " %d", get(L));
                        if(index(L)==length(L)-1){
                            break;
                        }
                        moveNext(L);
                    }
                    fprintf(out, "\n");
                }
            }
        }
        moveNext(NIL_List);
    }

    freeList(&L);
    freeList(&NIL_List);

    freeGraph(&G);
    freeGraph(&GT);
    fclose(out);
    return 0;
}