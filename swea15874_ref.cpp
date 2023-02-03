#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ld = long double;
using pll = pair<ll, ll>;
// and so on
ll BigN = 1000000007;
#define int long long
ll fact(int k) {
    ll ret = 1;
    for (int i = 2; i <= k; i++) ret = (ret * i) % BigN;
    return ret;
}
ll modmul(ll a, ll n) {
    ll ret = 1;
    while (n > 0) {
        if (n & 1) ret = (ret * a) % BigN;
        a = (a * a) % BigN;
        n >>= 1;
    }
    return ret;
}
ll inv(ll n) {
    return modmul(n, BigN - 2);
}
ll naive_comb(int n, int k) {
    ll ret = 1;
    for (int i = 0; i < k; i++) {
        ret = (ret * (n - i) + BigN * BigN) % BigN;
    }
    return (ret * inv(fact(k))) % BigN;
}
ll dp[4005][2005];
ll vis[4005][2005];
ll S2(int n, int m) {
    if (n == m) return 1;
    else if (n == 0 || m == 0) return 0;
    if (vis[n][m] == BigN) return dp[n][m];
    ll tmp = (m * S2(n - 1, m)) % BigN;
    vis[n][m] = BigN;
    return dp[n][m] = (tmp + S2(n - 1, m - 1)) % BigN;
}
ll sol(int n, int m) {
    // calc c(n, n - m)
    ll ret = 0;
    ll A = naive_comb(-(n - m), m);
    ll B = naive_comb(n + m, m);
    ret = (A * B) % BigN;
    ret = (ret * S2(m, 0)) % BigN;
    for (int k = 1; k <= m; k++) {
        A = (A * (-(n - m) - (m + k) + 1) + BigN * BigN) % BigN;
        A = (A * inv(m + k)) % BigN;
        B = (B * (m - k + 1)) % BigN;
        B = (B * inv(n + m - (m - k + 1) + 1)) % BigN;
        if (n + m - (m - k + 1) + 1 == BigN) {
            B = naive_comb(n + m, m - k);
        }
        ll cnt = (A * B) % BigN;
        ret += (cnt * S2(k + m, k)) % BigN;
        ret %= BigN;
    }
    return ret;
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int TC = 0;
    cin >> TC;
    for (int tc = 1; tc <= TC; tc++) {
        int N, K;
        cin >> N >> K >> BigN;
        cout << '#' << tc << ' ' << sol(N + 1, K) << endl;
    }
}