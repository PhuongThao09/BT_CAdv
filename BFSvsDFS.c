#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"dllist.h"
#include"jrb.h"
#include"jval.h"

typedef JRB Graph;

Graph createGraph();

void addEgde(Graph graph, int v1, int v2);// them dinh vao do thi
int adjacent(Graph graph, int v1, int v2);// kiem tra v1 v2 co ke ko
int getAdjacentVertices(Graph graph, int vertex, int* output);//lay ra canh ke cua vertex
void dropGraph(Graph graph);//xoa do thi
void printVertex(int v);
void BFS(Graph graph, int start, int stop, void(*func)(int));
void DFS(Graph graph, int start, int stop, void(*func)(int));
int main(){
   	int i, n, output[100];
	Graph g = createGraph();
	addEgde(g, 0, 1);
	addEgde(g, 0, 2);
	addEgde(g, 1, 2);
	addEgde(g, 1, 3);
   	addEgde(g, 2, 3);
	addEgde(g, 2, 4);
	addEgde(g, 4, 5);
	n = getAdjacentVertices(g, 1, output);
	if(n == 0)
		printf("khong co dinh lien ke nut 1\n");
	else{
		printf("dinh lien ke cua nut 1: ");
		for(i =0;i<n;i++){
			printf("%5d", output[i]);
		}
		printf("\n");
	}
	printf("BFS start from node 1 to 5 ");
	BFS(g, 1, 4, printVertex);

   	printf("\nDFS start from node 2 to 5 ");
	DFS(g, 1, 4, printVertex);
	printf("\n");
	return 0;
}

void dropGraph(Graph graph){
	JRB node, tree;
	jrb_traverse(node, graph){
		tree = (JRB) jval_v(node->val);
		jrb_free_tree(tree);
		
	}
	jrb_free_tree(graph);
}
int adjacent(Graph graph, int v1, int v2){
	JRB node, tree;
	node = jrb_find_int(graph, v1);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	if(jrb_find_int(tree, v2)==NULL)
		return 0;
	else
		return 1;
}

void addEgde(Graph graph, int v1, int v2){
	JRB node, tree;
	if(!adjacent(graph, v1, v2)){
		node = jrb_find_int(graph,v1);
		if(node == NULL){
			tree = make_jrb();
			jrb_insert_int(graph,v1, new_jval_v(tree));
		}else{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree,v2,new_jval_i(1));
	}
	if(!adjacent(graph, v2, v1)){
		node = jrb_find_int(graph,v1);
		if(node == NULL){
			tree = make_jrb();
			jrb_insert_int(graph,v2, new_jval_v(tree));
		}else{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree,v1,new_jval_i(1));
	}
}

int getAdjacentVertices(Graph graph, int vertex, int* output){
	JRB tree, node;
	int total;
	node = jrb_find_int(graph, vertex);
	if(node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	total = 0;
	jrb_traverse(node, tree){
		output[total] = jval_i(node->key);
		total++;
	}
	return total;
}
void printVertex(int v) {
	printf("%4d", v);
}
void BFS(Graph graph, int start, int stop, void(*func)(int)){
	int visited[1000] = {};
	int n, output[100], i, u, v;
	Dllist node, queue;

	queue = new_dllist();
	dll_append(queue, new_jval_i(start));//chen vao queue gia tri start

	while (!dll_empty(queue)){
		node = dll_first(queue);
		u = jval_i(node->val);
		dll_delete_node(node);
		if(!visited[u]){
			func(u);
			visited[u] = 1;
			if(u == stop) return ;
			n = getAdjacentVertices(graph, u, output);
			for(i =0;i<n;i++){
				v = output[i];
				if(!visited[v]){
					dll_append(queue, new_jval_i(v));
				}
			}
		}
	}
	
}

void DFS(Graph graph, int start, int stop, void(*func)(int)){
	int visited[1000] = {};
	int n, output[100], i, u, v;
	Dllist node, stack;

	stack = new_dllist();
	dll_append(stack, new_jval_i(start));

	while (!dll_empty(stack)){
		node = dll_last(stack);
		u = jval_i(node->val);
		dll_delete_node(node);
		if(!visited[u]){
			func(u);
			visited[u] = 1;
			if(u == stop) return ;
			n = getAdjacentVertices(graph, u, output);
			for(i =0;i<n;i++){
				v = output[i];
				if(!visited[v]){
					dll_append(stack, new_jval_i(v));
				}
			}
		}
	}
	
}
Graph createGraph(){
	return make_jrb();
}
