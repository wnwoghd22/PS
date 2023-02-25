#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <algorithm>
#include <cstring>

typedef long long int ll;
const ll INF = 1e18;

int N;
ll V[61];
ll d[61];
ll g[61] = { 2, };
int c[61];

int log(int base, int n) {
	int result = 0, k = 1;
	while ((k *= base) <= n) ++result;
	return result;
}

int solve() {
	memset(c, 0, sizeof c);
	std::cin >> N;
	std::cin >> V[0];
	for (int i = 1; i < N; ++i) {
		std::cin >> V[i];
		d[i - 1] = V[i] / V[i - 1];
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

	int max = 0;
	for (int i = 0; i <= pivot; ++i) max = std::max(max, log(g[i], c[i]) + 1);
	
	return max;
}

int main() {
	freopen("input.txt", "r", stdin);
	int t, T;
	std::cin >> T;
	for (t = 1; t <= T; ++t) std::cout << '#' << t << ' ' << solve() << '\n';
}