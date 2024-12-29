#include <iostream>

typedef long long ll;
const ll MAX = 1e9 + 7;
int Z, N, k;

int main() {
	std::cin.tie(0)->sync_with_stdio(0);
	std::cin >> Z;
	while (Z--) {
		ll S = 0, P = 1;
		std::cin >> N;
		while (N--) {
			std::cin >> k;
			S += k;
			P *= k;
			if (P > MAX) P = MAX;
		}
		if (S == P) std::cout << "=\n";
		if (S > P) std::cout << "SUMA\n";
		if (S < P) std::cout << "ILOCZYN\n";
	}
}