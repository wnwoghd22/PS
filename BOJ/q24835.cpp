#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int LEN = 1e5 + 1;

int N, Q, p[LEN][21], d[LEN];
std::vector<int> g[LEN];

void bfs(int v) {
    std::queue<int> q;
    memset(d, -1, sizeof d);

    q.push(v);
    d[v] = 0;

    while (!q.empty()) {
        v = q.front(); q.pop();

        if (d[v] > 0) {
            for (int i = 1; i < 21; ++i)
                p[v][i] = p[p[v][i - 1]][i - 1];
        }

        for (const int& u : g[v]) {
            if (d[u] == -1) {
                d[u] = d[v] + 1;
                p[u][0] = v;
                q.push(u);
            }
        }
    }
}

int lca(const int a, const int b) {
    int min = d[a] < d[b] ? a : b;
    int max = d[a] >= d[b] ? a : b;

    if (d[min] != d[max]) {
        for (int i = 20; i >= 0; --i) {
            if (d[p[max][i]] >= d[min])
                max = p[max][i];
        }
    }

    int result = max;

    if (min != max) {
        for (int i = 20; i >= 0; --i) {
            if (p[max][i] != p[min][i]) {
                max = p[max][i];
                min = p[min][i];
            }
            result = p[max][i];
        }
    }

    return result;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N;

    for (int u, v, i = 1; i < N; ++i) {
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    bfs(1);

    std::cin >> Q;
    for (int q = 0, x, y, a, b, k, w[3], ret; q < Q; ++q) {
        std::cin >> x >> y >> a >> b >> k;
        w[0] = d[a] + d[b] - 2 * d[lca(a, b)];
        w[1] = (d[x] + d[a] - 2 * d[lca(x, a)])
            + (d[y] + d[b] - 2 * d[lca(y, b)]) + 1;
        w[2] = (d[x] + d[b] - 2 * d[lca(x, b)])
            + (d[y] + d[a] - 2 * d[lca(y, a)]) + 1;
        ret = -1;
        std::cout << w[0] << ' ' << w[1] << ' ' << w[2] << '\n';
        for (int i = 0; i < 3; ++i) {
            if ((k ^ w[i]) & 1 ^ 1 && w[i] <= k) {
                ret = w[i];
            }
        }
        std::cout << (~ret ? "YES\n" : "NO\n");
    }
}