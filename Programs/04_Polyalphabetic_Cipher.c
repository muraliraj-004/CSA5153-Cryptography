#include <stdio.h>
#include <ctype.h>
#include <string.h>

void polyalphabeticCipher(char plaintext[],char key[]) 
{
    int i,kl=strlen(key),pl=strlen(plaintext);
    char ciphertext[pl+1];
    for(i=0;i<pl;i++)
    {
        int shift=key[i%kl]-'A';
        if (isupper(plaintext[i])) 
        {
            ciphertext[i]='A'+(plaintext[i]-'A'+shift)%26;
        }
        else if(islower(plaintext[i])) 
        {
            ciphertext[i]='a'+(plaintext[i]-'a'+shift)%26;
        }
        else 
        {
            ciphertext[i]=plaintext[i];
        }
    }
    ciphertext[i]='\0';
    printf("\nCiphertext = %s\n",ciphertext);
}
int main() 
{
    char plaintext[100],key[100];
    printf("\nEnter the plaintext = ");
    fgets(plaintext,sizeof(plaintext),stdin);
    printf("\nEnter the key = ");
    fgets(key,sizeof(key),stdin);
    plaintext[strcspn(plaintext,"\n")]='\0';
    key[strcspn(key,"\n")]='\0';
    polyalphabeticCipher(plaintext,key);
}