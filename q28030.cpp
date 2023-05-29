#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

const int LEN = 1001;

int T, N, M;
std::vector<int> i_children[LEN];
std::vector<int> m_children[LEN];
std::vector<int> row[LEN];
int i_parent[LEN], m_parent[LEN];
int root, level[LEN], extant[LEN];
bool dp[LEN][LEN];

void dfs(int u, int l) {
	level[u] = l;
	row[l].push_back(u);
	for (const int& v : i_children[u])
		dfs(v, l + 1);
}
bool mergable(int u, int v) {
	for (const int& cu : i_children[u]) {
		// if (extant[cu] && m_parent[cu] != v) return false;

		bool flag = false;
		for (const int& cv : m_children[v]) {
			if (dp[cu][cv]) {
				flag = true;
				break;
			}
		}
		if (!flag) return false;
	}
	return true;
}

void solve() {
	for (int i = 0; i < LEN; ++i) {
		i_children[i].clear();
		m_children[i].clear();
		row[i].clear();
	}
	memset(extant, 0, sizeof extant);
	memset(dp, 0, sizeof dp);

	std::cin >> N;

	root = N * (N + 1) >> 1;
	for (int i = 1, u, p; i < N; ++i) {
		std::cin >> u >> p;
		i_parent[u] = p;
		i_children[p].push_back(u);
		root -= u;
	}
	dfs(root, 0); extant[root] = root;

	std::cin >> M;
	for (int i = 1, u, p; i < M; ++i) {
		std::cin >> u >> p;
		m_parent[u] = p;
		m_children[p].push_back(u);
		extant[u] = u;
	}
	for (int l = N - 1; l > 0; --l) {
		for (const int& u : row[l]) {
			if (extant[u]) {
				dp[u][u] = true;
				continue;
			}
			for (const int& v : row[l]) {
				if (extant[v] && u < v && mergable(u, v))
					dp[u][v] = true;
			}
		}
	}
	std::cout << N - M << '\n';
	for (int l = 1; l < N; ++l) {
		for (const int& u : row[l]) {
			if (extant[u]) continue;
			
			for (const int& v : row[l]) {
				int e = extant[v];
				if (e) {
					if (extant[i_parent[u]] == extant[m_parent[e]] && dp[u][e]) {
						extant[u] = e;
						std::cout << u << ' ' << e << '\n';
						break;
					}
				}
			}
		}
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> T;
	while (T--) solve();
}