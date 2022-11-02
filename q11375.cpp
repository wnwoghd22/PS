#include <iostream>
#include <vector>

const int LEN = 1001;

std::vector<int> a[LEN];
int d[LEN];
bool c[LEN];
int N, M;

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
	for (int n, k, i = 0; i < N; ++i) {
		std::cin >> n;
		while (n--) {
			std::cin >> k;
			a[i].push_back(k);
		}
	}
	int count = 0;
	for (int i = 0; i < N; ++i) {
		std::fill(c, c + M + 1, false);
		if (dfs(i)) ++count;
	}
	std::cout << count;
}
