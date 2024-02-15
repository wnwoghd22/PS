#include <iostream>

typedef long long ll;
const int LEN = 1e5 + 1;

int N, x[LEN], y[LEN], cx[LEN], cy[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> x[i] >> y[i];
		++cx[x[i]], ++cy[y[i]];
	}
	ll cnt = 0;
	for (ll i = 0; i < N; ++i)
		cnt += (cx[x[i]] - 1) * (cy[y[i]] - 1);
	std::cout << cnt;
}