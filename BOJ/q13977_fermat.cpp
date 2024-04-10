#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const ll MOD = 1e9 + 7;
const int LEN = 4e6 + 1;
ll f[LEN] = { 1 };

ll power(ll A, ll B) {
    if (B == 1) return A % MOD;
    else {
        ll pw = power(A, B / 2);
        return pw * pw % MOD * (B % 2 ? A : 1) % MOD;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    ll M, N, K, A, B, Bp, i;
    for (i = 1; i < LEN; ++i) f[i] = f[i - 1] * i % MOD;
    std::cin >> M;
    while (M--) {
        std::cin >> N >> K;
        A = f[N];
        B = f[K] * f[N - K] % MOD;
        Bp = power(B, MOD - 2);
        std::cout << A * Bp % MOD << '\n';
    }
}