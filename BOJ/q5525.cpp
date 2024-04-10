#include <iostream>

int main() {
	int N, M; std::string S;
	std::cin >> N >> M;
	std::cin >> S;
	int count = 0;

	for (int j = 0, i = 0; i < M; ++i) {
		++j;
		if (j % 2 && S[i] == 'O') {
			j = 0;
			continue;
		}
		if (!(j % 2) && S[i] == 'I') {
			j = 1;
			continue;
		}

		if (j == 2 * N + 1) {
			++count;
			j -= 2;
		}
	}
	std::cout << count;
}