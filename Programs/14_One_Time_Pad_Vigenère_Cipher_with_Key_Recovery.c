#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext,int *key,int keyLength,char *ciphertext) 
{
    int len=strlen(plaintext);
    for(int i=0;i<len;i++) 
    {
        if(isalpha(plaintext[i])) 
        {
            char base=islower(plaintext[i])?'a':'A';
            int shift=key[i%keyLength];
            ciphertext[i]=((plaintext[i]-base+shift)%26)+base;
        } 
        else 
        {
            ciphertext[i]=plaintext[i];
        }
    }
    ciphertext[len]='\0';
}
void decrypt(char *ciphertext,int *key,int keyLength,char *plaintext) 
{
    int len=strlen(ciphertext);
    for(int i=0;i<len;i++) 
    {
        if(isalpha(ciphertext[i])) 
        {
            char base=islower(ciphertext[i])?'a':'A';
            int shift=key[i%keyLength];
            int decrypted_char=((ciphertext[i]-base-shift+26)%26)+base;
            plaintext[i]=decrypted_char;
        }
        else 
        {
            plaintext[i]=ciphertext[i];
        }
    }
    plaintext[len]='\0';
}
int main() 
{
    char plaintext[]="sendmoremoney";
    int key[]={9,0,1,7,23,15,21,14,11,11,2,8,9};
    int keyLength=sizeof(key)/sizeof(key[0]);
    char ciphertext[100];
    encrypt(plaintext,key,keyLength,ciphertext);
    printf("\nEncrypted ciphertext = %s\n",ciphertext);
    char targetPlaintext[]="cashnotneeded";
    char decryptedText[100];
        int found=0;
    for(int k=0;k<26;k++) 
    {
        int possibleKey[keyLength];
        for(int i=0;i<keyLength;i++) 
        {
            possibleKey[i]=(key[i]-k+26)%26;
        }
        decrypt(ciphertext,possibleKey,keyLength,decryptedText);
        if(strcmp(decryptedText,targetPlaintext)==0) 
        {
            printf("Found key: ");
            for(int i=0;i<keyLength;i++) 
            {
                printf("%d",possibleKey[i]);
            }
            printf("\n");
            found=1;
            break;
        }
    }
    if(!found) 
    {
        printf("\nKey not found\n");
    }
}