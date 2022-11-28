#include <iostream>

typedef unsigned long long int ll;

ll power(ll a, ll b, ll mod) {
    if (b == 1) return a % mod;
    else {
        ll pw = power(a, b / 2, mod);
        return pw * pw % mod * (b & 1 ? a : 1) % mod;
    }
}

// prevent overflow
ll power_(ll x, ll y, ll mod) {
    ll res = 1;
    x %= mod;
    while (y) {
        if (y & 1) res = (res * x) % mod;
        y >>= 1;
        x = (x * x) % mod;
    }
    return res;
}

bool miller_rabin(const ll n, const ll a) {
    if (!(a % n)) return true;
    ll k = n - 1;
    while (true) {
        ll temp = power(a, k, n);
        if (temp == n - 1) return true; // a^k = -1 (mod n)
        if (k & 1) return temp == 1;
        k >>= 1;
    }
}

bool miller_rabin(const ll n) {
    return miller_rabin(n, 2) && miller_rabin(n, 7) && miller_rabin(n, 61);
}

int main() {
    ll N, A, result = 0;
    std::cin >> N;
    while (N--) {
        std::cin >> A;
        if (miller_rabin(A * 2 + 1)) ++result; // 2A + 1이 소수인가?
    }
    std::cout << result;
}