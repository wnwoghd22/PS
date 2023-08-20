#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

typedef unsigned long long ull;
const int LEN = 1001;

int N, M;
std::string S, T, lcs;

ull sl[26][LEN], sr[26][LEN];

// execute a - b and returns borrow bit
ull sub(ull& a, ull b) {
	ull c = a;
	return (a = c - b) > c;
}

void hirschberg(int u, int d, int l, int r) {
	if (u > d) return;
	if (u == d) { // only one row
		for (int j = l; j <= r; ++j) {
			if (S[u] == T[j]) {
				lcs += S[u];
				break;
			}
		}
		return;
	}
	int mid = u + d >> 1;
	int len = r - l + 1;
	std::vector<int> L(len + 2), R(len + 2);
	std::vector<ull> dp((len >> 6) + 2);
	
	for (int j = l; j <= r; ++j) if (T[j] == S[u]) { dp[j - l >> 6] |= 1llu << (j - l & 63); break; }
	for (int i = u + 1; i <= mid; ++i) {
		ull s, x, y, z, carry = 1, borrow = 0;

		// x = s | dp0
		// y = dp0 << 1 | 1
		// dp1 = x & (x ^ (x - y))
		for (int j = 0; j <= (len >> 6); ++j) {
			s = (sl[S[i] - 'A'][(l >> 6) + j] >> (l & 63)) | ((l & 63) ? (sl[S[i] - 'A'][(l >> 6) + j + 1] << (64 - (l & 63))) : 0);
			x = s | dp[j];
			y = dp[j] << 1 | carry;
			carry = dp[j] >> 63;

			// z = x - y
			z = x;
			borrow = sub(z, borrow);
			borrow += sub(z, y);

			dp[j] = x & (x ^ z);
		}
		dp[len >> 6] &= (1llu << (len & 63)) - 1;
	}
	for (int j = l; j <= r; ++j) L[j - l + 1] = L[j - l] + !!(dp[(j - l) >> 6] & (1llu << ((j - l) & 63)));

	int o = M - r - 1; // offset
	std::fill(dp.begin(), dp.end(), 0);

	for (int j = r; j >= l; --j) if (T[j] == S[d]) { dp[r - j >> 6] |= 1llu << (r - j & 63); break; }
	for (int i = d - 1; i > mid; --i) {
		ull s, x, y, z, carry = 1, borrow = 0;
		
		// x = s | dp0
		// y = dp0 << 1 | 1
		// dp1 = x & (x ^ (x - y))
		for (int j = 0; j <= (len >> 6); ++j) {
			s = (sr[S[i] - 'A'][(o >> 6) + j] >> (o & 63)) | ((o & 63) ? (sr[S[i] - 'A'][(o >> 6) + j + 1] << (64 - (o & 63))) : 0);
			x = s | dp[j];
			y = dp[j] << 1 | carry;
			carry = dp[j] >> 63;

			// z = x - y
			z = x;
			borrow = sub(z, borrow);
			borrow += sub(z, y);

			dp[j] = x & (x ^ z);
		}
		dp[len >> 6] &= (1llu << (len & 63)) - 1;
	}
	for (int j = r; j >= l; --j) R[j - l + 1] = R[j - l + 2] + !!(dp[(r - j) >> 6] & (1llu << ((r - j) & 63)));

	int max = -1, idx = 0;
	for (int i = l; i <= r + 1; ++i) {
		if (L[i - l] + R[i - l + 1] > max) {
			max = L[i - l] + R[i - l + 1];
			idx = i;
		}
	}
	hirschberg(u, mid, l, idx - 1);
	hirschberg(mid + 1, d, idx, r);
}

int main() {
	std::cin >> S >> T;
	N = S.length(), M = T.length();

	for (int j = 0; j < M; ++j) { // preprocessing bitset s
		sl[T[j] - 'A'][j >> 6] |= 1llu << (j & 63);
		sr[T[M - j - 1] - 'A'][j >> 6] |= 1llu << (j & 63);
	}

	hirschberg(0, N - 1, 0, M - 1);
	std::cout << lcs.length() << '\n';
	std::cout << lcs;
}