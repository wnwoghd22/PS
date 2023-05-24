#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

const int LEN = 100'001;

struct Boomerang { int u, v, w; } b[LEN];
int N, M, K;

std::vector<int> graph[LEN];

int ord, order[LEN];

int dfs(int u, int p = 0) {
	// std::cout << K << '\n';
	// std::cout << u << ' ' << p << '\n';
	
	order[u] = ++ord;

	int hold = 0;

	for (const int& v : graph[u]) {
		if (v == p) continue;
		// std::cout << v << '\n';

		if (!order[v]) {
			int w = dfs(v, u);
			if (w) b[K++] = { u, v, w };
			else {
				if (hold) {
					b[K++] = { hold, u, v };
					hold = 0;
				}
				else hold = v;
			}
		}
		else if (order[v] < order[u]) {
			if (hold) {
				b[K++] = { hold, u, v };
				hold = 0;
			}
			else hold = v;
		}
	}
	return hold;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> M;

	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	for (int i = 1; i <= N; ++i) {
		if (!order[i])
			dfs(i);
	}

	std::cout << K << '\n';
	/*for (int i = 0; i < K; ++i)
		std::cout << b[i].u << ' ' << b[i].v << ' ' << b[i].w << '\n';*/
}