#include <iostream>
#include <algorithm>

const int LEN = 3e5 + 2;
int N, A[LEN];
int lmax[LEN], rmax[LEN];

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> N;
	for (int i = 1; i <= N; ++i) std::cin >> A[i];
	for (int i = 1; i <= N; ++i) lmax[i] = std::max(lmax[i - 1], A[i] + N - i);
	for (int i = N; i >= 1; --i) rmax[i] = std::max(rmax[i + 1], A[i] + i - 1);
	int power = 2e9 + 1;
	for (int i = 1; i <= N; ++i)
		power = std::min(power, std::max({ A[i], lmax[i - 1], rmax[i + 1] }));
	std::cout << power;
}