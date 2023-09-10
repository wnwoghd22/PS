#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

typedef unsigned long long ull;
const int LEN = 1001;

std::string A, B;
char X, Y;

int a, b;
std::string S[2], T[2];

int l, r, len;

ull dp[2][LEN], * dp0, * dp1;
ull s[26][LEN];

bool sieve[50001];

// execute a - b and returns borrow bit
ull sub(ull& a, ull b) {
	ull c = a;
	return (a = c - b) > c;
}

int lcs(const std::string& S, const std::string& T) {
	memset(dp, 0, sizeof dp);
	memset(s, 0, sizeof s);

	for (int j = 0; j < T.length(); ++j) // preprocessing bitset s
		s[T[j] - 'A'][j >> 6] |= 1llu << (j & 63);

	// if one character is same, then other right values are all 1. break
	for (int j = 0; j < T.length(); ++j) if (T[j] == S[0]) { dp[0][j >> 6] |= 1llu << (j & 63); break; }

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
		}
		dp1[T.length() >> 6] &= (1llu << (T.length() & 63)) - 1;
	}

	int len = 0;
	for (int j = 0; j < T.length(); ++j)
		len += !!(dp1[j >> 6] & (1llu << (j & 63)));

	return len;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> A >> B >> X >> Y;

	for (const char& c : A) {
		if (c == X) ++a;
		else if (c == Y) continue;
		else S[a] += c;
	}

	for (const char& c : B) {
		if (c == X) ++b;
		else if (c == Y) continue;
		else T[b] += c;
	}

	l = S[0].length() && T[0].length() ? lcs(S[0], T[0]) : 0;
	r = S[1].length() && T[1].length() ? lcs(S[1], T[1]) : 0;
	len = l + r + 1;

	if (len < 2) std::cout << -1;
	else {
		for (int i = 2; i <= len; ++i) {
			if (sieve[i]) continue;
			for (int j = i * 2; j <= len; j += i) sieve[j] = 1;
		}
		while (sieve[len]) --len;
		std::cout << len;
	}
}