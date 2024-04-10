#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>

struct Pos { int x, y; };
struct Rect {
	int r, c;
	int size() const { return r * c; }
	bool operator<(const Rect& rhs) const { return size() == rhs.size() ? r < rhs.r : size() < rhs.size(); }
} arr[3000];
int sp;

int N, map[100][100], visited[100][100];

void bfs(int x, int y) {
	std::queue<Pos> q;
	q.push({ x, y });
	visited[x][y] = 1;

	while (q.size()) {
		Pos cur = q.front(); q.pop();
		int nx = (cur.x < N - 1 && map[cur.x + 1][cur.y]) ? cur.x + 1 : -1;
		int ny = (cur.y < N - 1 && map[cur.x][cur.y + 1]) ? cur.y + 1 : -1;
		if (!~nx && !~ny) {
			// std::cout << x << ' ' << y << ' ' << nx << ' ' << ny << '\n';
			arr[sp++] = { cur.x - x + 1, cur.y - y + 1 };
			return;
		}
		if (~nx && !visited[nx][cur.y]) {
			visited[nx][cur.y] = 1;
			q.push({ nx, cur.y });
		}
		if (~ny && !visited[cur.x][ny]) {
			visited[cur.x][ny] = 1;
			q.push({ cur.x, ny });
		}
	}
}

void solve(int t) {
	sp = 0;
	memset(visited, 0, sizeof visited);
	std::cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			std::cin >> map[i][j];

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (map[i][j] && !visited[i][j])
				bfs(i, j);
	std::sort(arr, arr + sp);
	std::cout << '#' << t << ' ' << sp << ' ';
	for (int i = 0; i < sp; ++i)
		std::cout << arr[i].r << ' ' << arr[i].c << ' ';
	std::cout << '\n';
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) solve(t);
}