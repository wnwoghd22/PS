#include <iostream>
#include <queue>

const int dx[] = { 0, 0, 1, -1 };
const int dy[] = { 1, -1, 0, 0 };

char map[3][4];
bool visited[3][3];

int n, a[4];
int m, b[4];

int bfs(int i, int j) {
	std::queue<int> q;
	int size = 1;
	visited[i][j] = 1;
	q.push(i * 3 + j);

	while (q.size()) {
		i = q.front() / 3;
		j = q.front() % 3;
		q.pop();

		for (int d = 0, ni, nj; d < 4; ++d) {
			ni = i + dx[d], nj = j + dy[d];
			if (ni < 0 || ni >= 3 || nj < 0 || nj >= 3) continue;
			if (map[ni][nj] != 'O' || visited[ni][nj]) continue;
			++size;
			visited[ni][nj] = 1;
			q.push(ni * 3 + nj);
		}
	}
	return size;
}

bool solve() {
	for (int i = 0; i < 3; ++i) {
		std::cin >> map[i];
		for (int j = 0; j < 3; ++j)
			visited[i][j] = 0;
	}
	std::cin >> n;
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	m = 0;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (map[i][j] == 'O' && !visited[i][j])
				b[m++] = bfs(i, j);
		}
	}
	if (m ^ n) return 0;
	for (int i = 0, t; i < n - 1; ++i)
		for (int j = 0; j < n - i - 1; ++j)
			if (b[j] > b[j + 1]) 
				t = b[j], b[j] = b[j + 1], b[j + 1] = t;
	for (int i = 0; i < n; ++i)
		if (a[i] ^ b[i])
			return 0;
	return 1;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		std::cout << solve() << '\n';
	}
}