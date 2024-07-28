#include<stdio.h>
#include<ctype.h>

#define MAX_LENGTH 1000
int main()
{
    char plain_text[MAX_LENGTH];
    int key,i=0;
    printf("\nEnter the plain text = ");
    fgets(plain_text,MAX_LENGTH,stdin);
    printf("\nEnter the key value = ");
    scanf("%d",&key);
    while (plain_text[i]!='\0')
    {
        char ch=plain_text[i];
        if(isupper(ch))
        {
            plain_text[i]=(ch-'A'+key)%26+'A';
        }
        if(islower(ch))
        {
            plain_text[i]=(ch-'a'+key)%26+'a';
        }
        i++;
    }
    printf("\nThe cipher text = %s",plain_text);
}