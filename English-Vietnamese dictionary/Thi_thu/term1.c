
#include "minh_jrb_func.h"
#include "libfdr/fields.h"

int v_num; 
int read_print_file (Graph g, int E[4][4])
{	
	IS is = new_inputstruct("data.txt");	//open txt file to read	
	get_line (is);		//read the first line of .txt file
	v_num = is->NF;		//number of vertices
	for (int i=0; i<v_num; i++)
	{
		
		addVertex(g, i+1, "");
		for (int j=0; j<v_num; j++)
		{
			E[i][j] = atoi(is->fields[j]);
			if (E[i][j] != 0)
			addEdge(g, i+1, j+1, E[i][j]);
			printf ("%d ", E[i][j]);
		}
		printf("\n");
		get_line(is);		//read the next line of .txt file
	}
}

int count_vertices()
{
	return v_num;
}

int count_edges(int E[4][4])
{
	int count = 0;
	
	for (int i=0; i<v_num; i++)
		for (int j=i; j<v_num; j++)
			if (E[i][j] != 0)
				count ++;
	return count;
}

int isConnected(Graph g)
{			
	JRB node_key, node_val, tree;
	jrb_traverse (node_key, g.edges)
	{
		int count = 0;		//num_val when traverse val
		tree = make_jrb();
		tree = (JRB) jval_v(node_key->val);
		jrb_traverse(node_val, tree)
			count ++;
		if (count < v_num-1) 
		{
			jrb_free_tree(tree);
			return 0;
		}	
	}
	jrb_free_tree(tree);
	return 1;			
}

int main ()
{
	int room, room1, room2;
	int output[4];
    Graph g = createGraph();
	int E[4][4];
    int choice;
	printf("He thong day dien\n");
	printf("\t1.Doc va in ma tran du lieu.\n");
	printf("\t2.Tim so dinh, so cung.\n");
	printf("\t3.Nhap vao 1 phong, liet ke cac phong co day dan voi no.\n");
	printf("\t4.Kiem tra su lien ket giua hai phong.\n");
	printf("\t5.Kiem tra su lien thong.\n");
	printf("\t6.Thoat.\n");
	do
	{
		printf("Hay chon chuc nang ban muon: ");
		scanf("%d",&choice);
		switch(choice)
		{
            case 1:
			{
				read_print_file(g,E);
				break;
			}
            case 2: 
			{
				printf("So dinh cua do thi la: %d\n",count_vertices());
				printf("So cung cua do thi la: %d\n",count_edges(E));
				break;
			}
			case 3:
			{
				printf("Nhap vao phong can tim day dan: ");
				scanf("%d",&room);
				printf("So phong co day dan den phong %d la: %d\n",room,getAdjacentVertices(g,room,output));
				printf("Danh sach: ");
				for (int i = 0; i < getAdjacentVertices(g,room,output); i++)
					printf("%d ",output[i]);
				printf("\n");	
				break;			
			}
			case 4:
			{
				printf("Nhap vao 2 phong ban muon kiem tra: ");
				scanf("%d %d",&room1, &room2);
				if(hasEdge(g, room1, room2))
					printf("2 phong co lien ket!!\n");
				else printf("2 phong khong co lien ket!!\n");
				break;
			}
			case 5:
			{
				if(isConnected(g))
					printf("Do thi lien thong!!\n");
				else
					printf("Do thi khong lien thong!!\n");
					break;
			}
        }
    } while (choice != 6);
    dropGraph(g);
} 
