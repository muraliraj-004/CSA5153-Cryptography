#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void prepare_key(char *key,char *key_table) 
{
    int i,j,k,flag=0;
    char temp[26]={0};
    for(i=0;i<strlen(key);i++) 
    {
        if(key[i]==' ')
            continue;
        else if(islower(key[i]))
            key[i]=toupper(key[i]);
        temp[key[i]-'A']=1;
    }
    j=0;
    k=0;
    for(i=0;i<strlen(key);) 
    {
        if(temp[j]==1) 
        {
            key_table[k++]='A'+j;
            temp[j]=0;
            i++;
        }
        j++;
    }
    for(i=0;i<26;i++) 
    {
        if(temp[i]==0)
            continue;
        key_table[k++]='A'+i;
    }
}
void find_position(char ch,int *row,int *col,char key_table[SIZE][SIZE]) 
{
    int i,j;
    if(ch=='J')
        ch='I';
    for(i=0;i<SIZE;i++) 
    {
        for(j=0;j<SIZE;j++) 
        {
            if(key_table[i][j]==ch) 
            {
                *row=i;
                *col=j;
                return;
            }
        }
    }
}
void encrypt(char *text,char key_table[SIZE][SIZE]) 
{
    int i,len,row1,row2,col1,col2;
    char ch1,ch2;
    len=strlen(text);
    for(i=0;i<len;i++) 
    {
        if(islower(text[i]))
            text[i]=toupper(text[i]);
        if(text[i]=='J')
            text[i]='I';
    }
    for(i=0;i<len;i+=2) 
    {
        ch1=text[i];
        ch2=text[i+1];
        find_position(ch1,&row1,&col1,key_table);
        find_position(ch2,&row2,&col2,key_table);
        if(row1==row2) 
        {
            text[i]=key_table[row1][(col1+1)%SIZE];
            text[i+1]=key_table[row2][(col2+1)%SIZE];
        } 
        else if(col1==col2) 
        {
            text[i]=key_table[(row1+1)%SIZE][col1];
            text[i+1]=key_table[(row2+1)%SIZE][col2];
        } 
        else 
        {
            text[i]=key_table[row1][col2];
            text[i+1]=key_table[row2][col1];
        }
    }
}
int main() 
{
    char key[20],plaintext[100],key_table[SIZE][SIZE];
    printf("\nEnter the key = ");
    scanf("%s",key);
    printf("\nEnter the plaintext = ");
    scanf("%[^\n]s",plaintext);
    prepare_key(key,(char *)key_table);
    encrypt(plaintext,key_table);
    printf("\nEncrypted text = %s\n",plaintext);
}