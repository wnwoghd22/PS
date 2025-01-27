#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

typedef long long ll;
const int LEN = 1e5 + 1;

int N, Y, Q;
std::vector<int> g[LEN];
int p[LEN][21];
int depth[LEN], S[LEN];
int eu, s[LEN], e[LEN]; // euler tour trick order
int dfs(int u, int w = 0) {
    depth[u] = depth[w] + 1;
    S[u] = 1;
    s[u] = ++eu;
    for (int i = 1; i < 21; ++i)
        p[u][i] = p[p[u][i - 1]][i - 1];

    for (const int& v : g[u]) {
        if (v == w) continue;
        p[v][0] = u;
        S[u] += dfs(v, u);
    }
    e[u] = eu;
    return S[u];
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

// parallel binary search
ll t[LEN];
int X[LEN * 2];
int O[LEN * 3]; // order in tree
ll sum(int i) {
    ll ret = 0;
    while (i > 0) {
        ret += t[i];
        i -= i & -i;
    }
    return ret;
}
void update(int i, ll d) {
    while (i < LEN) {
        t[i] += d;
        i += i & -i;
    }
}
int ql[LEN * 3], qr[LEN * 3], len;
std::vector<int> queries[LEN];

// tree of tree
ll M[LEN]; // cumulative size of tree M
int P[LEN][21], R[LEN]; // parent tree of tree, root of tree 
std::vector<int> G[LEN];
ll D[LEN], level[LEN];
void DFS(int u) {
    for (int i = 1; i < 21; ++i)
        P[u][i] = P[P[u][i - 1]][i - 1];
    for (const int& v : G[u]) {
        level[v] = level[u] + 1;
        D[v] = D[u] + (depth[qr[u]] - depth[R[v]]);
        DFS(v);
    }
}

int LCA(const int a, const int b) {
    int min = level[a] < level[b] ? a : b;
    int max = level[a] >= level[b] ? a : b;

    if (level[min] != level[max]) {
        for (int i = 20; i >= 0; --i) {
            if (level[P[max][i]] >= level[min])
                max = P[max][i];
        }
    }

    int result = max;

    if (min != max) {
        for (int i = 20; i >= 0; --i) {
            if (P[max][i] != P[min][i]) {
                max = P[max][i];
                min = P[min][i];
            }
            result = P[max][i];
        }
    }

    return result;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N >> Y >> Q;
    for (int u, v, i = 1; i < N; ++i) {
        std::cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(depth, -1, sizeof depth);
    dfs(1);

    M[0] = N; R[0] = 1;
    for (ll i = 1, t; i <= Y; ++i) { // get trees
        std::cin >> R[i] >> t;
        int l = 0, r = i - 1, m;
        while (l <= r) { // binary search
            m = l + r >> 1;
            if (t <= M[m]) {
                P[i][0] = m;
                r = m - 1;
            }
            else l = m + 1;
        }
        G[P[i][0]].push_back(i);
        O[i] = t - (P[i] ? M[P[i][0] - 1] : 0); // set order of root node
        M[i] = M[i - 1] + S[R[i]];
        ql[i] = 1, qr[i] = N;
        // std::cout << O[i] << ' ' << P[i] << ' ' << R[i] << ' ' << M[i] << '\n';
    }
    for (ll i = 1, t; i <= Q * 2; ++i) { // get queries
        std::cin >> t;
        int l = 0, r = Y, m;
        while (l <= r) { // binary search
            m = l + r >> 1;
            if (t <= M[m]) {
                X[i] = m;
                r = m - 1;
            }
            else l = m + 1;
        }
        ql[i + Y] = 1, qr[i + Y] = N;
    }
    while (1) { // PBS
        len = 0;
        memset(t, 0, sizeof t);
        for (int i = 1; i <= N; ++i) queries[i].clear();
        for (int i = 1; i <= Y + Q * 2; ++i) {
            if (ql[i] < qr[i]) {
                int m = ql[i] + qr[i] >> 1;
                queries[m].push_back(i);
                ++len;
            }
        }
        if (!len) break;
        for (int m = 1; m <= N; ++m) {
            update(s[m], 1);
            for (const int& qi : queries[m]) {
                int root = R[P[qi][0]];
                int cnt = sum(e[root]) - sum(s[root] - 1);
                if (cnt >= O[qi]) qr[qi] = m;
                else ql[qi] = m + 1;
            }
        }
    }
    DFS(0);

    for (int k = 0, l, r, x, y; k < Q; ++k) {
        ll ret = 0;
        l = qr[Y + k * 2 + 1];
        r = qr[Y + k * 2 + 2];
        x = X[k * 2 + 1];
        y = X[k * 2 + 2];
        std::cout << "query " << k << ": [" << x << ", " << l << "] -> [" << y << ", " << r << "]\n";
        if (x == y) {
            int c = lca(l, r);
            std::cout << ret + (depth[l] + depth[r]) - depth[c] * 2 << '\n';
            continue;
        }
        if (level[x] > level[y]) std::swap(x, y), std::swap(l, r);
        if (level[y] > level[x]) {
            ret += depth[r] - depth[R[y]];
            ret += D[y];
            for (int i = 20; i >= 0; --i) {
                if (level[P[y][i]] > level[x])
                    y = P[y][i];
            }
            ret -= D[y];
            if (P[y][0] == x) {
                r = R[y];
                int c = lca(l, r);
                std::cout << ret + (depth[l] + depth[r]) - depth[c] * 2 << '\n';
                continue;
            }
        }
        ret += depth[l] - depth[R[x]];
        ret += depth[r] - depth[R[y]];
        int c = LCA(x, y);
        ret += D[x]; ret += D[y];
        for (int i = 20; i >= 0; --i) {
            if (level[P[x][i]] > level[x]) y = P[x][c];
            if (level[P[y][i]] > level[c]) y = P[y][c];
        }
        ret -= D[x]; ret -= D[y];
        l = R[x]; r = R[y];
        c = lca(l, r);
        std::cout << ret + (depth[l] + depth[r]) - depth[c] * 2 << '\n';
    }

    return 0;
}