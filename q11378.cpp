#include <iostream>
#include <vector>

const int LEN = 2001;

std::vector<int> a[LEN];
int d[LEN];
bool c[LEN], v[LEN];
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
	for (int n, k, i = 1; i <= N; ++i) {
		std::cin >> n;
		while (n--) {
			std::cin >> k;
			a[i].push_back(k);
			v[k] = true;
		}
	}
	for (int m = 1; m <= M; ++m) {
		if (v[m]) {
			for (int i = 1; i <= K; ++i) {
				a[N + i].push_back(m);
			}
		}
	}

	int count = 0;
	for (int i = 1; i <= N + K; ++i) {
		std::fill(c, c + M + 1, false);
		if (dfs(i)) ++count;
	}
	std::cout << count;
}
