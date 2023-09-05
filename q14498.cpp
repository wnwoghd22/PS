#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

struct Vote { int idx, n, m; };
const int LEN = 513;
std::vector<int> a[LEN];
std::vector<Vote> v[2];
int d[LEN];
bool c[LEN];
int N, M, K;

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
	std::cin >> N >> M >> K;
	for (int i = 1, n, m, c; i <= K; ++i) {
		std::cin >> n >> m >> c;
		v[c].push_back({ i, n, m });
	}
	for (const Vote& v0 : v[0]) {
		for (const Vote& v1 : v[1]) {
			if (v0.n == v1.n || v0.m == v1.m) {
				a[v0.idx].push_back(v1.idx);
			}
		}
	}

	int count = 0;
	for (int i = 1; i <= K; ++i) {
		std::fill(c, c + K + 1, false);
		if (dfs(i)) ++count;
	}
	std::cout << count << '\n';
}