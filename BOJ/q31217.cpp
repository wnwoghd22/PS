#include <iostream>

const int LEN = 1e5 + 1;
const int MOD = 1e9 + 7;
int N, M, C[LEN][4], deg[LEN];

int main() {
	std::cin >> N >> M;
	for (int i = 0; i <= N; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= std::min(3, i); ++j)
			C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
	}
	for (int i = 0, u, v; i < M; ++i) {
		std::cin >> u >> v;
		deg[u]++; deg[v]++;
	}
	int ret = 0;
	for (int i = 1; i <= N; ++i)
		ret = (ret + C[deg[i]][3]) % MOD;
	std::cout << ret;
}