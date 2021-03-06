#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct graph graph;

struct graph{
	size_t v_count;
	bool *isvisited;
	bool **adj_matrix;
	int *prev_list;
};

graph* create_graph(int);
void set_edge(graph*,int,int,bool);
bool dfs(graph*,int,int);

int main(){
	graph *g = create_graph(7);
	set_edge(g,0,1,1);
	set_edge(g,0,2,1);
	set_edge(g,1,3,1);
	set_edge(g,1,4,1);
	set_edge(g,2,5,1);
	set_edge(g,2,6,1);
	
	int start_node = 0,goal_node = 5;

	if(dfs(g,start_node,goal_node)){
		while(goal_node != -1){
			printf("%d, ",goal_node);
			goal_node = g->prev_list[goal_node];
		}
	}
}

graph* create_graph(int v){
	graph *g = malloc(sizeof(graph));
	g->v_count = v;
	g->isvisited = calloc(v,sizeof(bool));
	g->adj_matrix = malloc(sizeof(bool*) * v);
	for(int i = 0;i < v;i++){
		g->adj_matrix[i] = calloc(v,sizeof(bool));
	}	
	g->prev_list = malloc(sizeof(int) * v);
	memset(g->prev_list,-1,sizeof(int) * v);
	return g;
}

void set_edge(graph *g,int v1,int v2,bool w){
	g->adj_matrix[v1][v2] = w;
	g->adj_matrix[v2][v1] = w;
}
 
bool dfs(graph *g,int at,int goal){
	g->isvisited[at] = 1;
	for(int to = 0;to < g->v_count;to++){
		if(g->adj_matrix[at][to] && !g->isvisited[to]){
			g->prev_list[to] = at;
			if(to == goal){
				return 1;
			}
			if(dfs(g,to,goal)){
				return 1;
			}
		}
	}
	return 0;
}
