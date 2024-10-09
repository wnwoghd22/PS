#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int LEN = 1'000'001;
ll N, A, result, S[LEN];

int main() {
	freopen("input.txt", "r", stdin);

	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A;
		S[i] = S[i - 1] + A;
	}
	for (int x = 1; x <= N; ++x) {
		int l = x + 1, r = N - 1, m, y = -1, bound = N;
		while (l <= r) {
			m = l + r >> 1;
			ll head = S[x], tail = S[N] - S[m];
			if (head < tail) {
				y = m;
				l = m + 1;
			}
			else r = m - 1;
		}
		if (!~y) break;

		l = x + 1, r = y;
		while (l <= r) {
			m = l + r >> 1;
			ll body = S[m] - S[x], tail = S[N] - S[m];
			if (body > tail) {
				bound = m;
				r = m - 1;
			}
			else l = m + 1;
		}
		if (bound > y) continue;

		// std::cout << x << ' ' << bound << ' ' << y << '\n';
		result += y - bound + 1;
	}
	std::cout << result;
}