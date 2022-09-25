#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

typedef long long int ll;

int N;
std::vector<std::pair<int, int>> graph[100'001];
int parent[100'001][21];
ll cost[100'001];
int depth[100'001];

void bfs(int v) {
    std::queue<int> q;
    memset(depth, -1, sizeof depth);

    q.push(v);
    depth[v] = 0;

    while (!q.empty()) {
        v = q.front(); q.pop();

        if (depth[v] > 0) {
            for (int i = 1; i < 21; ++i) {
                parent[v][i] = parent[parent[v][i - 1]][i - 1];
            }
        }

        for (const std::pair<int, int>& pii : graph[v]) {
            int u = pii.first, c = pii.second;
            if (depth[u] == -1) {
                depth[u] = depth[v] + 1;
                parent[u][0] = v;
                cost[u] = cost[v] + c;
                q.push(u);
            }
        }
    }
}

int LCA(const int a, const int b) {
    int min = depth[a] < depth[b] ? a : b;
    int max = depth[a] >= depth[b] ? a : b;
    int minv = 1'000'000;
    int maxv = 0;

    if (depth[min] != depth[max]) {
        for (int i = 20; i >= 0; --i) {
            if (depth[parent[max][i]] >= depth[min]) {
                max = parent[max][i];
            }
        }
    }

    int result = max;

    if (min != max) {
        for (int i = 20; i >= 0; --i) {
            if (parent[max][i] != parent[min][i]) {
                max = parent[max][i];
                min = parent[min][i];
            }
            result = parent[max][i];
        }
    }

    return result;
}

ll get_cost(const int a, const int b) {
    int lca = LCA(a, b);
    return cost[a] + cost[b] - 2 * cost[lca];
}
int get_kth(int a, int b, int k) {
    int lca = LCA(a, b);
    int diff = depth[a] - depth[lca];
    k--;
    if (k <= diff) {
        for (int i = 0; k; ++i) {
            if (k & 1) a = parent[a][i];
            k >>= 1;
        }
        return a;
    }
    k = depth[b] - depth[lca] + diff - k;

    for (int i = 0; k; ++i) {
        if (k & 1) b = parent[b][i];
        k >>= 1;
    }
    return b;
}

int main() {
    int M;

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);

    std::cin >> N;

    for (int u, v, d, i = 0; i < N - 1; ++i) {
        std::cin >> u >> v >> d;
        graph[u].push_back({ v, d });
        graph[v].push_back({ u, d });
    }
    bfs(1);

    std::cin >> M;

    while (M--) {
        int q, a, b, k;
        std::cin >> q >> a >> b;
        if (q == 1) {
            std::cout << get_cost(a, b) << '\n';
        }
        else if (q == 2) {
            std::cin >> k;
            std::cout << get_kth(a, b, k) << '\n';
        }
    }

    return 0;
}