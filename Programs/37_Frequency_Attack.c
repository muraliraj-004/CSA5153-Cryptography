#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

void count_frequency(const char *text, int *frequency) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        }
    }
}

void sort_by_frequency(int *frequency, int *indices) {
    int temp;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequency[indices[i]] < frequency[indices[j]]) {
                temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
}

void apply_substitution(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = substitution[ciphertext[i] - 'a'];
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = substitution[ciphertext[i] - 'A'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void generate_plaintext_candidates(const char *ciphertext, int top_n) {
    int frequency[ALPHABET_SIZE] = {0};
    int indices[ALPHABET_SIZE];
    char substitution[ALPHABET_SIZE] = "abcdefghijklmnopqrstuvwxyz";
    char plaintext[256];

    count_frequency(ciphertext, frequency);
    sort_by_frequency(frequency, indices);

    char most_common[ALPHABET_SIZE] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    int substitutions[ALPHABET_SIZE] = {0};

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitutions[indices[i]] = most_common[i];
    }

    for (int k = 0; k < top_n; k++) {
        int temp_substitution[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            temp_substitution[i] = substitutions[i];
        }

        char temp_subs[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            temp_subs[i] = (char)temp_substitution[i];
        }

        apply_substitution(ciphertext, temp_subs, plaintext);
        printf("Possible Plaintext #%d: %s\n", k + 1, plaintext);
        substitutions[0]++;
    }
}

int main(void) {
    char ciphertext[] = "Wklv lv d whvw phvvdjh.";
    int top_n = 10;
    printf("Top %d possible plaintexts:\n", top_n);
    generate_plaintext_candidates(ciphertext, top_n);

    return 0;
}