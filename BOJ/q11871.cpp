#include <iostream>

int main() {
	int N, P, ret = 0;
	std::cin >> N;
	for (int i = 0; i < N; ++i) {
		std::cin >> P;
		if (P & 1) ret ^= (P + 1) / 2;
		else ret ^= (P - 1) / 2;
	}
	std::cout << (ret ? "koosaga" : "cubelover");
}