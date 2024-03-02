#include <iostream>

typedef long long ll;
const int LEN = 1'000'001;

/// <summary>
/// point update
/// range query
/// </summary>

int N, M, K;
ll a, b, c, d, A[LEN], fenwick[LEN];
ll sum(int i) {
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

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N >> M;
	while (M--) {
		std::cin >> a >> b >> c;
		if (a == 1) {
			d = c - A[b];
			A[b] = c;
			update(b, d);
		}
		if (a == 0) {
			if (b > c) std::swap(b, c);
			std::cout << sum(c) - sum(b - 1) << '\n';
		}
	}
}