#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>

const int LEN = 2000;
short map[LEN][LEN];
bool visited[LEN][LEN];
int dx[] = { 0, 0, -1, 1, -1, 1, -1, 1 };
int dy[] = { -1, 1, 0, 0, -1, 1, 1, -1 };
struct Pos { int x, y; };
int N, M;
bool bfs() {
	std::queue<Pos> q;
	q.push({ 0, 0 });
	visited[0][0] = 1;
	while (q.size()) {
		Pos p = q.front(); q.pop();
		for (int d = 0; d < 4; ++d) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < M && !map[nx][ny] && !visited[nx][ny]) {
				visited[nx][ny] = 1;
				q.push({ nx, ny });
			}
		}
	}
	return visited[N - 1][M - 1];
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			std::cin >> map[i][j];
	if (!bfs()) {
		std::cout << 0;
		return 0;
	}
	std::queue<Pos> q;
	for (int i = 0; i < N; ++i) {
		if (map[i][0] == 1) {
			map[i][0] = 2;
			q.push({ i, 0 });
		}
		if (map[i][M - 1] == 1) {
			map[i][M - 1] = 3;
			q.push({ i, M - 1 });
		}
	}
	for (int i = 0; i < M; ++i) {
		if (map[0][i] == 1) {
			map[0][i] = 3;
			q.push({ 0, i });
		}
		if (map[N - 1][i] == 1) {
			map[N - 1][i] = 2;
			q.push({ N - 1, i });
		}
	}
	while (q.size()) {
		Pos p = q.front(); q.pop();
		for (int d = 0; d < 8; ++d) {
			int nx = p.x + dx[d], ny = p.y + dy[d];
			if (0 <= nx && nx < N && 0 <= ny && ny < M && map[nx][ny] == 1) {
				map[nx][ny] = map[p.x][p.y];
				q.push({ nx, ny });
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j)
			std::cout << map[i][j] << ' ';
		std::cout << '\n';
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			bool f2 = 0, f3 = 0;
			if (j == 0 && i || i == N - 1 && j < M - 1) f2 = 1;
			if (i == 0 && j || j == M - 1 && i < N - 1) f3 = 1;
			for (int d = 0; d < 8; ++d) {
				int nx = i + dx[d], ny = j + dy[d];
				if (0 <= nx && nx < N && 0 <= ny && ny < M) {
					if (map[nx][ny] == 2) f2 = 1;
					if (map[nx][ny] == 3) f3 = 1;
				}
			}
			if (f2 && f3) {
				std::cout << 1;
				return 0;
			}
		}
	}
	std::cout << 2;
}