#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>

#define MAX 3'000'001

std::map<int, int> graph[20000];
bool visited[20000];
int distance[20000];
int V;

void dijkstra(int i) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> q;
    int dist, idx;
    for (idx = 0; idx < 20000; ++idx) distance[idx] = MAX;

    distance[i] = 0;
    q.push({ 0, i });

    while (!q.empty()) {
        if (q.top().first > distance[q.top().second]) {
            q.pop();
            continue;
        }

        dist = MAX; idx = q.top().second; q.pop();
        visited[idx] = true;

        for (const auto& [k, v] : graph[idx]) {
            if (distance[idx] + v < distance[k]) {
                distance[k] = distance[idx] + v;
                if (!visited[k])
                    q.push({ distance[k], k });
            }
        }
    }
}

int main() {
    int E, K, u, v, w;
    std::cin >> V >> E >> K;

    while (E--) {
        std::cin >> u >> v >> w;
        u--, v--;
        if (graph[u].find(v) != graph[u].end())
            graph[u][v] = std::min(graph[u][v], w);
        else graph[u][v] = w;
    }
    dijkstra(K - 1);

    for (v = 0; v < V; ++v) {
        if (!visited[v]) std::cout << "INF\n";
        else std::cout << distance[v] << '\n';
    }
}
