#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_N 10

const double english_freq[ALPHABET_SIZE] = {
    0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002,
    0.005, 0.040, 0.024, 0.067, 0.075, 0.019, 0.001, 0.060, 0.063, 0.091,
    0.028, 0.010, 0.023, 0.001, 0.020, 0.001
};

void count_frequency(const char *text, int *frequency) {
    memset(frequency, 0, ALPHABET_SIZE * sizeof(int));
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int index = tolower(text[i]) - 'a';
            frequency[index]++;
        }
    }
}

double score_plaintext(const int *frequency) {
    double score = 0.0;
    int total = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        total += frequency[i];
    }
    if (total == 0) return 0.0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observed = (double)frequency[i] / total;
        score -= observed * log(english_freq[i]);
    }

    return score;
}

void decrypt_substitution(const char *ciphertext, char *plaintext, const char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = base + (ciphertext[i] - base - (key[ciphertext[i] - base] - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

void generate_key(char *key, int shift) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        key[i] = 'A' + (i + shift) % ALPHABET_SIZE;
    }
}

void print_top_candidates(const char *ciphertext, int top_n) {
    char key[ALPHABET_SIZE];
    char plaintext[256];
    int frequency[ALPHABET_SIZE];

    double scores[TOP_N];
    char candidates[TOP_N][256];
    memset(scores, 0, TOP_N * sizeof(double));

    for (int shift = 0; shift < ALPHABET_SIZE; shift++) {
        generate_key(key, shift);
        decrypt_substitution(ciphertext, plaintext, key);
        count_frequency(plaintext, frequency);
        double score = score_plaintext(frequency);

        for (int i = 0; i < TOP_N; i++) {
            if (score > scores[i]) {
                for (int j = TOP_N - 1; j > i; j--) {
                    scores[j] = scores[j - 1];
                    strcpy(candidates[j], candidates[j - 1]);
                }
                scores[i] = score;
                strcpy(candidates[i], plaintext);
                break;
            }
        }
    }

    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("Rank %d: %s\n", i + 1, candidates[i]);
    }
}

int main(void) {
    char ciphertext[] = "Wklv lv d whvw phvvdjh.";
    int top_n = TOP_N;

    printf("Top %d possible plaintexts:\n", top_n);
    print_top_candidates(ciphertext, top_n);

    return 0;
}
