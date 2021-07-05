#include <string.h>
#include "./Btree/inc/btree.h"
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void ending()
{
	printf("================================\n");
}
int main()
{
	BTA * book;
    btinit();
    book = btopn("dict.dat", 0, 0);
    int size;//size chi la bien tam, khong quan trong
    	
	FILE *h = fopen("history.txt", "a+");
	time_t rawtime;
 	struct tm * timeinfo;
 	time ( &rawtime );
 	timeinfo = localtime ( &rawtime );
	fprintf(h,"%s",asctime (timeinfo));
 	
	char *word = (char*) malloc(100 * sizeof(char));
	char *mean = (char*) malloc(5000 * sizeof(char));
	char *hist = (char*) malloc(5000 * sizeof(char));
	int choice;
	choice=1;
	printf("Tu dien Anh viet 109k\n");
	printf("\t1.Tra tu.\n");
	printf("\t2.Them tu.\n");
	printf("\t3.Sua tu.\n");
	printf("\t4.xoa tu.\n");
	printf("\t5.Lich su.\n");
	printf("\t6.Thoat.\n");
	while(choice!=6)//lua chon
	{
		if (choice>6 || choice <1) printf("Lua chon khong hop le! Vui long nhap lai:");
		else printf("Hay chon chuc nang ban muon:");
		scanf("%d",&choice);
		while (getchar()!='\n');
		switch(choice)
		{
			strcpy(word,"");//Khoi tao lai word va mean
			strcpy(mean,"");
			case 1:printf("Nhap tu can tra:");
				//while(getchar()!='\n');scanf("%s",word);
				gets(word);
				if(btsel(book,word,mean,5000,&size))
				{
        			printf("Tu nay chua duoc cap nhat!\n");
				}
        		else
				{
					fprintf(h,"%s\n",word);
					printf("%s\n",mean);
        		}
				ending();
        		break;
        	case 2:printf("Nhap tu can them:");
        		gets(word);
        		printf("Nhap vao nghia:");
        		gets(mean);
        		btins(book,word,mean,1000);
        		printf("Tu da duoc nhap thanh cong!\n");
				ending();
        		break;
        	case 3:printf("Nhap tu can sua:");
        		gets(word);
        		printf("Nhap vao nghia moi:");
        		gets(mean);
				btupd(book, word, mean, 1000);//Ham de cap nhat nghia
				printf("Tu da duoc cap nhap thanh cong!\n");
				ending();
				break;
			case 4:printf("Nhap tu can xoa:");
        		gets(word);
        		btdel(book,word);//Ham de xoa tu
				printf("Tu da duoc xoa thanh cong!\n");
				ending();
        		break;
			case 5:
       			fscanf(h, "%[^@]", hist);
				printf("%s",hist);
				break;
        	case 6:printf("Have a good day!\n");
        		break;	
		}

	}
	btcls(book);
	fclose(h);
}
