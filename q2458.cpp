#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

const int LEN = 501;

int N, M;
int in[LEN], lv[LEN], ord[LEN], cnt[LEN];
std::vector<int> g[LEN];

void topo_sort() {
	int i = 0;
	std::queue<int> q;
	for (int u = 1; u <= N; ++u)
		if (!in[u]) ++cnt[0], q.push(u);
	while (q.size()) {
		int u = q.front();
		q.pop();
		ord[i++] = u;
		for (const int& v : g[u])
			if (!--in[v])
				++cnt[lv[v] = lv[u] + 1], q.push(v);
	}
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		in[v]++;
	}
	topo_sort();
	int ret = 0, max = 0;
	for (int i = 0, u; i < N; ++i) {
		u = ord[i];
		if (cnt[lv[u]] == 1 && max <= lv[u]) ++ret;
		int min = 1e9;
		for (const int& v : g[u]) min = std::min(min, lv[v]);
		max = std::max(max, min);
	}
	std::cout << ret;
}