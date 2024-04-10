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

int main() {
    ll N, M, A, Ap, H, result;
    
    std::cin >> N >> M >> A >> H;
    result = power(M, N, MOD);
    std::cout << result << '\n';
    Ap = power(M, MOD - 2, MOD); // B^-1 mod P = B^P-2 mod P
    std::cout << result * Ap % MOD;
}