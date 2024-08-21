#include <iostream>

const int LEN = 2e5 + 1;

int N;
char S[LEN], T[LEN];
int s[LEN], t[LEN * 2];
int fail[LEN];
int q[26];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> S >> T;

	if (N == 1) {
		std::cout << "Success\n" << 0 << ' ' << (T[0] - S[0]) % 26;
		return 0;
	}

	for (int i = 1; S[i]; ++i) s[i - 1] = (S[i] - S[i - 1] + 26) % 26;
	for (int i = 1, j = 0; i < N - 1; ++i) {
		while (j && s[i] != s[j]) j = fail[j - 1];
		if (s[i] == s[j]) fail[i] = ++j;
	}
	t[N - 1] = (T[0] - T[N - 1] + 26) % 26;
	for (int i = 1; T[i]; ++i) 
		t[N + i - 1] = t[i - 1] = (T[i] - T[i - 1] + 26) % 26;

	// for (int i = 0; i < N - 1; ++i) std::cout << s[i] << ' '; std::cout << '\n';
	// for (int i = 0; i < N * 2 - 1; ++i) std::cout << t[i] << ' '; std::cout << '\n';

	for (int i = 0, j = 0; i < N * 2 - 1; ++i) {
		while (j && t[i] != s[j]) j = fail[j - 1];
		if (t[i] == s[j]) {
			if (j == N - 2) { // matching
				std::cout << "Success\n";
				int k = (i + 2) % N;

				// std::cout << i << ' ' << k << '\n';
				// std::cout << T[k] << ' ' << S[0] << '\n';

				std::cout << k << ' ' << (T[k] - S[0]) % 26;
				return 0;
			}
			++j;
		}
	}
	std::cout << "Impossible";
}
