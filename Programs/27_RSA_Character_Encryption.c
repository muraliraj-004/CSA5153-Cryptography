#include <stdio.h>

typedef unsigned long long ull;

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

    char message[] = "HELLO";
    int length = sizeof(message) - 1;
    printf("Public Key (e, n): (%llu, %llu)\n", e, n);
    printf("Private Key (d): %llu\n", d);

    printf("Encrypted message:\n");
    for (int i = 0; i < length; i++) {
        ull num = message[i] - 'A';
        ull encrypted = rsa_encrypt(num, e, n);
        printf("%llu ", encrypted);
    }
    printf("\n");

    printf("Decrypted message:\n");
    for (int i = 0; i < length; i++) {
        ull num = rsa_encrypt(message[i] - 'A', e, n);
        ull decrypted = rsa_decrypt(num, d, n);
        printf("%c", decrypted + 'A');
    }
    printf("\n");

    return 0;
}
