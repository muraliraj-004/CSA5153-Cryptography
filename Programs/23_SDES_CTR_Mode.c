#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 10
#define COUNTER_SIZE 8

typedef uint8_t byte;

void SDES_encrypt_block(byte *block, byte *key, byte *output) { }

void SDES_decrypt_block(byte *block, byte *key, byte *output) { }

void XOR_blocks(byte *block1, byte *block2, byte *result) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}

void increment_counter(byte *counter) {
    for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
        if (counter[i] < 0xFF) {
            counter[i]++;
            break;
        }
        counter[i] = 0;
    }
}

void encrypt_CTR(byte *plaintext, int len, byte *key, byte *counter, byte *ciphertext) {
    byte keystream[BLOCK_SIZE];
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        SDES_encrypt_block(counter, key, keystream);
        XOR_blocks(plaintext + i, keystream, ciphertext + i);
        increment_counter(counter);
    }
}

void decrypt_CTR(byte *ciphertext, int len, byte *key, byte *counter, byte *plaintext) {
    byte keystream[BLOCK_SIZE];
    
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        SDES_encrypt_block(counter, key, keystream);
        XOR_blocks(ciphertext + i, keystream, plaintext + i);
        increment_counter(counter);
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
    byte counter[BLOCK_SIZE] = {0b00000000};
    byte plaintext[BLOCK_SIZE] = {0b00000001, 0b00000010, 0b00000100};
    byte ciphertext[BLOCK_SIZE];
    byte decryptedtext[BLOCK_SIZE];
    int len = BLOCK_SIZE;

    printf("Original Plaintext = ");
    print_binary(plaintext, len);

    encrypt_CTR(plaintext, len, key, counter, ciphertext);
    printf("Ciphertext = ");
    print_binary(ciphertext, len);

    decrypt_CTR(ciphertext, len, key, counter, decryptedtext);
    printf("Decrypted Text = ");
    print_binary(decryptedtext, len);

    return 0;
}
