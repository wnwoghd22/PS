#include <iostream>

typedef long long ll;
const int LEN = 100'001;

/// <summary>
/// range update
/// point query
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
void update(int l, int r, ll d) {
	update(l, d);
	update(r + 1, -d);
}

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		update(i, i, A[i]);
	}
	std::cin >> M;
	while (M--) {
		std::cin >> a;
		if (a == 1) {
			std::cin >> b >> c >> d;
			update(b, c, d);
		}
		if (a == 2) {
			std::cin >> b;
			std::cout << sum(b) << '\n';
		}
	}
}