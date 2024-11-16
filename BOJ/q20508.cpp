#include <iostream>

const int LEN = 200'001;
int N, idx, g[LEN][26], t[LEN];
char S[LEN];

int dfs(int k, int l) {
	int ret = 0;
	for (int i = 0; i < 26; ++i) {
		if (g[k][i] && t[g[k][i]] & 1 << l)
			ret |= !dfs(g[k][i], !l);
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	for (int b = 1; b <= 2; ++b) {
		std::cin >> N;
		for (int i = 0; i < N; ++i) {
			std::cin >> S;
			for (int j = 0, k = 0, c; S[j]; ++j) {
				c = S[j] - 'a';
				if (!g[k][c]) g[k][c] = ++idx;
				k = g[k][c];
				t[k] |= b;
			}
		}
	}
	std::cout << (dfs(0, 0) ?  "Nina" : "Emilija");
}