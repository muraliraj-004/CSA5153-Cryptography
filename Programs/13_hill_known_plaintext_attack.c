#include <stdio.h>
#include <string.h>

#define MAX_SIZE 100
void hillDecrypt(char *ciphertext,int key[2][2],char *decryptedText) 
{
    int len=strlen(ciphertext);
    int index=0;
    int det=key[0][0]*key[1][1]-key[0][1]*key[1][0];
    int invKey[2][2];
    int detInv=0;
    det=(det%26+26)%26;
    for(int i=1;i<26;i++)
    {
        if((det*i)%26==1) 
        {
            detInv=i;
            break;
        }
    }
    if(detInv==0) 
    {
        printf("\nInverse does not exist\n");
        return;
    }
    invKey[0][0]=(key[1][1]*detInv)%26;
    invKey[0][1]=(-key[0][1]*detInv)%26;
    invKey[1][0]=(-key[1][0]*detInv)%26;
    invKey[1][1]=(key[0][0]*detInv)%26;
    for(int i=0;i<2;i++) 
    {
        for(int j=0;j<2;j++) 
        {
            invKey[i][j]=(invKey[i][j]%26+26)%26;
        }
    }
    for(int i=0;i<len;i+=2) 
    {
        int ct1=ciphertext[i]-'a';
        int ct2=ciphertext[i+1]-'a';
        int pt1=(invKey[0][0]*ct1+invKey[0][1]*ct2)%26;
        int pt2=(invKey[1][0]*ct1+invKey[1][1]*ct2)%26;
        pt1=(pt1+26)%26;
        pt2=(pt2+26)%26;
        decryptedText[index++]='a'+pt1;
        decryptedText[index++]='a'+pt2;
    }
    decryptedText[index]='\0';
}
int main() 
{
    char ciphertext[]="zsebkfjnylytkr";
    char plaintext[]="helloworld";

    int key[2][2]= 
    {
        {plaintext[0]-'a',plaintext[1]-'a'},
        {plaintext[2]-'a',plaintext[3]-'a'}
    };
    char decryptedText[MAX_SIZE];
    hillDecrypt(ciphertext,key,decryptedText);
    printf("\nDecrypted plaintext = %s\n", decryptedText);
}