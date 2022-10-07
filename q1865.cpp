#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const ll INF = 1'000'000'001;

int graph[501][501];
std::vector<std::pair<std::pair<int, int>, int>> edges;
ll distance[501];
int N, M, W;

bool bellman_ford(int x) {
    int i, j;

    std::fill(&distance[0], &distance[0] + 501, INF);
    distance[x] = 0;

    for (i = 0; i < N - 1; ++i) {
        for (const auto& edge : edges) {
            int s = edge.first.first, e = edge.first.second, t = edge.second;
            if (distance[s] == INF) continue;
            distance[e] = std::min(distance[e], distance[s] + t);
        }
    }
    for (const auto& edge : edges) {
        int s = edge.first.first, e = edge.first.second, t = edge.second;
        if (distance[s] != INF && distance[s] + t < distance[e]) return false;
    }

    return true;
}

int main() {
    int TC;
    std::cin >> TC;
    while (TC--) {
        std::cin >> N >> M >> W;
        std::fill(&graph[0][0], &graph[0][0] + 501 * 501, INF);

        for (int i = 0; i < M; ++i) {
            int S, E, T;
            std::cin >> S >> E >> T;
            if (graph[S][E]== INF) {
                graph[S][E] = T;
                graph[E][S] = T;
            }
            else {
                graph[S][E] = std::min(graph[S][E], T);
                graph[E][S] = std::min(graph[E][S], T);
            }
        }
        for (int i = 0; i < W; ++i) {
            int S, E, T;
            std::cin >> S >> E >> T;
            if (graph[S][E] == INF) graph[S][E] = -T;
            else graph[S][E] = std::min(graph[S][E], -T);
        }
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (graph[i][j] != INF)
                    edges.push_back({ {i, j},graph[i][j] });

        if (bellman_ford(1)) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
}