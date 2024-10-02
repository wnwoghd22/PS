#include <iostream>

typedef long long ll;
const int LEN = 500'001;
const ll MOD = 1e9 + 7;
int N, h[LEN], C[LEN], sp, S[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;

	ll ret = 0;
	for (int i = 0, j, k; i < N; ++i) {
		std::cin >> h[i];
		C[i] = 1;
		while (sp && h[S[sp - 1]] <= h[i]) {
			j = S[--sp];
			k = sp && h[S[sp - 1]] < h[i] ? S[sp - 1] : i;
			ret = (ret + ((ll)N - C[j]) * C[j] % MOD * (h[k] - h[j]) % MOD * (h[k] - h[j])) % MOD;
			C[k] += C[j];
		}
		S[sp++] = i;
	}
	while (sp > 1) {
		int i = S[sp - 1];
		int j = S[sp - 2];
		ret = (ret + ((ll)N - C[i]) * C[i] % MOD * (h[j] - h[i]) % MOD * (h[j] - h[i])) % MOD;
		C[j] += C[i];
		sp--;
	}
	std::cout << ret;
}