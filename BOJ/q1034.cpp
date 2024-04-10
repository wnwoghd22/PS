#include <iostream>

typedef long long ll;
char s[50][51];

int N, M, K;
ll col[50];

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		std::cin >> s[i];
		for (int j = 0; j < M; ++j) {
			if (s[i][j] == '1')
				col[j] |= 1ll << i;
		}
	}
	std::cin >> K;
	int max = 0;
	for (int i = 0; i < N; ++i) {
		ll row = -1;
		int k = 0;
		for (int j = 0; j < M; ++j) {
			if (~col[j] & (1ll << i)) {
				++k;
				row &= ~col[j];
			}
			else row &= col[j];
		}
		if (k > K || (k ^ K) & 1) continue;

		int on = 0;
		for (int j = 0; j < N; ++j) {
			if (row & 1ll << j) ++on;
		}
		max = std::max(on, max);
	}
	std::cout << max;
}