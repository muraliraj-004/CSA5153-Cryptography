#include <stdio.h>

unsigned long long factorial(int n) 
{
    unsigned long long result=1;
    for(int i=2;i<=n;i++) 
    {
        result*=i;
    }
    return result;
}
unsigned long long calculateTotalKeys() 
{
    int n=25;
    int k=25;
    unsigned long long fact_n=factorial(n);
    unsigned long long fact_n_minus_k=factorial(n-k);
    unsigned long long total_keys=fact_n/fact_n_minus_k;
    return total_keys;
}
unsigned long long calculateUniqueKeys() 
{
    unsigned long long total_keys=calculateTotalKeys();
    unsigned long long unique_keys=total_keys/8;
    return unique_keys;
}
int main() 
{
    unsigned long long total_keys=calculateTotalKeys();
    unsigned long long unique_keys=calculateUniqueKeys();
    printf("\nTotal number of possible keys for the Playfair cipher: Approximately 1 in 2^%d\n",(int)(total_keys/2));
    printf("\nNumber of effectively unique keys for the Playfair cipher: Approximately 1 in 2^%d\n",(int)(unique_keys/2));

}