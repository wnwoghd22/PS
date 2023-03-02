#include <iostream>

#define MOD 1'000'000'007

typedef long long int LL;

LL power(LL A, LL B, LL C) {
    if (B == 1) return A % C;
    else {
        LL pw = power(A, B / 2, C);
        return pw * pw % C * (B % 2 ? A : 1) % C;
    }
}

int main() {
    LL N, K, A = 1, B = 1, Bp, i;
    std::cin >> N >> K;
    for (i = 1; i <= N; ++i) A *= i, A %= MOD;
    for (i = 1; i <= K; ++i) B *= i, B %= MOD;
    for (i = 1; i <= N - K; ++i) B *= i, B %= MOD;
    Bp = power(B, MOD - 2, MOD); // B^-1 mod P = B^P-2 mod P
    std::cout << A * Bp % MOD;
}