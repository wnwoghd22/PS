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
			// ll sum = S[i + M / 2][j + M / 2] - S[i - 1][j + M / 2] - S[i + M / 2][j - 1] + S[i - 1][j - 1];
			// C[i + M / 2][j + M / 2] = H[i][j]

		}
	}
}