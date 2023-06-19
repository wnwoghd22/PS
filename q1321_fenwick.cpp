#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

typedef long long int ll;
const int LEN = 5e5 + 1;
ll N, M, q, i, x, fenwick[LEN];
ll get(int i) {
	ll result = 0;
	while (i > 0) {
		result += fenwick[i];
		i -= i & -i;
	}
	return result;
}
void update(int i, ll d) {
	while (i <= N) {
		fenwick[i] += d;
		i += i & -i;
	}
}

int binary_search(ll x) {
	int l = 1, r = N, m, result = N;
	while (l <= r) {
		m = l + r >> 1;
		if (get(m) >= x) {
			result = std::min(m, result);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

int main() {
	// freopen("input.txt", "r", stdin);
	std::cin >> N;
	for (i = 1; i <= N; ++i) {
		std::cin >> x;
		update(i, x);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> q;
		if (q == 1) {
			std::cin >> i >> x;
			update(i, x);
		}
		if (q == 2) {
			std::cin >> x;
			std::cout << binary_search(x) << '\n';
		}
	}
}