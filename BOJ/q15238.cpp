#include <iostream>
#include <vector>
#include <algorithm>

const int LEN = 200'001;

char cmd;
int N, M;
std::vector<int> g[LEN];
std::vector<int> r[LEN];
int l[LEN], s[LEN], e[LEN], t[LEN], ret[LEN];
int order;
void dfs1(int u) {
	l[++order] = u;
	for (const int& v : g[u]) dfs1(v);
	r[order].push_back(u);
}
void dfs2(int u) {
	s[u] = ++order;
	for (const int& v : g[u]) dfs2(v);
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
	for (int v = 2, u; v <= N; ++v) {
		std::cin >> u;
		g[u].push_back(v);
	}
	dfs1(1);

	order = 0;
	for (int u = 1; u <= N; ++u) g[u].clear();
	for (int v = 2, u; v <= N; ++v) {
		std::cin >> u;
		g[u].push_back(v);
	}
	dfs2(1);

	for (int i = 1, u, v; i <= N; ++i) {
		u = l[i];
		update(s[u], 1);
		ret[u] -= sum(e[u]) - sum(s[u]);
		for (const int& v : r[i]) {
			ret[v] += sum(e[v]) - sum(s[v]);
		}
	}
	for (int i = 1; i <= N; ++i) std::cout << ret[i] << ' ';
}