#include <stdio.h>
#include <stdint.h>
#define DES_KEY_SIZE 64
#define NUM_SUBKEYS 16
#define SUBSET_SIZE 28
void des_key_schedule(uint64_t key,uint64_t subkeys[NUM_SUBKEYS])
{
    uint32_t subset1=(key>>36)&0x0FFFFFFF;
    uint32_t subset2=(key>>8)&0x0FFFFFFF;
    for(int i=0;i<NUM_SUBKEYS;i++)
    {
        subkeys[i]=(subset1<<4)&0xFFFFFF00;
        subkeys[i]|=(subset2>>4)&0x000000FF;
        subset1=(subset1<<1)|(subset1>>27);
        subset2=(subset2<<1)|(subset2>>27);
    }
}
int main()
{
    uint64_t key=0x1234567890ABCDEF;
    uint64_t subkeys[NUM_SUBKEYS];
    des_key_schedule(key,subkeys);
    for(int i=0;i<NUM_SUBKEYS;i++)
    {
        printf("\nSubkey %d = 0x%016llX\n",i,subkeys[i]);
    }
}