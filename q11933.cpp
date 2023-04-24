#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

typedef long long ll;
const int LEN = 100'001;
const ll INF = 2e17;

struct Edge { int v, d; };
std::vector<Edge> tree[LEN];
std::vector<int> cent_tree[LEN];

int N, Q, size[LEN];
bool visited[LEN];

void add_edge(int u, int v, int d) {
    tree[u].push_back({ v ,d });
    tree[v].push_back({ u, d });
}

int get_size(int u, int p = 0) {
    size[u] = 1;
    for (const Edge& e : tree[u]) {
        if (e.v == p || visited[e.v]) continue;
        size[u] += get_size(e.v, u);
    }
    return size[u];
}

int get_cent(int u, int p, int s) {
    for (const Edge& e : tree[u]) {
        if (e.v != p && !visited[e.v] && size[e.v] * 2 > s)
            return get_cent(e.v, u, s);
    }
    return u;
}

int decompose_tree(int u) {
    int cent = get_cent(u, 0, get_size(u));
    // std::cout << u << ' ' << size[u] << ' ' << cent << '\n';
    visited[cent] = 1;
    for (const Edge& e : tree[cent]) {
        if (!visited[e.v]) {
            int sub_cent = decompose_tree(e.v);
            cent_tree[cent].push_back(sub_cent);
            cent_tree[sub_cent].push_back(cent);
        }
    }
    return cent;
}

int level[LEN], parent[LEN][21];
ll dst[LEN];
void dfs(int u, ll d = 0, int p = 0) {
    parent[u][0] = p;
    level[u] = level[p] + 1;
    dst[u] = d;
    // std::cout << u << ' ' << dst[u] << '\n';
    for (int i = 1, v = p; v; v = parent[u][i++]) {
        parent[u][i] = parent[v][i - 1];
    }
    for (const Edge& e : tree[u]) {
        if (e.v == p) continue;
        dfs(e.v, dst[u] + e.d, u);
    }
}
int lca(int u, int v) {
    if (level[u] ^ level[v]) {
        if (level[u] > level[v]) std::swap(u, v);
        for (int i = 20; i >= 0; --i)
            if (level[parent[v][i]] >= level[u])
                v = parent[v][i];
    }
    int l = u;
    if (u ^ v) {
        for (int i = 20; i >= 0; --i) {
            if (parent[u][i] ^ parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
            l = parent[u][i];
        }
    }
    return l;
}
ll dist(int u, int v) { return dst[u] + dst[v] - dst[(lca(u, v))] * 2; }

int cent_parent[LEN];
ll min_dist[LEN];
void dfs_cent(int u, int p = 0) {
    cent_parent[u] = p;
    for (const int& v : cent_tree[u])
        if (v != p)
            dfs_cent(v, u);
}
void push(int u) {
    int v = u;
    while (v) {
        ll d = dist(u, v);
        min_dist[v] = std::min(min_dist[v], d);
        v = cent_parent[v];
    }
}
void pop(int u) {
    int v = u;
    while (v) {
        min_dist[v] = INF;
        v = cent_parent[v];
    }
}
ll query(int u) {
    int v = u;
    ll min = INF;
    while (v) {
        ll d = dist(u, v);
        min = std::min(min, min_dist[v] + d);
        v = cent_parent[v];
    }
    return min == INF ? -1 : min;
}
int X[LEN];

int main() {
    freopen("input.txt", "r", stdin);
    std::cin >> N >> Q;
    for (int i = 1, u, v, d; i < N; ++i) {
        std::cin >> u >> v >> d;
        add_edge(++u, ++v, d);
    }
    dfs(1);

    int root = decompose_tree(1);
    dfs_cent(root);

    for (int i = 1; i <= N; ++i) min_dist[i] = INF;

    for (int i = 0, S, T, Y; i < Q; ++i) {
        ll R = INF;
        std::cin >> S >> T;
        for (int j = 0; j < S; ++j) {
            std::cin >> X[j];
            push(++X[j]);
        }
        while (T--) {
            std::cin >> Y;
            R = std::min(R, query(++Y));
        }
        std::cout << R << '\n';
        for (int j = 0; j < S; ++j) {
            pop(X[j]);
        }
    }
}