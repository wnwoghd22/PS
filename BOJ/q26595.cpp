#include <iostream>

typedef long long int ll;

int main() {
	ll N, A, B, Pa, Pb, c, p, max = 0, maxA = 0, maxB = 0;
	std::cin >> N >> A >> Pa >> B >> Pb;
	for (ll i = 0, j; i <= N / Pa; ++i) {
		j = (N - i * Pa) / Pb;
		c = i * A + j * B;
		if (c > max) max = c, maxA = i, maxB = j;
	}
	std::cout << maxA << ' ' << maxB;
}