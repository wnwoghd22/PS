#include <iostream>
#include <vector>
#include <cstring>

const int LEN = 10'001;

int N, n_col = 1, n_row = 1, col[100][100], row[100][100];
int d[LEN];
bool c[LEN];
std::vector<int> a[LEN];
char map[100][101];

bool dfs(int x) {
	for (const int t : a[x]) {
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
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> map[i];

	for (int i = 0; i < N; ++i, ++n_row) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == 'X') ++n_row;
			if (map[i][j] == '.') row[i][j] = n_row;
		}
	}
	for (int i = 0; i < N; ++i, ++n_col) {
		for (int j = 0; j < N; ++j) {
			if (map[j][i] == 'X') ++n_col;
			if (map[j][i] == '.') col[j][i] = n_col;
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (map[i][j] == '.')
				a[row[i][j]].push_back(col[i][j]);
		}
	}
	/*for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			std::cout << row[i][j] << ' ';
		}
		std::cout << '\n';
	}*/

	int count = 0;
	for (int i = 1; i <= n_row; ++i) {
		memset(c, 0, sizeof c);
		if (dfs(i)) ++count;
	}
	std::cout << count;
}
