#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

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

int main(void) {
    int e = 31;
    int n = 3599;
    int p, q, phi_n, d;

    for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            if (q > 1 && gcd(p, q) == 1) break;
        }
    }

    phi_n = (p - 1) * (q - 1);

    d = mod_inverse(e, phi_n);

    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d): %d\n", d);

    return 0;
}