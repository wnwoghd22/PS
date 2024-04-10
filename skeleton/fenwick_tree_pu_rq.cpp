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
	std::cin >> N >> M >> K;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		update(i, A[i]);
	}
	while (M || K) {
		std::cin >> a >> b >> c;
		if (a == 1) {
			--M;
			d = c - A[b];
			A[b] = c;
			update(b, d);
		}
		if (a == 2) {
			--K;
			if (b > c) std::swap(b, c);
			std::cout << sum(c) - sum(b - 1) << '\n';
		}
	}
}