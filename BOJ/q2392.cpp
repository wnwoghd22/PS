#include <iostream>

typedef long long ll;
const ll MOD = 1e9;
const int LEN = 1001;

int N;
int C[LEN], D[LEN], S[LEN];

int main() {
	std::cin >> N;
	for (int i = C[0] = 1; i < N; ++i)
		for (int j = 0; j <= i; ++j)
			C[i] = (C[i] + (ll)C[j] * C[i - j - 1]) % MOD;
	for (int i = (D[0] = D[1] = S[0] = 1) + 1; i < N / 2; ++i) {
		for (int j = 0; j < i; ++j)
			S[i - 1] = (S[i - 1] + (ll)D[j] * D[i - j - 1]) % MOD;
		for (int j = 0; j < i; ++j)
			D[i] = (D[i] + (ll)D[i - j - 1] * S[j]) % MOD;
	}
	std::cout << C[N - 2] << '\n' << (N & 1 ? 0 : D[N / 2 - 1]);
}
