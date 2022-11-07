#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 501;

std::vector<int> a[LEN];
int d[LEN];
bool c[LEN];
int N, K;

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
	std::cin >> N >> K;
	for (int r, c, i = 0; i < K; ++i) {
		std::cin >> r >> c;
		a[r].push_back(c);
	}

	int count = 0;
	for (int i = 1; i <= N; ++i) {
		std::fill(c, c + N + 1, false);
		if (dfs(i)) ++count;
	}
	std::cout << count;
}