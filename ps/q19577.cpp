#include <iostream>

typedef long long ll;
const int LEN = 4e4;
int N, p[LEN];

int main() {
	std::cin >> N;
	for (int i = 2; i < LEN; ++i) {
		if (p[i]) continue;
		for (int j = i; j < LEN; j += i) p[j] = i;
	}
	int ret = -1;
	for (int x = 2; x <= std::min(N, LEN - 1); ++x) {
		if (N % x) continue;
		ll phi = x, n = x;
		while (n > 1) {
			phi /= p[n]; phi *= p[n] - 1;
			n /= p[n];
		}
		// std::cout << x << ' ' << phi << '\n';
		if (x * phi == N) {
			ret = x;
			break;
		}
	}
	std::cout << ret;
}