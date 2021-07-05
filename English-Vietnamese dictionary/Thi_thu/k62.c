
#include "graph_jrb.h"


void readFile1(Graph g, char *filename);
void readFile2(Graph g, char *filename);

int main(){
    Graph g1 = createGraph();// do thi luu tat ca canh
    Graph g2 = createGraph();// do thi chi luu duong co time >= 50
    char filename[] = "dothi.txt";

    readFile1(g1, filename);
    readFile2(g2, filename);

    int menu;
    do
    {
        printf("\n\n--------------MENU-------------\n"
                "1. In danh sach ma tran\n"
                "2. Danh sach ke cua moi thanh tri\n"
                "3. Danh sach !\n"
                "4. Tim duong di ngan nhat!\n"
                "5. Tim duong di bo ngan nhat!\n"
                "0. Thoat!\n"
                "----> Chon: ");
        scanf("%d", &menu);
        
        switch (menu)
        {
            case 1:
            {
                int num = getNumOfV(g1);

                printf("\nMa tran ke cua do thi: \n");

                JRB node1, node2;
                printf("\t");
                jrb_traverse(node1, g1.vertices){
                    int id = jval_i(node1->key);
                    printf("%d\t", id);
                }
                printf("\n");
                jrb_traverse(node1, g1.vertices){
                    int id1 = jval_i(node1->key);
                    printf("%d\t", id1);
                    jrb_traverse(node2, g1.vertices){
                        int id2 = jval_i(node2->key);
                        if(hasEdge(g1, id1, id2))
                            printf("1\t");
                        else
                            printf("0\t");
                    }
                    printf("\n");
                }
                break;
            }
            case 2:
            {
                JRB node;
                jrb_traverse(node, g1.vertices){
                    int output[100];
                    printf("Castle %d: ", jval_i(node->key));
                    int num = indegree(g1, jval_i(node->key), output);
                    for (int i = 0; i < num; i++)
                    {
                        printf("%d ", output[i]);
                    }
                    printf("\n");
                }
                break;
            }
            case 3:
            {
                JRB node1;
                int temp[100];
                int soluong = 0;
                jrb_traverse(node1, g1.vertices){
                    int check = 1;// neu time < 50 check = 0
                    int output[100];
                    int num = indegree(g1, jval_i(node1->key), output);
                    for (int i = 0; i < num; i++)
                    {
                        if(getEdgeValue(g1, jval_i(node1->key), output[i]) < 50)
                        {
                            check = 0;
                            break;
                        }
                    }
                    if(check == 1)
                    {
                        temp[soluong] = jval_i(node1->key);
                        soluong++;
                    } 
                }
                printf("Thanh tri chi di bo den duoc la: ");
                for (int i = 0; i < soluong; i++)
                {
                    printf("%d ", temp[i]);
                }
                printf("\n");
                int temp2[100];
                soluong = 0;
                int max = 0;
                jrb_traverse(node1, g1.vertices){
                    int output[100];
                    int num = indegree(g1, jval_i(node1->key), output);
                    if(max < num) max = num;
                }
                jrb_traverse(node1, g1.vertices){
                    int output[100];
                    int num = indegree(g1, jval_i(node1->key), output);
                    if(max == num){
                        temp2[soluong] = jval_i(node1->key);
                        soluong++;
                    }
                }
                printf("Danh sach thanh tri co nhieu duong noi nhat la: ");
                for (int i = 0; i < soluong; i++)
                {
                    printf("%d ", temp2[i]);
                }
                printf("\n");
                break;
            }
            case 4:
            {
                int s, t, sodinh;
                printf("Nhap thanh tri xuat phat s: ");
                scanf("%d", &s);
                printf("Nhap thanh tri dich t: ");
                scanf("%d", &t);
                int path[100];
                int dodai = shortestPath(g1, s, t,path , &sodinh);
                if(dodai != INF){
                printf("Do dai duong di:%d \n", dodai);
                printf("Duong di s->t: ");
                for (int i = 0; i < sodinh; i++)
                {
                    printf("%d ", path[i]);
                }
                printf("\n");
                
                }
                else printf("ROUTE NOT FOUND !\n");
                break;
            }
            case 5:
            {
                int s, t, sodinh;
                printf("Nhap thanh tri xuat phat s: ");
                scanf("%d", &s);
                printf("Nhap thanh tri dich t: ");
                scanf("%d", &t);
                int path[100];
                int dodai = shortestPath(g2, s, t,path , &sodinh);
                if(dodai != INF){
                printf("Do dai duong di:%d \n", dodai);
                printf("Duong di s->t: ");
                for (int i = 0; i < sodinh; i++)
                {
                    printf("%d ", path[i]);
                }
                printf("\n");
                
                }
                else printf("ROUTE NOT FOUND !\n");
                break;
            }
        }
    } while (menu != 0);
    dropGraph(g1);
    dropGraph(g2);
    return 0;
}

void readFile1(Graph g, char *filename){
    IS is = new_inputstruct(filename);
    if(is == NULL){
        printf("Error: file fail!\n");
        exit(1);
    }

    get_line(is);
    int n = atoi(is->fields[0]);
    int m = atoi(is->fields[1]);

    int id1, id2, time;
    while (get_line(is) > 0)
    {
        id1 = atoi(is->fields[0]);
        id2 = atoi(is->fields[1]);
        time = atoi(is->fields[2]);
        //printf("%d%d\n", id1, id2);
        addVertex(g, id1, "");
        addVertex(g, id2, "");
        addEdge(g, id1, id2, time);
    }
}

void readFile2(Graph g, char *filename){
    IS is = new_inputstruct(filename);
    if(is == NULL){
        printf("Error: file fail!\n");
        exit(1);
    }

    get_line(is);
    int n = atoi(is->fields[0]);
    int m = atoi(is->fields[1]);

    int id1, id2, time;
    while (get_line(is) > 0)
    {
        id1 = atoi(is->fields[0]);
        id2 = atoi(is->fields[1]);
        time = atoi(is->fields[2]);
        
        addVertex(g, id1, "");
        addVertex(g, id2, "");
        if(time >= 50)
            addEdge(g, id1, id2, time);
    }
}