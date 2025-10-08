#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 4'000;
int N, A[4][LEN], S[2][LEN * LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < 4; ++j)
			std::cin >> A[j][i];
	}
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				S[i][j * N + k] = A[i][j] + A[i + 2][k];
		std::sort(S[i], S[i] + N * N);
	}
	ll ret = 0;
	for (int i = N * N - 1, l = 0, r = 0; i >= 0; --i) {
		while (r < N * N && S[0][i] + S[1][r] <= 0) ++r;
		while (l < r && S[0][i] + S[1][l] < 0) ++l;
		ret += r - l + (r < N && S[0][i] + S[1][r] == 0);
	}
	std::cout << ret;
}