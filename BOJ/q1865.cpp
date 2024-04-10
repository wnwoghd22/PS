#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const ll INF = 1'000'000'001;

std::vector<std::pair<std::pair<int, int>, int>> edges;
ll distance[501];
int N, M, W;

bool bellman_ford(int x) {
    std::fill(&distance[0], &distance[0] + 502, INF);
    distance[x] = 0;

    for (int i = 1; i <= N; i++) {
        for (auto& edge : edges) {
            int s = edge.first.first, e = edge.first.second, t = edge.second;
            if (distance[e] > distance[s] + t) {
                distance[e] = distance[s] + t;
                if (i == N) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int TC, S, E, T;
    std::cin >> TC;
    while (TC--) {
        std::cin >> N >> M >> W;
        edges.clear();

        while (M--) {
            std::cin >> S >> E >> T;
            edges.push_back({ {S, E}, T });
            edges.push_back({ {E, S}, T });
        }
        while (W--) {
            std::cin >> S >> E >> T;
            edges.push_back({ {S, E}, -T });
        }

        if (bellman_ford(1)) std::cout << "NO\n";
        else std::cout << "YES\n";
    }
}