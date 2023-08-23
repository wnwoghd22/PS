#include <iostream>
#include <algorithm>
#include <string>

typedef unsigned long long ull;
const int LEN = 1001;

std::string S, T;

ull dp[2][LEN], *dp0, *dp1;
ull x[LEN], s[26][LEN];

// execute a - b and returns borrow bit
ull sub(ull& a, ull b) {
	ull c = a;
	return (a = c - b) > c;
}

int main() {
	std::cin >> S >> T;

	for (int j = 0; j < T.length(); ++j) // preprocessing bitset s
		s[T[j] - 'A'][j >> 6] |= 1llu << (j & 63);
	for (int i = 0; i < 26; ++i) std::cout << s[i][0] << '\n';

	// if one character is same, then other right values are all 1. break
	for (int j = 0; j < T.length(); ++j) if (T[j] == S[0]) { dp[0][j >> 6] |= 1llu << (j & 63); break; }
	std::cout << dp[0][0] << '\n';

	dp1 = dp[0];

	for (int i = 1; i < S.length(); ++i) {
		// toggling
		dp0 = dp[~i & 1];
		dp1 = dp[i & 1];

		ull carry = 1;
		ull borrow = 0;
		ull x, y, z;

		// x = s | dp0
		// y = dp0 << 1 | 1
		// dp1 = x & (x ^ (x - y))
		for (int j = 0; j <= (T.length() >> 6); ++j) {
			x = s[S[i] - 'A'][j] | dp0[j];
			y = dp0[j] << 1 | carry;
			carry = dp0[j] >> 63;

			// z = x - y
			z = x;
			borrow = sub(z, borrow);
			borrow += sub(z, y);

			dp1[j] = x & (x ^ z);

			std::cout << "s: " << s[S[i] - 'A'][j] << '\n';
			std::cout << "dp0: " << dp0[j] << '\n';
			std::cout << "x: " << x << '\n';
			std::cout << "y: " << y << '\n';
			std::cout << "z: " << z << '\n';
			std::cout << "dp1: " << dp1[j] << '\n';
		}
		dp1[T.length() >> 6] &= (1llu << (T.length() & 63)) - 1;
		std::cout << "dp1: " << dp1[T.length() >> 6] << '\n';
	}

	int len = 0;
	for (int j = 0; j < T.length(); ++j)
		len += !!(dp1[j >> 6] & (1llu << (j & 63)));

	for (int i = 0; i <= (T.length() >> 6); ++i)
		std::cout << dp1[i];
	std::cout << '\n';

	std::cout << len;
}