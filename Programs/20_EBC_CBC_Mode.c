#include <stdio.h>
#include <string.h>.c333-[[[eee.g9090]]]
#include <stdlib.h>

#define BLOCK_SIZE 8

void DES_encrypt_block(unsigned char *block,unsigned char *key);
void DES_decrypt_block(unsigned char *block,unsigned char *key);
void XOR_blocks(unsigned char *block1,unsigned char *block2,int len);
void encrypt_ECB(unsigned char *plaintext,int plaintext_len,unsigned char *key,unsigned char *ciphertext)
{
    for(int i=0;i<plaintext_len;i+=BLOCK_SIZE)
    {
        DES_encrypt_block(plaintext+i,key);
        memcpy(ciphertext+i,plaintext+i,BLOCK_SIZE);
    }
}
void decrypt_ECB(unsigned char *ciphertext,int ciphertext_len,unsigned char *key,unsigned char *plaintext)
{
    for(int i=0;i<ciphertext_len;i+=BLOCK_SIZE)
    {
        DES_decrypt_block(ciphertext+i,key);
        memcpy(plaintext+i,ciphertext+i,BLOCK_SIZE);
    }
}
void encrypt_CBC(unsigned char *plaintext,int plaintext_len,unsigned char *key,unsigned char *iv,unsigned char *ciphertext)
{
    unsigned char block[BLOCK_SIZE];
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block,iv,BLOCK_SIZE);
    for(int i=0;i<plaintext_len;i+=BLOCK_SIZE)
    {
        memcpy(block,plaintext+i,BLOCK_SIZE);
        XOR_blocks(block,prev_block,BLOCK_SIZE);
        DES_encrypt_block(block,key);
        memcpy(ciphertext+i,block,BLOCK_SIZE);
        memcpy(prev_block,block,BLOCK_SIZE);
    }
}
void decrypt_CBC(unsigned char *ciphertext,int ciphertext_len,unsigned char *key,unsigned char *iv,unsigned char *plaintext)
{
    unsigned char block[BLOCK_SIZE];
    unsigned char prev_block[BLOCK_SIZE];
    unsigned char decrypted_block[BLOCK_SIZE];
    memcpy(prev_block,iv,BLOCK_SIZE);
    for(int i=0;i<ciphertext_len;i+=BLOCK_SIZE)
    {
        memcpy(block,ciphertext+i,BLOCK_SIZE);
        memcpy(decrypted_block,block,BLOCK_SIZE);
        DES_decrypt_block(block,key);
        XOR_blocks(block,prev_block,BLOCK_SIZE);
        memcpy(plaintext+i,block,BLOCK_SIZE);
        memcpy(prev_block,decrypted_block,BLOCK_SIZE);
    }
}
void XOR_blocks(unsigned char *block1,unsigned char *block2,int len)
{
    for(int i=0;i<len;i++)
    {
        block1[i]^=block2[i];
    }
}
void DES_encrypt_block(unsigned char *block,unsigned char *key)
{
}
void DES_decrypt_block(unsigned char *block,unsigned char *key)
{
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
    unsigned char key[24]="0123456789abcdef01234567";
    unsigned char iv[BLOCK_SIZE]="01234567";
    unsigned char plaintext[16]="Hello, World!";
    int plaintext_len=16;
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];
    encrypt_ECB(plaintext,plaintext_len,key,ciphertext);
    printf("\nECB Ciphertext = ");
    print_hex(ciphertext,plaintext_len);
    decrypt_ECB(ciphertext,plaintext_len,key,decryptedtext);
    printf("\nECB Decrypted text = %s",decryptedtext);
    encrypt_CBC(plaintext,plaintext_len,key,iv,ciphertext);
    printf("\nCBC Ciphertext = ");
    print_hex(ciphertext,plaintext_len);
    decrypt_CBC(ciphertext,plaintext_len,key,iv,decryptedtext);
    printf("\nCBC Decrypted text = %s",decryptedtext);
}