#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

struct BC {
    int i, p; // index, performance
    bool operator<(const BC& r) const { return p > r.p; }
};
struct Info { int x, y; };

int dx[] = { 0, -1, 0, 1, 0 };
int dy[] = { 0, 0, 1, 0, -1 };

std::vector<BC> map[10][10];
int visited[10][10];
int M, A, moveA[100], moveB[100];

void bfs(int x, int y, int i, int c, int p) {
    memset(visited, -1, sizeof visited);
    std::queue<Info> q;
    q.push({ x, y });
    visited[x][y] = 0;
    map[x][y].push_back({ i, p });
    while (q.size()) {
        Info info = q.front(); q.pop();
        x = info.x, y = info.y;
        if (visited[x][y] == c) continue;
        for (int d = 1; d <= 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || nx > 9 || ny < 0 || ny > 9) continue;
            if (!~visited[nx][ny]) {
                visited[nx][ny] = visited[x][y] + 1;
                map[nx][ny].push_back({ i, p });
                q.push({ nx, ny });
            }
        }
    }
}

int get_max(int x1, int y1, int x2, int y2) {
    std::vector<BC>& v1 = map[x1][y1];
    std::vector<BC>& v2 = map[x2][y2];

    if (v1.empty() && v2.empty()) return 0;
    if (v1.empty()) return v2[0].p;
    if (v2.empty()) return v1[0].p;
    if (v1[0].i == v2[0].i) {
        if (v1.size() == 1 && v2.size() == 1) return v1[0].p;
        if (v1.size() == 1 && v2.size() >= 2) return v1[0].p + v2[1].p;
        if (v2.size() == 1 && v1.size() >= 2) return v1[1].p + v2[0].p;
        if (v1[1].p >= v2[1].p) return v1[1].p + v2[0].p;
        else return v1[0].p + v2[1].p;
    }
    return v1[0].p + v2[0].p;
}

int solve() {
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            map[i][j].clear();

    int x1 = 0, y1 = 0, x2 = 9, y2 = 9, result = 0;
    int x, y, c, p;
    std::cin >> M >> A;
    for (int i = 0; i < M; ++i) std::cin >> moveA[i];
    for (int i = 0; i < M; ++i) std::cin >> moveB[i];
    while (A--) {
        std::cin >> x >> y >> c >> p;
        bfs(y - 1, x - 1, A, c, p);
    }
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            std::sort(map[i][j].begin(), map[i][j].end());

    result += get_max(x1, y1, x2, y2);
    for (int i = 0; i < M; ++i) {
        x1 += dx[moveA[i]], y1 += dy[moveA[i]];
        x2 += dx[moveB[i]], y2 += dy[moveB[i]];
        result += get_max(x1, y1, x2, y2);
    }
    return result;
}

int main() {
    int t, T;
    std::cin >> T;
    for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}