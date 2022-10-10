#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>

typedef std::pair<int, int> pii;
const int INF = 1'000'000'001;
const int MAX = 1001;

std::map<int, int> graph[MAX];
std::map<int, int> graph_r[MAX];
bool visited[MAX];
int distance[MAX];
int distance_r[MAX];
int V;

void dijkstra(int i) {
    std::priority_queue<pii, std::vector<pii>, std::greater<>> q;
    int dist, idx;
    for (idx = 1; idx <= V; ++idx) distance[idx] = INF;
    memset(visited, 0, sizeof visited);

    distance[i] = 0;
    q.push({ 0, i });

    while (!q.empty()) {
        if (q.top().first > distance[q.top().second]) {
            q.pop();
            continue;
        }

        dist = INF; idx = q.top().second; q.pop();
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
void dijkstra_r(int i) {
    std::priority_queue<pii, std::vector<pii>, std::greater<>> q;
    int dist, idx;
    for (idx = 1; idx <= V; ++idx) distance_r[idx] = INF;
    memset(visited, 0, sizeof visited);

    distance_r[i] = 0;
    q.push({ 0, i });

    while (!q.empty()) {
        if (q.top().first > distance_r[q.top().second]) {
            q.pop();
            continue;
        }

        dist = INF; idx = q.top().second; q.pop();
        visited[idx] = true;

        for (const auto& [k, v] : graph_r[idx]) {
            if (distance_r[idx] + v < distance_r[k]) {
                distance_r[k] = distance_r[idx] + v;
                if (!visited[k])
                    q.push({ distance_r[k], k });
            }
        }
    }
}

int main() {
    int E, K, u, v, w;
    std::cin >> V >> E >> K;

    while (E--) {
        std::cin >> u >> v >> w;
        graph[u][v] = w;
        graph_r[v][u] = w;
    }
    dijkstra(K);
    dijkstra_r(K);

    K = 0;
    for (v = 1; v <= V; ++v) {
        K = std::max(K, distance[v] + distance_r[v]);
    }
    std::cout << K;
}
