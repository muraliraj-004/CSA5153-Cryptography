#include <stdio.h>

#define ALPHABET_SIZE 26

char encrypt_affine(char plaintext, int a, int b) {
    if (plaintext >= 'a' && plaintext <= 'z') {
        return 'a' + (a * (plaintext - 'a') + b) % ALPHABET_SIZE;
    } else if (plaintext >= 'A' && plaintext <= 'Z') {
        return 'A' + (a * (plaintext - 'A') + b) % ALPHABET_SIZE;
    } else {
        return plaintext;
    }
}

char decrypt_affine(char ciphertext, int a, int b) {
    int mod_inverse = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            mod_inverse = i;
            break;
        }
    }

    if (ciphertext >= 'a' && ciphertext <= 'z') {
        return 'a' + mod_inverse * (ciphertext - 'a' - b + ALPHABET_SIZE) % ALPHABET_SIZE;
    } else if (ciphertext >= 'A' && ciphertext <= 'Z') {
        return 'A' + mod_inverse * (ciphertext - 'A' - b + ALPHABET_SIZE) % ALPHABET_SIZE;
    } else {
        return ciphertext;
    }
}

void process_text(const char *text, int a, int b, char *result, int encrypt) {
    int (*func)(char, int, int) = encrypt ? encrypt_affine : decrypt_affine;
    for (int i = 0; text[i] != '\0'; i++) {
        result[i] = func(text[i], a, b);
    }
    result[sizeof(text) - 1] = '\0';
}

int main(void) {
    const char *plaintext = "HelloWorld";
    int a = 5, b = 8; 
    char ciphertext[50], decryptedtext[50];

    process_text(plaintext, a, b, ciphertext, 1);
    printf("Ciphertext: %s\n", ciphertext);

    process_text(ciphertext, a, b, decryptedtext, 0);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}
