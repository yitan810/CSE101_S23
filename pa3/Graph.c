/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#3
* Graph.c 
* C source code for Graph ADT program
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int time;

Graph newGraph(int n){
	Graph G=(Graph)malloc(sizeof(GraphObj));
	G->vertex=n;
	G->edge=0; 
	G->source=NIL;
	
	for(int i=1;i<=n;i++){
		G->ListArray[i]=newList();
		G->parent[i]=NIL;
		G->color[i]=0;
		G->discover[i]=UNDEF;
		G->finish[i]=UNDEF;
	}
	return G;
}
void freeGraph(Graph* pG){
	for(int i=1;i<=getOrder(*pG);i++){
		List cur=(*pG)->ListArray[i];
		(*pG)->parent[i]=NIL;
		(*pG)->color[i]=0;
		(*pG)->discover[i]=UNDEF;
		(*pG)->finish[i]=UNDEF;
		freeList(&cur);
	}
	(*pG)->vertex=0;
	(*pG)->edge=0;
	(*pG)->source=NIL;
	*pG=NULL;
	free(*pG);
}

int getOrder(Graph G){
	return G->vertex;
}
int getSize(Graph G){
	return G->edge;
}
int getParent(Graph G, int u){
	if(u<1 || u>getOrder(G)){
		printf("Error: calling getParent function with an out-of-range arguemnt\n");
		exit(1);
	}
	return G->parent[u];
}
int getDiscover(Graph G, int u){
	if(u<1 || u>getOrder(G)){
		printf("Error: calling getDiscover function with an out-of-range arguemnt\n");
		exit(1);
	}
	return G->discover[u];
}
int getFinish(Graph G, int u){
	if(u<1 || u>getOrder(G)){
		printf("Error: calling getFinish function with an out-of-range arguemnt\n");
		exit(1);
	}
	return G->finish[u];
}


void addArc(Graph G, int u, int v){
	if(u<1 || u>getOrder(G)){
		printf("Error: calling addArc function with arguemnt u is out of range\n");
		exit(1);
	}
	else if(v<1 || v>getOrder(G)){
		printf("Error: calling addArc function with arguemnt v is out of range\n");
		exit(1);
	}
	if(length(G->ListArray[u])==0){
		append(G->ListArray[u], v);
	}
	else{
		for(moveFront(G->ListArray[u]);index(G->ListArray[u])>=0;moveNext(G->ListArray[u])){
			if(get(G->ListArray[u])==v){
				return ;
			}
		}
		moveFront(G->ListArray[u]);
		while(v>get(G->ListArray[u]) && index(G->ListArray[u])!=length(G->ListArray[u])-1){
			moveNext(G->ListArray[u]);
		} 
		if(v>get(G->ListArray[u]) && index(G->ListArray[u]) == length(G->ListArray[u])-1){
			append(G->ListArray[u],v);
		}
		else{
			insertBefore(G->ListArray[u], v);
		}
	}
	G->edge++;
}
void addEdge(Graph G, int u, int v){
	if(u<1 || u>getOrder(G)){
		printf("Error: calling addEdge function with arguemnt u is out of range\n");
		exit(1);
	}
	else if(v<1 || v>getOrder(G)){
		printf("Error: calling addEdge function with arguemnt v is out of range\n");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->edge--;
	
}

void DFS(Graph G, List S){
	if(length(S)!=getOrder(G)){
		printf("Error: calling DFS with an invalid List\n");
		exit(1);
	}
	for(int i=1;i<=getOrder(G);i++){
		G->color[i] = 0;
		G->parent[i] = NIL;
	}
	time = 0;
	List S1 = newList();
	for(moveFront(S); index(S)>=0; moveNext(S)){
		int x = get(S);
		if(G->color[x] == 0){
			Visit(G, S1, x);
		}
	}
	for(moveFront(S1); index(S1)>=0; moveNext(S1)){
		append(S, get(S1));
	}
	for(int i=0; i<length(S1); i++){
		deleteFront(S);
	}
	freeList(&S1);

}

void Visit(Graph G, List S1, int x){
	G->discover[x] = ++time;
	G->color[x] = 1;
	List adj = G->ListArray[x];
	for(moveFront(adj); index(adj)>=0; moveNext(adj)){
		int y = get(adj);
		if(G->color[y] == 0){
			G->parent[y] = x;
			Visit(G, S1, y);
		}
	}
	G->color[x] = 2;
	G->finish[x] = ++time;
	prepend(S1, x);
}

Graph transpose(Graph G){
	Graph graph = newGraph(getOrder(G));

	for(int i=1;i<=getOrder(G);i++){
		moveFront(G->ListArray[i]);
		while(index(G->ListArray[i]) != -1){
			int data = get(G->ListArray[i]);
			addArc(graph,data,i);
			moveNext(G->ListArray[i]);
		}
	}
	return graph;
}



Graph copyGraph(Graph G){
	Graph graph = newGraph(getOrder(G));

	for(int i=1; i<=getOrder(G);i++){
		graph->ListArray[i]=G->ListArray[i];
		graph->parent[i]=G->parent[i];
		graph->color[i]=G->color[i];
		graph->discover[i]=G->discover[i];
		graph->finish[i]=G->finish[i];
	}
	graph->vertex=G->vertex;
	graph->edge=G->edge;
	graph->source=G->source;

	return graph;
}

void printGraph(FILE* out, Graph G){
	for(int i=1;i<=getOrder(G);++i){
		fprintf(out,"%d: ",i);
		printList(out,G->ListArray[i]);
		fprintf(out,"\n");
	}
}

