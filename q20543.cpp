#include <iostream>

typedef long long ll;
const int LEN = 2001;

int N, M, H[LEN][LEN];
ll C[LEN][LEN], S[LEN][LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			std::cin >> H[i][j];
	}
	for (int i = 1; i <= N - M + 1; ++i) {
		for (int j = 1; j <= N - M + 1; ++j) {
			int r = j + M / 2;
			int l = std::max(0, r - M);
			int d = i + M / 2;
			int u = std::max(0, d - M);
			S[d][r] += S[d][r - 1] + S[d - 1][r] - S[d - 1][r - 1];
			ll sum = S[d][r] - S[d][l] - S[u][r] + S[u][l];
			C[d][r] = -H[i][j] - sum;
			S[d][r] += C[d][r];
		}
	}
	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j)
			std::cout << C[i][j] << ' ';
		std::cout << '\n';
	}
}