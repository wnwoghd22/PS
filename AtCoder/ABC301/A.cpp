#include <iostream>

int main() {
	int N, t = 0, a = 0;
	char winner;
	std::string S;
	std::cin >> N >> S;
	for (const char& c : S) {
		if (c == 'T') {
			++t;
			if (t >= (N + 1) >> 1) {
				winner = 'T';
				break;
			}
		}
		else {
			++a;
			if (a >= (N + 1) >> 1) {
				winner = 'A';
				break;
			}

		}
	}
	std::cout << winner;
}