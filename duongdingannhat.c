#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"jrb.h"
#include"dllist.h"

#define INFINITE_VALUE 10000000

typedef struct{
  JRB edges;
  JRB vertices;
}Graph;

Graph createGraph();
void addVertex(Graph graph,int id,char* name);//luon add dinh truoc add canh
char *getVertex(Graph graph,int id);
void addEdge(Graph graph,int v1,int v2, double weight);
double getEdgeValue(Graph graph,int v1,int v2);
int indegree(Graph graph,int v,int* output);
int outdegree(Graph graph,int v,int* output);
void dropGraph(Graph graph);
double shorttestPath(Graph graph,int s,int t,int* path,int* length);

int main()
{
  int s,t,i,length;
  int path[1000];
  double w;
  char name;
  Graph g=createGraph();
  addVertex(g, 0, "V0");
  addVertex(g, 1, "V1");
  addVertex(g, 2, "V2");
  addVertex(g, 3, "V3");
  addEdge(g, 0, 1, 1);
  addEdge(g, 1, 2, 3);
  addEdge(g, 2, 0, 3);
  addEdge(g, 1, 3, 1);
  addEdge(g, 3, 2, 1);
  s = 0;
  t = 3;
  w=shorttestPath(g,s,t,path,&length);
  if(w==INFINITE_VALUE) printf("Khong tim duoc duong di ngan nhat tu %s den %s.\n",getVertex(g,s),getVertex(g,t));
  else
    {
      printf("Duong di ngan nhat tu %s den %s co do dai la %.1f.\n",getVertex(g,s),getVertex(g,t),shorttestPath(g,s,t,path,&length));
      for(i=0;i<length;i++)
	printf("=> %s ",getVertex(g,path[i]));
    }
  printf("\n");
  dropGraph(g);
  return 0;
}

Graph createGraph(){
  Graph g;
  g.edges=make_jrb();
  g.vertices=make_jrb();
  return g;
}

void addVertex(Graph g,int id,char* name)
{
  JRB node=jrb_find_int(g.vertices,id);
  if(node==NULL)
    jrb_insert_int(g.vertices,id,new_jval_s(strdup(name)));
}

char *getVertex(Graph g,int id)
{
  JRB node=jrb_find_int(g.vertices,id);
  if(node==NULL) return  NULL;
  else return jval_s(node->val);
}

void addEdge(Graph g,int v1,int v2,double weight)
{
  JRB node,tree;
  if(getEdgeValue(g,v1,v2)==INFINITE_VALUE)
    {
      node=jrb_find_int(g.edges,v1);
      if(node==NULL)
	{
	  tree=make_jrb();
	  jrb_insert_int(g.edges,v1,new_jval_v(tree));
	}
      else
	tree=(JRB) jval_v(node->val);
      jrb_insert_int(tree,v2,new_jval_d(weight));
    }
}

double getEdgeValue(Graph g,int v1,int v2)
{
  
  JRB node,tree;
  node=jrb_find_int(g.edges,v1);
  if(node==NULL) return INFINITE_VALUE;
  tree=(JRB) jval_v(node->val);
  node=jrb_find_int(tree,v2);
  if(node==NULL) return INFINITE_VALUE;
  else return jval_d(node->val);
  
}

int indegree(Graph g,int v,int* output)
{
  JRB tree,node;
  int total=0;
  jrb_traverse(node,g.edges)
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

int outdegree(Graph g,int v,int* output)
{
  JRB tree,node;
  int total;
  node=jrb_find_int(g.edges,v);
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

double shorttestPath(Graph g,int s,int t,int* path,int* length)
{
  double distance[1000],w,total,min;
  int pre[1000],tmp[1000];
  int n,output[1000],i,u,v,start;
  Dllist ptr,queue,node;

  for(i=0;i<1000;i++)
    distance[i]=INFINITE_VALUE;
  distance[s]=0;
  pre[s]=s;

  queue=new_dllist();
  
  dll_append(queue,new_jval_i(s));

  while(!dll_empty(queue))
    {
      //lay u tu hang doi dau tien
      min=INFINITE_VALUE;
      dll_traverse(ptr,queue)
	{
	  u=jval_i(ptr->val);
	  if(min>distance[u])
	    {
	      min=distance[u];
	      node=ptr;
	    }
	}
       u=jval_i(node->val);
      dll_delete_node(node);

      // if(u==t) break;

      n=outdegree(g,u,output);
      for(i=0;i<n;i++)
	{
	  v=output[i];
	  w=getEdgeValue(g,u,v);
	  if(distance[v]>distance[u]+w)
	    {
	      distance[v]=distance[u]+w;
	      pre[v]=u;
	     dll_append(queue,new_jval_i(v));
	    }
	   
	}
    }

  total=distance[t];
  if(total!=INFINITE_VALUE)
    {
      tmp[0]=t;
      n=1;
      while(t!=s)
	{
	  t=pre[t];
	  tmp[n++]=t;
	}

      for(i=n-1;i>=0;i--)
	path[n-i-1]=tmp[i];
      *length=n;
    }
  return total;
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
