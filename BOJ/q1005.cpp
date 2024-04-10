#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX = 1000;

int cost[MAX];
int incoming[MAX];
std::vector<int> graph[MAX];
std::vector<int> prior[MAX];
int N;

int topological_sort() {
    std::queue<int> q;

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();

        int pre = 0;
        for (const int& u : prior[v]) {
            pre = std::max(pre, cost[u]);
        }
        cost[v] += pre;

        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                q.push(u);
            }
        }
    }

    return 0;
}

int main() {
    // std::ios_base::sync_with_stdio(0);
    // std::cin.tie(0); std::cout.tie(0);

    int T, M, W;

    std::cin >> T;
    while (T--) {
        memset(cost, 0, sizeof cost);
        memset(incoming, 0, sizeof incoming);
        for (std::vector<int>& v : graph) v.clear();
        for (std::vector<int>& v : prior) v.clear();

        std::cin >> N >> M;
        for (int i = 1; i <= N; ++i) {
            std::cin >> cost[i];
        }

        while (M--) {
            int a, b;
            std::cin >> a >> b;
            graph[a].push_back(b);
            prior[b].push_back(a);
            incoming[b]++;
        }
        std::cin >> W;

        int result = topological_sort();

        std::cout << cost[W] << '\n';
    }

    return 0;
}