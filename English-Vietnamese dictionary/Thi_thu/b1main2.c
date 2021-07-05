#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"libfdr/jrb.h"//thu vien
#include "libfdr/dllist.h"
#include"libfdr/jval.h"
#include "libfdr/fields.h"

#define INF 999999//dat gia tri cho 1 bien, ko the bi thay doi

typedef struct {
   JRB edges;// day la cay do den de chua canh
   JRB vertices;//day la cay chua dinh
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
int numOfEdge(Graph graph);
int numOfVertex(Graph graph);
void readfile(Graph g,int *dinh, int *canh);
void printVertex(int v)
{
    printf("%4d", v);
}

double shortestPath(Graph graph, int s, int t, int* path,int*length);//tim duong ngan nhat
int main(int argc,char* argv[])
{
    if(strcmp(argv[1],"-t")==0) printf("C-Advance,HK20192");//doc lai de 20182
    //so tham so, argv la chuoi tham so
    Graph g = createGraph();
    int choice;
	choice=1;
    JRB tree, node;
    int output[100];//de chua indegree
    int input3;//chua nhap vao cho case 3
    int dinh,canh;
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
                /*addVertex(g,1,"P1");//g la ten cua graph, 1 la id cua dinh, p1 la ten dinh thich dat the nao cx dc
                addVertex(g,2,"P2");
                addVertex(g,3,"P3");
                addVertex(g,4,"P4");

                addEdge(g,2,1,3);addEdge(g,1,2,3);//2 la dinh 1, 1 la dinh 2, 3 la trong so giua 2 dinnh
                addEdge(g,3,1,4);addEdge(g,1,3,4);//addEdge trong do thi co huong nen can dung 2 lan de thanh vo huong
                addEdge(g,4,1,2);addEdge(g,1,4,2);
                addEdge(g,3,2,3);addEdge(g,2,3,3);
                addEdge(g,4,2,2);addEdge(g,2,4,2);
                addEdge(g,4,3,1);addEdge(g,3,4,1);*/
                readfile(g,&dinh,&canh);
                printf("%d",dinh);
                for(int i=1;i<=4;i++)
                {
                    for(int j=1;j<=4;j++)
                    {
                        if(i==j) printf("0 ");
                        else printf("%d ",(int)getEdgeValue(g,i,j));//getEdgeVa se tra ve trong so giua 2 canh
                    }
                    printf("\n");
                }
                break;
            case 2:
                printf("%d",numOfVertex(g));//tra ve so dinh
                printf("%d",numOfEdge(g)/2);//tra ve so canh
                printf("\n");
                break;
            case 3:
            printf("Nhap vao phong can kiem tra:");
            scanf("%d",&input3);
            for(int i=0;i<indegree(g, input3 ,output);i++)
            printf("%d",output[i]);
            printf("\n");
        }
    }
    
}
Graph createGraph()
{
    Graph graph;
    graph.edges=make_jrb();//cap phat bo nho
    graph.vertices= make_jrb();
    return graph;
}
void addVertex(Graph graph, int id, char* name)//them dinh
{
    if(jrb_find_int(graph.vertices, id)==NULL)//tim id trong graph neu chua co moi them
        jrb_insert_int(graph.vertices, id,new_jval_s(name));
        return;
}
char *getVertex(Graph graph, int id)//tim xem co dinh trong graph ko?
{
    JRB tmp=jrb_find_int(graph.vertices, id);
    if(tmp==NULL)
    return NULL;
    else return jval_s(tmp->val);
}
void addEdge(Graph graph, int v1, int v2, double weight)//them canh
{
     JRB node, tree;
     if (getEdgeValue(graph, v1, v2) == INF)
     {
        node = jrb_find_int(graph.edges, v1);
        if (node==NULL) {
           tree = make_jrb();
           jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        } 
        else
        {
           tree = (JRB) jval_v(node->val);   
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
     }
}
double getEdgeValue(Graph graph, int v1, int v2)//tim trong so giiua 2 canh
{
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    node = jrb_find_int(tree, v2);
    if (node==NULL)
       return 0;
    else
       return jval_d(node->val);       
}
int hasEdge(Graph graph, int v1, int v2) {//kiem tra xem co canh giua 2 dinh khong
    JRB node, tree;
    node = jrb_find_int(graph.edges, v1);
    if (node==NULL)
       return 0;
    tree = (JRB) jval_v(node->val);
    if (jrb_find_int(tree, v2)==NULL)
       return 0;
    else
       return 1; 
}

int indegree(Graph graph, int v, int* output)//so dinh ke voi v va co huong di vao v
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
int outdegree(Graph graph, int v, int* output)//so dinh ke voi v va co huong di ra khoi v
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
double shortestPath(Graph graph, int s, int t, int* path,int*length)//path la chuoi duong di, legth la tong do dai
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

int numOfEdge(Graph graph)
{
    JRB node1, node2;
    int count = 0;
    jrb_traverse(node1, graph.vertices)
    {
        jrb_traverse(node2, graph.vertices) if (hasEdge(graph, jval_i(node1->key), jval_i(node2->key)))
            count++;
    }
    return count;
}
int numOfVertex(Graph graph)
{
    int count = 0;
    JRB node;
    jrb_traverse(node, graph.vertices)
        count++;
    return count;
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
void topologicalSort(Graph g, int* output, int* n)//outpput la thu tu thuc hien
{
    int indeg[1000], tmp[100], m, i, u, v, total;
    JRB vertex;
    Dllist node, queue;//node la bien bien de duyet queue
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
    IS is=new_inputstruct("data.txt");// IS la 
    get_line(is);//doc 1 dong
    int sodinh=is->NF;//NF la so chuoi trong 1 dong
    *dinh=sodinh;
    double graph[100][100];
    for(int i=0;i<sodinh;i++)
    {
        for(int j=0;j<sodinh;j++)
        {
            graph[i][j]=atof(is->fields[j]);//field la chuoi so i trong dong
            //atof la chuyen tu chuoi thanh double
            printf("%lf",graph[i][j]);
        }
        get_line(is);
    }
    for(int i=0;i<sodinh;i++)
    {
        for(int j=0;j<sodinh;j++)
        {
            addEdge(g,i+1,j+1,graph[i][j]);
        }
    }
}
