#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef unsigned long long int ull;
ull gcd(ull a, ull b) {
    while (b != 0) {
        ull t = b;
        b = a % b;
        a = t;
    }
    return a;
}
ull mod_exp(ull base, ull exp, ull mod) {
    ull result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}
ull mod_inverse(ull a, ull m) {
    ull m0 = m, t, q;
    ull x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) x1 += m0;

    return x1;
}
void generate_keys(ull *e, ull *d, ull *n) {
    ull p = 61, q = 53;
    *n = p * q;
    ull phi_n = (p - 1) * (q - 1);
    *e = 17; 
    *d = mod_inverse(*e, phi_n);
}
ull rsa_encrypt(ull plaintext, ull e, ull n) {
    return mod_exp(plaintext, e, n);
}
ull rsa_decrypt(ull ciphertext, ull d, ull n) {
    return mod_exp(ciphertext, d, n);
}

int main(void) {
    ull e, d, n;
    generate_keys(&e, &d, &n);

    printf("Public Key (e, n): (%llu, %llu)\n", e, n);
    printf("Private Key (d): %llu\n", d);

    ull plaintext = 65;
    ull ciphertext = rsa_encrypt(plaintext, e, n);
    ull decryptedtext = rsa_decrypt(ciphertext, d, n);

    printf("Plaintext: %llu\n", plaintext);
    printf("Ciphertext: %llu\n", ciphertext);
    printf("Decrypted Text: %llu\n", decryptedtext);

    return 0;
}