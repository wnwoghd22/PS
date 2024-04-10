#include <iostream>
#include <cstring>

const int LEN = 1e6 + 1;

char S[LEN];
int N, fail[LEN];

int main() {
	while (1) {
		std::cin >> S;
		if (S[0] == '.') break;
		N = strlen(S);
		memset(fail, 0, sizeof fail);
		for (int i = 1, j = 0; i < N; ++i) {
			if (j && S[i] ^ S[j]) j = fail[j - 1];
			if (S[i] == S[j]) fail[i] = ++j;
		}
		std::cout << (N % (N - fail[N - 1]) ? 1 : N / (N - fail[N - 1])) << '\n';
	}

}