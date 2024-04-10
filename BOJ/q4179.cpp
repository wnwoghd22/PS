#include <iostream>
#include <cstring>
#include <queue>

const int LEN = 1001;
const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

int R, C, init, fire[LEN][LEN], route[LEN][LEN];
char map[LEN][LEN];
std::queue<int> q;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> R >> C;
	memset(fire, -1, sizeof fire);
	memset(route, -1, sizeof route);
	for (int i = 0; i < R; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < C; ++j) {
			if (map[i][j] == 'J') route[i][j] = 0, init = i * C + j;
			if (map[i][j] == 'F') {
				fire[i][j] = 0;
				q.push(i * C + j);
			}
		}
	}
	// std::cout << "Fire\n";
	while (q.size()) {
		int x = q.front() / C;
		int y = q.front() % C;
		q.pop();
		for (int d = 0; d < 4; ++d) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if (~fire[nx][ny] || map[nx][ny] == '#') continue;
			fire[nx][ny] = fire[x][y] + 1;
			q.push(nx * C + ny);
		}
	}
	// std::cout << "Route\n";
	q.push(init);
	while (q.size()) {
		int x = q.front() / C;
		int y = q.front() % C;
		q.pop();
		if (x == 0 || x == R - 1 || y == 0 || y == C - 1) {
			std::cout << route[x][y] + 1;
			return 0;
		}

		for (int d = 0; d < 4; ++d) {
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (nx < 0 || nx >= R || ny < 0 || ny >= C) continue;
			if (~route[nx][ny] || ~fire[nx][ny] && fire[nx][ny] <= route[x][y] + 1 || map[nx][ny] == '#') continue;
			route[nx][ny] = route[x][y] + 1;
			q.push(nx * C + ny);
		}
	}
	std::cout << "IMPOSSIBLE";
}