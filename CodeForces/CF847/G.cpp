#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

const int LEN = 200'001;
const int INF = 1e9;
std::vector<int> graph[LEN];
int bonus[LEN], bonus_adj[LEN], token[LEN], visited[LEN];
int n, m, p, b, a, u, v;
int encountered, dist;

void bfs_from_finish_line() {
	encountered = 0, dist = INF;
	memset(visited, -1, sizeof visited);
	std::queue<int> q;
	visited[1] = 0;
	q.push(1);
	while (q.size()) {
		int u = q.front(); q.pop();
		if (token[u]) {
			token[u] = false;
			++encountered;
			dist = std::min(dist, visited[u]);
		}
		for (const int& v : graph[u]) {
			if (!~visited[v] && bonus[v]) {
				visited[v] = visited[u] + 1;
				q.push(v);
			}
			else if (token[v]) {
				token[v] = false;
				++encountered;
				dist = std::min(dist, visited[u] + 1);
			}
		}
	}
}

int check(int u) {
	int encountered = 0;
	std::queue<int> q;
	int size = 1;
	visited[u] = 1;
	q.push(u);
	while (q.size()) {
		u = q.front(); q.pop();
		if (token[u]) {
			token[u] = false;
			++encountered;
		}
		for (const int& v : graph[u]) {
			if (!~visited[v] && bonus[v]) {
				visited[v] = 1;
				++size;
				q.push(v);
			}
			else if (token[v]) {
				token[v] = false;
				++encountered;
			}
		}
	}
	if (encountered) {
		if (size >= 2) return INF;
		return encountered;
	}
	return 0;
}

void solve() {
	memset(bonus, 0, sizeof bonus);
	memset(bonus_adj, 0, sizeof bonus_adj);
	memset(token, 0, sizeof token);
	for (std::vector<int>& v : graph) v.clear();

	std::cin >> n >> m >> p >> b;
	while (p--) {
		std::cin >> a;
		token[a] = true;
	}
	while (b--) {
		std::cin >> a;
		bonus[a] = true;
	}
	while (m--) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
		if (bonus[u] && bonus[v]) {
			bonus_adj[u] = bonus_adj[v] = true;
		}
	}

	bfs_from_finish_line();

	if (encountered >= 2) {
		std::cout << "YES\n";
		return;
	}
	if (!encountered) {
		std::cout << "NO\n";
		return;
	}
	if (encountered == 1 && dist <= 1) {
		std::cout << "YES\n";
		return;
	}

	int chance = 0;
	for (int i = 1; i <= n; ++i) {
		if (bonus[i] && !~visited[i]) {
			int c = check(i);
			if (c == INF) {
				std::cout << "YES\n";
				return;
			}
			chance += 1;
		}
	}
	if (chance >= dist - 1) {
		std::cout << "YES\n";
		return;
	}
	std::cout << "NO\n";
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	int T;
	std::cin >> T;
	while (T--) solve();
}