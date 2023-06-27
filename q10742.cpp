#include <iostream>

typedef long long ll;
const int LEN = 3e5 + 1;
const double ERR = 1e-4;
const double INF = 1e17;

int N, K, R;
int A[LEN];
ll S[LEN];

bool f(double m) {
	double min = 0;
	for (int i = K; i <= N; ++i) {
		min = std::min(min, S[i - K] - (i - K) * m);
		if (min - ERR < S[i] - i * m)
			return true;
	}
	return false;
}

double binary_search() {
	double l = 1, r = R, m;
	while (l < r) {
		m = (l + r) / 2;
		if (f(m)) l = m;
		else r = m - ERR;
	}
	return l;
}

int main() {
	std::cout << std::fixed;
	std::cout.precision(5);
	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i) {
		std::cin >> A[i];
		S[i] = S[i - 1] + A[i];
		R = std::max(R, A[i]);
	}
	std::cout << binary_search();
}