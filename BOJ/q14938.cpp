#include <iostream>

const int INF = 1'000'000'000;

int weight[100];
int graph[100][100];

void floyd_warshall(int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                graph[i][j] = std::min(graph[i][j], graph[i][k] + graph[k][j]);
}

int main() {
    int N, M, R, a, b, c;
    std::cin >> N >> M >> R;
    for (a = 0; a < N; ++a)
        for (b = 0; b < N; ++b)
            graph[a][b] = a == b ? 0 : INF;

    for (a = 0; a < N; ++a) std::cin >> weight[a];

    while (R--) {
        std::cin >> a >> b >> c;
        graph[a - 1][b - 1] = c;
        graph[b - 1][a - 1] = c;
    }

    floyd_warshall(N);

    int num = -1;

    for (a = 0; a < N; ++a) {
        int temp = 0;
        for (b = 0; b < N; ++b) temp += graph[a][b] <= M ? weight[b] : 0;

        num = std::max(num, temp);
    }

    std::cout << num;
}