#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 1000;

std::vector<int> a[LEN];
int d[LEN];
bool c[LEN];
int N, M, u, v;

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

		int count = 0;
		std::cin >> N >> M;

		while (M--) {
			std::cin >> u >> v;
			a[u].push_back(v);
		}

		for (int i = 0; i < N; ++i) {
			std::fill(c, c + LEN, false);
			if (dfs(i)) ++count;
		}
		std::cout << count << '\n';
	}
}