#include <iostream>
#include <queue>

struct pos { int x, y; };
bool map[20][20];
int visited[20][20];
int dx[] = { 0, 1, 0, -1 }, dy[] = { 1, 0, -1, 0 };
int N, M;

int bfs(int x, int y) {
    std::queue<pos> q;
    int depth = 0;
    int cnt = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            visited[i][j] = 0;
    visited[x][y] = 1;
    cnt = map[x][y];
    q.push({ x, y });
    int result = 0;
    while (q.size()) {
        pos cur = q.front(); q.pop();
        x = cur.x, y = cur.y;
        if (visited[x][y] > depth) {
            depth = visited[x][y];
            int cost = 1 + 2 * depth * (depth - 1);
            if (cnt * M - cost >= 0 && cnt > result) result = cnt;
        }
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                if (visited[nx][ny]) continue;
                visited[nx][ny] = visited[x][y] + 1;
                if (map[nx][ny]) ++cnt;
                q.push({ nx, ny });
            }
        }
    }
    return result;
}

int solve() {
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            std::cin >> map[i][j];
    int result = 0;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            result = std::max(result, bfs(i, j));
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}