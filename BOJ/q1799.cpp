#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 20;

std::vector<int> a[LEN];
int d[LEN];
bool c[LEN];
int N;

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
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int e, j = 0; j < N; ++j) {
			std::cin >> e;
			if (e) a[i + j + 1].push_back(N - i + j);
		}
	}
	int count = 0;

	for (int i = 1; i < N * 2; ++i) {
		std::fill(c, c + LEN, false);
		if (dfs(i)) ++count;
	}
	std::cout << count;
}