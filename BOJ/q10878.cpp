#include <iostream>
#include <string>

const int LEN = 1 << 20;

int K, N, cnt[LEN];
int x[24][2][2];

std::string S;

int main() {
	std::cin >> K >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> S;
		for (int k = 0, b = 0; k < K; ++k) {
			if (S[k] == '2') {
				x[i][0][0] |= 1 << k;
				x[i][0][1] |= 1 << k;
				x[i][1][0] |= 1 << k;
				x[i][1][1] |= 1 << k;
			}
			if (S[k] == '1') {
				x[i][0][0] |= 1 << k;
				x[i][1][b > 0] |= 1 << k;
				b++;
			}
		}
		std::cout << x[i][0][0] << ' ' << x[i][0][1] << '\n';
		std::cout << x[i][1][0] << ' ' << x[i][1][1] << "\n\n";
	}
	int ret = 1e9;
	for (int i = 0; i < (1 << N); ++i) {
		int cur = 0;
		for (int b = 0; b < N; ++b) {
			if (!cnt[x[b][!!(i & 1 << b)][0]]++) cur++;
			if (!cnt[x[b][!!(i & 1 << b)][1]]++) cur++;
		}
		ret = std::min(ret, cur);
		for (int b = 0; b < N; ++b) {
			cnt[x[b][!!(i & 1 << b)][0]]--;
			cnt[x[b][!!(i & 1 << b)][1]]--;
		}
	}
	std::cout << ret;
}