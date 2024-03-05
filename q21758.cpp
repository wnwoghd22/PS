#include <iostream>
#include <algorithm>

typedef long long ll;
const int LEN = 100'001;

int N, A[LEN];
ll S[LEN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		S[i] = S[i - 1] + A[i];
	}
	ll ret = 0;

	// middle
	for (ll i = 2, k = S[N - 1] - S[1]; i < N; ++i) {
		ret = std::max(ret, k + A[i]);
	}

	// right
	for (ll i = 2, k = S[N] - S[1]; i < N; ++i) {
		ret = std::max(ret, k - A[i] + S[N] - S[i]);
	}

	// left
	for (ll i = 2, k = S[N - 1]; i < N; ++i) {
		ret = std::max(ret, k - A[i] + S[i - 1]);
	}

	std::cout << ret;
}