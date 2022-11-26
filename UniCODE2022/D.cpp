#include <iostream>
#include <algorithm>

typedef long long int ll;
const ll INF = 1e15;
const int MAX_V = 300;

ll graph[MAX_V][MAX_V];

void floyd_warshall(int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
    ll N, M, S, T, Q, u, v, w, u2, v2, w2;
    std::cin >> N >> M >> S >> T;
    S--, T--;
    for (u = 0; u < N; ++u)
        for (v = 0; v < N; ++v)
            graph[u][v] = u == v ? 0 : INF;

    while (M--) {
        std::cin >> u >> v >> w;
        if (u == v) continue;
        graph[u - 1][v - 1] = std::min(graph[u - 1][v - 1], w);
    }

    floyd_warshall(N);

    std::cin >> Q;
    while (Q--) {
        std::cin >> u >> v >> w >> u2 >> v2 >> w2;
        u--, v--, u2--, v2--;
        ll min = graph[S][T];
        ll m1 = graph[S][u] + w + graph[v][T]; 
        ll m2 = graph[S][u2] + w2 + graph[v2][T];
        ll m12 = graph[S][u] + w + graph[v][u2] + w2 + graph[v2][T];
        ll m21 = graph[S][u2] + w2 + graph[v2][u] + w + graph[v][T];
        min = std::min({ min, m1, m2, m12, m21 });

        std::cout << (min >= INF ? -1 : min) << '\n';
    }
}