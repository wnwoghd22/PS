#include <iostream>
#include <cstring>

const int LEN = 1'500'001;

int N, P[LEN], T[LEN], dp[LEN][2];

int f(int i, int t) {
    if (i > N) return 0;
    int& ref = dp[i][t];
    if (~ref) return ref;
    if (t) {
        if (i + T[i] - 1 > N) return ref = 0;
        ref = std::max(f(i + T[i], 0), f(i + T[i], 1)) + P[i];
    }
    else ref = std::max(f(i + 1, 0), f(i + 1, 1));
    return ref;
}

int main() {
    memset(dp, -1, sizeof dp);
    std::cin >> N;
    for (int i = 1; i <= N; ++i) std::cin >> T[i] >> P[i];
    std::cout << std::max(f(1, 1), f(1, 0));
}