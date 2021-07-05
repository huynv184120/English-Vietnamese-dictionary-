#include <string.h>
#include "./Btree/inc/btree.h"
#include <termios.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void ending()
{
	printf("================================\n");
}
int main()
{
	struct termios info;
	int flag=0;
	tcgetattr(0, &info);          /* get current terminal attirbutes; 0 is the file descriptor for stdin */
	info.c_lflag &= ~ICANON;      /* disable canonical mode */
	info.c_cc[VMIN] = 1;          /* wait until at least one keystroke available */
	info.c_cc[VTIME] = 0;         /* no timeout */
	tcsetattr(0, TCSANOW, &info); /* set immediately */
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
	char *suggest = (char*) malloc(100 * sizeof(char));
	char *mean = (char*) malloc(5000 * sizeof(char));
	char *hist = (char*) malloc(5000 * sizeof(char));
	int choice;
	choice=1;
	printf("Tu dien Anh viet 109k\n");
	printf("\t1.Tra tu.\n\t2.Them tu.\n\t3.Sua tu.\n\t4.xoa tu.\n\t5.Lich su.\n\t6.Thoat.\n");

	char alpha;
	while(choice!=6)//lua chon
	{
		if (choice>6 || choice <1) printf("Lua chon khong hop le! Vui long nhap lai:");
		else printf("Hay chon chuc nang ban muon:");
		scanf("%d",&choice);
		while (getchar()!='\n');
		switch(choice)
		{
			//strcpy(word,"");//Khoi tao lai word va mean
			strcpy(mean,"");
			case 1:printf("Nhap tu can tra:");
				//gets(word);
				strcpy(word,"");
				strcpy(suggest,"");
				do
				{
					flag=0;
					alpha=getchar();
					if (alpha!=9)//9 la tab
					{
						strncat(word,&alpha,1);
						strncat(suggest,&alpha,1);
					}
					else//neu an nut tab
					{
						btsel(book,suggest,mean,5000,&size);
						//btseln(book,suggest,mean,5000,&size);
						printf("\n");
						printf("%s\n",mean);
						flag=1;// che do goi y
						break;
					}
				}
				while(alpha!=10);//10 la enter
				
				for(int k=0;k<strlen(word);k++)if (word[k]=='\n'){ word[k]='\0'; break;}
				if(flag!=1)
				{
					if(btsel(book,word,mean,5000,&size))
					{
        				printf("Tu nay chua duoc cap nhat!\n");
					}
        			else
					{
						fprintf(h,"%s\n",word);
						printf("%s\n",mean);
        			}
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
