#include <iostream>
#include <vector>
#include <queue>

typedef long long ll;
const int MOD = 1e9 + 7;
const int LEN = 200'001;

int visited[LEN], level[LEN], cnt[LEN];
std::vector<int> g[LEN];

int N, M;
ll R = 1;

void bfs(int u) {
	std::queue<int> q;
	q.push(u);
	visited[u] = 1;
	while (q.size()) {
		u = q.front(); q.pop();
		cnt[level[u]]++;
		for (const int& v : g[u]) {
			if (visited[v]) continue;
			visited[v] = 1;
			level[v] = level[u] + 1;
			q.push(v);
		}
	}
}

int main() {
	std::cin >> N >> M;
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	bfs(1);
	for (int i = 0; i < N; ++i) R = (R * (cnt[i] + 1)) % MOD;
	std::cout << (R - 1 + MOD) % MOD;
}