#include <stdio.h>
#include <ctype.h>

void encrypt(char plaintext[],char key[]) 
{
    for(int i=0;plaintext[i]!='\0';i++) 
    {
        if(isalpha(plaintext[i])) 
        {
            if(islower(plaintext[i])) 
            {
                plaintext[i]=key[plaintext[i]-'a'];
            } 
            else if(isupper(plaintext[i])) 
            {
                plaintext[i]=toupper(key[plaintext[i]-'A']);
            }
        }
    }
}
int main() 
{
    char plaintext[100];
    char key[]="zyxwvutsrqponmlkjihgfedcba";
    printf("\nEnter the plaintext = ");
    fgets(plaintext,sizeof(plaintext),stdin);
    encrypt(plaintext,key);
    printf("\nCiphertext = %s\n",plaintext);
}