/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#2
* Graph.c 
* C source code for Graph ADT program
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

Graph newGraph(int n){
	Graph G=(Graph)malloc(sizeof(GraphObj));
	G->vertex=n;
	G->edge=0; 
	G->source=NIL;
	int i;
	
	for(i=1;i<=n;++i){
		G->ListArray[i]=newList();
		G->parent[i]=NIL;
		G->dis[i]=INF;
		G->color[i]=0;
	}
	return G;
}
void freeGraph(Graph* pG){
	int i;
	for(i=1;i<=getOrder(*pG);++i){
		List cur=(*pG)->ListArray[i];
		(*pG)->color[i]=0;
		freeList(&cur);
	}
	(*pG)->source=NIL;
	free(*pG);
	pG=NULL;
}
/*** Access functions ***/
int getOrder(Graph G){
	return G->vertex;
}
int getSize(Graph G){
	return G->edge;
}
int getSource(Graph G){
	return G->source;
}
int getParent(Graph G, int u){
	if(getSource(G)==NIL) return NIL;
	return G->parent[u];
}
int getDist(Graph G, int u){
	if(getSource(G)==NIL) return INF;
	return G->dis[u];
}
void getPath(List L, Graph G, int u){
	if(getSource(G)==NIL) return ;
	while(u!=NIL){
		prepend(L,u);
		u=G->parent[u];
	} 
}
/*** Manipulation procedures ***/
void makeNull(Graph G){
	int i;
	for(i=1;i<=getOrder(G);++i){
		List cur=(G)->ListArray[i];
		G->color[i]=0;
		freeList(&cur);
		cur=newList();
	}
	G->edge=0;
}
void addEdge(Graph G, int u, int v){
	addArc(G,u,v);
	addArc(G,v,u);
}
void addArc(Graph G, int u, int v){
	append(G->ListArray[u],v);
	G->edge++;
}

void BFS(Graph G, int s){
	if(G == NULL){
		printf("Calling BFS function in NULL Graph.\n");
		exit(1);
	}
	G -> source = s;
	for(int x = 1; x <= getOrder(G); x++){
		G->dis[x] = INF;
		G->parent[x] = NIL;
		G->color[x] = 0;
	}

	G->dis[s] = 0;
	G->parent[s] = NIL;
	G->color[s] = 1; 

	List list1 = newList();
	append(list1,s);

	while(length(list1) != 0){
		moveFront(list1);

		int x = get(list1); 
		moveFront(G->ListArray[x]);
		List list2 = G->ListArray[x];
		for(int i=1; i<=length(list2); i++){
			int y = get(list2);
			if(G->color[y] == 0){
				G->color[y] = 1;
				G->dis[y] = G->dis[x] + 1;
				G->parent[y] = x;
				append(list1, y); 
			} 
		moveNext(list2);
		}
		G->color[x] = 2;
		deleteFront(list1);
	}

	free(list1); 
}


/*void BFS(Graph G, int s){
	G->source=s;
	int i;
	int queue[10000],front=0,tail=0;
	int IsExist[1000];
	for(i=1;i<=getOrder(G);++i){
		IsExist[i]=0;
		G->parent[i]=NIL;
		G->dis[i]=INF;
	}
	queue[tail++]=s;
	IsExist[s]=1;
	G->dis[s]=0;
	while(front<tail){
		int cur=queue[front++];
		
		Node node = G->ListArray[cur]->front;
		while(node!=NULL){
			int v=node->data;
		    if(IsExist[v]==1){
		    	node = node->next;
		    	continue;
			}
		    IsExist[v]=1;
		    queue[tail++]=v;
		    G->parent[v]=cur;
		    G->dis[v]=G->dis[cur]+1;
		    node = node->next;
		}
	} 
}*/
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	int i;
	for(i=1;i<=getOrder(G);++i){
		fprintf(out,"%d: ",i);
		printList(out,G->ListArray[i]);
		fprintf(out,"\n");
	}
}

