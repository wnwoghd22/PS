#include <iostream>

typedef long long int ll;
const ll MOD = 998'244'353;

int main() {
	ll R, C, A, P, result = 1;
	std::cin >> R >> C;
	for (int i = R + 1; i <= R * C; ++i) result = result * i % MOD;
	std::cout << result;
}