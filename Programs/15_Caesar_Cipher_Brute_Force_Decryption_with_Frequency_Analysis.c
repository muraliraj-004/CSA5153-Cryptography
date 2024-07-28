#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void countLetterFrequency(char *text, 
int freq[]) 
{
    int len=strlen(text);
    for(int i=0;i<len;i++) 
    {
        if(isalpha(text[i])) 
        {
            char ch=toupper(text[i]);
            freq[ch-'A']++;
        }
    }
}
void caesarDecrypt(char *ciphertext,int shift,char *plaintext) 
{
    int len=strlen(ciphertext);
    for(int i=0;i<len;i++) 
    {
        if(isalpha(ciphertext[i])) 
        {
            char base=islower(ciphertext[i])?'a':'A';
            plaintext[i]=((ciphertext[i]-base-shift+ALPHABET_SIZE)%ALPHABET_SIZE)+base;
        } 
        else 
        {
            plaintext[i]=ciphertext[i];
        }
    }
    plaintext[len]='\0';
}
void frequencyAttack(char *ciphertext,int topCount) 
{
    int freq[ALPHABET_SIZE]={0};
    countLetterFrequency(ciphertext,freq);
    int maxFreq=0,maxShift=0;
    for(int shift=0;shift<ALPHABET_SIZE;shift++) 
    {
        if(freq[shift]>maxFreq)
         {
            maxFreq=freq[shift];
            maxShift=shift;
        }
    }
    printf("\nTop %d possible plaintexts =\n\n",topCount);
    for(int i=0;i<topCount;i++) 
    {
        char plaintext[100];
        caesarDecrypt(ciphertext,(maxShift+i)%ALPHABET_SIZE,plaintext);
        printf("%d.%s\n",i+1,plaintext);
    }
}
int main() 
{
    char ciphertext[]="Tqxxa iyqp pia igk xrzx kv pia arpqvmk";
    int topCount=10;
    frequencyAttack(ciphertext,topCount);

}