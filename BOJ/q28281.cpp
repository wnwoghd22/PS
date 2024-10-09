#include <iostream>

int main() {
	int N, X, A0, A1;
	std::cin >> N >> X >> A0 >> A1;
	int min = (A0 + A1) * X;
	for (int i = 2; i < N; ++i) {
		A0 = A1;
		std::cin >> A1;
		min = std::min(min, (A0 + A1) * X);
	}
	std::cout << min;
}