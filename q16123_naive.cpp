#include <iostream>

int gcd(int a, int b) { return !b ? a : gcd(b, a % b); }

int main() {
	int N, cnt = 0;
	std::cin >> N;
	for (int m = 2; m <= N; ++m) {
		// printf("m = %2d:", m);
		for (int n = 1; n < m; ++n) {
			if (gcd(gcd(m * m + n * n, 2 * m * n), m * m - n * n) == 1) ++cnt;
			// if ((m ^ n) & 1)
			// 	printf("(%2d,%2d)", gcd(m, n), gcd(gcd(m * m + n * n, 2 * m * n), m * m - n * n));
			// else printf("[%2d,%2d]", gcd(m, n), gcd(gcd(m * m + n * n, 2 * m * n), m * m - n * n));

		}
		// printf("\n");
	}
	std::cout << cnt;
}