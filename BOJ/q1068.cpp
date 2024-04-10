#include <iostream>
#include <vector>

const int LEN = 50;

int N;
int root;
int cut;
std::vector<int> graph[LEN];

int dfs(int u, int p = -1) {
	int sz = 0;
	for (const int& v : graph[u]) {
		if (v == p || v == cut) continue;
		sz += dfs(v, u);
	}
	return sz + !sz;
}

int main() {
	std::cin >> N;
	for (int u = 0, p; u < N; ++u) {
		std::cin >> p;
		if (~p) graph[p].push_back(u);
		else root = u;
	}
	std::cin >> cut;

	if (cut == root) std::cout << 0;
	else std::cout << dfs(root);
}