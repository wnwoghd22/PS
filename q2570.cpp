#include <iostream>
#include <vector>
#include <cstring>

const int LEN = 10'001;

int N, M, n_col = 1, n_row = 1, col[100][100], row[100][100];
int d[LEN];
bool c[LEN];
std::vector<int> a[LEN];
bool map[100][100];

bool dfs(int x) {
	for (const int& t : a[x]) {
		if (c[t]) continue;
		c[t] = true;
		if (!d[t] || dfs(d[t])) {
			d[t] = x;
			return true;
		}
	}
	return false;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, x, y; i < M; ++i) {
		std::cin >> x >> y;
		map[x - 1][y - 1] = 1;
	}
	for (int d = -N + 1; d < N; ++d, ++n_row) {
		for (int i = 0; i < N; ++i) {
			int j = d + i;
			if (j < 0) continue;
			if (j >= N) break;
			if (map[i][j]) ++n_row;
			else row[i][j] = n_row;
		}
	}
	for (int d = 0; d < N * 2 - 1; ++d, ++n_col) {
		for (int i = 0; i < N; ++i) {
			int j = d - i;
			if (j >= N) continue;
			if (j < 0) break;
			if (map[i][j]) ++n_col;
			else col[i][j] = n_col;
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << row[i][j] << ' ';
		}
		std::cout << '\n';
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << col[i][j] << ' ';
		}
		std::cout << '\n';
	}
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			if (!map[i][j])
				a[row[i][j]].push_back(col[i][j]);
	int count = 0;
	for (int i = 1; i <= n_row; ++i) {
		memset(c, 0, sizeof c);
		if (dfs(i)) ++count;
	}
	std::cout << count;

}