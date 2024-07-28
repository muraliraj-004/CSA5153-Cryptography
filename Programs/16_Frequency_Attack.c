#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
const double english_frequencies[]=
{
    0.08167,0.01492,0.02782,0.04253,0.12702,0.02228,0.02015,
    0.06094,0.06966,0.00153,0.00772,0.04025,0.02406,0.06749,
    0.07507,0.01929,0.00095,0.05987,0.06327,0.09056,0.02758,
    0.00978,0.02360,0.00150,0.01974,0.00074
};
void calculate_frequencies(const char *ciphertext,double *frequencies) 
{
    int i,count[26]={0};
    for(i=0;i<strlen(ciphertext);i++)
    {
        if(isalpha(ciphertext[i]))
        {
            count[tolower(ciphertext[i])-'a']++;
        }
    }
    for(i=0;i<26;i++) 
    {
        frequencies[i]=(double)count[i]/strlen(ciphertext);
    }
}
double calculate_score(const char *plaintext,const double *frequencies)
{
    int i;
    double score=0.0;
    for(i=0;i<strlen(plaintext);i++)
    {
        if(isalpha(plaintext[i]))
        {
            score+=english_frequencies[tolower(plaintext[i])-'a']*frequencies[tolower(plaintext[i])-'a'];
        }
    }
    return score;
}
void perform_attack(const char *ciphertext,int num_plaintexts)
{
    double frequencies[26];
    calculate_frequencies(ciphertext,frequencies);
    int i,j;
    char plaintext[strlen(ciphertext)+1];
    double scores[num_plaintexts];
    char *top_plaintexts[num_plaintexts];
    for(i=0;i<num_plaintexts;i++)
    {
        scores[i]=0.0;
        top_plaintexts[i]=NULL;
    }
    for(i=0;i<26;i++)
    {
        for(j=0;j<strlen(ciphertext);j++)
        {
            if(isalpha(ciphertext[j]))
            {
                plaintext[j]='a'+(ciphertext[j]-'a'+i)%26;
            }
            else
            {
                plaintext[j]=ciphertext[j];
            }
        }
        plaintext[strlen(ciphertext)]='\0';
        double score=calculate_score(plaintext,frequencies);
        for(j=0;j<num_plaintexts;j++)
        {
            if(score>scores[j])
            {
                int k;
                for(k=num_plaintexts-1;k>j;k--)
                {
                    scores[k]=scores[k-1];
                    top_plaintexts[k]=top_plaintexts[k-1];
                }
                scores[j]=score;
                top_plaintexts[j]=strdup(plaintext);
                break;
            }
        }
    }
    printf("\nTop %d possible plaintexts = \n",num_plaintexts);
    for(i=0;i<num_plaintexts;i++)
    {
        printf("%d.%s(score = %f)\n",i+1,top_plaintexts[i],scores[i]);
        free(top_plaintexts[i]);
    }
}
int main()
{
    char ciphertext[1024];
    int num_plaintexts;
    printf("\nEnter the ciphertext = ");
    fgets(ciphertext,sizeof(ciphertext),stdin);
    ciphertext[strlen(ciphertext)-1]='\0';
    printf("\nEnter the number of top possible plaintexts to display = ");
    scanf("%d",&num_plaintexts);
    perform_attack(ciphertext,num_plaintexts);
}