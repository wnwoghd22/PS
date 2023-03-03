#include <iostream>

typedef long long int ll;
const int LEN = 100'000;
int N, M, T[LEN];

ll f(ll t) {
	ll result = 0;
	for (int i = 0; i < N; ++i) result += t / T[i];
	return result;
}

int binary_search() {
	int l = 1, r = 1e9, m, result = 1e9;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m) >= M) {
			if (m < result) result = m;
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

int main() {
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i) std::cin >> T[i];
	std::cout << binary_search();
}