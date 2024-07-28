#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define TOP_N 10

void count_frequency(const char *text, int *frequency) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        }
    }
}

int get_most_frequent_letter(int *frequency) {
    int max_freq = 0;
    int letter = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            letter = i;
        }
    }
    return letter;
}

void decrypt_additive_cipher(const char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + (ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = 'A' + (ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void print_top_candidates(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE];
    char plaintext[256];
    int letter_frequency[ALPHABET_SIZE];
    
    count_frequency(ciphertext, frequency);
    int most_frequent = get_most_frequent_letter(frequency);
    
    for (int i = 0; i < top_n; i++) {
        int shift = (most_frequent - i + ALPHABET_SIZE) % ALPHABET_SIZE;
        decrypt_additive_cipher(ciphertext, shift, plaintext);
        printf("Possible Plaintext #%d (shift %d): %s\n", i + 1, shift, plaintext);
    }
}

int main(void) {
    char ciphertext[] = "Uifsf jt b tfdsfu nfttbhf.";
    int top_n = TOP_N; 

    printf("Top %d possible plaintexts:\n", top_n);
    print_top_candidates(ciphertext, top_n);

    return 0;
}
