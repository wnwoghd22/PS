#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

int N;
std::vector<int> graph[100'001];
int parent[100'001][21];
int depth[100'001];

void bfs(int v) {
    std::queue<int> q;
    memset(depth, -1, sizeof depth);
    
    q.push(v);
    depth[v] = 0;
    
    while (!q.empty()) {
        v = q.front(); q.pop();
        
        if (depth[v] > 0) {
            for (int i = 1; i < 21; ++i)
                parent[v][i] = parent[parent[v][i - 1]][i - 1];
        }
        
        for (const int& u : graph[v]) {
            if (depth[u] == -1) {
                depth[u] = depth[v] + 1;
                parent[u][0] = v;
                q.push(u);
            }
        }
    }
}

int LCA(const int a, const int b) {
    int min = depth[a] < depth[b] ? a : b;
    int max = depth[a] >= depth[b] ? a : b;

    if (depth[min] != depth[max]) {
        for (int i = 20; i >= 0; --i) {
            if (depth[parent[max][i]] >= depth[min])
                max = parent[max][i];
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

int main() {
    int M;
    
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0); std::cout.tie(0);
    
    std::cin >> N;
    
    for (int u, v, i = 0; i < N - 1; ++i) {
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    bfs(1);
    
    std::cin >> M;
    
    while (M--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << LCA(a, b) << '\n';
    }

    return 0;
}