#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 150'000;

int N, A[LEN], B[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> A[i];
	for (int i = 0; i < N; ++i) std::cin >> B[i];
	ll ret = 0;
	std::sort(B, B + N);
	for (int i = 0; i < N; ++i) {
		for (ll j = 1, k = 1; j <= 11; k *= 10, ++j) {
			int L = -1, R = -1;
			int l = 0, r = N - 1, m;
			while (l <= r) {
				m = l + r >> 1;
				if (A[i] + B[m] < k) {
					L = std::max(L, m);
					l = m + 1;
				}
				else r = m - 1;
			}
			l = 0, r = N - 1;
			while (l <= r) {
				m = l + r >> 1;
				if (A[i] + B[m] < k * 10) {
					R = std::max(L, m);
					l = m + 1;
				}
				else r = m - 1;
			}
			ret += (R - L) * j;
		}
	}
	std::cout << ret;
}