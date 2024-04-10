#include <iostream>
#include <queue>

struct Vert {
    int x, y;
};
bool adj[4][8] = {
    0, 1, 1, 0, 0, 1, 1, 0, // up
    0, 1, 0, 1, 1, 1, 0, 0, // left
    0, 1, 0, 1, 0, 0, 1, 1, // right
    0, 1, 1, 0, 1, 0, 0, 1 // down
};

int map[50][50];
int visited[50][50];
int N, M, R, C, L;
int dx[] = { -1, 0, 0, 1 }, dy[] = { 0, -1, 1, 0 };

int bfs(int x, int y, int l) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            visited[i][j] = 0;
    std::queue<Vert> q;
    visited[x][y] = l;
    int result = 0;
    q.push({ x, y });
    while (q.size()) {
        Vert v = q.front(); q.pop();
        x = v.x, y = v.y;
        ++result;
        if (visited[x][y] == 1) continue;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if (adj[3 - d][map[x][y]] && adj[d][map[nx][ny]] && !visited[nx][ny]) { // if can get out and get in adj grid 
                visited[nx][ny] = visited[x][y] - 1;
                q.push({ nx, ny });
            }
        }
    }
    return result;
}

int solve() {
    std::cin >> N >> M >> R >> C >> L;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            std::cin >> map[i][j];
    return bfs(R, C, L);
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}