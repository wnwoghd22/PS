#include <iostream>

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		int N, F = 0, S = 0, C = 0, p, turn;
		std::cin >> N;
		for (int i = 1; i <= N; ++i) {
			std::cin >> p;
			if (p != i && p != N - i + 1) C++;
			else if (p != i) F++;
			else if (p != N - i + 1) S++;
		}
		p = 0, turn = 1;
		while (true) {
			if (turn) {
				if (!F && !C) {
					std::cout << "First\n";
					break;
				}
				if (F) F--;
				else {
					if (C == 1 && S == 0) {
						std::cout << "Tie\n";
						break;
					}
					if (C) C--;
				}
			}
			else {
				if (!S && !C) {
					std::cout << "Second\n";
					break;
				}
				if (S) S--;
				else {
					if (C == 1 && F == 0) {
						std::cout << "Tie\n";
						break;
					}
					if (C) C--;
				}
			}
			turn = !turn;
		}
	}
}