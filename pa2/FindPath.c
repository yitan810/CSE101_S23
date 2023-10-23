/********************************************************************************* 
* Daria Tan, ytan87 
* 2023 Winter CSE101 PA#2
* FindPath.h 
* main program for Graph ADT program
*********************************************************************************/ 

#include "Graph.h"
#include<stdio.h>
int main(int argc, char* argv[]){
	FILE* in;
	in=fopen(argv[1],"r");
	int n,i;
	fscanf(in,"%d",&n);
	Graph G=newGraph(n);
	while(1){
		int u,v;
		fscanf(in,"%d %d",&u,&v);
		if(u==0&&v==0){
			break;
		}
		addEdge(G,u,v);
	}
	int len=getOrder(G);
	for(i=0;i<len;++i){
    	MySort(G->ListArray[i+1]);
  	}
	FILE* out;
	out = fopen(argv[2], "w");
    printGraph(out,G);
    fprintf(out,"\n");
    while(1){
		int u,v;
		fscanf(in,"%d %d",&u,&v);
		if(u==0&&v==0){
			break;
		}
		BFS(G,u);
		
		if(getDist(G,v)==INF){
			fprintf(out,"The distance from %d to %d is infinity\n",u,v);
			fprintf(out,"No %d-%d path exists\n\n",u,v);
			continue;
		}
		fprintf(out,"The distance from %d to %d is %d\n",u,v,getDist(G,v));
		
		fprintf(out,"A shortest %d-%d path is: ",u,v);
		
		List path=newList();
		getPath(path,G,v);
		
		printList(out,path);
		fprintf(out,"\n\n");

		freeList(&path);
	}
	
	freeGraph(&G);
	return 0;
}
