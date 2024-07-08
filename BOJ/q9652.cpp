#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

#include <cassert>

const int INF = 1e9;
const int LEN = 1001;
char S[LEN * 30];

int L[LEN * 3], R[LEN * 3];
int B[LEN * 3], C[LEN * 3];

int dp[LEN * 3][LEN];

void dfs(int u) {
	if (~L[u]) dfs(L[u]);
	if (~R[u]) dfs(R[u]);
	std::cout << u << ' ' << B[u] << '\n';
}

int dfs(int u, int k) {
	int& ref = dp[u][k];
	if (~ref) return ref;
	ref = INF;
	if (!~L[u] && !~R[u]) {
		if (k > 1) return INF;
		return ref = B[u] ^ k;
	}
	if (k & 1) {
		ref = std::min(ref, dfs(L[u], (k + 1) / 2) + dfs(R[u], k / 2));
		ref = std::min(ref, dfs(L[u], k / 2) + dfs(R[u], (k + 1) / 2));
	}
	else ref = std::min(ref, dfs(L[u], k / 2) + dfs(R[u], k / 2));
	return ref;
}

int main() {
	freopen("input.txt", "r", stdin);

	std::cin.tie(0)->sync_with_stdio(0);
	while (std::cin >> S) {
		// std::cout << S << '\n';
		std::vector<int> stack;
		int cnt = 0;
		for (int i = 0, u = 0; S[i]; ++i) {
			if (S[i] == '(') {
				L[u] = R[u] = -1;
				C[u] = B[u] = 0;
				if (stack.size()) {
					int p = stack.back();
					(!~L[p] ? L[p] : R[p]) = u;
				}
				stack.push_back(u);
				u++;
			}
			if (S[i] == ')') {
				int x = stack.back();
				stack.pop_back();
				if (stack.size()) {
					int p = stack.back();
					C[p] += C[x];
				}
			}
			if (S[i] == 'B') {
				int x = stack.back();
				B[x] = C[x] = 1;
			}
		}
		assert(stack.empty());
		// dfs(0); std::cout << '\n';
		memset(dp, -1, sizeof dp);

		int ret = dfs(0, C[0]);
		if (ret == INF) std::cout << "impossible\n";
		else std::cout << ret / 2 << '\n';
	}
}