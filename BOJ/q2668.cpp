#include <iostream>

const int LEN = 101;

int N, C;
int g[LEN];
int c[LEN];
int o[LEN];

int dfs(int u, int mask, int order) {
	o[u] = order;
	c[u] = mask;
	int v = g[u];
	if (c[v] == mask) {
		C++;
		c[u] = -1;
		return o[v];
	}
	if (c[v]) return order;
	int m = dfs(v, mask, order + 1);
	if (m <= order) C++, c[u] = -1;
	return m;
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> g[i];
	for (int i = 1; i <= N; ++i)
		if (!c[i]) dfs(i, i, 1);
	std::cout << C << '\n';
	for (int i = 1; i <= N; ++i)
		if (!~c[i]) std::cout << i << '\n';
}