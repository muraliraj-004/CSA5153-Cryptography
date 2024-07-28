#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(unsigned char *block1, unsigned char *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block1[i] ^= block2[i];
    }
}

void encrypt_block(unsigned char *block, unsigned char *key) {
    xor_blocks(block, key);
}

void decrypt_block(unsigned char *block, unsigned char *key) {
    encrypt_block(block, key);
}

void encrypt_ECB(unsigned char *plaintext, int len, unsigned char *key, unsigned char *ciphertext) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        encrypt_block(plaintext + i, key);
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
    }
}

void decrypt_ECB(unsigned char *ciphertext, int len, unsigned char *key, unsigned char *plaintext) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        decrypt_block(ciphertext + i, key);
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
    }
}

void encrypt_CBC(unsigned char *plaintext, int len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        xor_blocks(block, prev_block);
        encrypt_block(block, key);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(prev_block, block, BLOCK_SIZE);
    }
}

void decrypt_CBC(unsigned char *ciphertext, int len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    unsigned char prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, ciphertext + i, BLOCK_SIZE);
        decrypt_block(block, key);
        xor_blocks(block, prev_block);
        memcpy(plaintext + i, block, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void encrypt_CFB(unsigned char *plaintext, int len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char shift_reg[BLOCK_SIZE];
    memcpy(shift_reg, iv, BLOCK_SIZE);
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        unsigned char encrypted_block[BLOCK_SIZE];
        encrypt_block(shift_reg, key);
        xor_blocks(block, encrypted_block);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(shift_reg, ciphertext + i, BLOCK_SIZE);
    }
}

void decrypt_CFB(unsigned char *ciphertext, int len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    unsigned char shift_reg[BLOCK_SIZE];
    memcpy(shift_reg, iv, BLOCK_SIZE);
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];
        unsigned char encrypted_block[BLOCK_SIZE];
        memcpy(encrypted_block, shift_reg, BLOCK_SIZE);
        encrypt_block(encrypted_block, key);
        xor_blocks(ciphertext + i, encrypted_block);
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
        memcpy(shift_reg, ciphertext + i, BLOCK_SIZE);
    }
}

void print_hex(unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main(void) {
    unsigned char key[BLOCK_SIZE] = "mykey123";
    unsigned char iv[BLOCK_SIZE] = "12345678";
    unsigned char plaintext[16] = "abcdefgh";
    unsigned char ciphertext[16];
    unsigned char decryptedtext[16];

    encrypt_ECB(plaintext, 16, key, ciphertext);
    printf("ECB Ciphertext: ");
    print_hex(ciphertext, 16);

    decrypt_ECB(ciphertext, 16, key, decryptedtext);
    printf("ECB Decrypted text: %s\n", decryptedtext);

    encrypt_CBC(plaintext, 16, key, iv, ciphertext);
    printf("CBC Ciphertext: ");
    print_hex(ciphertext, 16);

    decrypt_CBC(ciphertext, 16, key, iv, decryptedtext);
    printf("CBC Decrypted text: %s\n", decryptedtext);

    encrypt_CFB(plaintext, 16, key, iv, ciphertext);
    printf("CFB Ciphertext: ");
    print_hex(ciphertext, 16);

    decrypt_CFB(ciphertext, 16, key, iv, decryptedtext);
    printf("CFB Decrypted text: %s\n", decryptedtext);

    return 0;
}