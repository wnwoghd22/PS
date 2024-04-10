#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 1e6 + 1;
const int P = 917, MOD = 993244853;

int N, Q;
ll p[LEN], h[LEN];
ll hash(int s, int e) { return (h[e] - h[s - 1] + MOD) * p[N - e] % MOD; }
char S[LEN];


int main() {
	std::cin >> N >> S;
	for (int i = p[0] = 1; i <= N; ++i) p[i] = p[i - 1] * P % MOD;
	for (int i = 1; i <= N; ++i)
		h[i] = (p[i] * S[i - 1] + h[i - 1]) % MOD;

	int len = 0;
	for (int i = N / 2, j = 0; i; --i) {
		j = std::min(j + 2, N / 2 - i);
		while (j && hash(i + 1, i + j) != hash(N - i - j + 1, N - i)) --j;
		if (hash(1, i) == hash(N - i + 1, N)) len = std::max(len, i + j);
	}
	std::cout << len;
}