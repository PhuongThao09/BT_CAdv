#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"jrb.h"
#include"dllist.h"

typedef struct{
  JRB edges;//do thi chi chua thong tin ve canh,giong nhu do thi vo huong
  JRB vertices;//do thi chua thong tin ve dinh,key la id con val la name
}Graph;

  Graph createGraph();
void addVertex(Graph graph,int id,char* name);//them 1 dinh vao graph
char *getVertex(Graph graph,int id);//tim trong Vertex id co name la gi
void addEdge(Graph graph,int v1,int v2);//add canh co huong tu v1 toi v2
int hasEdge(Graph graph,int v1,int v2);//kiem tra xem co canh di tu v1 den v2 khong
int indegree(Graph graph,int v,int* output);//tim dinh vao
int outdegree(Graph graph,int v,int* output);//tim dinh ra
int getComponents(Graph graph);
void dropGraph(Graph graph);
int DGA(Graph graph);

Graph createGraph(){
  Graph g;
  g.edges=make_jrb();
  g.vertices=make_jrb();
  return g;
}


void addVertex(Graph g,int id,char* name)//Them 1 dinh vao graph
{
  JRB node=jrb_find_int(g.vertices,id);//tim trong Vertices xem co id hay khong
  if(node==NULL)
    jrb_insert_int(g.vertices,id,new_jval_s(strdup(name)));
}


char *getVertex(Graph graph,int id)//tim trong Vertex id co name la gi
{
  JRB node=jrb_find_int(graph.vertices,id);
  if(node==NULL) return NULL;
  else return jval_s(node->val);
}


void addEdge(Graph graph,int v1,int v2){
  JRB node,tree;
  if(!hasEdge(graph,v1,v2))
    {
      node=jrb_find_int(graph.edges,v1);
      if(node==NULL)
	{
	  tree=make_jrb();
	  jrb_insert_int(graph.edges,v1,new_jval_v(tree));
	}
      else
	tree=(JRB) jval_v(node->val);
    }
  jrb_insert_int(tree,v2,new_jval_i(1));
}


int hasEdge(Graph graph,int v1,int v2)
{
  JRB node,tree;
  node=jrb_find_int(graph.edges,v1);
  if(node==NULL) return 0;
  tree=(JRB) jval_v(node->val);
  if(jrb_find_int(tree,v2)==NULL)
    return 0;
  else return 1;
}


int indegree(Graph graph,int v,int* output)
{
  JRB tree,node;
  int total=0;
  jrb_traverse(node,graph.edges)
    {
      tree=(JRB) jval_v(node->val);
      if(jrb_find_int(tree,v))
	{
	  output[total]=jval_i(node->key);
	  total++;
	}
    }
  return total;
}

int outdegree(Graph graph,int v,int* output)
{
  JRB tree,node;
  int total;
  node=jrb_find_int(graph.edges,v);
  if(node==NULL) return 0;
  tree=(JRB) jval_v(node->val);
  total=0;
  jrb_traverse(node,tree)
    {
      output[total]=jval_i(node->key);
      total++;
    }
  return total;
}



int DAG(Graph graph)
{
  int visited[100];
  int n,output[100],i,u,v,start;
  Dllist node,stack;
  JRB vertex;
  jrb_traverse(vertex,graph.vertices)
    {
      memset(visited,0,sizeof(visited));

      start=jval_i(vertex->key);
      stack=new_dllist();
      dll_append(stack,new_jval_i(start));

      while(!dll_empty(stack))
	{
	  node=dll_last(stack);
	  u=jval_i(node->val);
	  dll_delete_node(node);
	  if(!visited[u])
	    {
	      visited[u]=1;
	      u=outdegree(graph,u,output);
	      for(i=0;i<n;i++)
		{
		  v=output[i];
		  if(v==start) return 0;
		  if(!visited[v])
		    dll_append(stack,new_jval_i(v));
		}
	    }
	}
    }
  return 1;
}


void dropGraph(Graph graph)
{
  JRB node,tree;
  jrb_traverse(node,graph.edges)
    {
      tree=(JRB) jval_v(node->val);
      jrb_free_tree(tree);
    }
  jrb_free_tree(graph.edges);
  jrb_free_tree(graph.vertices);
}


int main()
{
  Graph g=createGraph();
  addVertex(g,0,"V0");
  addVertex(g,1,"V1");
  addVertex(g,2,"V2");
  addVertex(g,3,"V3");

  addEdge(g,0,1);
  addEdge(g,1,2);
  addEdge(g,2,0);
  addEdge(g,1,3);

  if(DAG(g)) printf("The graph is acycle\n");
  else printf("Have cycles in the graph\n");
  
  return 0;
}
