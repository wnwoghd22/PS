#include <iostream>

typedef long long ll;
const int LEN = 1001;

int N, Q;
char S[LEN];
ll sum[LEN][LEN];

ll get(int x, int y) {
	ll ret = 0;
	ret += sum[N][N] * (x / N) * (y / N);
	ret += sum[N][y % N] * (x / N);
	ret += sum[x % N][N] * (y / N);
	ret += sum[x % N][y % N];
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 1; i <= N; ++i) {
		std::cin >> S;
		for (int j = 1; j <= N; ++j) {
			sum[i][j] = S[j - 1] == 'B';
			sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
		}
	}
	for (int q = 0, a, b, c, d; q < Q; ++q) {
		std::cin >> a >> b >> c >> d;
		++c, ++d;
		std::cout << get(c, d) - get(c, b) - get(a, d) + get(a, b) << '\n';
	}
}