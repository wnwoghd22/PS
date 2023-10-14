#include <iostream>

int N, A0, A1;

int main() {
	std::cin >> N >> A0;
	for (int i = 1; i < N; ++i) {
		std::cin >> A1;
		if (A0 != A1) {
			std::cout << "No";
			return 0;
		}
		A0 = A1;
	}
	std::cout << "Yes";
}