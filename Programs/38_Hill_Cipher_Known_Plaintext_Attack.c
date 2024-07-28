#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 2
#define MOD 26

void matrix_mult(int a[MATRIX_SIZE][MATRIX_SIZE], int b[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % MOD;
            }
        }
    }
}

void matrix_mod_inverse(int a[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = (a[0][0] * a[1][1] - a[0][1] * a[1][0] + MOD) % MOD;
    int inv_det = 0;
    for (int i = 1; i < MOD; i++) {
        if ((det * i) % MOD == 1) {
            inv_det = i;
            break;
        }
    }
    result[0][0] = (a[1][1] * inv_det) % MOD;
    result[0][1] = (-a[0][1] * inv_det + MOD) % MOD;
    result[1][0] = (-a[1][0] * inv_det + MOD) % MOD;
    result[1][1] = (a[0][0] * inv_det) % MOD;
}

void hill_encrypt(int plaintext[], int key[MATRIX_SIZE][MATRIX_SIZE], int ciphertext[]) {
    int pt_matrix[MATRIX_SIZE][1] = {{plaintext[0]}, {plaintext[1]}};
    int ct_matrix[MATRIX_SIZE][1];
    matrix_mult(key, pt_matrix, ct_matrix);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        ciphertext[i] = (ct_matrix[i][0] + MOD) % MOD;
    }
}

void hill_decrypt(int ciphertext[], int key[MATRIX_SIZE][MATRIX_SIZE], int plaintext[]) {
    int key_inv[MATRIX_SIZE][MATRIX_SIZE];
    matrix_mod_inverse(key, key_inv);
    int ct_matrix[MATRIX_SIZE][1] = {{ciphertext[0]}, {ciphertext[1]}};
    int pt_matrix[MATRIX_SIZE][1];
    matrix_mult(key_inv, ct_matrix, pt_matrix);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        plaintext[i] = (pt_matrix[i][0] + MOD) % MOD;
    }
}

void print_matrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void known_plaintext_attack(int pt1[], int ct1[], int pt2[], int ct2[], int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int matrix1[MATRIX_SIZE][MATRIX_SIZE] = {
        {pt1[0], pt1[1]},
        {pt2[0], pt2[1]}
    };
    int matrix2[MATRIX_SIZE][MATRIX_SIZE] = {
        {ct1[0], ct1[1]},
        {ct2[0], ct2[1]}
    };
    int matrix1_inv[MATRIX_SIZE][MATRIX_SIZE];
    matrix_mod_inverse(matrix1, matrix1_inv);
    int key_matrix[MATRIX_SIZE][MATRIX_SIZE];
    matrix_mult(matrix2, matrix1_inv, key_matrix);
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            key[i][j] = key_matrix[i][j];
        }
    }
}

int main(void) {
    int plaintext1[MATRIX_SIZE] = {0, 1};
    int ciphertext1[MATRIX_SIZE] = {7, 22};
    int plaintext2[MATRIX_SIZE] = {2, 3};
    int ciphertext2[MATRIX_SIZE] = {23, 20};

    int key[MATRIX_SIZE][MATRIX_SIZE];
    known_plaintext_attack(plaintext1, ciphertext1, plaintext2, ciphertext2, key);

    printf("Key Matrix:\n");
    print_matrix(key);

    int plaintext[MATRIX_SIZE];
    int ciphertext[MATRIX_SIZE] = {0, 1};

    hill_decrypt(ciphertext, key, plaintext);
    printf("Decrypted Text: %d %d\n", plaintext[0], plaintext[1]);

    return 0;
}
