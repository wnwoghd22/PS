#include <iostream>
#include <queue>

int visited[1000][1000];
bool state[1000][1000];
bool map[1000][1000];

int N, M;

struct Info {
    int x, y, order;
    bool state;
};

int bfs(int x, int y) {
    std::queue<Info> q;

    q.push({ x, y, 1, false });
    visited[x][y] = 1;

    while (!q.empty()) {
        Info i = q.front(); q.pop();
        if ((i.x == N - 1) && (i.y == M - 1)) return i.order;
        i.order++;

        if (i.x > 0) {
            if (map[i.x - 1][i.y]) { // wall
                if (!i.state) {
                    q.push({ i.x - 1, i.y, i.order, true });
                    visited[i.x - 1][i.y] = i.order;
                    state[i.x - 1][i.y] = true;
                }
            }
            else if (!visited[i.x - 1][i.y]) {
                q.push({ i.x - 1, i.y, i.order, i.state });
                visited[i.x - 1][i.y] = i.order;
                state[i.x - 1][i.y] = i.state;
            }
            else if (state[i.x - 1][i.y]) {
                if (!i.state) {
                    q.push({ i.x - 1, i.y, i.order, false });
                    visited[i.x - 1][i.y] = i.order;
                    state[i.x - 1][i.y] = false;
                }
            }
        }
        if (i.x < N - 1) {
            if (map[i.x + 1][i.y]) { // wall
                if (!i.state) {
                    q.push({ i.x + 1, i.y, i.order, true });
                    visited[i.x + 1][i.y] = i.order;
                    state[i.x + 1][i.y] = true;
                }
            }
            else if (!visited[i.x + 1][i.y]) {
                q.push({ i.x + 1, i.y, i.order, i.state });
                visited[i.x + 1][i.y] = i.order;
                state[i.x + 1][i.y] = i.state;
            }
            else if (state[i.x + 1][i.y]) {
                if (!i.state) {
                    q.push({ i.x + 1, i.y, i.order, false });
                    visited[i.x + 1][i.y] = i.order;
                    state[i.x + 1][i.y] = false;
                }
            }
        }
        if (i.y > 0) {
            if (map[i.x][i.y - 1]) { // wall
                if (!i.state) {
                    q.push({ i.x, i.y - 1, i.order, true });
                    visited[i.x][i.y - 1] = i.order;
                    state[i.x][i.y - 1] = true;
                }
            }
            else if (!visited[i.x][i.y - 1]) {
                q.push({ i.x, i.y - 1, i.order, i.state });
                visited[i.x][i.y - 1] = i.order;
                state[i.x][i.y - 1] = i.state;
            }
            else if (state[i.x][i.y - 1]) {
                if (!i.state) {
                    q.push({ i.x, i.y - 1, i.order, false });
                    visited[i.x][i.y - 1] = i.order;
                    state[i.x][i.y - 1] = false;
                }
            }
        }
        if (i.y < M - 1) {
            if (map[i.x][i.y + 1]) { // wall
                if (!i.state) {
                    q.push({ i.x, i.y + 1, i.order, true });
                    visited[i.x][i.y + 1] = i.order;
                    state[i.x][i.y + 1] = true;
                }
            }
            else if (!visited[i.x][i.y + 1]) {
                q.push({ i.x, i.y + 1, i.order, i.state });
                visited[i.x][i.y + 1] = i.order;
                state[i.x][i.y + 1] = i.state;
            }
            else if (state[i.x][i.y + 1]) {
                if (!i.state) {
                    q.push({ i.x, i.y + 1, i.order, false });
                    visited[i.x][i.y + 1] = i.order;
                    state[i.x][i.y + 1] = false;
                }
            }
        }
    }
    return -1;
}

int main() {
    int i, j; char s[1001];
    std::cin >> N >> M;
    for (i = 0; i < N; ++i) {
        std::cin >> s;
        for (j = 0; j < M; ++j) map[i][j] = s[j] - '0';
    }
    std::cout << bfs(0, 0);
}