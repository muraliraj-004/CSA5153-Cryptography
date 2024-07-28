#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8
void DES_encrypt_block(unsigned char *block,unsigned char *key){ }
void DES_decrypt_block(unsigned char *block,unsigned char *key){ }
void XOR_blocks(unsigned char *a,unsigned char *b)
{
    for(int i=0;i<BLOCK_SIZE;i++)
    {
        a[i]^=b[i];
    }
}
void pad_data(unsigned char *data,int *len)
{
    int pad_len=BLOCK_SIZE-(*len%BLOCK_SIZE);
    if(pad_len==BLOCK_SIZE)pad_len=0;
    memset(data+ *len,0,pad_len-1);
    data[*len+pad_len-1]=0x80;
    *len+=pad_len;
}
void process_mode(unsigned char *data,int len,unsigned char *key,unsigned char *iv,int mode,int encrypt)
{
    unsigned char block[BLOCK_SIZE],feedback[BLOCK_SIZE];
    memcpy(feedback,iv,BLOCK_SIZE);
    for(int i=0;i<len;i+=BLOCK_SIZE)
    {
        memcpy(block,data+i,BLOCK_SIZE);
        if(mode==0)
        {
            if(encrypt)DES_encrypt_block(block,key);
            else DES_decrypt_block(block,key);
        }
        else if(mode==1)
        {
            if(encrypt)
            {
                XOR_blocks(block,feedback);
                DES_encrypt_block(block,key);
            }
            else
            {
                memcpy(feedback,data+i,BLOCK_SIZE);
                DES_decrypt_block(block,key);
                XOR_blocks(block,feedback);
            }
            memcpy(feedback,block,BLOCK_SIZE);
        }
        else if(mode==2)
        {
            DES_encrypt_block(feedback,key);
            if(encrypt)
            {
                XOR_blocks(block,feedback);
                memcpy(feedback,block,BLOCK_SIZE);
            }
            else
            {
                XOR_blocks(block,feedback);
                memcpy(feedback,data+i,BLOCK_SIZE);
            }
        }
        memcpy(data+i,block,BLOCK_SIZE);
    }
}
void print_hex(unsigned char *data,int len)
{
    for(int i=0;i<len;i++)
    {
        printf("%02x",data[i]);
    }
    printf("\n");
}
int main(void)
{
    unsigned char key[BLOCK_SIZE]="01234567";
    unsigned char iv[BLOCK_SIZE]="87654321";
    unsigned char data[32]="This is 16 bytes!Another16bytes";
    int len=32;
    pad_data(data,&len);
    process_mode(data,len,key,iv,0,1);printf("ECB Ciphertext = ");print_hex(data,len);
    process_mode(data,len,key,iv,0,0);printf("ECB Decrypted text = %s\n",data);
    process_mode(data,len,key,iv,1,1);printf("CBC Ciphertext = ");print_hex(data,len);
    process_mode(data,len,key,iv,1,0);printf("CBC Decrypted text = %s\n",data);
    process_mode(data,len,key,iv,2,1);printf("CFB Ciphertext = ");print_hex(data,len);
    process_mode(data,len,key,iv,2,0);printf("CFB Decrypted text = %s\n",data);
}