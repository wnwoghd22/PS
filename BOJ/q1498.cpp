#include <iostream>
#include <cstring>

const int LEN = 1e6 + 1;

std::string S;
int fail[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> S;
	memset(fail, 0, sizeof fail);
	for (int i = 1, j = 0; i < S.length(); ++i) {
		while (j && S[i] ^ S[j]) j = fail[j - 1];
		if (S[i] == S[j]) fail[i] = ++j;
	}
	for (int i = 2, m, n; i <= S.length(); ++i) {
		m = i % (i - fail[i - 1]);
		n = i / (i - fail[i - 1]);
		if (!m && n > 1) {
			std::cout << i << ' ' << n << '\n';
		}
	}
}