#include <iostream>
#include <algorithm>

typedef long long ll;
const ll INF = 1e12;
const int LEN = 1e6;

ll N, K, A[LEN], F[LEN];

ll f(ll m) {
	ll cnt = 0;
	for (int i = 0; i < N; ++i) {
		ll a = m / F[N - i - 1];
		if (A[i] > a) cnt += A[i] - a;
	}
	return cnt;
}

ll binary_search() {
	ll l = 0, r = INF, m, result = INF;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m) <= K) {
			result = std::min(result, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

ll solve() {
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; ++i) std::cin >> F[i];
	std::sort(A, A + N);
	std::sort(F, F + N);
	return binary_search();
}

int main() {
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t)
		std::cout << '#' << t << ' ' << solve() << '\n';
}