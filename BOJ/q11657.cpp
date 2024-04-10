#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <algorithm>
#include <cstring>

#define INF 60'000'001

int edges[6000][3];
long distance[501];
int N, M;

bool bellman_ford(int x) {
    int i, j;

    for (i = 0; i < 501; ++i) distance[i] = INF;
    distance[x] = 0;

    for (i = 0; i < N - 1; ++i) {
        for (j = 0; j < M; ++j) {
            if (distance[edges[j][0]] == INF) continue;
            distance[edges[j][1]] = std::min(distance[edges[j][1]], distance[edges[j][0]] + edges[j][2]);
        }
    }
    for (j = 0; j < M; ++j) {
        if (distance[edges[j][0]] != INF && distance[edges[j][0]] + edges[j][2] < distance[edges[j][1]])
            return false;
    }

    return true;
}

int main() {
    std::cin >> N >> M;
    for (int i = 0; i < M; ++i)
        std::cin >> edges[i][0] >> edges[i][1] >> edges[i][2];

    if (bellman_ford(1)) {
        for (int i = 2; i <= N; ++i)
            std::cout << (distance[i] != INF ? distance[i] : -1) << '\n';
    }
    else std::cout << -1;
}