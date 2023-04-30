#include <iostream>

int main() {
	int N, P, R = 0;
	std::cin >> N;
	while (N--) {
		std::cin >> P;
		R ^= P;
	}
	std::cout << (R ? "koosaga" : "cubelover");
}