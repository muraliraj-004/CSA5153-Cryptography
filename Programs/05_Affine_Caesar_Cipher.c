#include <stdio.h>
#include <string.h>

void affineCaesarEncrypt(char plaintext[],int a,int b) 
{
    int n=strlen(plaintext);
    char ciphertext[n];
    for(int i=0;i<n;i++) 
    {
        char p=plaintext[i];
        if(p>='A'&&p<='Z') 
        {
            ciphertext[i]='A'+(a*(p-'A')+b)%26;
        }
        else 
        {
            ciphertext[i]=p;
        }
    }
    ciphertext[n]='\0';
    printf("\nPlaintext = %s\n",plaintext);
    printf("\nCiphertext = %s\n",ciphertext);
}
int main() 
{
    int a=5;
    int b=4;
    char plaintext[]="HELLO IMRAN";
    affineCaesarEncrypt(plaintext,a,b);
}