#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void DES_encrypt_block(unsigned char *block,unsigned char *key);
void DES_decrypt_block(unsigned char *block,unsigned char *key);
void XOR_blocks(unsigned char *block1,unsigned char *block2,int len);
void encrypt_CBC(unsigned char *plaintext,int plaintext_len,unsigned char *key,unsigned char *iv,unsigned char *ciphertext)
{
    int block_size=8;
    unsigned char block[block_size];
    unsigned char prev_block[block_size];
    memcpy(prev_block,iv,block_size);
    for(int i=0;i<plaintext_len;i+=block_size)
    {
        memcpy(block,plaintext+i,block_size);
        XOR_blocks(block,prev_block,block_size);
        DES_encrypt_block(block,key);
        DES_decrypt_block(block,key+8);
        DES_encrypt_block(block,key+16);
        memcpy(ciphertext+i,block,block_size);
        memcpy(prev_block,block,block_size);
    }
}
void decrypt_CBC(unsigned char *ciphertext,int ciphertext_len,unsigned char *key,unsigned char *iv,unsigned char *plaintext)
{
    int block_size=8;
    unsigned char block[block_size];
    unsigned char prev_block[block_size];
    unsigned char decrypted_block[block_size];
    memcpy(prev_block,iv,block_size);
    for(int i=0;i<ciphertext_len;i+=block_size)
    {
        memcpy(block,ciphertext+i,block_size);
        memcpy(decrypted_block,block,block_size);
        DES_decrypt_block(block,key+16);
        DES_encrypt_block(block,key+8);
        DES_decrypt_block(block,key);
        XOR_blocks(block,prev_block,block_size);
        memcpy(plaintext+i,block,block_size);
        memcpy(prev_block,decrypted_block,block_size);
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
int main(void)
{
    unsigned char *key=(unsigned char *)"0123456789abcdef0123456789abcdef";
    unsigned char *iv=(unsigned char *)"01234567";
    unsigned char *plaintext=(unsigned char *)"This is a test message";
    int plaintext_len=strlen((char *)plaintext);
    int block_size=8;
    int padded_len=((plaintext_len+block_size-1)/block_size)*block_size;
    unsigned char padded_plaintext[padded_len];
    memset(padded_plaintext,0,padded_len);
    memcpy(padded_plaintext,plaintext,plaintext_len);
    unsigned char ciphertext[padded_len];
    unsigned char decryptedtext[padded_len];
    encrypt_CBC(padded_plaintext,padded_len,key,iv,ciphertext);
    decrypt_CBC(ciphertext,padded_len,key,iv,decryptedtext);
    printf("\nDecrypted text is = %s",decryptedtext);
}