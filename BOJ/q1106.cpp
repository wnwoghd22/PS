#include <iostream>
#include <cstring>
int dp[1200];

int main() {
    int N, C, W, V;
    std::cin >> C >> N;
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    for (int i = 0; i < N; ++i) {
        std::cin >> W >> V;
        for (int k = 0; k < (C + 100) / V; ++k) {
            // std::cout << W << V << '\n';
            for (int j = C + 100; j >= V; --j) {
                if (~dp[j - V] && (!~dp[j] || dp[j - V] + W < dp[j])) 
                    dp[j] = dp[j - V] + W;

            }
        }
        // for (int j = 0; j <= C + 10; ++j) std::cout << dp[j] << ' '; std::cout << '\n';
    }
    int ret = 1e9;
    for (int i = C; i <= C + 100; ++i) ret = std::min(ret, dp[i]);
    std::cout << ret;
}