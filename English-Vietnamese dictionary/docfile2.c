#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "Btree/inc/btree.h"
#define INF 108858

int main()
{   
    FILE *fp = fopen("anhviet109K.dict", "r");
    FILE *f = fopen("A.txt", "w");
    int i;
    int j;
    int k;
    int spec1;

    BTA * book;
    btinit();
    book = btopn("dict.dat", 0, 0);
    if (!book) book = btcrt("dict.dat", 0, 0);
    char *tmp = (char*) malloc(1000 * sizeof(char));
    for (i=0;i<3;i++)//bo qua credit
    {
        fscanf(fp, "%[^\n]", tmp);
        fscanf(fp, "%[^@]", tmp);
    }
    free(tmp);

    char *allword = (char*) malloc(20000 * sizeof(char));//ca tu
    char *word = (char*) malloc(50 * sizeof(char));//tu chua ca dau cach
   // char *word1 = (char*) malloc(50 * sizeof(char));//tu chinh
    char *mean = (char*) malloc(19950 * sizeof(char));//nghia

    //while(!feof(fp))
    for(i=0;i<108858;i++)
    {
        strcpy(word, "");//khoi tao lai word, vi ham strcat se noi chu ko ghi de
        strcpy(mean, "");//khoi tao lai mean, vi ham strcat se noi chu ko ghi de
        fseek(fp,1,SEEK_CUR);//bo qua @
        fscanf(fp, "%[^@]", allword);
        spec1=0;//neu tu khong co gach cheo 
        for(j=0;j<strlen(allword);j++)//tach tu
        {
            strncat(word,&allword[j],1);
            if(allword[j+1]=='\n')
            {
                spec1=2;
                break;
            }
            if(allword[j+2]=='/') 
            {
                spec1=1;
                break;            
            }
        }
        //if(spec1==1) j+=2;
        j+=2;
        for(j;j<strlen(allword)-1;j++)//tach mean
            strncat(mean,&allword[j],1);

        //fprintf(f,"@%s@\n",word);
        //printf("@%s@\n",mean);
        btins(book,word,mean,1000);
    }
    btcls(book);
    //free(allword);
    //free(word);
    //free(mean);
    fclose(fp);
    fclose(f);
    return 0;

}