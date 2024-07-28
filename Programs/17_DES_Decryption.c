#include <stdio.h>
#include <stdint.h>

#define DES_BLOCK_SIZE 8
#define DES_KEY_SIZE 8

void des_decrypt(uint8_t *block,uint8_t keys[16][8])
{
    for(int i=15;i>=0;i--)
    {
        uint8_t *key_ptr=keys[i];
        uint8_t temp[8];
        for(int j=0;j<8;j++)
        {
            temp[j]=block[j]^key_ptr[j];
        }
        for(int j=0;j<8;j++)
        {
            block[j]=temp[j];
        }
    }
}
void generate_keys(uint8_t *key,uint8_t keys[16][8])
{
    int shifts[]={1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
    for(int i=0;i<16;i++)
    {
        for(int j=0;j<shifts[i];j++)
        {
            uint8_t temp[8];
            for(int k=0;k<8;k++)
            {
                temp[k]=key[k];
            }
            for(int k=0;k<8;k++)
            {
                key[k]=temp[(k+1)%8];
            }
        }
        for(int j=0;j<8;j++)
        {
            keys[i][j]=key[j];
        }
    }
}
int main()
{
    uint8_t block[8]={0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF};
    uint8_t key[8]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
    uint8_t keys[16][8];
    generate_keys(key,keys);
    des_decrypt(block,keys);
    for(int i=0;i<8;i++)
    {
        printf("%02x",block[i]);
    }
    printf("\n");
}