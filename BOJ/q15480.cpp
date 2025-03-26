#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

typedef long long ll;
const int LEN = 1e5 + 1;

int N, Q;
std::vector<int> g[LEN];
int p[LEN][21];
int depth[LEN];
void dfs(int u, int w = 0) {
    depth[u] = depth[w] + 1;
    for (int i = 1; i < 21; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];

    for (const int& v : g[u]) {
        if (v == w) continue;
        p[v][0] = u;
        dfs(v, u);
    }
}

int lca(const int a, const int b) {
    int min = depth[a] < depth[b] ? a : b;
    int max = depth[a] >= depth[b] ? a : b;

    if (depth[min] != depth[max]) {
        for (int i = 20; i >= 0; --i) {
            if (depth[p[max][i]] >= depth[min])
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
    dfs(1);
    
    std::cin >> Q;
    for (int k = 0, r, u, v, a, b, c, ret; k < Q; ++k) {
        std::cin >> r >> u >> v;
        a = lca(r, u);
        b = lca(r, v);
        c = lca(u, v);
        ret = depth[a] > depth[b] ? a : b;
        ret = depth[ret] > depth[c] ? ret : c;
        std::cout << ret << '\n';
    }
}