#include <iostream>

typedef long long ll;
ll MOD = 998244353;

ll power(ll a, ll b) {
    if (b == 1) return a % MOD;
    ll pw = power(a, b >> 1);
    return pw * pw % MOD * (b & 1 ? a : 1) % MOD;
}

ll inv[11];

ll N, A, B, P, Q, R, dp[201][101][101];

int main() {
    for (int i = 1; i <= 10; ++i) {
        inv[i] = power(i, MOD - 2);
        // std::cout << inv[i] << ' ';
    }
    std::cin >> N >> A >> B >> P >> Q;
    dp[0][A][B] = 1;
    for (int t = 0; t < 200; ++t) {
        for (int i = A; i < N; ++i) {
            for (int j = B; j < N; ++j) {
                if (~t & 1) {
                    for (ll p = 1; p <= P; ++p) {
                        dp[t + 1][std::min(i + p, N)][j] += (dp[t][i][j] * inv[P] % MOD);
                        dp[t + 1][std::min(i + p, N)][j] %= MOD;
                    }
                }
                else {
                    for (ll q = 1; q <= Q; ++q) {
                        dp[t + 1][i][std::min(j + q, N)] += (dp[t][i][j] * inv[Q] % MOD);
                        dp[t + 1][i][std::min(j + q, N)] %= MOD;
                    }
                }
            }
        }
        if (~t & 1) {
            for (int i = 1; i <= N; ++i) {
                R += dp[t + 1][N][i];
                R %= MOD;
            }
        }
    }
    std::cout << R;
}