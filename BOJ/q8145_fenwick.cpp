#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 250'001;

char cmd;
int N, M;
std::vector<int> g[LEN];
int s[LEN], e[LEN], t[LEN], l[LEN];
int order = 0;
void dfs(int u) {
	s[u] = ++order;
	for (const int& v : g[u]) {
		if (!s[v]) {
			l[v] = l[u] + 1;
			dfs(v);
		}
	}
	e[u] = order;
}
int sum(int i) {
	int ret = 0;
	while (i > 0) {
		ret += t[i];
		i -= i & -i;
	}
	return ret;
}
void update(int i, int d) {
	while (i <= N) {
		t[i] += d;
		i += i & -i;
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1, u, v; i < N; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
	}
	dfs(1);
	std::cin >> M;
	for (int i = 1, u, v; i < N + M; ++i) {
		std::cin >> cmd;
		if (cmd == 'A') {
			std::cin >> u >> v;
			update(s[v], 1);
			update(e[v] + 1, -1);
		}
		if (cmd == 'W') {
			std::cin >> v;
			std::cout << l[v] - sum(s[v]) << '\n';
		}
	}
}