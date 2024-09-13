#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 51;

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, -1, 0, 1 };

int map[LEN][LEN];
int visited[LEN][LEN][4];
int sx, sy, ex, ey;
std::string dir;

struct E {
	int x, y, d;
};

int solve(int n, int m) {
	memset(map, 0, sizeof map);
	memset(visited, -1, sizeof visited);
	for (int i = 0, a; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			std::cin >> a;
			if (a) {
				map[i][j] = map[i + 1][j] = map[i][j + 1] = map[i + 1][j + 1] = 1;
			}
		}
	}
	std::cin >> sx >> sy >> ex >> ey >> dir;
	int d = dir == "south" ? 0 :
		dir == "west" ? 1 :
		dir == "north" ? 2 : 3;
	std::queue<E> q;
	q.push({ sx, sy, d });
	visited[sx][sy][d] = 0;
	while (q.size()) {
		int x = q.front().x;
		int y = q.front().y;
		int d = q.front().d;
		q.pop();
		if (x == ex && y == ey) return visited[x][y][d];
		if (!~visited[x][y][(d + 1) % 4]) {
			visited[x][y][(d + 1) % 4] = visited[x][y][d] + 1;
			q.push({ x, y, (d + 1) % 4 });
		}
		if (!~visited[x][y][(d + 3) % 4]) {
			visited[x][y][(d + 3) % 4] = visited[x][y][d] + 1;
			q.push({ x, y, (d + 3) % 4 });
		}
		for (int k = 1; k <= 3; ++k) {
			int nx = x + dx[d] * k;
			int ny = y + dy[d] * k;
			if (nx <= 0 || nx >= n || ny <= 0 || ny >= m) break;
			if (map[nx][ny]) break;
			if (!~visited[nx][ny][d]) {
				visited[nx][ny][d] = visited[x][y][d] + 1;
				q.push({ nx, ny, d });
			}
		}
	}
	return -1;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	while (1) {
		int n, m;
		std::cin >> n >> m;
		if (!n && !m) break;
		std::cout << solve(n, m) << '\n';
	}
}