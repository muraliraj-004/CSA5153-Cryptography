#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(unsigned char *block1, unsigned char *block2) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block1[i] ^= block2[i];
    }
}

void cbc_mac(unsigned char *key, unsigned char *message, unsigned char *mac) {
    unsigned char iv[BLOCK_SIZE] = {0};
    unsigned char block[BLOCK_SIZE];
    memcpy(block, iv, BLOCK_SIZE);

    for (int i = 0; i < BLOCK_SIZE; i++) {
        xor_blocks(block, message + i * BLOCK_SIZE);
        memcpy(mac, block, BLOCK_SIZE);
    }
}

int main(void) {
    unsigned char key[BLOCK_SIZE] = "mykey123";
    unsigned char message[BLOCK_SIZE] = "message";
    unsigned char mac[BLOCK_SIZE];
    unsigned char two_block_message[2 * BLOCK_SIZE];
    unsigned char x_xor_t[BLOCK_SIZE];

    cbc_mac(key, message, mac);

    printf("MAC(T) = ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    xor_blocks(message, mac);
    memcpy(x_xor_t, message, BLOCK_SIZE);
    memcpy(two_block_message, message, BLOCK_SIZE);
    memcpy(two_block_message + BLOCK_SIZE, x_xor_t, BLOCK_SIZE);

    unsigned char new_mac[BLOCK_SIZE];
    cbc_mac(key, two_block_message, new_mac);

    printf("MAC for X || (X ⊕ T) = ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", new_mac[i]);
    }
    printf("\n");

    return 0;
}