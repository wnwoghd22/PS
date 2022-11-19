#include <iostream>
#include <algorithm>

typedef long long int ll;
ll N, K, L, R, S = 3e9, A[5'000];
int main() {
	std::cin >> N;
	for (ll i = 0; i < N; ++i) std::cin >> A[i];
	std::sort(A, A + N);
	K = 0, L = 1, R = N - 1;
	for (ll k = 0; k < N - 2; ++k) {
		ll l = k + 1, r = N - 1, s;
		while (l < r) {
			s = A[k] + A[l] + A[r];
			if (abs(s) < S) S = abs(s), K = k, L = l, R = r;
			if (!s) break;
			else if (s > 0) --r;
			else ++l;
		}
	}
	std::cout << A[K] << ' ' << A[L] << ' ' << A[R];
}