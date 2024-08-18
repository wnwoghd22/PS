#include <iostream>

const int LEN = 2e5 + 1;

int N;
char S[LEN], T[LEN];
int t[LEN * 2];
int fail[LEN];
int q[26];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> S >> T;
	for (int i = 1, j = 0; S[i]; ++i) {
		while (j && S[i] != S[j]) j = fail[j - 1];
		if (S[i] == S[j]) fail[i] = ++j;
	}
	for (int i = 0; i < N; ++i)
		t[i] = t[N + i] = T[i] - 'a';
	
	for (int i = 0; i < N * 2; ++i) {
		for (int k = 0; k < 26; ++k) {
			int& j = q[k];
			while (j && (t[i] + k) % 26 != S[j] - 'a') j = fail[j - 1];
			if ((t[i] + k) % 26 == S[j] - 'a') {
				if (j == N - 1) { // matching
					std::cout << "Success\n";
					std::cout << i - N + 1 << ' ' << (26 - k) % 26;
					return 0;
				}
				++j;
			}
		}
	}
	std::cout << "Impossible";
}
