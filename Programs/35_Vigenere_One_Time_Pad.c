#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ALPHABET_SIZE 26

void encrypt_vigenere(const char *plaintext, const int *key, int key_length, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = 'a' + (plaintext[i] - 'a' + key[i % key_length]) % ALPHABET_SIZE;
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = 'A' + (plaintext[i] - 'A' + key[i % key_length]) % ALPHABET_SIZE;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt_vigenere(const char *ciphertext, const int *key, int key_length, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + (ciphertext[i] - 'a' - key[i % key_length] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = 'A' + (ciphertext[i] - 'A' - key[i % key_length] + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main(void) {
    srand(time(NULL));
    const char *plaintext = "HelloWorld";
    int key[] = {3, 19, 5, 10, 7, 2, 15, 9, 4, 11};
    int key_length = sizeof(key) / sizeof(key[0]);
    char ciphertext[50];
    char decryptedtext[50];

    encrypt_vigenere(plaintext, key, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt_vigenere(ciphertext, key, key_length, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}