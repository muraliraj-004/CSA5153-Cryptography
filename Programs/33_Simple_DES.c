#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 8

typedef uint8_t byte;

void des_encrypt_block(byte *block, const byte *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

void des_decrypt_block(byte *block, const byte *key) {
    des_encrypt_block(block, key);
}

void print_hex(const byte *data, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main(void) {
    byte key[KEY_SIZE] = "mykey123";
    byte plaintext[BLOCK_SIZE] = "plaintext";
    byte ciphertext[BLOCK_SIZE];
    byte decryptedtext[BLOCK_SIZE];

    des_encrypt_block(plaintext, key);
    printf("Ciphertext: ");
    print_hex(plaintext, BLOCK_SIZE);

    des_decrypt_block(plaintext, key);
    printf("Decrypted text: ");
    print_hex(plaintext, BLOCK_SIZE);

    return 0;
}