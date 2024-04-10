#include <iostream>

typedef long long ll;

ll N;

int main() {
	std::cin >> N;
	if (N == 1) {
		std::cout << 2;
		return 0;
	}

	if (N == 2) {
		std::cout << 2 << ' ' << 4;
		return 0;
	}

	ll sum = (N - 2) * (N - 1) / 2;
	ll fin = N - 1;
	if ((sum + fin) % 3) fin += 3 - (sum + fin) % 3;

	// std::cout << "sum: " << sum << '\n';
	// std::cout << "fin: " << fin << '\n';

	std::cout << 3 << ' ';
	for (int i = 1; i < N - 1; ++i) std::cout << i * 2 << ' ';
	std::cout << fin * 2;

	// std::cout << '\n' << 3 + sum * 2 + fin * 2;
}