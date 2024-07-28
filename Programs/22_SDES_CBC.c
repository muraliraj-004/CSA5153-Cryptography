#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10
#define IV_SIZE 8

typedef uint8_t byte;

void SDES_encrypt_block(byte *block, byte *key, byte *output) { }

void SDES_decrypt_block(byte *block, byte *key, byte *output) { }

void XOR_blocks(byte *block1, byte *block2, byte *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void encrypt_CBC(byte *plaintext, int len, byte *key, byte *iv, byte *ciphertext) {
    byte prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        byte block[BLOCK_SIZE];
        memcpy(block, plaintext + i, BLOCK_SIZE);
        XOR_blocks(block, prev_block, block);
        SDES_encrypt_block(block, key, ciphertext + i);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void decrypt_CBC(byte *ciphertext, int len, byte *key, byte *iv, byte *plaintext) {
    byte prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        byte block[BLOCK_SIZE];
        byte decrypted_block[BLOCK_SIZE];
        memcpy(block, ciphertext + i, BLOCK_SIZE);
        SDES_decrypt_block(block, key, decrypted_block);
        XOR_blocks(decrypted_block, prev_block, plaintext + i);
        memcpy(prev_block, ciphertext + i, BLOCK_SIZE);
    }
}

void print_binary(byte *data, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

int main(void) {
    byte key[KEY_SIZE / 8] = {0b01111111, 0b101};
    byte iv[BLOCK_SIZE] = {0b10101010};
    byte plaintext[BLOCK_SIZE] = {0b00000001, 0b00100011};
    byte ciphertext[BLOCK_SIZE];
    byte decryptedtext[BLOCK_SIZE];
    int len = BLOCK_SIZE;

    printf("Original Plaintext = ");
    print_binary(plaintext, len);

    encrypt_CBC(plaintext, len, key, iv, ciphertext);
    printf("Ciphertext = ");
    print_binary(ciphertext, len);

    decrypt_CBC(ciphertext, len, key, iv, decryptedtext);
    printf("Decrypted Text = ");
    print_binary(decryptedtext, len);

    return 0;
}
