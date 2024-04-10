#include <iostream>

typedef long long int ll;
const ll MOD = 998'244'353;

int main() {
	ll R, C, A, P, result = 1;
	std::cin >> R >> C;
	for (int i = 0; i < R * C; ++i) std::cin >> A;
	for (int i = 0; i < R; ++i) std::cin >> P;

	for (int i = R + 1; i <= R * C; ++i) {
		result *= i;
		result %= MOD;
	}
	std::cout << result;
}