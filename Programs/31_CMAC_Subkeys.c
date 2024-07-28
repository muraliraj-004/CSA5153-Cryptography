#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16
#define CONSTANT_64 0x1B
#define CONSTANT_128 0x87

void left_shift(unsigned char *block, int size) {
    int carry = 0;
    for (int i = 0; i < size; i++) {
        int new_carry = (block[i] >> 7) & 1;
        block[i] = (block[i] << 1) | carry;
        carry = new_carry;
    }
}

void xor_with_constant(unsigned char *block, unsigned char constant) {
    block[0] ^= constant;
}

void generate_subkeys(unsigned char *key, unsigned char *K1, unsigned char *K2, int size) {
    unsigned char constant = (size == BLOCK_SIZE_64) ? CONSTANT_64 : CONSTANT_128;
    memcpy(K1, key, size);
    left_shift(K1, size);

    if (K1[0] & 0x80) {
        xor_with_constant(K1, constant);
    }

    memcpy(K2, K1, size);
    left_shift(K2, size);

    if (K2[0] & 0x80) {
        xor_with_constant(K2, constant);
    }
}

void print_key(unsigned char *key, int size) {
    for (int i = 0; i < size; i++) {
        printf("%02x", key[i]);
    }
    printf("\n");
}

int main(void) {
    unsigned char zero_block_64[BLOCK_SIZE_64] = {0};
    unsigned char zero_block_128[BLOCK_SIZE_128] = {0};
    unsigned char K1[BLOCK_SIZE_128], K2[BLOCK_SIZE_128];

    printf("64-bit Block Size Subkeys:\n");
    generate_subkeys(zero_block_64, K1, K2, BLOCK_SIZE_64);
    printf("K1 = ");
    print_key(K1, BLOCK_SIZE_64);
    printf("K2 = ");
    print_key(K2, BLOCK_SIZE_64);

    printf("128-bit Block Size Subkeys:\n");
    generate_subkeys(zero_block_128, K1, K2, BLOCK_SIZE_128);
    printf("K1 = ");
    print_key(K1, BLOCK_SIZE_128);
    printf("K2 = ");
    print_key(K2, BLOCK_SIZE_128);

    return 0;
}