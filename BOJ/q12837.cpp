#include <iostream>

typedef long long ll;
const int LEN = 1e6 + 1;

int N, Q;
ll t[LEN];
void update(int i, ll x) {
	while (i <= N) {
		t[i] += x;
		i += i & -i;
	}
}
ll sum(int i) {
	ll ret = 0;
	while (i > 0) {
		ret += t[i];
		i -= i & -i;
	}
	return ret;
}

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> Q;
	for (int i = 0, c, p, q; i < Q; ++i) {
		std::cin >> c >> p >> q;
		if (c == 1) update(p, q);
		if (c == 2) std::cout << sum(q) - sum(p - 1) << '\n';
	}
}