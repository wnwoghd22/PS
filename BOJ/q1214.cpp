#include <iostream>

typedef long long int ll;
ll D, P, Q, n, m, cost, result = 1e17;

int main() {
	std::cin >> D >> P >> Q;
	if (Q > P) std::swap(P, Q);
	for (n = std::min(D / P + 1, Q); n >= 0; --n) {
		m = ceil((double)std::max(D - n * P, 0ll) / Q);
		cost = n * P + m * Q;
		if (cost == result) break;
		result = std::min(result, cost);
	}
	std::cout << result;
}