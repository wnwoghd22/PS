#include <iostream>
#include <queue>

const int LEN = 100;
const int RIGHT = 1;
const int LEFT = 2;
const int UP = 4;
const int DOWN = 8;
const int COW = 16;
const int dx[] = { 0, 0, -1, 1 }, dy[] = { 1, -1 ,0, 0 };
const int VISITED = 32;


short map[LEN][LEN];

int N, K, R;

int bfs(int i, int j) {
	std::queue<int> q;
	map[i][j] |= VISITED;
	int cnt = !!(map[i][j] & COW);
	q.push(i * N + j);
	while (q.size()) {
		i = q.front() / N;
		j = q.front() % N;
		q.pop();
		for (int d = 0; d < 4; ++d) {
			int nx = i + dx[d];
			int ny = j + dy[d];
			if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
			if (map[i][j] & 1 << d) continue;
			if (~map[nx][ny] & VISITED) {
				map[nx][ny] |= VISITED;
				cnt += !!(map[nx][ny] & COW);
				q.push(nx * N + ny);
			}
		}
	}
	return cnt;
}

int main() {
	std::cin >> N >> K >> R;
	for (int i = 0, r, c, _r, _c; i < R; ++i) {
		std::cin >> r >> c >> _r >> _c;
		if (r != _r) {
			if (r < _r) map[r - 1][c - 1] |= DOWN, map[_r - 1][_c - 1] |= UP;
			if (r > _r) map[r - 1][c - 1] |= UP, map[_r - 1][_c - 1] |= DOWN;
		}
		if (c != _c) {
			if (c < _c) map[r - 1][c - 1] |= RIGHT, map[_r - 1][_c - 1] |= LEFT;
			if (c > _c) map[r - 1][c - 1] |= LEFT, map[_r - 1][_c - 1] |= RIGHT;
		}
	}
	for (int i = 0, r, c; i < K; ++i) {
		std::cin >> r >> c;
		map[r - 1][c - 1] |= COW;
	}
	int ans = K * (K - 1) / 2;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (~map[i][j] & VISITED) {
				int k = bfs(i, j);
				ans -= k * (k - 1) / 2;
			}
		}
	}
	std::cout << ans;
}