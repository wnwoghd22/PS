#include <iostream>

typedef long long ll;
const ll MOD = 998244353;
const int LEN = 2e5 + 1;
const int D_LEN = 11;

int N;
ll A[LEN];
int cnts[D_LEN];

int get_len(int a) {
	int len = 0;
	while (a) {
		++len;
		a /= 10;
	}
	return len;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];

	ll ret = 0;
	for (int i = N - 1, j; i >= 0; --i) {
		ll a = A[i];
		ret += a * i % MOD;
		ret %= MOD;
		j = get_len(a);
		for (ll d = 0; d < D_LEN; ++d) {
			ret += a * cnts[d] % MOD;
			ret %= MOD;
			a = a * 10 % MOD;
		}
		cnts[j]++;
	}
	std::cout << ret;
}