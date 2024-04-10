#include <iostream>
#include <queue>
#include <cstring>

int visited[1000][1000];
int state[1000][1000];
bool map[1000][1000];

int N, M, K;

struct Info {
    int x, y, order;
    int state;
};

int bfs(int x, int y) {
    std::queue<Info> q;
    memset(state, 1, sizeof state);

    q.push({ x, y, 1, 0 });
    visited[x][y] = 1;

    while (!q.empty()) {
        Info i = q.front(); q.pop();
        if ((i.x == N - 1) && (i.y == M - 1)) return i.order;
        i.order++;

        if (i.x > 0) {
            if (map[i.x - 1][i.y]) { // wall
                if (i.state + 1 < state[i.x - 1][i.y] && i.state < K) {
                    q.push({ i.x - 1, i.y, i.order, i.state + 1 });
                    visited[i.x - 1][i.y] = i.order;
                    state[i.x - 1][i.y] = i.state + 1;
                }
            }
            else if (!visited[i.x - 1][i.y] || i.state < state[i.x - 1][i.y]) {
                q.push({ i.x - 1, i.y, i.order, i.state });
                visited[i.x - 1][i.y] = i.order;
                state[i.x - 1][i.y] = i.state;
            }
        }
        if (i.x < N - 1) {
            if (map[i.x + 1][i.y]) { // wall
                if (i.state + 1 < state[i.x + 1][i.y] && i.state < K) {
                    q.push({ i.x + 1, i.y, i.order, i.state + 1 });
                    visited[i.x + 1][i.y] = i.order;
                    state[i.x + 1][i.y] = i.state + 1;
                }
            }
            else if (!visited[i.x + 1][i.y] || i.state < state[i.x + 1][i.y]) {
                q.push({ i.x + 1, i.y, i.order, i.state });
                visited[i.x + 1][i.y] = i.order;
                state[i.x + 1][i.y] = i.state;
            }
        }
        if (i.y > 0) {
            if (map[i.x][i.y - 1]) { // wall
                if (i.state + 1 < state[i.x][i.y - 1] && i.state < K) {
                    q.push({ i.x, i.y - 1, i.order, i.state + 1 });
                    visited[i.x][i.y - 1] = i.order;
                    state[i.x][i.y - 1] = i.state + 1;
                }
            }
            else if (!visited[i.x][i.y - 1] || i.state < state[i.x][i.y - 1]) {
                q.push({ i.x, i.y - 1, i.order, i.state });
                visited[i.x][i.y - 1] = i.order;
                state[i.x][i.y - 1] = i.state;
            }
        }
        if (i.y < M - 1) {
            if (map[i.x][i.y + 1]) { // wall
                if (i.state + 1 < state[i.x][i.y + 1] && i.state < K) {
                    q.push({ i.x, i.y + 1, i.order, i.state + 1 });
                    visited[i.x][i.y + 1] = i.order;
                    state[i.x][i.y + 1] = i.state + 1;
                }
            }
            else if (!visited[i.x][i.y + 1] || i.state < state[i.x][i.y + 1]) {
                q.push({ i.x, i.y + 1, i.order, i.state });
                visited[i.x][i.y + 1] = i.order;
                state[i.x][i.y + 1] = i.state;
            }
        }
    }
    return -1;
}

int main() {
    int i, j; char s[1001];
    std::cin >> N >> M >> K;
    for (i = 0; i < N; ++i) {
        std::cin >> s;
        for (j = 0; j < M; ++j) map[i][j] = s[j] - '0';
    }
    std::cout << bfs(0, 0);
}