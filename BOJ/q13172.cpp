#include <iostream>

typedef long long int ll;
const ll MOD = 1'000'000'007;

ll power(ll A, ll B, ll C) {
    if (B == 1) return A % C;
    else {
        ll pw = power(A, B / 2, C);
        return pw * pw % C * (B % 2 ? A : 1) % C;
    }
}
ll gcd(ll A, ll B) { return !B ? A : gcd(B, A % B); }

int main() {
    ll M, N, S, sum = 0;
    std::cin >> M;
    
    for (int i = 0; i < M; ++i) {
        std::cin >> N >> S;
        ll D = gcd(N, S);
        N /= D, S /= D;
        sum += power(N, MOD - 2, MOD) * S % MOD;
        sum %= MOD;
    }
    std::cout << sum;
}