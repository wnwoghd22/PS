#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 6401;

std::string S[80];
std::vector<int> a[LEN];
int d[LEN];
bool c[LEN];
int N, M;

bool dfs(int x) {
	for (const int& t : a[x]) {
		if (c[t]) continue;
		c[t] = true;
		if (!~d[t] || dfs(d[t])) {
			d[t] = x;
			return true;
		}
	}
	return false;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		for (std::vector<int>& v : a) v.clear();
		std::fill(d, d + LEN, -1);

		int total = 0, count = 0;
		std::cin >> N >> M;
		for (int i = 0; i < N; ++i) {
			std::cin >> S[i];
			for (const char& c : S[i])
				if (c == '.') ++total;
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; j += 2) {
				if (S[i][j] == 'x') continue;
				if (i > 0 && j > 0 && S[i - 1][j - 1] == '.')
					a[i * M + j].push_back((i - 1) * M + j - 1);
				if (i > 0 && j < M - 1 && S[i - 1][j + 1] == '.')
					a[i * M + j].push_back((i - 1) * M + j + 1);

				if (j > 0 && S[i][j - 1] == '.')
					a[i * M + j].push_back(i * M + j - 1);
				if (j < M - 1 && S[i][j + 1] == '.')
					a[i * M + j].push_back(i * M + j + 1);

				if (i < N - 1 && j > 0 && S[i + 1][j - 1] == '.')
					a[i * M + j].push_back((i + 1) * M + j - 1);
				if (i < N - 1 && j < M - 1 && S[i + 1][j + 1] == '.')
					a[i * M + j].push_back((i + 1) * M + j + 1);
			}
		}

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; j += 2) {
				std::fill(c, c + LEN, false);
				if (dfs(i * M + j)) ++count;
			}
		}
		std::cout << total - count << '\n';
	}
}