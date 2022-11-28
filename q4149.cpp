#include <iostream>
#include <vector>
#include <algorithm>

typedef long long int ll;
ll prime_set[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
ll gcd(const ll a, const ll b) { return !b ? a : gcd(b, a % b); }
ll power(ll a, ll b, ll mod) {
    if (b == 1) return a % mod;
    else {
        ll pw = power(a, b / 2, mod);
        return pw * pw % mod * (b & 1 ? a : 1) % mod;
    }
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
    for (const ll& p : prime_set)
        if (!miller_rabin(n, p))
            return false;
    return true;
}

void pollard_rho(const ll n, std::vector<ll>& v) {
    if (n == 1) return;
    if (!(n & 1)) {
        v.push_back(2);
        pollard_rho(n >> 1, v);
        return;
    }
    if (miller_rabin(n)) {
        v.push_back(n);
        return;
    }

    ll a, b, c, g = n;
    auto f = [&](ll x) { return (c + x * x) % n; };
    do {
        if (g == n) {
            a = b = std::rand() % (n - 2) + 2;
            c = std::rand() % 20 + 1;
        }
        a = f(a);
        b = f(f(b));
        g = gcd(abs(a - b), n);
    } while (g == 1);

    pollard_rho(g, v);
    pollard_rho(n / g, v);
}
std::vector<ll> pollard_rho(const ll n) {
    std::vector<ll> v;
    pollard_rho(n, v);
    std::sort(v.begin(), v.end());
    return v;
}

int main() {
    ll N;
    std::cin >> N;
    for (const ll& i : pollard_rho(N)) {
        std::cout << i << '\n';
    }
}