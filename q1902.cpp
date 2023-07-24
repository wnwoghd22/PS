#include <iostream>

typedef long double ld;
const int LEN = 5000;
const ld ERR = 1e-7;

int N, X;

int x[LEN], y[LEN];
ld d[LEN];

ld get(int i, ld h) { return (h - y[i]) / d[i] + x[i]; }

bool f(ld h) {
	ld l = 0, r = X;
	for (int i = 0; i < N - 1; ++i) {
		if (y[i] == y[i + 1]) {
			if (y[i] > h)
				return false;
		}
		else {
			if (d[i] < 0) l = std::max(l, get(i, h));
			else r = std::min(r, get(i, h));
		}
	}
	return l < r;
}

ld binary_search() {
	ld l = 0, r = 1e6, m, result = 1e6;

	while (l < r) {
		m = (l + r) / 2;
		if (f(m)) {
			result = std::min(result, m);
			r = m - 1e-3;
		}
		else l = m + 1e-3;
	}
	return result;
}

int main() {
	std::cin >> N;
	for (int i = 0; i < N; ++i) std::cin >> x[i] >> y[i];
	
	for (int i = 0; i < N - 1; ++i) d[i] = (ld)(y[i + 1] - y[i]) / (x[i + 1] - x[i]);
	X = x[N - 1];

	ld ans = binary_search();
	ans = (((int)(ans * 1000) + 5) / 10) / 1e2;
	std::cout << ans;
}