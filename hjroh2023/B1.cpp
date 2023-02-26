#include <iostream>
#include <cmath>

int N, i, c[63];
long long a;

int main() {
	std::cin >> N;
	while (N--) {
		std::cin >> a;
		if (a) ++c[(int)log2(a)];
	}
	for (i = 0; i < 62; ++i) c[i + 1] += c[i] >> 1;
	for (i = 62; i >= 0; --i) if (c[i]) break;
	std::cout << (1ll << i);
}