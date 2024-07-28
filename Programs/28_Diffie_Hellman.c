#include <stdio.h>

typedef unsigned long long ull;

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

int main(void) {
    ull a = 5;
    ull q = 23;
    ull alice_secret = 6;
    ull bob_secret = 15;

    ull alice_public = mod_exp(a, alice_secret, q);
    ull bob_public = mod_exp(a, bob_secret, q);

    ull alice_shared_key = mod_exp(bob_public, alice_secret, q);
    ull bob_shared_key = mod_exp(alice_public, bob_secret, q);

    printf("Alice's public value: %llu\n", alice_public);
    printf("Bob's public value: %llu\n", bob_public);
    printf("Shared secret: %llu\n", alice_shared_key);

    return 0;
}