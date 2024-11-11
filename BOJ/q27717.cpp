#include <iostream>

typedef long long int ll;
const ll MOD = 1e9 + 9;
const int LEN = 2e6 + 1;
ll T, N, D, A, f[LEN] = { 1 }, fi[LEN] = { 1 };

ll power(ll A, ll B) {
    ll ret = 1;
    while (B) {
        if (B & 1) ret = ret * A % MOD;
        A = A * A % MOD; B >>= 1;
    }
    return ret;
}

ll C(ll n, ll k) { return f[n] * fi[k] % MOD * fi[n - k] % MOD; }

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> T;
    for (int i = 1; i < LEN; ++i) f[i] = f[i - 1] * i % MOD;
    for (int i = 1; i < LEN; ++i) fi[i] = power(f[i], MOD - 2);
    while (T--) {
        std::cin >> N >> D;
        ll ret = 0;
        for (int i = 0; i < N; ++i) {
            std::cin >> A;
            ret = (ret + C(D + i, D) * C(N - i - 1 + D, D) % MOD * A) % MOD;
        }
        std::cout << ret << '\n';
    }
}