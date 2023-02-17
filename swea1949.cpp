#include <queue>
#include <iostream>

int N, K, map[8][8];
bool visited[8][8];
int dx[] = { 0, -1, 0, 1 }, dy[] = { -1, 0, 1, 0 };

int dfs(int x, int y, int f) { // f: can lower one block only.
    visited[x][y] = true;
    int max = 0;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (!visited[nx][ny]) {
            if (map[nx][ny] >= map[x][y]) {
                if (f && map[nx][ny] - K < map[x][y]) {
                    int origin = map[nx][ny];
                    map[nx][ny] = map[x][y] - 1; // a block is lowered
                    max = std::max(max, dfs(nx, ny, 0));  // f = 0
                    map[nx][ny] = origin; // recover height
                }
            }
            else max = std::max(max, dfs(nx, ny, f));
        }
    }
    visited[x][y] = false;

    return max + 1;
}

int solve() {
    std::cin >> N >> K;
    int max = 0;
    int dist = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cin >> map[i][j];
            if (map[i][j] > max) max = map[i][j];
        }
    }
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            if (map[i][j] == max)
                dist = std::max(dist, dfs(i, j, 1));

    return dist;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}