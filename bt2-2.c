#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"

typedef JRB Graph;

Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices(Graph graph, int vertex, int *output);
void dropGraph(Graph graph);

int main()
{
	int i, n, output[100];
	Graph g = createGraph();
	addEdge(g, 0, 1);
	addEdge(g, 0, 2);
	addEdge(g, 1, 2);
	addEdge(g, 1, 3);
	n = getAdjacentVertices(g, 2, output);
	if (n==0)
		printf("No adjacent Vertices of node 1\n");
	else
	{
		printf("adjacent of node 1 %d :", n);
                for (i=0;i<n;i++)
                    printf("%5d",output[i]);
        }
	printf("\n");
        dropGraph(g);
        return 0;

}

Graph createGraph()
{
        return make_jrb();
}

void addEdge(Graph graph, int v1, int v2)
{
	JRB node, tree;
	if (!adjacent(graph, v1, v2))
	{
		node = jrb_find_int(graph, v1);
		if (node == NULL) {
			tree = make_jrb();
			jrb_insert_int(graph, v1, new_jval_i(tree));
		} else
		{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v2, new_jval_i(1));
	}
	if (!adjacent(graph,v2,v1))
	{
		node = jrb_find_int(graph,v2);
		if (node == NULL)
		{
			tree = make_jrb();
			jrb_insert_int(graph, v2, new_jval_i(tree));
		} else
		{
			tree = (JRB) jval_v(node->val);
		}
		jrb_insert_int(tree, v1, new_jval_i(1));
	}	
}

int adjacent(Graph graph, int v1, int v2)
{
	JRB node, tree;
	node = jrb_find_int(graph,v1);
	if (node == NULL)
		return 0;
	tree = (JRB) jval_v(node->val);
	if (jrb_find_int(tree,v2) == NULL)
	return 0;
	else return 1;
}

int getAdjacentVertices(Graph graph,  int vertex, int *output)
{
	JRB node, tree;
	int total;
	node = jrb_find_int(graph, vertex);
	if (node == NULL)
		return total = 0;
	tree = (JRB) jval_v(node->val);
	total = 0;
	jrb_traverse(node, tree)
	{
		output[total] = jval_i(node->key);
		total++;
	}
	return total;
}

void dropGraph(Graph graph)
{
	JRB node, tree;
	jrb_traverse(node,graph)
	{
		tree = (JRB) jval_v(node->val);
		jrb_free_tree(tree);
	}
	jrb_free_tree(graph);

}
