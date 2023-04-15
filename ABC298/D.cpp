#include <iostream>
#include <queue>

typedef long long ll;
const ll MOD = 998244353;
std::deque<int> S;
ll Q, total = 1;

ll power(ll a, ll b) {
    if (b == 1) return a % MOD;
    ll pw = power(a, b >> 1);
    return pw * pw % MOD * (b & 1 ? a : 1) % MOD;
}

int main() {
    std::cin >> Q;
    S.push_back(1);
    for (ll i = 0, q, x; i < Q; ++i) {
        std::cin >> q;
        if (q == 1) {
            std::cin >> x;
            total = (total * 10 + x) % MOD;
            S.push_back(x);
        }
        if (q == 2) {
            ll k = S.front() * power(10, S.size() - 1) % MOD;
            total = (total - k + MOD) % MOD;
            S.pop_front();
        }
        if (q == 3) std::cout << total << '\n';
    }
}