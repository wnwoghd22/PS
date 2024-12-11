#include <iostream>
#include <cstring>

const int LEN = 1 << 20;
int N, M, idx, len, g[LEN][26], d[LEN];
char S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 0, b; i < N; ++i) {
		std::cin >> S;
		len = strlen(S);
		b = -1;
		for (int j = 0, k = 0, c; j < len; ++j) {
			c = S[j] - 'a';
			if (!g[k][c]) {
				g[k][c] = ++idx;
				if (!~b) b = d[k] + 2; // tab
			}
			if (!d[g[k][c]]) d[g[k][c]] = d[k] + 1;
			k = g[k][c];
			if (~b) d[k] = std::min(d[k], b + len - j - 1);
		}
	}
	for (int i = 0, ret; i < M; ++i) {
		std::cin >> S;
		len = strlen(S);
		ret = len;
		for (int j = 0, k = 0, c, t; j < len; ++j) {
			c = S[j] - 'a';
			if (!g[k][c]) break;
			k = g[k][c];
			ret = std::min(ret, d[k] + len - j - 1);
		}
		std::cout << ret << '\n';
	}
}