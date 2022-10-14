#include <iostream>
#include <map>
#include <cstring>

typedef long long int ll;
const int CHILDREN = 30'001;
const int MAX_WEIGHT = 3001;
int N, M, K;

int p[CHILDREN];
ll weight[CHILDREN];

int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
int get_size(int i) { return -p[find(i)]; }
ll get_weight(int i) { return weight[find(i)]; }
bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;

    if (p[a] < p[b]) p[a] += p[b], p[b] = a, weight[a] += weight[b];
    else p[b] += p[a], p[a] = b, weight[b] += weight[a];
    return true;
}

ll dp[CHILDREN][MAX_WEIGHT];
std::map<int, std::pair<int, ll>> group;

int main() {
    int W, i, j;
    ll V;
    std::cin >> N >> M >> K;

    memset(p, -1, sizeof p);
    for (i = 1; i <= N; ++i) std::cin >> weight[i];
    while (M--) {
        std::cin >> i >> j;
        join(i, j);
    }

    for (i = 1; i <= N; ++i)
        if (group.find(find(i)) == group.end())
            group[find(i)] = { get_size(i), get_weight(i) };

    i = 0;
    for (const auto& [k, v] : group) {
        ++i;
        W = v.first; V = v.second;

        for (j = 1; j <= K; ++j) {
            if (j < W) dp[i][j] = dp[i - 1][j];
            else dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - W] + V);
        }
    }

    std::cout << dp[i][K - 1];
}