#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/jrb.h"
#include "libfdr/dllist.h"
#include"libfdr/jval.h"
#include "libfdr/fields.h"

#define INF 10000000

typedef struct {
   JRB edges;
   JRB vertices;
} Graph;

Graph createGraph();
void addVertex(Graph graph, int id, char* name);
char *getVertex(Graph graph, int id);
void addEdge(Graph graph, int v1, int v2,double weight);//them canh voi weight
int hasEdge(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);//lay weight cua canh
int indegree(Graph graph, int v, int* output);//so canh di vao
int outdegree(Graph graph, int v, int* output);//so canh di ra
int DAG(Graph graph);
void dropGraph(Graph graph);
void topologicalSort(Graph g, int* output, int* n);
void readfile(Graph g,int *dinh, int *canh);
void printVertex(int v)
{
    printf("%4d", v);
}

double shortestPath(Graph graph, int s, int t, int* path,int*length);//tim duong ngan nhat
int main()
{
    Graph g = createGraph();
    int choice;
    int dinh=0,canh=0;
	choice=1;
	printf("He thong day dien\n");
	printf("\t1.Doc va in ma tran du lieu.\n");
	printf("\t2.Tim so dinh, so cung.\n");
	printf("\t3.Nhap vao 1 phong, liet ke cac phong co day dan voi no.\n");
	printf("\t4.Kiem tra su lien ket giua hai phong.\n");
	printf("\t5.Kiem tra su lien thong.\n");
	printf("\t6.Thoat.\n");
	while(choice!=6)//lua chon
	{
        if (choice>6 || choice <1) printf("Lua chon khong hop le! Vui long nhap lai:");
		else printf("Hay chon chuc nang ban muon:");
		scanf("%d",&choice);
		while (getchar()!='\n');
		switch(choice)
		{
            case 1:
                addVertex(g,1,"P1");
                addVertex(g,2,"P2");
                addVertex(g,3,"P3");
                addVertex(g,4,"P4");

                addEdge(g,2,1,3);addEdge(g,1,2,3);
                addEdge(g,3,1,4);addEdge(g,1,3,4);
                addEdge(g,4,1,2);addEdge(g,1,4,2);
                addEdge(g,3,2,3);addEdge(g,2,3,3);
                addEdge(g,4,2,2);addEdge(g,2,4,2);
                addEdge(g,4,3,1);addEdge(g,3,4,1);
                printf("%d",getEdgeValue(g,1,2));
                /*for(int i=1;i<=4;i++)
                {
                    for(int j=1;j<=4;j++)
                    {
                        if(i==j) printf("0 ");
                        else printf("%d ",getEdgeValue(g,i,j));
                    }
                    printf("\n");
                }*/

            break;
            case 2:break;
        }
    }
    
}
Graph createGraph()
{
    Graph graph;
    graph.edges=make_jrb();
    graph.vertices= make_jrb();
    return graph;
}
void addVertex(Graph graph, int id, char* name)
{
    if(jrb_find_int(graph.vertices, id)==NULL)
        jrb_insert_int(graph.vertices, id,new_jval_s(name));
        return;
}
char *getVertex(Graph graph, int id)
{
    JRB tmp=jrb_find_int(graph.vertices, id);
    if(tmp==NULL)
    return NULL;
    else return jval_s(tmp->val);
}
void addEdge(Graph graph, int v1, int v2, double weight)
{
	JRB tree;
	JRB node = jrb_find_int(graph.edges, v1);
	if (node == NULL) 
    {
		tree = make_jrb();
		jrb_insert_int(graph.edges, v1, new_jval_v(tree));
	}
	else 
    {
		tree = (JRB)jval_v(node->val);
	}
	jrb_insert_int(tree, v2, new_jval_v(weight));
}
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node = jrb_find_int(graph.edges, v1);

    if(node == NULL) return INF;
    else{
        JRB subTree = (JRB)jval_v(node->val);
        JRB node2 = jrb_find_int(subTree, v2);

        if(node2 == NULL) return INF;
        else return jval_d(node2->val);
    }
}
int hasEdge(Graph graph, int v1, int v2)
{
    JRB node =jrb_find_int(graph.edges,v1);
    if(node==NULL)
        return -1;
    else
    {
        JRB tree=(JRB)jval_v(node->val);
        JRB tmp=jrb_find_int(tree,v2);
        if(tmp=NULL)
            return 0;
        else 
            return 1;  
    }
}

int indegree(Graph graph, int v, int* output)
{
    JRB tree,node;
    int total=0;
    jrb_traverse(node,graph.edges)
    {
        tree=(JRB)jval_v(node->val);
        if(jrb_find_int(tree,v))
        {
            output[total]=jval_i(node->key);
            total++;
        }
    }
    return total;
}
int outdegree(Graph graph, int v, int* output)
{
    JRB tree, node;
	int total = 0;
	node = jrb_find_int(graph.edges, v);
	if (node == NULL)
		return 0;
	else {
		tree = jval_v(node->val);
		jrb_traverse(node, tree) {
			output[total] = jval_i(node->key);
			total++;
		}
	}
	return total;
}
double shortestPath(Graph graph, int s, int t, int* path,int*length)
{
    double distance[1000], total;
    int previous[1000], u, visit[1000], tmp[1000];
    int i, number;
    for (int i=0; i<1000; i++){
        distance[i] = INF;
        visit[i] = 0;
        previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visit[s] = 1;
    
    Dllist ptr, queue, node;
    queue = new_dllist();
    dll_append(queue, new_jval_i(s));
    
    // Duyet Queue
    while (!dll_empty(queue)){
        node = dll_first(queue);
        int u = jval_i(node->val);
        dll_delete_node(node);
        int output[100];
        number = outdegree(graph,u,output);
        for (int i =0; i<number; i++) 
        {
            if (visit[output[i]]==0) 
            {
                visit[output[i]] = 1;
                dll_append(queue,new_jval_i(output[i]));
            }
            if ((getEdgeValue(graph,u,output[i])+distance[u])<distance[output[i]]) 
            {
                distance[output[i]]= getEdgeValue(graph,u,output[i])+distance[u];
                previous[output[i]] = u;
            }
        }
    }
   total = distance[t];
   if (total != INF)
   {
       tmp[0] = t;
       number = 1;              
       while (t != s)
       {
             t = previous[t];
             tmp[number++] = t;
       }
       for (i=number-1; i>=0; i--)
           path[number-i-1] = tmp[i];
       *length = number;       
   }
   return total;
}

int DAG(Graph graph)//check cycle
{
   int visited[1000];
   int n, output[100], i, u, v, start;
   Dllist node, stack;
   JRB vertex;
   
   jrb_traverse(vertex, graph.vertices)
   {
       memset(visited, 0, sizeof(visited));

       start = jval_i(vertex->key);              
       stack = new_dllist();
       dll_append(stack, new_jval_i(start));
    
       while ( !dll_empty(stack) )
       {
          node = dll_last(stack);
          u = jval_i(node->val);
          dll_delete_node(node);
          if (!visited[u])
          {
              visited[u] = 1;
              n = outdegree(graph, u, output);
              for (i=0; i<n; i++)
              {
                  v = output[i];
                  if ( v == start ) // cycle detected 
                     return 0;
                  if (!visited[v])    
                     dll_append(stack, new_jval_i(v));
              }
          }           
       }
   }
   return 1; // no cycle    
}
void dropGraph(Graph graph)
{
    JRB node,tree;
    jrb_traverse(node,graph.edges)
    {
        tree=(JRB) jval_v (node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
	jrb_free_tree(graph.vertices);
}
void topologicalSort(Graph g, int* output, int* n)
{
    int indeg[1000], tmp[100], m, i, u, v, total;
    JRB vertex;
    Dllist node, queue;
    queue = new_dllist();
    jrb_traverse(vertex, g.vertices)
    {
        u = jval_i(vertex->key);
        indeg[u] = indegree(g, u, tmp);
        if (indeg[u]==0)
        dll_append(queue, new_jval_i(u));
    }
    total = 0;
    while ( !dll_empty(queue) )
    {
        node = dll_first(queue);
        u = jval_i(node->val);
        dll_delete_node(node);
        output[total++] = u;
        m = outdegree(g, u, tmp);
        for (i=0; i<m; i++)
        {
            v = tmp[i];
            indeg[v]--;
            if (indeg[v]==0)
            dll_append(queue, new_jval_i(v));
        }
    }
*n = total;
}
void readfile(Graph g,int *dinh, int *canh)
{
    *dinh=0;*canh=0;
    FILE *fptr;
    fptr=fopen("data.txt","r");
    if(fptr==NULL)
    {
        printf("Read file failed!\n");
        exit(1);
    }
    char room;
    int i=0,j=0;
    int conti=1;
    while(conti)
    {
        room=fgetc(fptr);
        if(room!='\n')
        {
            //printf("@%c@",room);
            addVertex(g,room,"room");
            (*dinh)+=1;
            if(room!=0)
            {
                addEdge(g,i,j,room);
                addEdge(g,j,i,room);
                (*canh)+=1;
                if (i==3) j+=1;
                else i+=1;
            }
        }
        if(fgetc(fptr)==EOF) conti=0;
    
    }
    //printf("%d", *dinh );
     fclose(fptr);
}