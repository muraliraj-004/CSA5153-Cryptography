#include <stdio.h>
#include <string.h>
#include <ctype.h>

void hillEncrypt(char *plaintext,int key[2][2],char *ciphertext) 
{
    int len=strlen(plaintext);
    int i,j;
    int index=0;
    char processedText[len];
    int pt_index=0;
    for(i=0;i<len;i++) 
    {
        if(isalpha(plaintext[i])) 
        {
            processedText[pt_index++]=toupper(plaintext[i]);
        }
    }
    processedText[pt_index]='\0';
    for(i=0;i<pt_index;i+=2) 
    {
        int pt1=processedText[i]-'A';
        int pt2=processedText[i+1]-'A';
        int ct1=(key[0][0]*pt1+key[0][1]*pt2)%26;
        int ct2=(key[1][0]*pt1+key[1][1]*pt2)%26;
        ciphertext[index++]='A'+ct1;
        ciphertext[index++]='A'+ct2;
    }
    ciphertext[index]='\0';
}
void hillDecrypt(char *ciphertext,int key[2][2],char *decryptedText) 
{
    int len=strlen(ciphertext);
    int i,j;
    int index=0;
    int det=key[0][0]*key[1][1]-key[0][1]*key[1][0];
    int invKey[2][2];
    invKey[0][0]=key[1][1];
    invKey[0][1]=-key[0][1];
    invKey[1][0]=-key[1][0];
    invKey[1][1]=key[0][0];
    det=(det%26+26)%26;
    int detInv=0;
    for(i=1;i<26;i++) 
    {
        if((det*i)%26==1) 
        {
            detInv=i;
            break;
        }
    }
    for(i=0;i<len;i+=2) 
    {
        int ct1=ciphertext[i]-'A';
        int ct2=ciphertext[i+1]-'A';
        int pt1=(invKey[0][0]*ct1+invKey[0][1]*ct2)%26;
        int pt2=(invKey[1][0]*ct1+invKey[1][1]*ct2)%26;
        pt1=(pt1+26)%26;
        pt2=(pt2+26)%26;
        decryptedText[index++]='A'+pt1;
        decryptedText[index++]='A'+pt2;
    }
    decryptedText[index]='\0';
}
int main() 
{
    int key[2][2]={{9,4},{5,7}};
    char plaintext[]="meet me at the usual place at ten rather than eight oclock";
    char ciphertext[100];
    char decryptedText[100];
    hillEncrypt(plaintext,key,ciphertext);
    printf("\nEncrypted ciphertext = \n%s\n\n",ciphertext);
    hillDecrypt(ciphertext,key,decryptedText);
    printf("\nDecrypted plaintext = \n%s\n",decryptedText);
}