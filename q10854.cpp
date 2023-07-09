#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int ll;
ll prime_set[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
ll gcd(ll a, ll b) { return !b ? a : gcd(b, a % b); }
ll mul(ll p, ll q, ll m) {
    p %= m; q %= m;
    ll r = 0, w = p;
    while (q) {
        if (q & 1) {
            r = (r + w) % m;
        }
        w = (w + w) % m;
        q >>= 1;
    }
    return r;
}
ll power(ll p, ll q, ll m) {
    p %= m;
    ll r = 1, w = p;
    while (q) {
        if (q & 1) {
            r = mul(r, w, m);
        }
        w = mul(w, w, m);
        q >>= 1;
    }
    return r;
}

bool miller_rabin(ll n, ll a) {
    if (!(n % a)) return false;
    ll k = n - 1;
    while (true) {
        ll temp = power(a, k, n);
        if (k & 1) return (temp != 1 && temp != n - 1);
        else if (temp == n - 1) return false;

        k >>= 1;
    }
}
bool miller_rabin(ll n) {
    for (auto& p : prime_set) {
        if (n == p) return true;
        if (n > 40 && miller_rabin(n, p))
            return false;
    }
    if (n <= 40) return false;
    return true;
}

void pollard_rho(ll n, vector<ll>& v) {
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
    a = b = rand() % (n - 2) + 2;
    c = rand() % 20 + 1;
    auto f = [&](ll x) { return (c + mul(x, x, n)) % n; };
    do {
        a = f(a);
        b = f(f(b));
        g = gcd(abs(a - b), n);
    } while (g == 1);

    pollard_rho(g, v);
    pollard_rho(n / g, v);
}
vector<ll> pollard_rho(ll n) {
    vector<ll> v;
    pollard_rho(n, v);
    sort(v.begin(), v.end());
    return v;
}

int main() {
    ll N;
    cin >> N;

    ll result = 1;
    ll cnt = 0;
    ll p = -1;
    for (auto& i : pollard_rho(N)) {
        if (p ^ i) {
            result *= cnt + 1;
            cnt = 1;
            p = i;
        }
        else ++cnt;
    }
    result *= cnt + 1;
    cout << result;
}