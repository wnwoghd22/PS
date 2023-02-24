#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>

typedef long long int ll;
const ll INF = 1e18;

int N;
ll V[61];
ll d[61];
ll g[61] = { 1, };
int c[61];

int solve() {
	memset(c, 0, sizeof c);
	std::cin >> N;
	std::cin >> V[0];
	for (int i = 1; i < N; ++i) {
		std::cin >> V[i];
		d[i - 1] = V[i] / V[i - 1] - 1;
	}
	std::sort(d, d + N - 1);
	for (int i = 0; i < N - 1; ++i) std::cout << d[i] << ' ';
	std::cout << '\n';
	// classify
	int pivot = 0;
	for (int i = 0; i < N - 1; ++i) {
		if (g[pivot] != d[i]) g[++pivot] = d[i];
		++c[pivot];
	}
	for (int i = 0; i <= pivot; ++i) std::cout << g[i] << ' ';
	std::cout << '\n';
	for (int i = 0; i <= pivot; ++i) std::cout << c[i] << ' ';
	std::cout << '\n';

	// flatten
	int max;
	for (max = 1; max <= N; ++max) {
		ll remain = 0;
		for (int i = pivot; i > 0; --i) {
			remain += c[i];
			ll spl = max * (g[i] - g[i - 1]);
			remain = std::max(0ll, remain - spl);
		}
		std::cout << "remain: " << remain + c[0] << '\n';
		if (remain + c[0] <= max) break;
	}

	// identify
	return log2(max) + 1;
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}