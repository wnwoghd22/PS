#include <iostream>

int main() {
	int N, T1, T2, T3;

	while (1) {
		std::cin >> N >> T1 >> T2 >> T3;
		if (!N && !T1 && !T2 && !T3) break;
		std::cout << N * 4 + (T2 + N - T1) % N + (T2 + N - T3) % N - 1 << '\n';
	}
}