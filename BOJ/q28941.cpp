#include <iostream>

typedef long long ll;
int N, K, cnt[10][10];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> K;
	for (int i = 0, a; i < N; ++i) {
		std::cin >> a;
		for (int j = 0, d; a; ++j, a /= 10) {
			d = a % 10;
			cnt[j][d]++;
		}
	}
	ll ret = 0;
	for (ll e = 9, eff = 1e9; e >= 0; --e, eff /= 10) {
		for (ll d = 0, c; d < 9; ++d) {
			c = std::min(cnt[e][d], K);
			ret += eff * (9 - d) * c;
			K -= c;
		}
	}
	std::cout << ret;
}