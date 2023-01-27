#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int MAX = 101;

int vert[MAX][MAX];
int incoming[MAX];
std::vector<int> graph[MAX];
int N;

void topological_sort() {
    std::queue<int> q;

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        std::cout << v << ' ';
        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                q.push(u);
            }
        }
    }
}

void solve() {
    for (std::vector<int>& v : graph) v.clear();
    memset(vert, 0, sizeof vert);
    memset(incoming, 0, sizeof incoming);
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        int U, V;
        std::cin >> U;
        for (int j = 1; j < N - 1; ++j) {
            std::cin >> V;
            ++vert[U][V];
            U = V;
        }
    }
    for (int u = 1; u <= N; ++u) {
        for (int v = 1; v <= N; ++v) {
            if (vert[u][v]) {
                graph[u].push_back(v);
                ++incoming[v];
            }
        }
    }
    topological_sort();
    std::cout << '\n';
}

int main() {
    int T;
    std::cin >> T;
    while (T--) solve();
}