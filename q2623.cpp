#include <iostream>
#include <vector>
#include <queue>

const int MAX = 1001;

int vertex[MAX][MAX];
int order[MAX];
int visited[MAX];
int incoming[MAX];
std::vector<int> graph[MAX];
int N;

std::vector<int> topological_sort() {
    std::queue<int> q;
    std::vector<int> result;

    for (int i = 1; i <= N; ++i) {
        if (!incoming[i]) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (!q.empty()) {
        int v = q.front(); q.pop();
        result.push_back(v);

        for (const int& u : graph[v]) {
            if (!--incoming[u]) {
                if (visited[u]) return std::vector<int>(0);
                visited[u] = true;
                q.push(u);
            }
        }
    }

    return result;
}

int main() {
    int M;

    std::cin >> N >> M;
    while (M--) {
        int K, u, v;
        std::cin >> K;
        for (v = 1; v <= K; ++v) {
            std::cin >> order[v];
            for (u = 1; u < v; ++u) {
                vertex[order[u]][order[v]]++;
            }
        }
    }
    for (int u = 1; u <= N; ++u) {
        for (int v = 1; v <= N; ++v) {
            if (vertex[u][v]) {
                graph[u].push_back(v);
                incoming[v]++;
            }
        }
    }

    std::vector<int> result = topological_sort();

    if (result.size()) for (const int& e : result) std::cout << e << '\n';
    else std::cout << 0;

    return 0;
}