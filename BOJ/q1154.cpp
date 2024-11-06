#include <iostream>
#include <vector>
#include <queue>

const int LEN = 1001;

int N, adj[LEN][LEN];

std::vector<int> graph[LEN];
int visited[LEN];

bool bfs(int idx) {
    int u, color; bool result = true;
    std::queue<std::pair<int, int>> q;
    visited[idx] = 1;
    q.push({ idx, 1 });

    while (!q.empty()) {
        u = q.front().first, color = q.front().second, q.pop();
        for (const int& v : graph[u]) {
            if (!visited[v]) {
                visited[v] = color == 1 ? 2 : 1;
                q.push({ v, color == 1 ? 2 : 1 });
            }
            else if (visited[v] == color) result = false;
        }
    }
    return result;
}

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    std::cin >> N;
    while (1) {
        int u, v;
        std::cin >> u >> v;
        if (!~u && !~v) break;
        adj[u][v] = adj[v][u] = 1;
    }
    for (int u = 1; u <= N; ++u) {
        for (int v = u + 1; v <= N; ++v) {
            if (!adj[u][v]) {
                graph[u].push_back(v);
                graph[v].push_back(u);
            }
        }
    }
    int ret = 1;

    for (int u = 1; u <= N; ++u) {
        if (!visited[u] && !bfs(u)) {
            ret = 0;
            break;
        }
    }
    if (ret) {
        std::cout << "1\n";
        for (int i = 1; i <= 2; ++i) {
            for (int u = 1; u <= N; ++u) {
                if (visited[u] == i)
                    std::cout << u << ' ';
            }
            std::cout << "-1\n";
        }
    }
    else std::cout << -1;
}