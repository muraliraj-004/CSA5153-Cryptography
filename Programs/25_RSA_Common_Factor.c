#include <stdio.h>
#include <stdlib.h>
unsigned long long mod_exp(unsigned long long base,unsigned long long exp,unsigned long long mod)
{
    unsigned long long result=1;
    base=base%mod;
    while(exp>0)
    {
        if(exp%2==1)
            result=(result*base)%mod;
        exp=exp>>1;
        base=(base*base)%mod;
    }
    return result;
}
unsigned long long gcd(unsigned long long a,unsigned long long b)
{
    while(b!=0)
    {
        unsigned long long t=b;
        b=a%b;
        a=t;
    }
    return a;
}
int main(void)
{
    unsigned long long n=55;
    unsigned long long e=3;
    unsigned long long plaintext=5;
    unsigned long long ciphertext=mod_exp(plaintext,e,n);
    printf("\nCiphertext = %llu\n",ciphertext);
    unsigned long long common_factor=gcd(plaintext,n);
    printf("\nGCD of plaintext and n = %llu\n",common_factor);
    if(common_factor>1)
    {
        printf("\nFound a non-trivial factor of n = %llu\n",common_factor);
    }
    else
    {
        printf("\nNo non-trivial factor found\n");
    }
}