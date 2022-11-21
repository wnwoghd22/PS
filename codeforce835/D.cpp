#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int N, a1, a2;
		bool ascending = false;
		bool result = false;
		std::cin >> N;
		std::cin >> a1;
		for (int i = 1; i < N; ++i) {
			std::cin >> a2;
			if (a2 - a1 > 0) ascending = true;
			if (a2 - a1 < 0 && ascending) result = true;
			a1 = a2;
		}
		if (result) std::cout << "NO\n";
		else std::cout << "YES\n";
	}
}