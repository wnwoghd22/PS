#include <iostream>
#include <algorithm>
#include <cstring>

const int CHILDREN = 30'001;
const int MAX_WEIGHT = 3001;
int N, M, K;
int p[CHILDREN], weight[CHILDREN], dp[MAX_WEIGHT];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
void join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a, weight[a] += weight[b];
    else p[b] += p[a], p[a] = b, weight[b] += weight[a];
}

int main() {
    int W, V, i, j;
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cin >> N >> M >> K;

    memset(p, -1, sizeof p);
    for (i = 1; i <= N; ++i) std::cin >> weight[i];
    while (M--) {
        std::cin >> i >> j;
        join(i, j);
    }

    for (i = 1; i <= N; ++i) {
        if (i != find(i)) continue;
        W = -p[i]; V = weight[i];
        for (j = K; j >= W; --j) dp[j] = std::max(dp[j], dp[j - W] + V);
    }

    std::cout << dp[K - 1];
}