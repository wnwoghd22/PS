#include <iostream>

typedef long long ll;
const ll MOD = 1e9 + 7;
const int LEN = 1e5 + 3;
ll Q, A, B, D, S[LEN] = { 0, 1 };

ll power(ll a, ll b) {
    ll p = 1;
    for (; b; b /= 2, a = a * a % MOD)
        if (b & 1) p = p * a % MOD;
    return p;
}

ll C(ll n, ll k) {
    ll num = 1, den = 1;
    for (ll p = 0; p < k; ++p) {
        num = num * (n - p) % MOD;
        den = den * (p + 1) % MOD;
    }
    ll ret = num * power(den, MOD - 2) % MOD;
    return ret;
}

ll F(ll n, ll k) {
    for (ll i = 2; i < k + 2; ++i) 
        S[i] = (S[i - 1] + power(i, k)) % MOD;
    if (n < k + 2) return S[n];

    ll ret = 0, nCi = 1, nCk = C(n - 1, k + 1);
    for (int i = 1, j = k & 1 ? -1 : 1; i < k + 2; ++i, j *= -1) {
        nCi *= (n - i + 1); nCi %= MOD;
        nCi *= power(i, MOD - 2); nCi %= MOD;
        nCk *= (k - i + 2); nCk %= MOD;
        nCk *= power(n - i, MOD - 2); nCk %= MOD;
        ret += S[i] * nCi % MOD * nCk % MOD * j;
        ret = (ret + MOD) % MOD;
    }
    return ret;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> Q;
    while (Q--) {
        std::cin >> A >> B >> D;
        std::cout << F(B, D) << ' ';
        std::cout << F(A - 1, D) << ' ';
        std::cout << (F(B, D) - F(A - 1, D) + MOD) % MOD << '\n';
    }
}