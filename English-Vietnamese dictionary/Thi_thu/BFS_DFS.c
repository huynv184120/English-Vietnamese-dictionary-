
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"libfdr/jrb.h"
#include "libfdr/dllist.h"
#include"libfdr/jval.h"
#include "libfdr/fields.h"

typedef struct {
    JRB edges;
    JRB vertices;
} Graph;//tao struct Graph

void BFS(Graph graph, int start, int stop, void (*func)(int));//breadth-first search
void DFS(Graph graph, int start, int stop, void (*func)(int));//depth-first search

void BFS(Graph graph, int start, int stop, void (*func)(int))//Duyet theo chieu rong
{
    /* 
    start la dinh dau tien tham
    stap la dinh cuoi cung tham stop=-1 la tat ca ca dinh da duoc tham
    func la ham duoc thuc hien khi tham cac dinh, o day la ham printVertex
    vd:BFS(g, 1, 5, printVertex);, chay tu dinh 1 den dinh 5
    */
    int visited[1000] = {};
    int n, output[100], i, u, v;
    Dllist node, queue;

    queue = new_dllist();//khoi tao queue
    dll_append(queue, new_jval_i(start));//cho start vao queue
    //tham cac dinh lan can cua start,danh dau dinh da tham roi cho vao queue
    while ( !dll_empty(queue) )
    {
        node = dll_first(queue);//phan tu dau tien cua queue
        u = jval_i(node->val);//lay gia tri cua node hien tai
        dll_delete_node(node);
        if (!visited[u])//neu u chua dc tham
        {
            func(u);// in ra u
            visited[u] = 1;//dat u la da tham
            if ( u == stop ) return;//neu u la dinh cuoi dung lai
            n = getAdjacentVertices(graph, u, output);//tim cac dinh lan can cua u
            for (i=0; i<n; i++)
            {
                v = output[i];
                if (!visited[v])
                dll_append(queue, new_jval_i(v));
            }
        }
    }
}
void DFS(Graph graph, int start, int stop, void (*func)(int))//Duyet theo chieu sau
{
    int visited[1000] = {};
    int n, output[100], i, u, v;
    Dllist node, stack;

    stack = new_dllist();
    dll_append(stack, new_jval_i(start));

    while ( !dll_empty(stack) )
    {
        node = dll_last(stack);
        u = jval_i(node->val);
        dll_delete_node(node);
        if (!visited[u])
        {
            func(u);
            visited[u] = 1;
            if ( u == stop ) return;
            n = getAdjacentVertices(graph, u, output);
            for (i=0; i<n; i++)
            {
                v = output[i];
                if (!visited[v])
                dll_append(stack, new_jval_i(v));
            }
        }
    }
}