#include <iostream>

int main() {
	int r1 = 0, r2, mod;
	int n, sz[6], t, p;
	std::cin >> n;
	for (int i = 0; i < 6; ++i) std::cin >> sz[i];
	std::cin >> t >> p;
	for (int i = 0; i < 6; ++i) r1 += (sz[i] + t - 1) / t;
	r2 = n / p; mod = n % p;
	std::cout << r1 << '\n' << r2 << ' ' << mod;
}