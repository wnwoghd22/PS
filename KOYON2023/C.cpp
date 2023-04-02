#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int LEN = 1e6;
int N, k, h[LEN];

int f(int x) {
	int result = 0;
	if (std::abs(h[1] - h[0]) > x) ++result;
	if (std::abs(h[N - 1] - h[N - 2]) > x) ++result;
	for (int i = 1; i < N - 1; ++i)
		if (std::abs(h[i + 1] - h[i]) > x || std::abs(h[i - 1] - h[i]) > x)
			++result;
	return result;
}

int binary_search(int k) {
	int l = 0, r = 1e9, m, result = 1e9;
	while (l <= r) {
		m = l + r >> 1;
		if (f(m) <= k) {
			result = std::min(result, m);
			r = m - 1;
		}
		else l = m + 1;
	}
	return result;
}

int main() {
	freopen("input.txt", "r", stdin);
	std::cin >> N >> k;
	for (int i = 0; i < N; ++i) std::cin >> h[i];
	std::cout << binary_search(k);
}