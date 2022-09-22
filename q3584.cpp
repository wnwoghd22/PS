#include <iostream>
#include <vector>
#include <cstring>

int N;
std::vector<int> graph[10001];
int parent[10001][15];
int depth[10001];

void dfs(int v) {
    for (int i = 1; i < 15; ++i)
        parent[v][i] = parent[parent[v][i - 1]][i - 1];

    for (const int& u : graph[v]) {
        if (depth[u] == -1) {
            depth[u] = depth[v] + 1;
            dfs(u);
        }
    }
}

int LCA(const int a, const int b) {
    int min = depth[a] < depth[b] ? a : b;
    int max = depth[a] >= depth[b] ? a : b;

    if (depth[min] != depth[max]) {
        for (int i = 14; i >= 0; --i) {
            if (depth[parent[max][i]] >= depth[min])
                max = parent[max][i];
        }
    }

    int result = max;

    if (min != max) {
        for (int i = 14; i >= 0; --i) {
            if (parent[max][i] != parent[min][i]) {
                max = parent[max][i];
                min = parent[min][i];
            }
            result = parent[max][i];
        }
    }

    return result;
}

int main() {
    int T;
    std::cin >> T;
    while (T--) {
        for (std::vector<int>& v : graph) v.clear();
        memset(parent, 0, sizeof parent);
        memset(depth, -1, sizeof depth);

        std::cin >> N;
        for (int a, b, i = 0; i < N - 1; ++i) {
            std::cin >> a >> b;
            graph[a].push_back(b);
            parent[b][0] = a;
        }
        int root = 0;
        for (int i = 1; i <= N; ++i)
            if (parent[i][0] == 0) root = i;
        depth[root] = 0;
        dfs(root);

        int A, B;
        std::cin >> A >> B;
        std::cout << LCA(A, B) << '\n';
    }

    return 0;
}