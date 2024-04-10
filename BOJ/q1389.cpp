#include <iostream>

#define INF 1'000'000'000

int graph[100][100];

void floyd_warshall(int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
    int N, M, a, b, c;
    std::cin >> N;
    for (a = 0; a < N; ++a)
        for (b = 0; b < N; ++b)
            graph[a][b] = a == b ? 0 : INF;

    std::cin >> M;
    while (M--) {
        std::cin >> a >> b;
        graph[a - 1][b - 1] = 1;
        graph[b - 1][a - 1] = 1;
    }

    floyd_warshall(N);

    int num = -1;
    int kevin_bacon = INF;

    for (a = 0; a < N; ++a) {
        int temp = 0;
        for (b = 0; b < N; ++b) temp += graph[a][b];

        if (temp < kevin_bacon) {
            kevin_bacon = temp;
            num = a + 1;
        }
    }

    std::cout << num;
}