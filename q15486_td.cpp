#include <iostream>
#include <algorithm>

const int LEN = 1'500'001;

int N, P[LEN], T[LEN], dp[LEN];

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        dp[i] = std::max(dp[i], dp[i - 1]);
        std::cin >> T[i] >> P[i];
        if (i + T[i] - 1 > N) continue;
        dp[i + T[i] - 1] = std::max(dp[i + T[i] - 1], dp[i - 1] + P[i]);
    }
    std::cout << dp[N];
}