#include <iostream>

const int LEN = 1'000'000;
int N, p, k, s[LEN], f[LEN];

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> s[N - i - 1];
	p = 1, k = N - 1;
	for (int i = 1, j = 0, cp, ck; i < N; ++i) {
		while (j && s[i] ^ s[j]) j = f[j - 1];
		if (s[i] == s[j]) f[i] = ++j;
		cp = i - f[i] + 1, ck = N - i - 1;
		if (cp + ck < p + k || cp + ck == p + k && cp < p)
			p = cp, k = ck;
	}
	std::cout << k << ' ' << p;
}