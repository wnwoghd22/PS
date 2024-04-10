#include <iostream>

const int LEN = 1e6 + 1;
int N, fail[LEN];
char S[LEN];

int main() {
	std::cin >> N >> S;
	for (int i = 1, j = 0; i < N; ++i) {
		while (j && S[i] != S[j]) j = fail[j - 1];
		if (S[i] == S[j]) fail[i] = ++j;
	}
	std::cout << N - fail[N - 1];
}