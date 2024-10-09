#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>

int Q, i, e, c[63], s[63];
char q;
long long a;

int main() {
	freopen("input.txt", "r", stdin);
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0); std::cout.tie(0);

	std::cin >> Q;
	while (Q--) {
		memset(s, 0, sizeof s);
		std::cin >> q >> a;
		if (a) {
			if (q == '+') ++c[(int)log2(a)];
			if (q == '-') --c[(int)log2(a)];
		}
		for (s[0] = c[0], i = 1; i < 63; ++i) s[i] = c[i] + (s[i - 1] >> 1);
		for (i = 62; i >= 0; --i) if (s[i]) break;
		std::cout << (~i ? 1ll << i : 0) << '\n';
		// std::cout << (1ll << i) << '\n';
	}
}