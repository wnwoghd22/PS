#include <iostream>

typedef long long ll;
const int LEN = 1'000'001;
const ll MOD = 1e9 + 7;
int N, M, K;

ll R[LEN], C[LEN];
char c;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) R[i] = 1;
	for (int i = 1; i <= M; ++i) C[i] = 1;

	for (int i = 0, k, x, y; i < K; ++i) {
		std::cin >> c >> x >> y;
		if (c == 'R') R[x] = R[x] * y % MOD;
		else C[x] = C[x] * y % MOD;
	}

	// column process
	ll eff = 0;
	ll sum = 0;
	for (int i = 1; i <= M; ++i) {
		eff = (eff + C[i]) % MOD;
		sum = (sum + C[i] * i) % MOD;
	}

	// row proces
	ll ret = 0;
	for (ll i = 1; i <= N; ++i)
		ret = (ret + ((i - 1) * M % MOD * eff % MOD + sum) % MOD * R[i]) % MOD;
	std::cout << ret;
}